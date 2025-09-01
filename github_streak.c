#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct Memory {
    char *response;
    size_t size;
};

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct Memory *mem = (struct Memory *)userp;

    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if(ptr == NULL) return 0; // out of memory

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = '\0';

    return realsize;
}

int main() {
    CURL *curl;
    CURLcode res;
    struct Memory chunk = {0};

    const char *username = "YOUR_GITHUB_USERNAME"; // change this
    char url[256];
    snprintf(url, sizeof(url), "https://github.com/users/%s/contributions", username);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl failed: %s\n", curl_easy_strerror(res));
        } else {
            // naive parse: count "data-count" > 0 for streaks
            char *p = chunk.response;
            int currentStreak = 0, maxStreak = 0;
            while((p = strstr(p, "data-count=\""))) {
                p += 12; // move past 'data-count="'
                int count = atoi(p);
                if(count > 0) {
                    currentStreak++;
                    if(currentStreak > maxStreak) maxStreak = currentStreak;
                } else {
                    currentStreak = 0;
                }
            }
            printf("Max streak: %d days\n", maxStreak);
        }
        curl_easy_cleanup(curl);
        free(chunk.response);
    }
    curl_global_cleanup();
    return 0;
}
