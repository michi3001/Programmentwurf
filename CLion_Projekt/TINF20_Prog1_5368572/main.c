#include <stdio.h>
#include <stdlib.h>
#define MYFILENAME "testimage.ppm" // Ihr Filename
#define X_PIXEL 200 // Ihre Bildbreite
#define Y_PIXEL 200 // Ihre Bildhöhe

#define MATRIXROW 4
#define MATRIXCOL 6

int create_ppm(void)
{
    FILE *p_file = fopen(MYFILENAME,"w");
    if (NULL != p_file)
    {
        fprintf (p_file, "P3\n %d %d\n 255\n", X_PIXEL, Y_PIXEL);
        fclose (p_file);
        printf("\nCreated the ppm file");
    }
}

// DIESE FUNKTIONEN MÜSSEN SPÄTER INS HEADERFILE EINGEBUNDEN WERDEN UND DÜRFEN NICHT IM MAIN FILE STEHEN

//Arrayindex = row * num_columns + column;
void fillMatrix(char* pMatrix) {
    for(int i = 0; i < MATRIXROW; i++) {
        if (i == 0 || i == MATRIXROW - 1) {
            for (int j = 0; j < MATRIXCOL; j++) pMatrix[i * MATRIXCOL + j] = '+';
            printf("\n");
        }
        else {
            for(int x = 0; x < MATRIXCOL; x++) {
                if(x == 0 || x == MATRIXCOL - 1) pMatrix[i * MATRIXCOL + x] = '+';
                else pMatrix[i * MATRIXCOL + x] = ' ';
            }
        }
    }
}


void drawMatrix(char* pMatrix) {
    for(int i=0; i<MATRIXROW; i++) {
        printf("\n");
        for(int j=0; j<MATRIXCOL; j++) printf("%c", pMatrix[i * MATRIXCOL + j]);
    }
}


void setPixel(char* pMatrix, int iX, int iY) {  //X&Y Coordinate are indexed like the Array Index, means from 0 to ...
    pMatrix[iX * MATRIXCOL + iY] = '*';
}


void drawLine() {
    NULL;
}


void drawCircle() {
    NULL;
}
// ENDE FUNKTIONEN

int main() {
    int iParameter = 0;
    char cMatrix[MATRIXROW][MATRIXCOL];
    /* printf("Programmentwurf\n");
    printf("Bitte geben sie den Parameter ein: ");
    scanf("%d", &iParameter);
    printf("\nParameterwert: ");
    printf("%d", iParameter);
    */

    create_ppm();
    fillMatrix(cMatrix);
    drawMatrix(cMatrix);
    setPixel(cMatrix,  0, 0);
    drawMatrix(cMatrix);

    return 0;
}
