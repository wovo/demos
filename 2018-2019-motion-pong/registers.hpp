
//          Copyright Dylan Griffioen.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef REGISTERS_HPP
#define REGISTERS_HPP

/// @file

/// \brief 
/// this file contains defines for all the registers for the ADXL345 Accelerometer
/// \description
/// DEVID: Device ID
/// THRESH_TAP: Tap threshold
/// OFSX: X-axis offset
/// OFSY: Y-axis offset
/// OFSZ: Z-axis offset
/// DUR: Tap duration
/// LATENT: Tap latency
/// WINDOW: Tap window
/// THRESH_ACT: Activity threshold
/// THRESH_INACT: Inactivity threshold
/// TIME_INACT: Inactivity time
/// ACT_INACT_CTL: Axis enable control for activity and inactivity detection
/// THRESH_FF: Free-fall threshold
/// TIME_FF: Free-fall time
/// TAP_AXES: Axis Control for single tap/double tap
/// ACT_TAP_STATUS: Source of single tap/double tap
/// BW_RATE: Data rate and power mode control
/// POWER_CTL: Power saving features control
/// INT_ENABLE: Interrupt enable control
/// INT_MAP: Interupt mapping control
/// INT_SOURCE: Source of interupts
/// DATA_FORMAT: Data format control
/// DATAX0: X-Axis Data 0
/// DATAX1: X-Axis Data 1
/// DATAY0: Y-Axis Data 0
/// DATAY1: Y-Axis Data 1
/// DATAZ0: Z-Axis Data 0
/// DATAZ1: Z-Axis Data 1
/// FIFO_CTL: FIFO control
/// FIFO_STATUS: FIFO status

#define DEVID           0x00 /// DEVID: Device ID
#define THRESH_TAP      0x1D /// THRESH_TAP: Tap threshold
#define OFSX            0x1E /// OFSX: X-axis offset
#define OFSY            0x1F /// OFSY: Y-axis offset
#define OFSZ            0x20 /// OFSZ: Z-axis offset
#define DUR             0x21 /// DUR: Tap duration
#define LATENT          0x22 /// LATENT: Tap latency
#define WINDOW          0x23 /// WINDOW: Tap window
#define THRESH_ACT      0x24 /// THRESH_ACT: Activity threshold
#define THRESH_INACT    0x25 /// THRESH_INACT: Inactivity threshold
#define TIME_INACT      0x26 /// TIME_INACT: Inactivity time
#define ACT_INACT_CTL   0x27 /// ACT_INACT_CTL: Axis enable control for activity and inactivity detection
#define THRESH_FF       0x28 /// THRESH_FF: Free-fall threshold
#define TIME_FF         0x29 /// TIME_FF: Free-fall time
#define TAP_AXES        0x2A /// TAP_AXES: Axis Control for single tap/double tap
#define ACT_TAP_STATUS  0x2B /// ACT_TAP_STATUS: Source of single tap/double tap
#define BW_RATE         0x2C /// BW_RATE: Data rate and power mode control
#define POWER_CTL       0x2D /// POWER_CTL: Power saving features control
#define INT_ENABLE      0x2E /// INT_ENABLE: Interrupt enable control
#define INT_MAP         0x2F /// INT_MAP: Interupt mapping control
#define INT_SOURCE      0x30 /// INT_SOURCE: Source of interupts
#define DATA_FORMAT     0x31 /// DATA_FORMAT: Data format control
#define DATAX0          0x32 /// DATAX0: X-Axis Data 0
#define DATAX1          0x33 /// DATAX1: X-Axis Data 1
#define DATAY0          0x34 /// DATAY0: Y-Axis Data 0
#define DATAY1          0x35 /// DATAY1: Y-Axis Data 1
#define DATAZ0          0x36 /// DATAZ0: Z-Axis Data 0
#define DATAZ1          0x37 /// DATAZ1: Z-Axis Data 1
#define FIFO_CTL        0x38 /// FIFO_CTL: FIFO control
#define FIFO_STATUS     0x39 /// FIFO_STATUS: FIFO status

#endif
