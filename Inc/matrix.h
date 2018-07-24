/**********************************************************************************************************************
 * @file    matrix.h
 * @author  Simon Benoit
 * @date    20-07-2018
 * @brief   
 *********************************************************************************************************************/

#ifndef __MATRIX_H__
#define __MATRIX_H__

/* Includes ---------------------------------------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/* Global Defines ---------------------------------------------------------------------------------------------------*/

/* Global Enum ------------------------------------------------------------------------------------------------------*/

/* Global Typedef ------------------------------------------------------------------------------------------------------*/

typedef struct __xyz_coord_t
{
    double x;
    double y;
    double z;
}xyz_coord_t;

typedef struct __coord_matrix_t
{
    xyz_coord_t xp;
    xyz_coord_t yp;
    xyz_coord_t zp;
}coord_matrix_t;

/* Global Variables -------------------------------------------------------------------------------------------------*/

/* Global Functions Prototypes --------------------------------------------------------------------------------------*/

coord_matrix_t      identityMatrix3                 (void);
coord_matrix_t      skewSymmetriCrossProductMatrix3 (xyz_coord_t vector);
coord_matrix_t      rotationMatrix3                 (xyz_coord_t a, xyz_coord_t b);
coord_matrix_t      addMatrices3                    (coord_matrix_t a, coord_matrix_t b);
coord_matrix_t      multiplyMatrix3                 (coord_matrix_t matrix, double factor);
coord_matrix_t      multiplyMatrices3               (coord_matrix_t a, coord_matrix_t b);
coord_matrix_t      divideMatrix3                   (coord_matrix_t matrix, double divider);
xyz_coord_t         multiplyVector3                 (xyz_coord_t *vector, coord_matrix_t *matrix);
xyz_coord_t         crossProduct3                   (xyz_coord_t a, xyz_coord_t b);
xyz_coord_t         normalize3                      (xyz_coord_t vector);
double              length3                         (xyz_coord_t vector);
double              dotProduct3                     (xyz_coord_t a, xyz_coord_t b);
coord_matrix_t      get_zyRotate                    (xyz_coord_t coord);
coord_matrix_t      get_zRotate                     (xyz_coord_t coord);
coord_matrix_t      get_yRotate                     (xyz_coord_t coord);
coord_matrix_t      get_xRotate                     (xyz_coord_t coord);

/* ------------------------------------------------------------------------------------------------------------------*/

#endif//__MATRIX_H__