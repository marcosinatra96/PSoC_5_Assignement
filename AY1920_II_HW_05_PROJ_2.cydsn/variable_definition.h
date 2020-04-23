/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef _VARIABLE_DEFINITION_H
    
    /*Header guard*/
    #define _VARIABLE_DEFINITION_H
    
    /**
    *   \brief 7-bit I2C address of the slave device.
    */
    #define LIS3DH_DEVICE_ADDRESS 0x18

    /**
    *   \brief Address of the WHO AM I register
    */
    #define LIS3DH_WHO_AM_I_REG_ADDR 0x0F

    /**
    *   \brief Address of the Status register
    */
    #define LIS3DH_STATUS_REG 0x27

    /**
    *   \brief Address of the Control register 1
    */
    #define LIS3DH_CTRL_REG1 0x20

    /**
    *   \brief Hex value to set normal resolution mode to the accelerator.
    *    In order to achieve that aim, we also need the 'LPen' bit (of the 
    *    Temperature Sensor Configuration register) set to 0 and then, at 
    *    the same time, the 'HR' bit (of the Control register 4) set to 0  
    *    (see below for these 2 specific bits configuration).
    */
    #define LIS3DH_NORMAL_MODE_CTRL_REG1 0x57 //set normal mode at 100 Hz (according to datasheet related information)

    /**
    *   \brief  Address of the Temperature Sensor Configuration register
    */
    #define LIS3DH_TEMP_CFG_REG 0x1F

    #define LIS3DH_TEMP_CFG_REG_ACTIVE 0xC0 // in this way also 'LPen' bit is set to 0

    /**
    *   \brief Address of the Control register 4
    */
    #define LIS3DH_CTRL_REG4 0x23

    #define LIS3DH_CTRL_REG4_BDU_ACTIVE 0x80 // in this way also 'HR' bit is set to 0

    /**
    *   \brief Address of the ADC output LSB register
    */
    #define LIS3DH_OUT_ADC_3L 0x0C

    /**
    *   \brief Address of the ADC output MSB register
    */
    #define LIS3DH_OUT_ADC_3H 0x0D

    /**
    *   \brief Address of the accelerometer X-axis (LOW register)
    */
    #define LIS3DH_OUT_X_L 0x28

    /**
    *   \brief bit of the STATUS REGISTER (will be used in the main.c 
    *   in order to understand if a new set of data is available or not)
    */    
    #define ZYXDA 3
    
    /**
    *   \brief number of bytes to be sent definition
    */    
    #define BYTE_TO_SEND 6 //We know EXACTLY the number of bytes to be sent
    #define TRANSMIT_BUFFER_SIZE 1+ BYTE_TO_SEND +1 //Contains 1 header byte and 1 tail byte

    /**
    *   \brief conversion factor from raw data (received by the accelerometer) into mg
    */  
    #define CONVERSION_FACTOR 1000/256    
#endif
/* [] END OF FILE */
