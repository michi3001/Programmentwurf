#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "headers/functions.h"
#include "headers/constants.h"



int main() {
    char cMatrix[MATRIXROW][MATRIXCOL];
    int iParameter;

    printf("Programmentwurf\n");
    printf("Bitte geben sie den Parameter ein: ");
    scanf("%d", &iParameter);
    printf("\nParameterwert: ");
    printf("%d", iParameter);


    point sInnerPoints[iParameter], sOuterPoints[iParameter];     //These 2 Struct Arrays store the values of the points on the circle based on the
                                                                //Parameter Value. These points all have an equivalent distance to each other = equidistant
                                                                //The matching points of the inner and outer Array have to be connected in the last step


    fillMatrix(cMatrix);
    
    drawCircle(cMatrix, '-', 200);                  //Draw the inner circle
    calc_equidistant_points(&sInnerPoints, 200, iParameter);    //Fill the inner circle with equidistant points
    drawCircle(cMatrix, '*', 400);                  //Draw the outer circle
    calc_equidistant_points(&sOuterPoints, 400, iParameter);    //Fill the inner circle with equidistant points

    connect_points(cMatrix, &sInnerPoints, &sOuterPoints, iParameter);

    create_ppm(cMatrix);


    return 0;
}
