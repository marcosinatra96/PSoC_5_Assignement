# PSoC Projects Assignment 05
This repository contains 3 projects I developed for the fifth Assignment of the ‘Electronic Technology and Biosensors Laboratory’ course. 
The projects are aimed to understand the functionalities of a LIS3DH Accelerometer, which is connected to a PSoC 5LP microcontroller (in 
particular I used the [CY8CKIT-059](https://www.cypress.com/documentation/development-kitsboards/cy8ckit-059-psoc-5lp-prototyping-kit-onboard-programmer-and) 
development kit).

## List of projects:

- [AY1920_II_HW_05_PROJ_1.cydsn](https://github.com/marcosinatra96/PSoC_5_Assignement/tree/master/AY1920_II_HW_05_PROJ_1.cydsn): in this project we setup a I2C master device to understand the I2C protocol and communicate with a I2C Slave device (LIS3DH Accelerometer). The adjacent registers 
are specifically read and written in sequence thanks to the implementation of MultiRead and MultiWrite functions, respectively.

- [AY1920_II_HW_05_PROJ_2.cydsn](https://github.com/marcosinatra96/PSoC_5_Assignement/tree/master/AY1920_II_HW_05_PROJ_2.cydsn): this project shows to test the capabilities of the LIS3DH accelerometer. In particular, the output is a 3-Axis Signal in 'Normal Mode' configuration at 100Hz. 
These output values, according to UART communication protocol, are sent to the Bridge Control Panel software in order to be plotted.

- [AY1920_II_HW_05_PROJ_3.cydsn](https://github.com/marcosinatra96/PSoC_5_Assignement/tree/master/AY1920_II_HW_05_PROJ_3.cydsn): this project shows how to test the capabilities of the LIS3DH accelerometer. In particular, the output is a 3-Axis Signal in 'High resolution Mode' configuration at 100Hz. 
These output values are firstly converted to floating points in m/s2 units. Then, according to UART communication protocol, the data is sent to the Bridge  Control Panel software in order to be plotted.












