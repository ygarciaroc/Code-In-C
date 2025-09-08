#include <stdio.h>
#include <string.h>

int main() {
    char choice[20];

    printf("What meal are you looking for? (breakfast/lunch/dinner): ");
    scanf("%s", choice);

    if (strcmp(choice, "breakfast") == 0) {
        printf("\nSuggested Recipes:\n");
        printf("1. Oatmeal with fruits and honey\n");
        printf("2. Scrambled eggs with spinach\n");
        printf("3. Yogurt with granola\n");
    } 
    else if (strcmp(choice, "lunch") == 0) {
        printf("\nSuggested Recipes:\n");
        printf("1. Grilled chicken salad\n");
        printf("2. Rice with beans and vegetables\n");
        printf("3. Tuna sandwich with avocado\n");
    } 
    else if (strcmp(choice, "dinner") == 0) {
        printf("\nSuggested Recipes:\n");
        printf("1. Baked salmon with quinoa\n");
        printf("2. Vegetable stir-fry with tofu\n");
        printf("3. Chicken soup with vegetables\n");
    } 
    else {
        printf("\nSorry, I don't have recipes for that option.\n");
    }

    return 0;
}
