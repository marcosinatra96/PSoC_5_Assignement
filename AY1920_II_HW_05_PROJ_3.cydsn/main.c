/**
* 
* \file main.c
* In this project we set up a I2C master device and communicate with a 
* I2C Slave device (LIS3DH Accelerometer).This project shows indeed how 
* to test the capabilities of the LIS3DH accelerometer.  The output is a
* 3-Axis Signal in 'High resolution Mode' configuration at 100Hz. The adjacent registers 
* are specifically read in sequence thanks to the implementation of a multiread 
* function. The output values are converted to floating points in m/s2 units. 
* Then, according to UART communication protocol, the data is sent to the
* Bridge Control Panel software in order to be plotted. The BAUD rate is set
* to 19200 bps and, in this way, it is sufficient since we are sending about
* 11200 bps (further information are explained in TopDesign interface).
*
* \Author Marco Sinatra
*/

// Include required header files
#include "I2C_Interface.h"
#include "project.h"
#include "stdio.h"
#include "math.h"
#include "variable_definition.h"

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
            // print out the address in hex format
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
    
    
    /****************************************************/
    /*   variable declaration and for(;;) definition)   */
    /****************************************************/
    
    int range = 512; /*Maximum data range: indeed, 12-bit resolution corresponds to 4096 levels (values are 
                      from -2048 to + 2048),namely ±4g. Hence ±1g corresponds to ±512 */
    float32 gravity = 9.81; //Gravity acceleration 
    int16_t Out_Acc_X; //X-axis accelerometer value in integer
    int16_t Out_Acc_Y; //Y-axis accelerometer value in integer
    int16_t Out_Acc_Z; //Z-axis accelerometer value in integer
    float32 Out_Acc_X_f; //X-axis accelerometer value in float
    float32 Out_Acc_Y_f; //Y-axis accelerometer value in float
    float32 Out_Acc_Z_f; //Z-axis accelerometer value in float
    uint8_t X_axis[sizeof(float)]; //Usnigned int array storing the 4-bytes X-axis information 
    uint8_t Y_axis[sizeof(float)]; //Usnigned int array storing the 4-bytes Y-axis information
    uint8_t Z_axis[sizeof(float)]; //Usnigned int array storing the 4-bytes Z-axis information   
    uint8_t OutArray[TRANSMIT_BUFFER_SIZE]; //Array of dimension 'TRANSMIT_BUFFER_SIZE' containing all the axis information
    uint8_t register_count = 5; //Number of registers to be read in sequence (exluding the first passed as argoment of the function 'I2C_Peripheral_ReadRegisterMulti'
    uint8_t AccData[6]; //Array storing the info read from the 6 adjacent registers
    uint8_t header = 0xA0;
    uint8_t footer = 0xC0;
    
    /*Setup header and tail*/
    OutArray[0] = header; //Header
    OutArray[TRANSMIT_BUFFER_SIZE-1] = footer; //Tail

    for(;;)
    {
        /*    I2C Reading Status Register     */        
        error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                            LIS3DH_STATUS_REG,
                                            &status_register);
        
        /*  Check if a new set of data is available  */
        if (status_register & (1 << ZYXDA))
        {        
            error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                     LIS3DH_OUT_X_L,
                                                     register_count,
                                                     &AccData[0]);
            
            if(error == NO_ERROR)
            {
                /*  Brief explanation to send data as float to the Bridge Control Panel: the METHOD HERE
                USED, namely  < *(float*)(axis) > , allows to directly take the memory occupied by the specific 
                axis (namely the uint8_t X-axis, Y_axis and Z_axis) and read it as a floating point number. 
                In this way, we can just set the parameters of the Bridge Control Panel inerface as 'float'
                and the 'scale' is set as default to value 1 (we do not lose information at all!). 
                ANOTHER ALTERNATIVE and STANDARD method implies multiplying the values by a factor of 1000 and 
                then, in the Bridge Control Panel interface, setting the 'scale' parameter equal to '0.001' (thus 
                allowing to keep at least 3 decimals) */
                
                
                /*  X-AXIS  */
                Out_Acc_X = (int16)((AccData[0] | (AccData[1]<<8)))>>4; //Right justified 16bit integer         
                Out_Acc_X_f  = (float32)(Out_Acc_X * gravity) / range;  //Convert data into float and rescale in accelaration units 
                *(float*)(X_axis) = Out_Acc_X_f ;  //Convert float to uint bytes 
                
                /*  Y-AXIS  */
                Out_Acc_Y = (int16)((AccData[2] | (AccData[3]<<8)))>>4; //Right justified 16bit integer
                Out_Acc_Y_f  = (float32)(Out_Acc_Y * gravity) / range;  //Convert data into float and rescale in accelaration units 
                *(float*)(Y_axis) = Out_Acc_Y_f ;  //Convert float to uint bytes 
                
                /*  Z-AXIS  */
                Out_Acc_Z = (int16)((AccData[4] | (AccData[5]<<8)))>>4; //Right justified 16bit integer
                Out_Acc_Z_f  = (float32)(Out_Acc_Z * gravity) / range;  //Convert data into float and rescale in accelaration units  
                *(float*)(Z_axis) = Out_Acc_Z_f ;  //Convert float to uint bytes

                
                OutArray[1] = X_axis [0];  //LSB of accelerometer X-axis
                OutArray[2] = X_axis [1]; 
                OutArray[3] = X_axis [2]; 
                OutArray[4] = X_axis [3];  //MSB of accelerometer X-axis
                OutArray[5] = Y_axis [0];  //LSB of accelerometer Y-axis
                OutArray[6] = Y_axis [1];
                OutArray[7] = Y_axis [2];
                OutArray[8] = Y_axis [3];  //MSB of accelerometer Y-axis
                OutArray[9] = Z_axis [0];  //LSB of accelerometer Z-axis
                OutArray[10] = Z_axis [1];
                OutArray[11] = Z_axis [2];
                OutArray[12] = Z_axis [3]; //MSB of accelerometer Z-axis         
                UART_Debug_PutArray(OutArray, TRANSMIT_BUFFER_SIZE); //Send information through UART communication protocol
                
            }
        }
    }
}

/* [] END OF FILE */
