#include <stdio.h>

int main() {
    float weight, height, bmi;

    printf("Enter weight (kg): ");
    scanf("%f", &weight);

    printf("Enter height (m): ");
    scanf("%f", &height);

    bmi = weight / (height * height);

    printf("Your BMI is: %.2f\n", bmi);

    if (bmi < 18.5)
        printf("Category: Underweight\n");
    else if (bmi < 25)
        printf("Category: Normal weight\n");
    else if (bmi < 30)
        printf("Category: Overweight\n");
    else
        printf("Category: Obese\n");

    return 0;
}
