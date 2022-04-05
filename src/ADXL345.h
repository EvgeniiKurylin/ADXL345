#ifndef ADXL345_H
#define ADXL345_H

#include "mbed.h"
#include "utilities.h"
#include <cstdint>

#define ADXL345_DEFAULT_ADDR        0xA6
#define ADXL345_WRITE_ADDR          _address & 0b11111110
#define ADXL345_READ_ADDR           _address | 0b00000001

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
        ~ADXL345();

        bool init();

        xyzFloat getAcceleration();

        void calibrate();
        void setCalibrationParameters(uint8_t OFX, uint8_t OFY, uint8_t OFZ);
    
    protected:
        bool init(uint8_t expectedValue);
        uint8_t whoAmI();

        uint8_t readRegister8(uint8_t reg);
        void writeRegister(uint8_t reg, uint8_t val);

    private:
        I2C * _i2c;
        uint8_t _address;
        uint8_t _ID;

        xyzFloat _acceleration;
        xyzFloat _offset;

        xyzFloat readAcceleration();
        void setOffsets(uint8_t OFX, uint8_t OFY, uint8_t OFZ);

        float _scale;
        void updateScale();
};

void printByte(char byte);
#endif