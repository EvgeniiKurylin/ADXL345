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

    if (adxl345.init()) {
        printf("\nADXL345 is detected\r\n");
        // adxl345.calibrate();
        adxl345.setCalibrationParameters(0, 0, -12);
    }
    else {
        printf("ADXL345 isn't found\r\n");
    }

    xyzFloat acc;

    while (true) {
        acc = adxl345.getAcceleration();
        printf("accX: %.2f\taccY: %.2f\taccZ: %.2f\r\n", acc.x, acc.y, acc.z);
        wait_us(10e3);
    }
}

