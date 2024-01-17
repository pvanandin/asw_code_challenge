# AAC-Clydespace Avionics Software Challenge
You are given the LIS3MDLTR 3-Axis Magnetometer sensor. The data sheet is
located at `doc/lism3mdl.pdf`

## Task Description
You must use the C API defined in `i2c.h` to operate on an I2C bus.

We provide example stub implementations of this API in `i2c.c`. You are free to
extend the provided stub functions for the API.

Please write a device driver that implements the following API:
- Get the full-scale configuration
- Get and set the output data rate
- Enable or disable the interrupt pin
- Read the output data of a specified axis

## API implementation notes
- Get the full-scale configuration by calling `getFullScaleConfig()`
  Full scale configuration of the i2c device shall be read from register address CTRL_REG2 (0x21), at bit positions 5 and 6. So, api is writted to read the 8bit data from this register and mask the bits at these two bits to get the FS configuration. The value read shalle be interpretted as below. 
    0x00 indicates full-scale +/- 4 gauss
    0x01 indicates full-scale +/- 8 gauss
    0x02 indicates full-scale +/- 12 gauss
    0x03 indicates full-scale +/- 16 gauss
- Apis to get and set the output data rate are `getOutputDataRate()` and `setOutputDataRate()`
    output data rate of the i2c device shall be read from register address CTRL_REG1 (0x20), at bit positions 2 to 4. Read the 8bit data from this register and mask the bits at these three positions to get the ODR configuration. Apart from the ODR configuration information, this register also allows X and Y axes operative mode selectiom using bits at position 5 and 6. And, bit 1 refers to FAST_ODR which enables data rates higher than 80 Hz. Refer to section 7.5 in the datasheet (/doc/lis3mdl.pdf) for the different operating modes and output data configuration. Both the get and set apis are written to operate with these three paramaters xyaxes_opmode, odr_config and fastodr_en_status.
- Enable or disable the interrupt pin by calling `enableInterruptPin()` and `disableInterruptPin()`
  Interrupt configuration of the i2c device shall be done by setting bit 0 of register INT_CFG (0x30) with appropriate value (0- disable and 1 to enable the interrupt).
- Read the output data of a specified axis through `readAxisOutputData()`
  Output data of the individual axes (x, y, z) shall be read as Hibyte and low byte vales from two different registers for each each axis. The read api takes index to the axis ()as char value (x, y, z) and the output data value os retured as a two byte unsigned integer. The upper byte of this 16bit integer holds the H byte of the output data and the lower byte holds the L byte value.  
   
## Development
You are provided this minimal repository, `aac-code-challenge`, please perform
your work on branch `<candidate_name>`

Documentation can be found in `aac-code-challenge/doc`

Once complete, please repackage and email back this repo to your interviewers

## Scope
You shouldn't need to spend more than a couple of hours on the task.

This is not a closed book assessment.

## Extra Thoughts
If you have time, answer the following questions:
- What changes you would make to this interfaces for use in an RTOS
environment?
- How might the I2C API be improved
