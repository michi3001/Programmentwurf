#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

//#define FILEPATH "../PPM_Files/N2.ppm" // Ihr Filename
#define X_PIXEL 1001 // Ihre Bildbreite
#define Y_PIXEL 1001 // Ihre Bildhöhe
#define CENTER 500


#define MATRIXROW X_PIXEL
#define MATRIXCOL Y_PIXEL

#define PARAMETER 8            //IHR PARAMETERWERT
#define FILEPATH "../PPM_Files/ChangedLineBehaviour.ppm" // Ihr Filename


typedef struct {
    int x;
    int y;
} point;

int create_ppm(char* pMatrix) {
    FILE *p_file = fopen((FILEPATH),"wb"); //mode wb - write binary mode
    if (NULL != p_file) { //if theres an error due to the fopen() function p_file = NULL
        fprintf (p_file, "P6\n %d %d\n 255\n", X_PIXEL, Y_PIXEL); //P6 = file is in binary format

        for(int i=0; i<MATRIXROW; i++) {
            for (int j = 0; j < MATRIXCOL; j++) {
                if ('+' == pMatrix[i * MATRIXCOL + j]) fprintf(p_file, "%c%c%c", 0, 0, 255);
                else fprintf(p_file, "%c%c%c", 255, 255, 255);
            }
        }
        fclose (p_file);
        printf("\nCreated the ppm file");
    }
    else printf("\nFailed to create the ppm file");
    return 0;
}

// DIESE FUNKTIONEN MÜSSEN SPÄTER INS HEADERFILE EINGEBUNDEN WERDEN UND DÜRFEN NICHT IM MAIN FILE STEHEN
// WAHRSCHEINLICH MÜSSEN DANN AUCH DIE KONSTANTEN IRGENDWIE ÜBERGEBEN WERDEN

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
    assert(iX <= MATRIXROW);
    assert(iY <= MATRIXCOL);
    pMatrix[iX * MATRIXCOL + iY] = '+';
}

//Hier überprüfen ob die Parameter in der richtigen Reihenfolge sind
void drawLine(char* pMatrix, int iVerticalIdx0, int iHorizontalIdx0, int iVerticalIdx1, int iHorizontalIdx1) {
    int iDeltaY =  abs (iVerticalIdx1 - iVerticalIdx0), iDirVertical = iVerticalIdx0 < iVerticalIdx1 ? 1 : -1; //abs() returns the absolute value (positive value)
    int iDeltaX = -abs (iHorizontalIdx1 - iHorizontalIdx0), iDirHorizontal = iHorizontalIdx0 < iHorizontalIdx1 ? 1 : -1;
    int err = iDeltaY + iDeltaX, e2;

    while(1) {
        setPixel(pMatrix, iVerticalIdx0, iHorizontalIdx0);
        if (iVerticalIdx0 == iVerticalIdx1 && iHorizontalIdx0 == iHorizontalIdx1) break;
        e2 = 2 * err;
        if (e2 >= iDeltaX) {
            err += iDeltaX;
            iVerticalIdx0 += iDirVertical;
        }
        if (e2 <= iDeltaY) {
            err += iDeltaY;
            iHorizontalIdx0 += iDirHorizontal;
        }
    }
}

void drawCircle(char* pMatrix, int iRadius) {
    int x = iRadius;
    int y = 0;
    int radiusError = 1 - x;

    while (x >= y) {
        setPixel(pMatrix, CENTER + x, CENTER + y);
        setPixel(pMatrix, CENTER - x, CENTER + y);
        setPixel(pMatrix, CENTER + x, CENTER - y);
        setPixel(pMatrix, CENTER - x, CENTER - y);
        setPixel(pMatrix, CENTER + y, CENTER + x);
        setPixel(pMatrix, CENTER - y, CENTER + x);
        setPixel(pMatrix, CENTER + y, CENTER - x);
        setPixel(pMatrix, CENTER - y, CENTER - x);

        y++;
        if (radiusError < 0) {
            radiusError += 2 * y + 1;
        } else {
            x--;
            radiusError += 2 * (y - x) + 1;
        }
    }
}

void calc_equidistant_points(point* pPointArray, int iRadius) {
    //Pointer auf Struct Array: (pPointArray+ArrayIndex)->Element

    //PROBLEM HIER: erster Strich muss oben mittig im Kreis sein
    //(pPointArray+0)->x = CENTER-iRadius;
    //(pPointArray+0)->y = CENTER;
    for(int i=0; i < PARAMETER; i++) {
        //Calculate X-Value
        (pPointArray+i)->x = CENTER + (iRadius * sin((360/PARAMETER)* i * M_PI/180));  //*MPI/180 = Conversion to Radiant

        //Calculate Y-Value
        (pPointArray+i)->y = CENTER + (iRadius * cos((360/PARAMETER)* i * M_PI/180));
    }
}
// ENDE FUNKTIONEN

int main() {
    int iParameter = 0;
    char cMatrix[MATRIXROW][MATRIXCOL];
    point sInnerPoints[PARAMETER], sOuterPoints[PARAMETER];      //These 2 Struct Arrays store the values of the points on the circle based on the
                                                                        //Parameter Value. These points all have an equivalent distance to each other = equidistant
                                                                        //The matching points of the inner and outer Array have to be connected in the last step



    /* printf("Programmentwurf\n");
    printf("Bitte geben sie den Parameter ein: ");
    scanf("%d", &iParameter);
    printf("\nParameterwert: ");
    printf("%d", iParameter);
    */


    fillMatrix(cMatrix);
    drawCircle(cMatrix, 200);   //Draw the inner circle
    calc_equidistant_points(&sInnerPoints, 200);
    drawCircle(cMatrix, 400);   //Draw the outer circle
    calc_equidistant_points(&sOuterPoints, 400);

    //void drawLine(char* pMatrix, int iVerticalIdx0, int iHorizontalIdx0, int iVerticalIdx1, int iHorizontalIdx1)

    for(int i=0; i<PARAMETER; i++) {
        drawLine(cMatrix, sInnerPoints[i].y, sInnerPoints[i].x, sOuterPoints[i].y, sOuterPoints[i].x);
    }

    create_ppm(cMatrix);


    return 0;
}
