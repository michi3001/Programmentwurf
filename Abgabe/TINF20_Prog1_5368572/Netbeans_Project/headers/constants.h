//
// Created by MSCHIC1 on 12.04.2023.
//

#ifndef TINF20_PROG1_5368572_CONSTANTS_H
#define TINF20_PROG1_5368572_CONSTANTS_H

// CONSTANTS
#define FILEPATH "PPM_Files/Filename.ppm"       // !!!Defines the name and the location of the generated file!!!
                                                // If you want to add the file into an folder you have to create the folder at first
                                                // In this case you have to create the folder PPM_Files at the same location where the 
                                                // main.c file is stored

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
