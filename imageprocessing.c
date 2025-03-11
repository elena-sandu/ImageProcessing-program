#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"

int ***flip_horizontal(int ***image, int N, int M) {
    int i = 0, j = 0, k = 0, aux = 0;
    for (j = 0; j < M/2; j++) {
        for (i = 0; i < N; i++) {
            for (k = 0; k < 3 ; k++) {
                aux = image[i][j][k];
                image[i][j][k] = image[i][M-j-1][k];
                image[i][M-j-1][k] = aux;
            }
        }
    }
    return image;
}

int ***rotate_left(int ***image, int N, int M) {
    int i = 0, j = 0, k = 0;
    int ***a = (int ***)malloc(M * sizeof(int **));
    for (i = 0; i < M; i++) {
        a[i] = (int **)malloc(N * sizeof(int *));
        for (j = 0; j < N; j++) {
            a[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < 3; k++) {
                a[i][j][k] = image[j][M-i-1][k];
            }
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
             free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return a;
}

int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    int i = 0, j = 0, k = 0;
    int ***a = (int ***)malloc(h * sizeof(int **));
    for (i = 0; i < h; i++) {
        a[i] = (int **)malloc(w * sizeof(int *));
        for (j = 0; j < w; j++) {
            a[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    int t = 0, m = 0;
    for (i = y; i < y + h && i < N; i++) {
        m = 0;
        for (j = x; j < x + w && j < M; j++) {
            for (k = 0; k < 3; k++) {
                a[t][m][k] = image[i][j][k];
            }
            m++;
        }
        t++;
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return a;
}

int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    int i = 0, j = 0, k = 0;
    int ***a = (int ***)malloc((N + 2*rows) * sizeof(int **));
    for (i = 0; i < N + 2 * rows; i++) {
        a[i] = (int **)malloc((M + 2 * cols) * sizeof(int *));
        for (j = 0; j < M + 2 * cols; j++) {
            a[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    int aux = 0;
    for (k = 0 ; k < 3 ; k++) {
            if (k == 0) {
               aux = new_R;
            } else if (k == 1) {
               aux = new_G;
            } else {
               aux = new_B;
            }
        // deasupra
        for (i = rows - 1; i >= 0; i--) {
            for (j = 0 ; j < M + 2 * cols; j++) {
                a[i][j][k] = aux;
            }
        }
        // dedesubt
        for (i = N + rows; i < N + 2 * rows; i++) {
            for (j = 0; j < M + 2 * cols; j++) {
                a[i][j][k] = aux;
            }
        }
        // stanga
        for (i = rows ; i < N + rows; i++) {
            for (j = 0 ; j < cols; j++) {
                a[i][j][k] = aux;
            }
        }
        // dreapta
        for (i = rows ; i < N + rows; i++) {
            for (j = M + cols; j < M + 2 * cols; j++) {
                a[i][j][k] = aux;
            }
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            for (k = 0; k < 3; k++) {
                a[i + rows][j + cols][k] = image[i][j][k];
            }
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return a;
}

int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y) {
    int i = 0, j = 0, k = 0, t = 0, m = 0;
    for (i = y; i < N_dst && t < N_src; i++) {
        m = 0;
        for (j = x; j < M_dst && m < M_src; j++) {
            for (k = 0; k < 3; k++) {
                image_dst[i][j][k] = image_src[t][m][k];
            }
            m++;
        }
        t++;
    }
    return image_dst;
}

int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    int i = 0, j = 0, k = 0, t = 0;
    int ***a = (int ***)malloc(N * sizeof(int **));
    for (i = 0; i < N; i++) {
        a[i] = (int **)malloc(M * sizeof(int *));
        for (j = 0; j < M; j++) {
            a[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    int aux = filter_size/2;
    int x = 0, y = 0;
    float s0 = 0, s1 = 0, s2 = 0;
    const float n1 = 0;
    const float n2 = 255;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            s0 = 0;
            s1 = 0;
            s2 = 0;
            for (k = 0; k < filter_size; k++) {
                for (t = 0; t < filter_size; t++) {
                    x = i - aux + k;
                    y = j - aux + t;
                    if ((x < 0 || x >= N) || (y < 0 || y >= M)) {
                        s0 = s0 + 0;
                        s1 = s1 + 0;
                        s2 = s2 + 0;
                    } else {
                        s0 = s0 + (float)image[x][y][0] * filter[k][t];
                        s1 = s1 + (float)image[x][y][1] * filter[k][t];
                        s2 = s2 + (float)image[x][y][2] * filter[k][t];
                    }
                }
            }
            if (s0 < n1) {
                a[i][j][0] = (int)n1;
            } else if (s0 > n2) {
                a[i][j][0] = (int)n2;
            } else {
                a[i][j][0] = (int)s0;
            }
            if (s1 < n1) {
                a[i][j][1] = (int)n1;
            } else if (s1 > n2) {
                a[i][j][1] = (int)n2;
            } else {
                a[i][j][1] = (int)s1;
            }
            if (s2 < n1) {
                a[i][j][2] = (int)n1;
            } else if (s2 > n2) {
                a[i][j][2] = (int)n2;
            } else {
                a[i][j][2] = (int)s2;
            }
        }}
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return a;
}
