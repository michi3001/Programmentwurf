//
// Created by MSCHIC1 on 12.04.2023.
//

#include "constants.h"

#ifndef TINF20_PROG1_5368572_FUNCTIONS_H
#define TINF20_PROG1_5368572_FUNCTIONS_H

int create_ppm(char* pMatrix) {     // Creates the ppm file and changes the character symbols to pixels
    FILE *p_file = fopen((FILEPATH),"wb");  //mode wb - write binary mode
    if (NULL != p_file) {   //if theres an error due to the fopen() function p_file = NULL
        fprintf (p_file, "P6\n %d %d\n 255\n", X_PIXEL, Y_PIXEL); //P6 = file is in binary format

        for(int i=0; i<MATRIXROW; i++) {
            for (int j = 0; j < MATRIXCOL; j++) {
                if ('+' == pMatrix[i * MATRIXCOL + j]) fprintf(p_file, "%c%c%c", 0, 255, 102);          //Line Color
                else if('-' == pMatrix[i * MATRIXCOL + j]) fprintf(p_file, "%c%c%c", 238, 255, 0);      //Innercircle Color
                else if('*' == pMatrix[i * MATRIXCOL + j]) fprintf(p_file, "%c%c%c", 0, 234, 255);      //Outercircle Color
                else if('.' == pMatrix[i * MATRIXCOL + j]) fprintf(p_file, "%c%c%c", 255, 255, 255);    //Matrixborder Color
                else fprintf(p_file, "%c%c%c", 72, 73, 74);                                             //Background Color
            }
        }

        fclose (p_file);
        printf("\nCreated the ppm file");
    }
    else printf("\nFailed to create the ppm file");
    return 0;
}

void fillMatrix(char* pMatrix) {   // Matrix is filled with characters
    for(int i = 0; i < MATRIXROW; i++) {
        if (i == 0 || i == MATRIXROW - 1) {
            for (int j = 0; j < MATRIXCOL; j++) pMatrix[i * MATRIXCOL + j] = '.';   //draws the border
                                                                                    //Pointer to an array indexing: Arrayindex = row * num_columns + column;
            printf("\n");
        }
        else {
            for(int x = 0; x < MATRIXCOL; x++) {
                if(x == 0 || x == MATRIXCOL - 1) pMatrix[i * MATRIXCOL + x] = '.';  //draws the border
                else pMatrix[i * MATRIXCOL + x] = ' ';
            }
        }
    }
}

void drawMatrix(char* pMatrix) {    // Prints the matrix on the console
    for(int i=0; i<MATRIXROW; i++) {
        printf("\n");
        for(int j=0; j<MATRIXCOL; j++) printf("%c", pMatrix[i * MATRIXCOL + j]);
    }
}

void setPixel(char* pMatrix, char cSymbol, int iX, int iY) {    // Change one specified pixel with the
    //X&Y Coordinate are indexed like the Array Index, means from 0 to ...
    assert(iX <= MATRIXROW);
    assert(iY <= MATRIXCOL);
    pMatrix[iX * MATRIXCOL + iY] = cSymbol;
}

void drawLine(char* pMatrix, int iVerticalIdx0, int iHorizontalIdx0, int iVerticalIdx1, int iHorizontalIdx1) {      //Draws a line from one Matrix Field to another Matrix Field
    int iDeltaY =  abs (iVerticalIdx1 - iVerticalIdx0);
    int iDirVertical = iVerticalIdx0 < iVerticalIdx1 ? 1 : -1; //abs() returns the absolute value (positive value)
    int iDeltaX = -abs (iHorizontalIdx1 - iHorizontalIdx0);
    int iDirHorizontal = iHorizontalIdx0 < iHorizontalIdx1 ? 1 : -1;
    int err = iDeltaY + iDeltaX;
    int e2;

    while(1) {
        setPixel(pMatrix, '+', iVerticalIdx0, iHorizontalIdx0);
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

void drawCircle(char* pMatrix, char cSymbol, int iRadius) {     // Draws a circle depending on the Radius
    int x = iRadius;
    int y = 0;
    int radiusError = 1 - x;

    while (x >= y) {
        setPixel(pMatrix, cSymbol, CENTER + x, CENTER + y);
        setPixel(pMatrix, cSymbol, CENTER - x, CENTER + y);
        setPixel(pMatrix, cSymbol, CENTER + x, CENTER - y);
        setPixel(pMatrix, cSymbol, CENTER - x, CENTER - y);
        setPixel(pMatrix, cSymbol, CENTER + y, CENTER + x);
        setPixel(pMatrix, cSymbol, CENTER - y, CENTER + x);
        setPixel(pMatrix, cSymbol, CENTER + y, CENTER - x);
        setPixel(pMatrix, cSymbol, CENTER - y, CENTER - x);

        y++;
        if (radiusError < 0) {
            radiusError += 2 * y + 1;
        } else {
            x--;
            radiusError += 2 * (y - x) + 1;
        }
    }
}


void calc_equidistant_points(point* pPointArray, int iRadius) {         // Calculates points which are on a circel with the radius XY and which are equidistant
                                                                        // (have the same distance to each other)
    // Pointer on struct array: (pPointArray+ArrayIndex)->Element
    double dAngle = 2 * PI / PARAMETER;        //Angle in rad

    for(int i=0; i < PARAMETER; i++) {
        double dPointAngle = i * dAngle;

        //Calculate X-Value
        int iX = CENTER + (iRadius * sin(dPointAngle));
        (pPointArray+i)->x = iX;

        //Calculate Y-Value
        int iY = CENTER - (iRadius * cos(dPointAngle));     // - the y-offset because if you want to go up, you have to lower the vertical matrix index
        (pPointArray+i)->y = iY;
    }
}


void connect_points(char* pMatrix, point* pInnerPoints, point* pOuterPoints) {  //Connect the equidistant points from the inner circle with the points on the outer circle
    for(int i=0; i < PARAMETER; i++) {
        //void drawLine(char* pMatrix, int iVerticalIdx0, int iHorizontalIdx0, int iVerticalIdx1, int iHorizontalIdx1)
        drawLine(pMatrix, (pInnerPoints + i)->y, (pInnerPoints + i)->x, (pOuterPoints + i)->y, (pOuterPoints + i)->x);
    }
}


#endif //TINF20_PROG1_5368572_FUNCTIONS_H
