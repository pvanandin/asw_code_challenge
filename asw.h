#ifndef ASW_HEADER_H
#define ASW_HEADER_H

#include <stdio.h>
#include <stdint.h>
#include "i2c.h"

//I2C slave devide (SAS) address
#define I2C_SAD_READ_ADDRESS_1 0x39
#define I2C_SAD_WRITE_ADDRESS_1 0x38
#define I2C_SAD_READ_ADDRESS_2 0x3D
#define I2C_SAD_WRITE_ADDRESS_2 0x3C

//Register Data size
#define REG_DATA_SIZE 1 /* in bytes */

//Register addresses 
#define CTRL_REG1 (0x20)
#define CTRL_REG2 (0x21)
#define INTR_CFG (0x30)
#define OUT_X_L (0x28)
#define OUT_X_H (0x29)
#define OUT_Y_L (0x2A)
#define OUT_Y_H (0x2B)
#define OUT_Z_L (0x2C)
#define OUT_Z_H (0x2D)

//Register mappings 
#define REG_ADDRESS_FS_CONFIG CTRL_REG1
#define REG_ADDRESS_ODR CTRL_REG2
#define REG_ADDRESS_IEN INTR_CFG
#define REG_ADDRESS_OUT_X_L OUT_X_L
#define REG_ADDRESS_OUT_X_H OUT_X_H
#define REG_ADDRESS_OUT_Y_L OUT_Y_L
#define REG_ADDRESS_OUT_Y_H OUT_Y_H
#define REG_ADDRESS_OUT_Z_L OUT_Z_L
#define REG_ADDRESS_OUT_Z_H OUT_Z_H

#define BITMASK_FS_CONFIG (0x60)
#define BITMASK_FAST_ODR (0x02)
#define BITMASK_ODR (0x1C)
#define BITMASK_XY_AXES_OPMODE (0x60)
#define BITMASK_IEN (0x01)

#define GET_FS_CONFIG(_X_) ((_X_ & BITMASK_FS_CONFIG) >> 5)

#define GET_FAST_ODR(_X_) ((_X_ & BITMASK_FAST_ODR) >> 1)
#define GET_ODR(_X_) ((_X_ & BITMASK_ODR) >> 2)
#define GET_XY_AXES_OPMODE(_X_) ((_X_ & BITMASK_XY_AXES_OPMODE) >> 5)

#define SET_FAST_ODR(_BUFFER_, _FAST_ODR_) ( (_FAST_ODR_ << 1) | _BUFFER_ )
#define SET_ODR(_BUFFER_, _ODR_) ((_ODR_ << 2) | _BUFFER_)
#define SET_XY_AXES_OPMODE(_BUFFER_, _OPMODE_) ((_OPMODE_ << 5) | _BUFFER_)

#define GET_IEN_STATUS(_X_) (_X_ & BITMASK_IEN)
#define SET_IEN_STATUS(_X_) (_X_ | BITMASK_IEN)

#endif