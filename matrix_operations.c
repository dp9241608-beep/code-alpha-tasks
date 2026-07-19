/*
 * CodeAlpha C Programming Internship - Task 2
 * Matrix Operations Program
 *
 * Implements Matrix Addition, Matrix Multiplication, and Transpose
 * using functions and 2D arrays for modularity.
 */

#include <stdio.h>

#define MAX 10

// Function prototypes
void inputMatrix(int mat[MAX][MAX], int rows, int cols, const char *name);
void printMatrix(int mat[MAX][MAX], int rows, int cols, const char *name);
void addMatrices(int a[MAX][MAX], int b[MAX][MAX], int result[MAX][MAX], int rows, int cols);
void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX], int result[MAX][MAX],
                       int r1, int c1, int r2, int c2);
void transposeMatrix(int mat[MAX][MAX], int result[MAX][MAX], int rows, int cols);
int getMenuChoice(void);

int main() {
    int choice;

    printf("=========================================\n");
    printf("      MATRIX OPERATIONS PROGRAM (C)\n");
    printf("=========================================\n");

    do {
        printf("\nSelect an operation:\n");
        printf("1. Matrix Addition\n");
        printf("2. Matrix Multiplication\n");
        printf("3. Matrix Transpose\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");

        choice = getMenuChoice();

        if (choice == 4) {
            printf("Exiting program. Goodbye!\n");
            break;
        }

        switch (choice) {
            case 1: {
                int rows, cols;
                int a[MAX][MAX], b[MAX][MAX], result[MAX][MAX];

                printf("\n--- Matrix Addition ---\n");
                printf("Enter rows and columns (both matrices must match): ");
                scanf("%d %d", &rows, &cols);

                if (rows <= 0 || cols <= 0 || rows > MAX || cols > MAX) {
                    printf("Invalid dimensions (max %d x %d).\n", MAX, MAX);
                    break;
                }

                inputMatrix(a, rows, cols, "A");
                inputMatrix(b, rows, cols, "B");

                addMatrices(a, b, result, rows, cols);

                printMatrix(a, rows, cols, "Matrix A");
                printMatrix(b, rows, cols, "Matrix B");
                printMatrix(result, rows, cols, "A + B");
                break;
            }

            case 2: {
                int r1, c1, r2, c2;
                int a[MAX][MAX], b[MAX][MAX], result[MAX][MAX];

                printf("\n--- Matrix Multiplication ---\n");
                printf("Enter rows and columns of Matrix A: ");
                scanf("%d %d", &r1, &c1);
                printf("Enter rows and columns of Matrix B: ");
                scanf("%d %d", &r2, &c2);

                if (r1 <= 0 || c1 <= 0 || r2 <= 0 || c2 <= 0 || r1 > MAX || c1 > MAX || r2 > MAX || c2 > MAX) {
                    printf("Invalid dimensions (max %d x %d).\n", MAX, MAX);
                    break;
                }

                if (c1 != r2) {
                    printf("Error: Multiplication not possible. Columns of A must equal rows of B.\n");
                    break;
                }

                inputMatrix(a, r1, c1, "A");
                inputMatrix(b, r2, c2, "B");

                multiplyMatrices(a, b, result, r1, c1, r2, c2);

                printMatrix(a, r1, c1, "Matrix A");
                printMatrix(b, r2, c2, "Matrix B");
                printMatrix(result, r1, c2, "A x B");
                break;
            }

            case 3: {
                int rows, cols;
                int a[MAX][MAX], result[MAX][MAX];

                printf("\n--- Matrix Transpose ---\n");
                printf("Enter rows and columns: ");
                scanf("%d %d", &rows, &cols);

                if (rows <= 0 || cols <= 0 || rows > MAX || cols > MAX) {
                    printf("Invalid dimensions (max %d x %d).\n", MAX, MAX);
                    break;
                }

                inputMatrix(a, rows, cols, "A");
                transposeMatrix(a, result, rows, cols);

                printMatrix(a, rows, cols, "Matrix A");
                printMatrix(result, cols, rows, "Transpose of A");
                break;
            }

            default:
                printf("Invalid choice! Please select between 1 and 4.\n");
        }

    } while (1);

    return 0;
}

/* Reads matrix values from the user */
void inputMatrix(int mat[MAX][MAX], int rows, int cols, const char *name) {
    printf("Enter elements of Matrix %s (%d x %d):\n", name, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &mat[i][j]);
        }
    }
}

/* Prints a matrix with a label */
void printMatrix(int mat[MAX][MAX], int rows, int cols, const char *name) {
    printf("\n%s:\n", name);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%6d ", mat[i][j]);
        }
        printf("\n");
    }
}

/* Adds two matrices of the same dimensions */
void addMatrices(int a[MAX][MAX], int b[MAX][MAX], int result[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

/* Multiplies matrix a (r1 x c1) by matrix b (r2 x c2), requires c1 == r2 */
void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX], int result[MAX][MAX],
                       int r1, int c1, int r2, int c2) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

/* Computes the transpose of a matrix */
void transposeMatrix(int mat[MAX][MAX], int result[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = mat[i][j];
        }
    }
}

/* Safely reads an integer menu choice, clearing invalid input */
int getMenuChoice(void) {
    int choice;
    while (scanf("%d", &choice) != 1) {
        printf("Invalid input. Please enter a number: ");
        while (getchar() != '\n'); // clear buffer
    }
    return choice;
}
