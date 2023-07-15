#include <stdint.h>
#include <Wire.h>
#include <MLX90640_I2C_Driver.h>

void MLX90640_I2CInit()
{
    Wire.begin();
}

int MLX90640_I2CGeneralReset()
{
    Wire.clearWireTimeoutFlag();
    return 0;
}

// This function reads a desired number of words from a selected MLX90640 device memory starting from a given address and stores the data in the MCU memory location defined by the user.
// - uint8_t slaveAddr – Slave address of the MLX90640 device (the default slave address is 0x33)
// - uint16_t startAddress – First address from the MLX90640 memory to be read. The MLX90640 EEPROM is in the address range 0x2400 to 0x273F and the MLX90640 RAM is in the address range 0x0400 to 0x073F.
// - uint16_t nMemAddressRead – Number of 16-bits words to be read from the MLX90640 memory
// - uint16_t *data – pointer to the MCU memory location where the user wants the data to be stored
// TODO: Add error check (return -1)
int MLX90640_I2CRead(uint8_t slaveAddr,uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *data)
{
    Wire.beginTransmission(slaveAddr);
    Wire.write((uint8_t*)&startAddress, 2);
    Wire.endTransmission();
    Wire.requestFrom(slaveAddr, nMemAddressRead*2);


    Wire.readBytes((uint8_t*)data, nMemAddressRead*2);

    // uint16_t buff;
    // for (uint16_t i = 0; i < nMemAddressRead; i++)
    // {
    //     buff = Wire.read() << 8;
    //     buff |= Wire.read();

    //     memcpy(data+i, &buff, 2);
    // }
    return 0;
}

// This function writes a 16-bit value to a desired memory address of a selected MLX90640 device. 
// The function reads back the data after the write operation is done and returns:
//  -    0 if the write was successful
//  -   -1 if NACK occurred during the communication
//  -   -2 if the data in the memory is not the same as the intended one.
// 
//  -   uint8_t slaveAddr – Slave address of the MLX90640 device (the default slave address is 0x33)
//  -   uint16_t writeAddress – The MLX90640 memory address to write data to
//  -   uint16_t data - Data to be written in the MLX90640 memory address
int MLX90640_I2CWrite(uint8_t slaveAddr,uint16_t writeAddress, uint16_t data)
{
    Wire.beginTransmission(slaveAddr);
    Wire.write((uint8_t*)&writeAddress, 2);
    
    Wire.write((uint8_t*)&data, 2);
    uint8_t status = Wire.endTransmission();
    
    switch (status)
    {
        // No fault
        case 0:
            break;
        
        // Data too long to fit in buffer
        case 1:
            return -2;
            break;
        
        // Received NACK on transmit of address.
        case 2:
            return -1;
            break; 
       
        // Received NACK on transmit of data.
        case 3:
            return -1;
            break;
        
        // Other error occured
        default:
            return -3;
            break;
    }

    Wire.requestFrom(slaveAddr, (uint8_t)2);

    uint16_t readback;
    Wire.readBytes((uint8_t*)&readback, 2);

    if(readback == data)
        return 0;
    else
        return -2;
}

// This function sets the I2C frequency in kHz.
void MLX90640_I2CFreqSet(int freq)
{
    Wire.setClock(freq*1000);

}
