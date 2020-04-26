/**
*
* \file main.c
* In this project we set up a I2C master device
* to understand the I2C protocol and communicate with a
* a I2C Slave device (LIS3DH Accelerometer). The adjacent registers 
* are specifically read and written in sequence thanks to the 
* implementation of multiread and multiwrite functions.
*
* \Author Marco Sinatra
* 
*/

// Include required header files
#include "I2C_Interface.h"
#include "project.h"
#include "stdio.h"
#include "macro_definition.h"


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Peripheral_Start();
    UART_Debug_Start();
    
    CyDelay(5); //"The boot procedure is complete about 5 milliseconds after device power-up."
    
    // String to print out messages on the UART
    char message[50];

    // Check which devices are present on the I2C bus
    for (int i = 0 ; i < 128; i++)
    {
        if (I2C_Peripheral_IsDeviceConnected(i))
        {
            // print out the address is hex format
            sprintf(message, "Device 0x%02X is connected\r\n", i);
            UART_Debug_PutString(message); 
        }
        
    }
    
    /******************************************/
    /*            I2C Reading                 */
    /******************************************/
    
    /* Read WHO AM I REGISTER register */
    uint8_t who_am_i_reg;
    ErrorCode error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                  LIS3DH_WHO_AM_I_REG_ADDR, 
                                                  &who_am_i_reg);
    if (error == NO_ERROR)
    {
        sprintf(message, "WHO AM I REG: 0x%02X [Expected: 0x33]\r\n", who_am_i_reg);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm\r\n");   
    }
    
    /*      I2C Reading Status Register       */
    
    uint8_t status_register; 
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_STATUS_REG,
                                        &status_register);
    
    if (error == NO_ERROR)
    {
        sprintf(message, "STATUS REGISTER: 0x%02X\r\n", status_register);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read status register\r\n");   
    }
    
    /******************************************/
    /*        Read Control Register 1         */
    /******************************************/
    uint8_t ctrl_reg1; 
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_CTRL_REG1,
                                        &ctrl_reg1);
    
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 1: 0x%02X\r\n", ctrl_reg1);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read control register 1\r\n");   
    }
    
    /******************************************/
    /*            I2C Writing                 */
    /******************************************/
    
        
    UART_Debug_PutString("\r\nWriting new values..\r\n");
    
    if (ctrl_reg1 != LIS3DH_NORMAL_MODE_CTRL_REG1)
    {
        ctrl_reg1 = LIS3DH_NORMAL_MODE_CTRL_REG1;
    
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                             LIS3DH_CTRL_REG1,
                                             ctrl_reg1);
    
        if (error == NO_ERROR)
        {
            sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
            UART_Debug_PutString(message); 
        }
        else
        {
            UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");   
        }
    }
    
    /******************************************/
    /*     Read Control Register 1 again      */
    /******************************************/

    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_CTRL_REG1,
                                        &ctrl_reg1);
    
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 1 after overwrite operation: 0x%02X\r\n", ctrl_reg1);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read control register 1\r\n");   
    }
    
     /******************************************/
     /* I2C Reading Temperature sensor CFG reg */
     /******************************************/

    uint8_t tmp_cfg_reg;

    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_TEMP_CFG_REG,
                                        &tmp_cfg_reg);
    
    if (error == NO_ERROR)
    {
        sprintf(message, "TEMPERATURE CONFIG REGISTER: 0x%02X\r\n", tmp_cfg_reg);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read temperature config register\r\n");   
    }
    
    
    tmp_cfg_reg = LIS3DH_TEMP_CFG_REG_ACTIVE; // must be changed to the appropriate value
    
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                         LIS3DH_TEMP_CFG_REG,
                                         tmp_cfg_reg);
    
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_TEMP_CFG_REG,
                                        &tmp_cfg_reg);
    
    
    if (error == NO_ERROR)
    {
        sprintf(message, "TEMPERATURE CONFIG REGISTER after being updated: 0x%02X\r\n", tmp_cfg_reg);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read temperature config register\r\n");   
    }
    
    uint8_t ctrl_reg4;

    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_CTRL_REG4,
                                        &ctrl_reg4);
    
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 4: 0x%02X\r\n", ctrl_reg4);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read control register4\r\n");   
    }
    
    
    ctrl_reg4 = LIS3DH_CTRL_REG4_BDU_ACTIVE; // must be changed to the appropriate value
    
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                         LIS3DH_CTRL_REG4,
                                         ctrl_reg4);
    
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_CTRL_REG4,
                                        &ctrl_reg4);
    
    
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 4 after being updated: 0x%02X\r\n", ctrl_reg4);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read control register4\r\n");   
    }
    
     /******************************************/
     /* Test to verify the MultiWrite function */
     /******************************************/    
    uint8_t ctrl_reg23 [2];
    
    error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                        0x21,
                                        2,
                                        &ctrl_reg23[0]);
    
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 2 and 3: 0x%02X\r\n and 0x%02X\r\n", ctrl_reg23 [0],ctrl_reg23 [1] );
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read control register23\r\n");   
    }
    
    
    ctrl_reg23[0] = 0x50; // must be changed to the appropriate value
    ctrl_reg23[1] = 0x51;
    
    error = I2C_Peripheral_WriteRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                         0x21,
                                         1,
                                         &ctrl_reg23[0]);
    
    error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                        0x21,
                                        1,
                                        &ctrl_reg23[0]);
    
    
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 2 and 3 after being updated: 0x%02X\r\n and 0x%02X\r\n", ctrl_reg23 [0],ctrl_reg23 [1]);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read control register23\r\n");   
    }
    
     /******************************************/
     /*          Variable delcaration          */
     /******************************************/      

    int16_t OutTemp; 
    uint8_t header = 0xA0;
    uint8_t footer = 0xC0;
    uint8_t OutArray[TRANSMIT_BUFFER_SIZE]; //Array of dimension 'TRANSMIT_BUFFER_SIZE' containing all the axis information
    uint8_t TemperatureData[2]; //Array storing the info read from the 2 adjacent registers
    uint8_t register_count = 1; //Number of registers to be read in sequence (exlcuding the one we start from)
    
    /* Setup header and tail */
    OutArray[0] = header;//Header
    OutArray[TRANSMIT_BUFFER_SIZE-1] = footer; //Tail
    
    for(;;)
    {
        CyDelay(100); //Arbitrary delay (we do not need a high sampling from the temperature sensor)
        
        /********************************************************************/
        /*    Read Auxiliary ADC register with ReadRegisterMulti function   */
        /********************************************************************/
        
        error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                            LIS3DH_OUT_ADC_3L,
                                            register_count,
                                            &TemperatureData[0]);
        
        if(error == NO_ERROR)
        {
            OutTemp = (int16)((TemperatureData[0] | (TemperatureData[1]<<8)))>>6; //Right justified 16bit integer
            OutArray[1] = (uint8_t)(OutTemp & 0xFF); //LSB of temperature sensor data
            OutArray[2] = (uint8_t)(OutTemp >> 8); //MSB of temperature sensor data
            UART_Debug_PutArray(OutArray, TRANSMIT_BUFFER_SIZE); //Send information through UART communication protocol
        }
    }
}

/* [] END OF FILE */
