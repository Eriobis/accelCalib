# Accelerometer Calibration Module

A simple module to remove the offset from a 3-axis accelerometer.

- With only the static vector [x,y,z] as an input, it can create a rotation matrix to rotate the axis to [0,0,-1]

    Use the 'get_negative_z_matrix()' function to achieve this.

- The second step would be to get a "forward" sample with the static G removed to set the proper X axis

    I am still working on the routine, but I would like to make the vector "auto-correct" to make it orthogonal to the Z axis