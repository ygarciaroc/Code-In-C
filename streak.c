#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#ifdef _WIN32
  #include <direct.h>
  #define MKDIR(path,mode) _mkdir(path)
#else
  #define MKDIR(path,mode) mkdir(path, mode)
#endif

#define STATE_DIR ".streak"
#define STATE_FILE ".streak/state.txt"
#define NOTES_DIR "notes"

typedef struct {
    int year, month, day; // YYYY, 1-12, 1-31
} Date;

static void ensure_dir(const char *path) {
    struct stat st;
    if (stat(path, &st) != 0) {
        #ifdef _WIN32
        MKDIR(path, 0);
        #else
        MKDIR(path, 0755);
        #endif
    }
}

static Date today_local() {
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    Date d = { lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday };
    return d;
}

static int parse_date(const char *s, Date *out) {
    // expects "YYYY-MM-DD"
    return sscanf(s, "%d-%d-%d", &out->year, &out->month, &out->day) == 3;
}

static void format_date(Date d, char *buf, size_t n) {
    snprintf(buf, n, "%04d-%02d-%02d", d.year, d.month, d.day);
}

static time_t to_time_t(Date d) {
    struct tm tmv;
    memset(&tmv, 0, sizeof(tmv));
    tmv.tm_year = d.year - 1900;
    tmv.tm_mon  = d.month - 1;
    tmv.tm_mday = d.day;
    tmv.tm_hour = 12; // noon to avoid DST edge cases
    tmv.tm_isdst = -1;
    return mktime(&tmv);
}

static int days_between(Date a, Date b) {
    time_t ta = to_time_t(a);
    time_t tb = to_time_t(b);
    double diff = difftime(tb, ta) / (60*60*24);
    if (diff > 0) return (int)(diff + 0.5);
    if (diff < 0) return (int)(diff - 0.5);
    return 0;
}

int main(void) {
    ensure_dir(STATE_DIR);
    ensure_dir(NOTES_DIR);

    Date today = today_local();
    char today_str[16];
    format_date(today, today_str, sizeof(today_str));

    // Load state
    FILE *sf = fopen(STATE_FILE, "r");
    int streak = 0;
    Date last = {0,0,0};
    if (sf) {
        char datebuf[32];
        if (fscanf(sf, "%31s %d", datebuf, &streak) == 2) {
            parse_date(datebuf, &last);
        }
        fclose(sf);
    }

    int delta = 0;
    if (last.year != 0) {
        delta = days_between(last, today);
    }

    // Update streak logic
    const char *status_msg = NULL;
    if (last.year == 0) {
        streak = 1;
        status_msg = "New streak started!";
    } else if (delta == 0) {
        status_msg = "Already logged today. Updating today’s note.";
    } else if (delta == 1) {
        streak += 1;
        status_msg = "Streak increased! Nice.";
    } else if (delta > 1) {
        streak = 1;
        status_msg = "Gap detected—streak reset to 1.";
    } else { // delta < 0 (time travel or manual backdate)
        status_msg = "Date appears earlier than last log; keeping current streak.";
    }

    // Prompt for a quick note
    printf("Daily note for %s (single line, press Enter to save):\n> ", today_str);
    char note[2048];
    if (!fgets(note, sizeof(note), stdin)) {
        note[0] = '\0';
    }

    // Trim newline
    size_t len = strlen(note);
    if (len > 0 && note[len-1] == '\n') note[len-1] = '\0';

    // Save note
    char note_path[256];
    snprintf(note_path, sizeof(note_path), NOTES_DIR "/%s.txt", today_str);
    FILE *nf = fopen(note_path, "w");
    if (!nf) {
        fprintf(stderr, "Error: could not write note to %s\n", note_path);
        return 1;
    }
    fprintf(nf, "%s\n", note);
    fclose(nf);

    // Persist state
    sf = fopen(STATE_FILE, "w");
    if (!sf) {
        fprintf(stderr, "Error: could not write state to %s\n", STATE_FILE);
        return 1;
    }
    fprintf(sf, "%s %d\n", today_str, streak);
    fclose(sf);

    // Output summary
    printf("\n%s\n", status_msg ? status_msg : "");
    printf("Current streak: %d day%s\n", streak, (streak==1?"":"s"));
    printf("Note saved to: %s\n", note_path);
    printf("Keep it up!\n");

    return 0;
}
