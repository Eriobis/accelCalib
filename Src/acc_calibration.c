/**********************************************************************************************************************
 * @file    main.c
 * @author  Simon Benoit
 * @date    20-07-2018
 * @brief   
 **********************************************************************************************************************

/* Includes ---------------------------------------------------------------------------------------------------------*/

#include "acc_calibration.h"
#include <string.h>

/* Local Defines ----------------------------------------------------------------------------------------------------*/

/* Local Typedefs ---------------------------------------------------------------------------------------------------*/

/* Forward Declarations ---------------------------------------------------------------------------------------------*/

/* Local Constants --------------------------------------------------------------------------------------------------*/

/* Local Variables --------------------------------------------------------------------------------------------------*/

static coord_matrix_t conversionMatrix;

/* Local Functions --------------------------------------------------------------------------------------------------*/

/* Global Functions -------------------------------------------------------------------------------------------------*/

/**
  *--------------------------------------------------------------------------------------------------------------------
  * EXAMPLE
  *--------------------------------------------------------------------------------------------------------------------
int calibration_example()
{
    xyz_coord_t coord = {-50,-24,-60};
    xyz_coord_t output;
    coord_matrix_t zy_matrix, z_matrix;

    // Replace Z (fix actual position)
    zy_matrix = get_negative_z_matrix(&coord);

    // Move FW, grab the current vector
    // coord = blablabla

    // Get the Z rotation matrix to transfer current vector to [1,0,0]
    z_matrix = get_x_adjust_matrix(&coord)

    // Store the result to the global variable
    set_conversionMatrix(multiplyMatrices3(zy_matrix,z_matrix));

    return 0;
}
*/

/**
  *--------------------------------------------------------------------------------------------------------------------
  * @brief  Returns the rotation matrix to set a vector to [0,0,-1]
  *
  * @param  xyz_coord_t input coordinates
  *
  * @retval ZY rotation matrix
  *
  *--------------------------------------------------------------------------------------------------------------------
  */
coord_matrix_t get_negative_z_matrix(xyz_coord_t *coord)
{
    xyz_coord_t normCoord;

    //printCoord(*coord);
    normCoord = normalize3(*coord);
    return get_zyRotate(normCoord);
}

/**
  *--------------------------------------------------------------------------------------------------------------------
  * @brief  Returns the rotation matrix to set a vector to [1,0,0]
  *
  * @param  xyz_coord_t input coordinates
  *
  * @retval ZY rotation matrix
  *
  *--------------------------------------------------------------------------------------------------------------------
  */
coord_matrix_t get_x_adjust_matrix(xyz_coord_t *coord)
{
    xyz_coord_t normCoord;

    //printCoord(*coord);
    normCoord = normalize3(*coord);
    return get_zRotate(normCoord);
}

/**
  *--------------------------------------------------------------------------------------------------------------------
  * @brief  Set the global conversion matrix
  *
  * @param  coord_matrix_t
  *
  * @retval none
  *
  *--------------------------------------------------------------------------------------------------------------------
  */
void set_conversionMatrix(coord_matrix_t matrix)
{
    memcpy(&conversionMatrix, &matrix, sizeof(coord_matrix_t));
}

/**
  *--------------------------------------------------------------------------------------------------------------------
  * @brief  Get the current stored conversion matrix
  *
  * @param  none
  *
  * @retval coord_matrix_t
  *
  *--------------------------------------------------------------------------------------------------------------------
  */
coord_matrix_t get_conversionMatrix()
{
    return conversionMatrix;
}

/**
  *--------------------------------------------------------------------------------------------------------------------
  * @brief  Convert the xyz vector by the stored conversion matrix
  *
  * @param  data
  *
  * @retval converted data
  *
  *--------------------------------------------------------------------------------------------------------------------
  */
xyz_coord_t convert_data(xyz_coord_t data)
{
    return multiplyVector3(&data, &conversionMatrix);
}
