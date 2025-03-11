#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"
#define MAX 1000
#define MAX2 100

int main() {
    char in[3];
    int N[MAX], M[MAX];
    int k = 0, i = 0, j = 0, l = 0;
    int ****a = NULL;
    float ***filter = NULL;
    char path[MAX], path2[MAX];
    int size[MAX];
    scanf("%s", in);
    while (1) {
        if (strcmp(in, "e") == 0) {
            for (i = 0; i < k; i++) {
                for (j = 0; j < N[i]; j++) {
                    for (int c = 0; c < M[i]; c++) {
                        free(a[i][j][c]);
                    }
                    free(a[i][j]);
                }
                free(a[i]);
            }
            free(a);
            for (i = 0; i < l; i++) {
                for (j = 0; j < size[i]; j++) {
                    free(filter[i][j]);
                }
                free(filter[i]);
            }
            free(filter);
            break;
        } else if (strcmp(in, "l") == 0) {
                scanf("%d%d%s", &N[k], &M[k], path);
                a = (int ****)realloc(a, (k+1) * sizeof(int ***));
                a[k] = (int ***)malloc(N[k] * sizeof(int **));
                for (i = 0; i < N[k]; i++) {
                    a[k][i] = (int **)malloc(M[k] * sizeof(int *));
                    for (j = 0; j < M[k]; j++) {
                         a[k][i][j] = (int *)malloc(3 * sizeof(int));
                    }
                }
                read_from_bmp(a[k], N[k], M[k], path);
                k++;
            } else if (strcmp(in, "s") == 0) {
                int index = 0;
                scanf("%d%s", &index, path2);
                write_to_bmp(a[index], N[index], M[index], path2);
            } else if (strcmp(in, "ah") == 0) {
                int index = 0;
                scanf("%d", &index);
                a[index] = flip_horizontal(a[index], N[index], M[index]);
            } else if (strcmp(in, "ar") == 0) {
                int index = 0;
                scanf("%d", &index);
                a[index] = rotate_left(a[index], N[index], M[index]);
                int aux = N[index];
                N[index] = M[index];
                M[index] = aux;
            } else if (strcmp(in, "ac") == 0) {
                int index = 0, x = 0, y = 0, w = 0, h = 0;
                scanf("%d%d%d%d%d", &index, &x, &y, &w, &h);
                a[index] = crop(a[index], N[index], M[index], x, y, h, w);
                N[index] = h;
                M[index] = w;
            } else if (strcmp(in, "ae") == 0) {
                int index = 0, rows = 0, cols = 0, R = 0, G = 0, B = 0;
                scanf("%d%d%d%d%d%d", &index, &rows, &cols, &R, &G, &B);
                a[index] = extend(a[index], N[index], M[index], rows, cols, R, G, B);
                N[index] = N[index] + 2 * rows;
                M[index] = M[index] + 2 * cols;
            } else if (strcmp(in, "ap") == 0) {
                int index_dst = 0, index_src = 0, x = 0, y = 0;
                scanf("%d%d%d%d", &index_dst, &index_src, &x, &y);
                a[index_dst] = paste(a[index_dst], N[index_dst], M[index_dst],
                        a[index_src], N[index_src], M[index_src], x, y);
            } else if (strcmp(in, "cf") == 0) {
                scanf("%d", &size[l]);
                filter = (float ***)realloc(filter, (l + 1) * sizeof(float **));
                filter[l] = (float **)malloc(size[l] * sizeof(float *));
                for (i = 0; i < size[l]; i++) {
                    filter[l][i] = (float *)malloc(size[l] * sizeof(float));
                    for (j = 0; j < size[l]; j++) {
                        scanf("%f", &filter[l][i][j]);
                    }
                }
                l++;
            } else if (strcmp(in, "af") == 0) {
                int index_filter = 0, index_img = 0;
                scanf("%d%d", &index_img, &index_filter);
                a[index_img] = apply_filter(a[index_img], N[index_img],
                     M[index_img], filter[index_filter], size[index_filter]);
            } else if (strcmp(in, "df") == 0) {
                int index_filter = 0, c = 0;
                scanf("%d", &index_filter);
                for (i = 0; i < size[index_filter]; i++) {
                    free(filter[index_filter][i]);
                }
                free(filter[index_filter]);
                for (c = index_filter; c < l - 1; c++) {
                            filter[c] = filter[c+1];
                            size[c] = size[c+1];
                        }
                l--;
            } else if (strcmp(in, "di") == 0) {
                int index_img = 0;
                scanf("%d", &index_img);
                for (i = 0; i < N[index_img]; i++) {
                    for (j = 0; j < M[index_img]; j++) {
                        free(a[index_img][i][j]);
                    }
                    free(a[index_img][i]);
                }
                free(a[index_img]);
                for (i = index_img; i < k - 1; i++) {
                    a[i] = a[i+1];
                    N[i] = N[i+1];
                    M[i] = M[i+1];
                }
                k--;
            }
            scanf("%s", in);
    }
    return 0;
}
