#include "mbed.h"
#include "ADXL345.h"
#include <cstdint>
#include <cstdio>

/* 
ADXL345 -  0xA6 — Three axis acceleration 
*/

Serial  pc(USBTX, USBRX, 115200);   // TX,  RX, baudrate
I2C     i2c(PA_10, PA_9);           // SDA, SCL

ADXL345 adxl345_dev(&i2c);

// main() runs in its own thread in the OS
int main()
{
    if (adxl345_dev.init()) {
        printf("\nADXL345 is detected\r\n");
        // adxl345_dev.calibrate();     // last calibration result : [0, 1, -11]
        adxl345_dev.setCalibrationParameters(0, 1, -11);
    }
    else {
        printf("\nADXL345 isn't found\r\n");
    }

    // Measurement in [g] -> 9.81 [m/s^2]
    xyzFloat acc;

    while (true) {
        acc = adxl345_dev.getAcceleration();
        printf("accX: %.2f\taccY: %.2f\taccZ: %.2f\r\n", acc.x, acc.y, acc.z);
        wait_us(50e3);
    }
}

