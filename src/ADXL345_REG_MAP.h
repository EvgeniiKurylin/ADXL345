#ifndef ADXL345_REG_MAP_H
#define ADXL345_REG_MAP_H

#define ADXL345_DEFAULT_ADDR                0xA6

#define ADXL345_DEVID                       0x00    // R            Device ID
                                            // 0x01 - 0x0c  Reserved. Do not access
#define ADXL345_THRESH_TAP                  0x1D    // R/W          Tap threshold
#define ADXL345_OFSX                        0x1E    // R/W          X-axis offset
#define ADXL345_OFSY                        0x1F    // R/W          Y-axis offset
#define ADXL345_OFSZ                        0x20    // R/W          Z-axis offset
#define ADXL345_DUR                         0x21    // R/W          Tap duration
#define ADXL345_LATENT                      0x22    // R/W          Tap latency
#define ADXL345_WINDOW                      0x23    // R/W          Tap window
#define ADXL345_THRESH_ACT                  0x24    // R/W          Activity threshold
#define ADXL345_THRESH_INACT                0x25    // R/W          Inactivity threshold
#define ADXL345_TIME_INACT                  0x26    // R/W          Inactivity time
#define ADXL345_ACT_INACT_CTL               0x27    // R/W          Axis enable control for activity and inactivity detection
#define ADXL345_THRESH_FF                   0x28    // R/W          Free-fall threshold
#define ADXL345_TIME_FF                     0x29    // R/W          Free-fall time
#define ADXL345_TAP_AXES                    0x2A    // R/W          Axis control for tap/double tap
#define ADXL345_ACT_TAP_STATUS              0x2B    // R            Source of tap/double tap
#define ADXL345_BW_RATE                     0x2C    // R/W          Data rate and power mode control
#define ADXL345_POWER_CTL                   0x2D    // R/W          Power-saving features control
#define ADXL345_INT_ENABLE                  0x2E    // R/W          Interrupt enable control
#define ADXL345_INT_MAP                     0x2F    // R/W          Interrupt mapping control
#define ADXL345_INT_SOURCE                  0x30    // R            Source of interrupts
#define ADXL345_DATA_FORMAT                 0x31    // R/W          Data format control
#define ADXL345_DATAX0                      0x32    // R            X-Axis Data 0
#define ADXL345_DATAX1                      0x33    // R            X-Axis Data 1
#define ADXL345_DATAY0                      0x34    // R            Y-Axis Data 0
#define ADXL345_DATAY1                      0x35    // R            Y-Axis Data 1
#define ADXL345_DATAZ0                      0x36    // R            Z-Axis Data 0
#define ADXL345_DATAZ1                      0x37    // R            Z-Axis Data 1
#define ADXL345_FIFO_CTL                    0x38    // R/W          FIFO control
#define ADXL345_FIFO_STATUS                 0x39    // R            FIFO status

#define ADXL345_BW_1600                     0xF     // 1111
#define ADXL345_BW_800                      0xE     // 1110
#define ADXL345_BW_400                      0xD     // 1101  
#define ADXL345_BW_200                      0xC     // 1100
#define ADXL345_BW_100                      0xB     // 1011  
#define ADXL345_BW_50                       0xA     // 1010 
#define ADXL345_BW_25                       0x9     // 1001 
#define ADXL345_BW_12                       0x8     // 1000 
#define ADXL345_BW_6                        0x7     // 0111
#define ADXL345_BW_3                        0x6     // 0110

#define ADXL345_MODE_BYPASS                 0x0 	// 0000
#define ADXL345_MODE_FIFO                   0x1 	// 0001
#define ADXL345_MODE_STREM                  0x2 	// 0010
#define ADXL345_MODE_TRIGGER                0x3 	// 0011

#define ADXL345_RESOLUTION_DEFAULT          0x0     // 0000
#define ADXL345_RESOLUTION_FULL             0x1     // 0001
#define ADXL345_JUSTIFY_RIGHT               0x0     // 0000
#define ADXL345_JUSTIFY_LEFT                0x1     // 0001
#define ADXL345_RANGE_2G                    0x0     // 0000
#define ADXL345_RANGE_4G                    0x1     // 0001
#define ADXL345_RANGE_8G                    0x2     // 0010
#define ADXL345_RANGE_16G                   0x3     // 0011


#define ADXL345_OFFSET_SCALE                15.6    // [mg/LSB]
#define ADXL345_THRESH_TAP_SCALE            62.5    // [mg/LSB]
#define ADXL345_DUR_SCALE                   625     // [us/LSB]
#define ADXL345_LATENT_SCALE                1.25    // [ms/LSB]
#define ADXL345_WINDOW_SCALE                1.25    // [ms/LSB]
#define ADXL345_THRESH_ACT_SCALE            62.5    // [mg/LSB]
#define ADXL345_THRESH_INACT_SCALE          62.5    // [mg/LSB]
#define ADXL345_TIME_INACT_SCALE            1       // [ s/LSB]
#define ADXL345_THRESH_FF_SCALE             62.5    // [mg/LSB]
#define ADXL345_TIME_FF_SCALE               5       // [ms/LSB]





#endif