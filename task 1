/*
 * CodeAlpha C Programming Internship - Task 1
 * Basic Calculator Program
 *
 * Performs Addition, Subtraction, Multiplication, and Division
 * using switch-case for operation selection.
 */

#include <stdio.h>

int main() {
    double num1, num2, result;
    char operation;
    int choice;

    printf("===================================\n");
    printf("      SIMPLE CALCULATOR (C)\n");
    printf("===================================\n");

    do {
        printf("\nSelect an operation:\n");
        printf("1. Addition       (+)\n");
        printf("2. Subtraction    (-)\n");
        printf("3. Multiplication (*)\n");
        printf("4. Division       (/)\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            // clear bad input from buffer
            while (getchar() != '\n');
            continue;
        }

        if (choice == 5) {
            printf("Exiting calculator. Goodbye!\n");
            break;
        }

        if (choice < 1 || choice > 5) {
            printf("Invalid choice! Please select between 1 and 5.\n");
            continue;
        }

        printf("Enter first number: ");
        scanf("%lf", &num1);
        printf("Enter second number: ");
        scanf("%lf", &num2);

        switch (choice) {
            case 1:
                operation = '+';
                result = num1 + num2;
                printf("Result: %.2lf %c %.2lf = %.2lf\n", num1, operation, num2, result);
                break;

            case 2:
                operation = '-';
                result = num1 - num2;
                printf("Result: %.2lf %c %.2lf = %.2lf\n", num1, operation, num2, result);
                break;

            case 3:
                operation = '*';
                result = num1 * num2;
                printf("Result: %.2lf %c %.2lf = %.2lf\n", num1, operation, num2, result);
                break;

            case 4:
                operation = '/';
                if (num2 == 0) {
                    printf("Error: Division by zero is not allowed!\n");
                } else {
                    result = num1 / num2;
                    printf("Result: %.2lf %c %.2lf = %.2lf\n", num1, operation, num2, result);
                }
                break;

            default:
                printf("Invalid operation.\n");
        }

    } while (1);

    return 0;
}
