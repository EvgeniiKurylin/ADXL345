#ifndef ADXL345_H
#define ADXL345_H

#include "mbed.h"
// #include "ADXL345_REG_MAP.h"
#include <cstdint>

#define ADXL345_DEFAULT_ADDR        0xA6
#define ADXL345_WRITE_ADDR          _address & 0b11111110
#define ADXL345_READ_ADDR           _address | 0b00000001

#define AUTO_SLEEP_MODE             0b00010000
#define STANDBY_MODE                0b00000000
#define MEASUREMENT_MODE            0b00001000
#define SLEEP_MODE                  0b00000100

#define RIGHT_JUSTIFY               (_dataFormat | 0b00000100)
#define LEFT_JUSTIFY                (_dataFormat & 0b11111011)

#define FULL_RES_MODE               (_dataFormat | 0b00001000)
#define BIT10_RES_MODE              (_dataFormat & 0b11110111)

#define RANGE_2G                    (_dataFormat & 0b11111100)
#define RANGE_4G                    ((_dataFormat & 0b11111100) | 0b01)
#define RANGE_8G                    ((_dataFormat & 0b11111100) | 0b10)
#define RANGE_16G                   ((_dataFormat & 0b11111100) | 0b11)

#define FIFO_BYPASS                 (_fifoMode & 0b00111111)
#define FIFO_FIFO                   ((_fifoMode & 0b00111111) | 0b01000000)
#define FIFO_STREAM                 ((_fifoMode & 0b00111111) | 0b10000000)
#define FIFO_TRIGGER                ((_fifoMode & 0b00111111) | 0b11000000)

struct xyzAcc{
    float x;
    float y;
    float z;
};


class ADXL345{
    public:
        // Registers
        static uint8_t constexpr REGISTER_DEVID             = 0x00;     // R            Device ID
        static uint8_t constexpr REGISTER_THRESH_TAP        = 0x1D;     // R/W          Tap threshold
        static uint8_t constexpr REGISTER_OFSX              = 0x1E;     // R/W          X-axis offset
        static uint8_t constexpr REGISTER_OFSY              = 0x1F;     // R/W          Y-axis offset
        static uint8_t constexpr REGISTER_OFSZ              = 0x20;     // R/W          Z-axis offset
        static uint8_t constexpr REGISTER_DUR               = 0x21;     // R/W          Tap duration
        static uint8_t constexpr REGISTER_LATENT            = 0x22;     // R/W          Tap latency
        static uint8_t constexpr REGISTER_WINDOW            = 0x23;     // R/W          Tap window
        static uint8_t constexpr REGISTER_THRESH_ACT        = 0x24;     // R/W          Activity threshold
        static uint8_t constexpr REGISTER_THRESH_INACT      = 0x25;     // R/W          Inactivity threshold
        static uint8_t constexpr REGISTER_TIME_INACT        = 0x26;     // R/W          Inactivity time
        static uint8_t constexpr REGISTER_ACT_INACT_CTL     = 0x27;     // R/W          Axis enable control for activity and inactivity detection
        static uint8_t constexpr REGISTER_THRESH_FF         = 0x28;     // R/W          Free-fall threshold
        static uint8_t constexpr REGISTER_TIME_FF           = 0x29;     // R/W          Free-fall time
        static uint8_t constexpr REGISTER_TAP_AXES          = 0x2A;     // R/W          Axis control for tap/double tap
        static uint8_t constexpr REGISTER_ACT_TAP_STATUS    = 0x2B;     // R            Source of tap/double tap
        static uint8_t constexpr REGISTER_BW_RATE           = 0x2C;     // R/W          Data rate and power mode control
        static uint8_t constexpr REGISTER_POWER_CTL         = 0x2D;     // R/W          Power-saving features control
        static uint8_t constexpr REGISTER_INT_ENABLE        = 0x2E;     // R/W          Interrupt enable control
        static uint8_t constexpr REGISTER_INT_MAP           = 0x2F;     // R/W          Interrupt mapping control
        static uint8_t constexpr REGISTER_INT_SOURCE        = 0x30;     // R            Source of interrupts
        static uint8_t constexpr REGISTER_DATA_FORMAT       = 0x31;     // R/W          Data format control
        static uint8_t constexpr REGISTER_DATAX0            = 0x32;     // R            X-Axis Data 0
        static uint8_t constexpr REGISTER_DATAX1            = 0x33;     // R            X-Axis Data 1
        static uint8_t constexpr REGISTER_DATAY0            = 0x34;     // R            Y-Axis Data 0
        static uint8_t constexpr REGISTER_DATAY1            = 0x35;     // R            Y-Axis Data 1
        static uint8_t constexpr REGISTER_DATAZ0            = 0x36;     // R            Z-Axis Data 0
        static uint8_t constexpr REGISTER_DATAZ1            = 0x37;     // R            Z-Axis Data 1
        static uint8_t constexpr REGISTER_FIFO_CTL          = 0x38;     // R/W          FIFO control
        static uint8_t constexpr REGISTER_FIFO_STATUS       = 0x39;     // R            FIFO status

        // Register values
        static uint8_t constexpr WHO_AM_I_CODE              = 0xE5;

        ADXL345(I2C * busI2C, uint8_t addr = ADXL345_DEFAULT_ADDR);

        bool init();

        xyzAcc getAcceleration();

        void calibrate();
        
        // void powerOn();
        // bool ping();

        // void setMode(uint8_t mode);
        // void setBandWigth(uint8_t bw);

        // void setResolution(uint8_t res);
        // void setJusifyBit(uint8_t jBit);
        // void setRange(uint8_t range);

        // void readXYZ(float* accX, float* accY, float* accZ);

        

        // void updateMeasurement();

        // void printAllRegister();
    
    protected:
        bool init(uint8_t expectedValue);
        uint8_t whoAmI();

        uint8_t readRegister8(uint8_t reg);
        void writeRegister(uint8_t reg, uint8_t val);

    private:
        I2C * _i2c;
        uint8_t _address;
        uint8_t _ID;

        xyzAcc _acceleration;
        xyzAcc _offset;

        xyzAcc readAcceleration();
        void setOffsets(xyzAcc offset);

        float _scale;
        void updateScale();
};

void printByte(char byte);

#endif