/**********************************************************************************************************************
 * @file    matrix.c
 * @author  Simon Benoit
 * @date    20-07-2018
 * @brief   
 **********************************************************************************************************************

/* Includes ---------------------------------------------------------------------------------------------------------*/

#include "matrix.h"

/* Local Defines ----------------------------------------------------------------------------------------------------*/

/* Local Typedefs ---------------------------------------------------------------------------------------------------*/

/* Forward Declarations ---------------------------------------------------------------------------------------------*/

/* Local Constants --------------------------------------------------------------------------------------------------*/

/* Local Variables --------------------------------------------------------------------------------------------------*/

/* Local Functions --------------------------------------------------------------------------------------------------*/

/* Global Functions -------------------------------------------------------------------------------------------------*/

/**
 * Multiplies a 1x3 vector with a 3x3 matrix
 *
 * @param vector
 * @param matrix
 * @return
 */
xyz_coord_t multiplyVector3(xyz_coord_t *vector, coord_matrix_t *matrix)
{
    xyz_coord_t result;
    result.x = (vector->x * matrix->xp.x) + (vector->y * matrix->yp.x) + (vector->z * matrix->zp.x);
    result.y = (vector->x * matrix->xp.y) + (vector->y * matrix->yp.y) + (vector->z * matrix->zp.y);
    result.z = (vector->x * matrix->xp.z) + (vector->y * matrix->yp.z) + (vector->z * matrix->zp.z);
    return result;
}

/**
 * Print the whole matrix in printf
 *
 * @param vector
 * @param matrix
 * @return
 */
void printMatrix(coord_matrix_t *matrix)
{
    printf("The matrix is :\n");

    printf("% 4.3f",matrix->xp.x);
    printf("% 4.3f",matrix->xp.y);
    printf("% 4.3f",matrix->xp.z);
    printf("\n");
    printf("% 4.3f",matrix->yp.x);
    printf("% 4.3f",matrix->yp.y);
    printf("% 4.3f",matrix->yp.z);
    printf("\n");
    printf("% 4.3f",matrix->zp.x);
    printf("% 4.3f",matrix->zp.y);
    printf("% 4.3f",matrix->zp.z);
    printf("\n");
}

/**
 * Print a vector's coordinates
 *
 * @param vector
 * @return
 */
void printCoord(xyz_coord_t coord)
{
    printf("Coord [x][y][z] :");
    printf(" [%4.6f] [%4.6f] [%4.6f] ",coord.x, coord.y, coord.z);
}

/**
 * Get the determinant of a matrix
 *
 * @param matrix
 * @return
 */
int getMatrixDeterminant(coord_matrix_t *matrix)
{
  int i,j,n;
  double det=0;

    printf("\n\nCalculate the determinant of a 3 x 3 matrix :\n");
    printf("-------------------------------------------------\n");

    printf("The matrix is :\n");
    printMatrix(matrix);

    det = det + (matrix->xp.x*(matrix->yp.y*matrix->zp.z - matrix->yp.z*matrix->zp.y));
    det = det + (matrix->xp.y*(matrix->yp.z*matrix->zp.x - matrix->yp.x*matrix->zp.z));
    det = det + (matrix->xp.z*(matrix->yp.x*matrix->zp.y - matrix->yp.y*matrix->zp.x));


    printf("\nThe Determinant of the matrix is: %f\n\n",det);
    return det;
}

/**
 * Return the 3x3 "x" rotate matrix from coordinates
 *
 * @param vector
 * @return
 */
coord_matrix_t get_xRotate(xyz_coord_t coord)
{
    double angle;
    coord_matrix_t xRotate;
    int i,j;

    //printf("The input coord are: %f , %f, %f \n", coord.x, coord.y, coord.z);
    angle = atan(coord.z/coord.y);
    //printf("The coord angle for X is : %f \n", angle);

    xRotate.xp.x = 1;
    xRotate.xp.y = 0;
    xRotate.xp.z = 0;

    xRotate.yp.x = 0;
    xRotate.yp.y = cos(angle);
    xRotate.yp.z = -sin(angle);

    xRotate.zp.x = 0;
    xRotate.zp.y = sin(angle);
    xRotate.zp.z = cos(angle);

    //printf("The xRotate matrix is :\n");
    //printMatrix(&xRotate);
    return xRotate;
}

/**
 * Return the 3x3 "y" rotate matrix from coordinates
 *
 * @param vector
 * @return
 */
coord_matrix_t get_yRotate(xyz_coord_t coord)
{
    double angle;
    coord_matrix_t yRotate;
    double r;
    double cos_angle, sin_angle;
    double r_sign;
    r = sqrt(pow(coord.x,2)+pow(coord.y,2));
    angle = -atan2(coord.z,r) + M_PI_2 + M_PI;

    yRotate.xp.x = cos(angle);
    yRotate.xp.y = 0;
    yRotate.xp.z = sin(angle);

    yRotate.yp.x = 0;
    yRotate.yp.y = 1;
    yRotate.yp.z = 0;

    yRotate.zp.x = -sin(angle);
    yRotate.zp.y = 0;
    yRotate.zp.z = cos(angle);

    //printf("The yRotate matrix is :\n");
    //printMatrix(&yRotate);

    return yRotate;
}

/**
 * Return the 3x3 "z" rotate matrix from coordinates
 *
 * @param vector
 * @return
 */
coord_matrix_t get_zRotate(xyz_coord_t coord)
{
    double angle;
    double r;
    coord_matrix_t zRotate;

    r = sqrt(pow(coord.x,2)+pow(coord.y,2));
/*
    angle = atan2(coord.y, coord.x);
    zRotate.xp.x = cos(angle);
    zRotate.xp.y = -sin(angle);
    zRotate.xp.z = 0;

    zRotate.yp.x = sin(angle);
    zRotate.yp.y = cos(angle);
    zRotate.yp.z = 0;

    zRotate.zp.x = 0;
    zRotate.zp.y = 0;
    zRotate.zp.z = 1;
*/

    /*
    This should speed up the process
    cos(atan2(y,x)) == x/r
    sin(atan2(y,x)) == y/r
    */

    zRotate.xp.x = coord.x/r;
    zRotate.xp.y = -coord.y/r;
    zRotate.xp.z = 0;

    zRotate.yp.x = coord.y/r;
    zRotate.yp.y = coord.x/r;
    zRotate.yp.z = 0;

    zRotate.zp.x = 0;
    zRotate.zp.y = 0;
    zRotate.zp.z = 1;
   //printf("The zRotate matrix is :\n");
   // printMatrix(&zRotate);

    return zRotate;
}

/**
 * Return the 3x3 "z * y" rotate matrix from coordinates
 *
 * @param vector
 * @return
 */
coord_matrix_t get_zyRotate(xyz_coord_t coord)
{
    double alpha, beta;
    coord_matrix_t zyRotate;
    double r;

    r = sqrt(pow(coord.x,2)+pow(coord.y,2));
    beta = -atan2(coord.z,r) + M_PI_2 + M_PI;
    alpha= atan2(coord.y, coord.x);

    zyRotate.xp.x = (coord.x/r)*cos(beta);
    zyRotate.xp.y = -coord.y/r;
    zyRotate.xp.z = cos(alpha)*sin(beta);

    zyRotate.yp.x = (coord.y/r)*cos(beta);
    zyRotate.yp.y = coord.x/r;
    zyRotate.yp.z = (coord.y/r)*sin(beta);

    zyRotate.zp.x = -sin(beta);
    zyRotate.zp.y = 0;
    zyRotate.zp.z = cos(beta);

    return zyRotate;
}

/**
 * Multiplies two 3x3 matrix
 *
 * @param vector
 * @param matrix
 * @return
 */

coord_matrix_t multiplyMatrices3(coord_matrix_t a, coord_matrix_t b)
{
    coord_matrix_t result;

    result.xp.x = a.xp.x * b.xp.x + a.xp.y * b.yp.x + a.xp.z * b.zp.x;
    result.xp.y = a.xp.x * b.xp.y + a.xp.y * b.yp.y + a.xp.z * b.zp.y;
    result.xp.z = a.xp.x * b.xp.z + a.xp.y * b.yp.z + a.xp.z * b.zp.z;

    result.yp.x = a.yp.x * b.xp.x + a.yp.y * b.yp.x + a.yp.z * b.zp.x;
    result.yp.y = a.yp.x * b.xp.y + a.yp.y * b.yp.y + a.yp.z * b.zp.y;
    result.yp.z = a.yp.x * b.xp.z + a.yp.y * b.yp.z + a.yp.z * b.zp.z;

    result.zp.x = a.zp.x * b.xp.x + a.zp.y * b.yp.x + a.zp.z * b.zp.x;
    result.zp.y = a.zp.x * b.xp.y + a.zp.y * b.yp.y + a.zp.z * b.zp.y;
    result.zp.z = a.zp.x * b.xp.z + a.zp.y * b.yp.z + a.zp.z * b.zp.z;

    return result;
}

/**
 * Maps the vector to the skew-symmetric cross-product matrix
 *
 * @param vector a 3x1 array
 * @return a 3x3 matrix
 */
coord_matrix_t skewSymmetriCrossProductMatrix3(xyz_coord_t vector)
{
    coord_matrix_t skewSymmetricMatrix;

    skewSymmetricMatrix.xp.x = 0;
    skewSymmetricMatrix.yp.x = vector.z;
    skewSymmetricMatrix.zp.x = -vector.y;

    skewSymmetricMatrix.xp.y = -vector.z;
    skewSymmetricMatrix.yp.y = 0;
    skewSymmetricMatrix.zp.y = vector.x;

    skewSymmetricMatrix.xp.z = vector.y;
    skewSymmetricMatrix.yp.z = -vector.x;
    skewSymmetricMatrix.zp.z = 0;

    return skewSymmetricMatrix;
}

/**
 * Returns the 3x3 identity matrix
 *
 * @return
 */
coord_matrix_t identityMatrix3() {
    coord_matrix_t identityMatrix;

    identityMatrix.xp.x = 1;
    identityMatrix.yp.y = 1;
    identityMatrix.zp.z = 1;

    return identityMatrix;
}

/**
 * Returns the cross product of two 3x1 vectors
 *
 * @param a
 * @param b
 * @return
 */
xyz_coord_t crossProduct3(xyz_coord_t a, xyz_coord_t b)
{
    xyz_coord_t result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

/**
 * Returns the dot product of two 3x1 vectors
 *
 * @param a
 * @param b
 * @return
 */
double dotProduct3(xyz_coord_t a, xyz_coord_t b)
{
    double result = a.x * b.x + a.y * b.y + a.z * b.z;
    return result;
}

xyz_coord_t normalize3(xyz_coord_t vector)
{
    double length = length3(vector);

    vector.x /= length;
    vector.y /= length;
    vector.z /= length;

    return vector;
}

/**
 * Calculates the length of a 3x1 vector
 *
 * @param vector
 * @return
 */
double length3(xyz_coord_t vector)
{
    double result = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
    return result;
}

/**
 * Adds to 3x3 matrics
 *
 * @param a
 * @param b
 * @return The sum of both matrices
 */
coord_matrix_t addMatrices3(coord_matrix_t a, coord_matrix_t b)
{
    coord_matrix_t result;
    result.xp.x = a.xp.x + b.xp.x;
    result.xp.y = a.xp.y + b.xp.y;
    result.xp.z = a.xp.z + b.xp.z;
    result.yp.x = a.yp.x + b.yp.x;
    result.yp.y = a.yp.y + b.yp.y;
    result.yp.z = a.yp.z + b.yp.z;
    result.zp.x = a.zp.x + b.zp.x;
    result.zp.y = a.zp.y + b.zp.y;
    result.zp.z = a.zp.z + b.zp.z;
    return result;
}

/**
 * Multiplies a 3x3 matrices with a factor
 *
 * @param matrix
 * @param factor
 * @return The matrix multiplied by a factor
 */
coord_matrix_t multiplyMatrix3(coord_matrix_t matrix, double factor)
{
    coord_matrix_t result;

    result.xp.x = matrix.xp.x * factor;
    result.xp.y = matrix.xp.y * factor;
    result.xp.z = matrix.xp.z * factor;
    result.yp.x = matrix.yp.x * factor;
    result.yp.y = matrix.yp.y * factor;
    result.yp.z = matrix.yp.z * factor;
    result.zp.x = matrix.zp.x * factor;
    result.zp.y = matrix.zp.y * factor;
    result.zp.z = matrix.zp.z * factor;
    return result;
}

/**
 * Divides a 3x3 matrix by the given value
 *
 * @param matrix
 * @param divider
 * @return The matrix divided by divider
 */
coord_matrix_t divideMatrix3(coord_matrix_t matrix, double divider)
{
    coord_matrix_t result;
    result.xp.x = matrix.xp.x / divider;
    result.xp.y = matrix.xp.y / divider;
    result.xp.z = matrix.xp.z / divider;
    result.yp.x = matrix.yp.x / divider;
    result.yp.y = matrix.yp.y / divider;
    result.yp.z = matrix.yp.z / divider;
    result.zp.x = matrix.zp.x / divider;
    result.zp.y = matrix.zp.y / divider;
    result.zp.z = matrix.zp.z / divider;
    return result;
}
