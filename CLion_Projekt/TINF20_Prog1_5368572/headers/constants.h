//
// Created by MSCHIC1 on 12.04.2023.
//

#ifndef TINF20_PROG1_5368572_CONSTANTS_H
#define TINF20_PROG1_5368572_CONSTANTS_H

// CONSTANTS
#define FILEPATH "../PPM_Files/ParamUserInput.ppm"     // !!!Defines the name and the location of the generated file!!!

#define X_PIXEL 1001 // ppm file width
#define Y_PIXEL 1001 // ppm file height
#define PI 3.14159265

#define MATRIXROW X_PIXEL
#define MATRIXCOL Y_PIXEL
#define CENTER 500  // defines the center field of the Matrix

// END CONSTANTS

// STRUCTS
typedef struct {
    int x;
    int y;
} point;
// END STRUCTS


#endif //TINF20_PROG1_5368572_CONSTANTS_H
