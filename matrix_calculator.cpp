#include <stdio.h>
#define MAX_SIZE 10
void input_matrix(double matrix[MAX_SIZE][MAX_SIZE], int size) {
    printf("Enter the elements of a %dx%d matrix, row by row:\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }
}
void display_matrix(double matrix[MAX_SIZE][MAX_SIZE], int size) {
    printf("Matrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}
void matrix_addition(double mat1[MAX_SIZE][MAX_SIZE], double mat2[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}
void matrix_subtraction(double mat1[MAX_SIZE][MAX_SIZE], double mat2[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
}
void matrix_multiplication(double mat1[MAX_SIZE][MAX_SIZE], double mat2[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = 0;
            for (int k = 0; k < size; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}
double matrix_determinant(double matrix[MAX_SIZE][MAX_SIZE], int size) {
    if (size == 1) return matrix[0][0];
    if (size == 2) return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);

    double det = 0;
    for (int p = 0; p < size; p++) {
        double submatrix[MAX_SIZE][MAX_SIZE];
        for (int i = 1; i < size; i++) {
            int sub_col = 0;
            for (int j = 0; j < size; j++) {
                if (j == p) continue;
                submatrix[i - 1][sub_col++] = matrix[i][j];
            }
        }
        det += (p % 2 == 0 ? 1 : -1) * matrix[0][p] * matrix_determinant(submatrix, size - 1);
    }
    return det;
}
void matrix_transpose(double matrix[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matrix[j][i];
        }
    }
}
void matrix_inverse(double matrix[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE], int size) {
    double det = matrix_determinant(matrix, size);
    if (det == 0) {
        printf("Inverse does not exist (determinant is zero).\n");
        return;
    }
    if (size == 1) {
        result[0][0] = 1 / matrix[0][0];
        return;
    }

    double adjoint[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double submatrix[MAX_SIZE][MAX_SIZE];
            int subi = 0;
            for (int k = 0; k < size; k++) {
                if (k == i) continue;
                int subj = 0;
                for (int l = 0; l < size; l++) {
                    if (l == j) continue;
                    submatrix[subi][subj++] = matrix[k][l];
                }
                subi++;
            }
            adjoint[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * matrix_determinant(submatrix, size - 1);
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = adjoint[i][j] / det;
        }
    }
}

int main() {
    int choice, size;

    printf("WELCOME TO THE MATRIX OPERATIONS PROGRAM\n");
    printf("Press a key to select the appropriate operation:\n");
    printf("1. Determinant\n");
    printf("2. Addition of matrices\n");
    printf("3. Subtraction of matrices\n");
    printf("4. Product of matrices\n");
    printf("5. Transpose of a matrix\n");
    printf("6. Inverse of matrix\n");
    printf("7. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 6) {
        printf("Enter the order of matrix (max %d): ", MAX_SIZE);
        scanf("%d", &size);

        if (size > MAX_SIZE) {
            printf("Size exceeds maximum allowed value (%d).\n", MAX_SIZE);
            return 1;
        }

        double mat1[MAX_SIZE][MAX_SIZE];
        input_matrix(mat1, size);

        if (choice == 1) {
            printf("Determinant: %lf\n", matrix_determinant(mat1, size));
        } else if (choice == 5) {
            double result[MAX_SIZE][MAX_SIZE];
            matrix_transpose(mat1, result, size);
            display_matrix(result, size);
        } else if (choice == 6) {
            double result[MAX_SIZE][MAX_SIZE];
            matrix_inverse(mat1, result, size);
            display_matrix(result, size);
        } else {
            double mat2[MAX_SIZE][MAX_SIZE];
            printf("Enter the second matrix:\n");
            input_matrix(mat2, size);
            double result[MAX_SIZE][MAX_SIZE];

            if (choice == 2) {
                matrix_addition(mat1, mat2, result, size);
            } else if (choice == 3) {
                matrix_subtraction(mat1, mat2, result, size);
            } else if (choice == 4) {
                matrix_multiplication(mat1, mat2, result, size);
            }
            display_matrix(result, size);
        }
    } else if (choice == 7) {
        printf("Exiting the program.\n");
    } else {
        printf("Invalid choice. Please try again.\n");
    }

    return 0;
}

