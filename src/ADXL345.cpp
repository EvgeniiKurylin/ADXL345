#include "ADXL345.h"
#include <cstdint>
#include <cstdio>

/* ADXL345 Registers */
uint8_t constexpr ADXL345::REGISTER_DEVID             ;     // R            Device ID
uint8_t constexpr ADXL345::REGISTER_THRESH_TAP        ;     // R/W          Tap threshold
uint8_t constexpr ADXL345::REGISTER_OFSX              ;     // R/W          X-axis offset
uint8_t constexpr ADXL345::REGISTER_OFSY              ;     // R/W          Y-axis offset
uint8_t constexpr ADXL345::REGISTER_OFSZ              ;     // R/W          Z-axis offset
uint8_t constexpr ADXL345::REGISTER_DUR               ;     // R/W          Tap duration
uint8_t constexpr ADXL345::REGISTER_LATENT            ;     // R/W          Tap latency
uint8_t constexpr ADXL345::REGISTER_WINDOW            ;     // R/W          Tap window
uint8_t constexpr ADXL345::REGISTER_THRESH_ACT        ;     // R/W          Activity threshold
uint8_t constexpr ADXL345::REGISTER_THRESH_INACT      ;     // R/W          Inactivity threshold
uint8_t constexpr ADXL345::REGISTER_TIME_INACT        ;     // R/W          Inactivity time
uint8_t constexpr ADXL345::REGISTER_ACT_INACT_CTL     ;     // R/W          Axis enable control for activity and inactivity detection
uint8_t constexpr ADXL345::REGISTER_THRESH_FF         ;     // R/W          Free-fall threshold
uint8_t constexpr ADXL345::REGISTER_TIME_FF           ;     // R/W          Free-fall time
uint8_t constexpr ADXL345::REGISTER_TAP_AXES          ;     // R/W          Axis control for tap/double tap
uint8_t constexpr ADXL345::REGISTER_ACT_TAP_STATUS    ;     // R            Source of tap/double tap
uint8_t constexpr ADXL345::REGISTER_BW_RATE           ;     // R/W          Data rate and power mode control
uint8_t constexpr ADXL345::REGISTER_POWER_CTL         ;     // R/W          Power-saving features control
uint8_t constexpr ADXL345::REGISTER_INT_ENABLE        ;     // R/W          Interrupt enable control
uint8_t constexpr ADXL345::REGISTER_INT_MAP           ;     // R/W          Interrupt mapping control
uint8_t constexpr ADXL345::REGISTER_INT_SOURCE        ;     // R            Source of interrupts
uint8_t constexpr ADXL345::REGISTER_DATA_FORMAT       ;     // R/W          Data format control
uint8_t constexpr ADXL345::REGISTER_DATAX0            ;     // R            X-Axis Data 0
uint8_t constexpr ADXL345::REGISTER_DATAX1            ;     // R            X-Axis Data 1
uint8_t constexpr ADXL345::REGISTER_DATAY0            ;     // R            Y-Axis Data 0
uint8_t constexpr ADXL345::REGISTER_DATAY1            ;     // R            Y-Axis Data 1
uint8_t constexpr ADXL345::REGISTER_DATAZ0            ;     // R            Z-Axis Data 0
uint8_t constexpr ADXL345::REGISTER_DATAZ1            ;     // R            Z-Axis Data 1
uint8_t constexpr ADXL345::REGISTER_FIFO_CTL          ;     // R/W          FIFO control
uint8_t constexpr ADXL345::REGISTER_FIFO_STATUS       ;     // R            FIFO status

/* Constructors */
ADXL345::ADXL345(I2C * busI2C, uint8_t addr)
 : _i2c(busI2C),
   _address(addr)
{

}

ADXL345::~ADXL345(){
    delete this;
}

/* Public functions */
bool ADXL345::init(){
    return init(WHO_AM_I_CODE);
}

xyzFloat ADXL345::getAcceleration(){
    return readAcceleration();
}

void ADXL345::calibrate(){
    printf("Calibration...\r\n");
    // Reset offsets : Register 0x1E, Register 0x1F, Register 0x20 — OFSX, OFSY, OFSZ (Read/Write) → 0x00
    writeRegister(REGISTER_OFSX, 0x00);
    writeRegister(REGISTER_OFSY, 0x00);
    writeRegister(REGISTER_OFSZ, 0x00);

    // Collect N measurement
    // Calculate the average values for each axis
    int N = 420;
    int n = 0;
    xyzFloat accSum(0,0,0);

    xyzFloat mes;
    for (int i=0; i<N; ++i) {
        mes = readAcceleration();
        if (i >= 20) {
            accSum += mes;
            ++n;
        }
        wait_us(10e3);
    }

    xyzFloat offset;
    offset = accSum/n;

    uint8_t offX = -1 *  offset.x    * 1000 / 15.6;
    uint8_t offY = -1 *  offset.y    * 1000 / 15.6;
    uint8_t offZ = -1 * (offset.z-1) * 1000 / 15.6;

    printf("Finished\r\n");
    printf("Calibration parameters: [%d, %d, %d]\r\n", offX, offY, offZ);

    setOffsets(offX, offY, offZ);
}

void ADXL345::setCalibrationParameters(uint8_t OFX, uint8_t OFY, uint8_t OFZ){
    setOffsets(OFX, OFY, OFZ);
}

/* Protected functions */
bool ADXL345::init(uint8_t expectedValue){
    // Standby mode: Register 0x2D—POWER_CTL → 0x00
    writeRegister(REGISTER_POWER_CTL, 0x00);
    // Verify device ID (should be 0xE5) : Register 0x00—DEVID (Read Only)
    if (whoAmI() != expectedValue) {
        return false;
    }
    // Pass to normal operation and set data rate to max (3600 Hz) : Register 0x2C—BW_RATE → 0x0F
    writeRegister(REGISTER_BW_RATE, 0x0F);
    // Set data format (full resolution, right justify, 16g range) : Register 0x31—DATA_FORMAT → 0x0B
    writeRegister(REGISTER_DATA_FORMAT, 0x0B);
    // Set FIFO stream mode : Register 0x38—FIFO_CTL → 0x80
    writeRegister(REGISTER_FIFO_CTL, 0x80);
    // Get scale parameter : from Register 0x31—DATA_FORMAT
    updateScale();
    // Switch to Stream mode (measurements) : Register 0x2D—POWER_CTL → 0x08
    writeRegister(REGISTER_POWER_CTL, 0x08);
    return true;
}

uint8_t ADXL345::whoAmI(){
    return readRegister8(REGISTER_DEVID);
}

uint8_t ADXL345::readRegister8(uint8_t reg){
    char requiredReg[1] = {reg};
    _i2c->write(ADXL345_WRITE_ADDR, requiredReg, 1, false);

    char recievedData[1];
    _i2c->read(ADXL345_READ_ADDR, recievedData, 1, false);

    return recievedData[0];
}

void ADXL345::writeRegister(uint8_t reg, uint8_t val){
    char msg[2] = {reg, val};
    _i2c->write(ADXL345_WRITE_ADDR, msg, 2, false);
    wait_us(5e2);
}

/* Private functions */
void ADXL345::updateScale(){
    char actualDataFormat = readRegister8(REGISTER_DATA_FORMAT);
    char fullResolution = (actualDataFormat >> 3) & 1;
    char range = actualDataFormat & 3;
    _scale =  (int)(1 << ((1 - fullResolution) * range)) * 3.9 / 1000;
}

void ADXL345::setOffsets(uint8_t OFX, uint8_t OFY, uint8_t OFZ){
    // Write result to offset registers
    writeRegister(REGISTER_OFSX, OFX);
    writeRegister(REGISTER_OFSY, OFY);
    writeRegister(REGISTER_OFSZ, OFZ);
    wait_us(100e3);
}

xyzFloat ADXL345::readAcceleration(){
    xyzFloat measurement;
    char request[1] = {REGISTER_DATAX0};
    _i2c->write(ADXL345_WRITE_ADDR, request, 1, false);

    char recievedData[6];
    _i2c->read(ADXL345_READ_ADDR, recievedData, 6, false);

    measurement.x = (int16_t)((recievedData[1] << 8) | recievedData[0]) * _scale;
    measurement.y = (int16_t)((recievedData[3] << 8) | recievedData[2]) * _scale;
    measurement.z = (int16_t)((recievedData[5] << 8) | recievedData[4]) * _scale;

    return measurement;
}

void printByte(char byte) {
  printf("0b");
  for (int i = 7; i >= 0; --i)
    printf("%d", (byte >> i) & 1);
}