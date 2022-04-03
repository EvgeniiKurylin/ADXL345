#include "mbed.h"
#include "ADXL345.h"
#include <cstdint>
#include <cstdio>

/* 
ADXL345 -  0xA6 — Three axis acceleration 
ITG3205  - 0xD0 — Three axis gyroscope
HMC5883L - 0x1E — Three axis magnetic field
*/

Serial  pc(USBTX, USBRX, 115200);   // TX,  RX, baudrate
I2C     i2c(PA_10, PA_9);           // SDA, SCL

ADXL345 adxl345(&i2c);

// main() runs in its own thread in the OS
int main()
{

    // sensor.printAllRegister();
    // BW_RATE
    // sensor.setBandWigth(ADXL345_BW_1600);
    // DATA_FORMAT
    // sensor.setRange(ADXL345_RANGE_2G);
    // sensor.setResolution(ADXL345_RESOLUTION_FULL);
    // sensor.setJusifyBit(ADXL345_JUSTIFY_LEFT);
    // FIFO_CTL
    // sensor.setMode(ADXL345_MODE_STREM);
    // POWER_CTL
    // sensor.powerOn();

    // wait_us(10e3);

    // float accX, accY, accZ;
    // sensor.readXYZ(&accX, &accY, &accZ);
    // pc.printf("accX: %.2f\taccY: %.2f\taccZ: %.2f\r\n", accX, accY, accZ);

    // sensor.updateMeasurement();
    
    // sensor.printAllRegister();
    
    // if(sensor.init()){
        // pc.printf("Sensor is present\r\n");
        // printf("ID = 0x%2X\r\n", sensor.readRegister(DEVID));
        // printf("ID = 0x%2X\r\n", sensor.readDeviceID());
        // printf("TH = %.2f [g]\r\n", sensor.readThreshTap());
        // sensor.updateState();
    // }
    // else    pc.printf("Sensor isn't present\r\n");

    if (adxl345.init()) {
        printf("\nADXL345 is detected\r\n");
        adxl345.calibrate();
    }
    else {
        printf("ADXL345 isn't found\r\n");
    }

    xyzAcc acc;

    while (true) {
        acc = adxl345.getAcceleration();
        printf("accX: %.2f\taccY: %.2f\taccZ: %.2f\r\n", acc.x, acc.y, acc.z);
        wait_us(10e3);
    }
}

