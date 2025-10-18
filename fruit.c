/* fruit.c
Student: Yamilet Rocha
Extra Credit 10/16
Done by: 10/18/2025
- Program that takes user input to select from a number of choices using
- scanf (single character) and an array of strings.
- No if-tree or switch-case allowed.
- Handles both lowercase and uppercase (a-z, A-Z).
*/

#include <stdio.h>
#include <ctype.h>  // for tolower()

int main(void)
{
    // Array of strings for fruits (a-z)
    char* fruits[26] = {
        "Apple", "Banana", "Cherry", "Date", "Elderberry", "Fig",
        "Grape", "Honeydew", "Indian Fig", "Jackfruit", "Kiwi", "Lemon",
        "Mango", "Nectarine", "Orange", "Papaya", "Quince", "Raspberry",
        "Strawberry", "Tomato", "Ugli Fruit", "Vanilla Bean", "Watermelon",
        "Xigua", "Yellow Passionfruit", "Zucchini"
    };

    char choice;

    printf("\nChoose a fruit (a-z):\n");
    printf("a = Apple\n");
    printf("b = Banana\n");
    printf("c = Cherry\n");
    printf("d = Date\n");
    printf("... \n");
    printf("z = Zucchini\n");

    printf("\nEnter your choice: ");
    scanf(" %c", &choice);

    choice = tolower(choice); // convert uppercase to lowercase
    int index = choice - 'a'; // calculate index in array

    if (index >= 0 && index < 26)
        printf("You chose: %s\n", fruits[index]);
    else
        printf("Invalid input. Please enter a letter between a and z.\n");

    return 0;
}
