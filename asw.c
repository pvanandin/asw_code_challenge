#include "asw.h"

// Api to  Get the full-scale configuration
status_t getFullScaleConfig(uint8_t *p_fsconfig)
{
	status_t status = STATUS_OK;
	uint8_t buffer = 0;
	
	if (p_fsconfig == NULL)
		return STATUS_ERROR;
	
	status = i2c_read(I2C_SAD_READ_ADDRESS_1, CTRL_REG2, REG_DATA_SIZE, &buffer);
	if (status == STATUS_OK)
	{
	    printf("in getFullScaleConfig() buffer = 0x%x \n", buffer);
		*p_fsconfig = GET_FS_CONFIG(buffer);
	}
	else
	{
		*p_fsconfig = 0xFF;
	}
	
	printf("in getFullScaleConfig() fs_config = 0x%x \n", *p_fsconfig);
	
	return status;
}

// Api to Get the output data rate
status_t getOutputDataRate(uint8_t *p_xyaxes_opmode, uint8_t *p_odr_config, uint8_t *p_fastodr_en_status)
{
	status_t status = STATUS_OK;
	uint8_t buffer = 0;
	
	if (p_xyaxes_opmode == NULL || p_odr_config == NULL || p_fastodr_en_status == NULL)
		return STATUS_ERROR;
	
	status = i2c_read(I2C_SAD_READ_ADDRESS_1, CTRL_REG1, REG_DATA_SIZE, &buffer);
	if (status == STATUS_OK)
	{
	    printf("in getOutputDataRate() buffer = 0x%x \n", buffer);
		*p_xyaxes_opmode = GET_XY_AXES_OPMODE(buffer);
		*p_odr_config = GET_ODR(buffer);
		*p_fastodr_en_status = GET_FAST_ODR(buffer);
	}
	else
	{
		*p_xyaxes_opmode = 0xFF;
		*p_fastodr_en_status = 0xFF;
		*p_odr_config = 0xFF;
	}
	
	printf("in getOutputDataRate() xyaxes_opmode = 0x%x \n", *p_xyaxes_opmode);
	printf("in getOutputDataRate() p_odr_config = 0x%x \n", *p_odr_config);
	printf("in getOutputDataRate() fastodr_en_status = 0x%x \n", *p_fastodr_en_status);
	
	return status;
}

// Api to set the output data rate
status_t setOutputDataRate(uint8_t xyaxes_opmode, uint8_t odr_config, uint8_t fastodr_en_status)
{
	status_t status = STATUS_OK;
	uint8_t buffer = 0;
	
	buffer = SET_XY_AXES_OPMODE(buffer, xyaxes_opmode);
	printf("in setOutputDataRate() buffer = 0x%x xyaxes_opmode = 0x%x \n", buffer, xyaxes_opmode);
	
	buffer = SET_ODR(buffer, odr_config);
	printf("in setOutputDataRate() buffer = 0x%x  odr_config = 0x%x \n", buffer, odr_config);
	
	buffer = SET_FAST_ODR(buffer, fastodr_en_status);
	printf("in setOutputDataRate() buffer = 0x%x fastodr_en_status = 0x%x \n", buffer, fastodr_en_status);
	
	status = i2c_write(I2C_SAD_READ_ADDRESS_1, CTRL_REG1, REG_DATA_SIZE, &buffer);
	if (status == STATUS_OK)
	{
	    printf("in setOutputDataRate() buffer = 0x%x \n", buffer);
	}
	
	return status;
}

// Api to enable the interrupt pin
status_t enableInterruptPin(void)
{
	status_t status = STATUS_OK;
	uint8_t buffer = 0, IEN_status = 1;
	
	buffer = SET_IEN_STATUS(buffer, 1);
	printf("in enableInterruptPin() buffer = 0x%x IEN_status = 0x%x \n", buffer, IEN_status);
	
	status = i2c_write(I2C_SAD_READ_ADDRESS_1, INTR_CFG, REG_DATA_SIZE, &buffer);
	if (status == STATUS_OK)
	{
	    printf("in enableInterruptPin() buffer = 0x%x \n", buffer);
	}
	
	return status;	
}

// Api to disable the interrupt pin
status_t disableInterruptPin(void)
{
	status_t status = STATUS_OK;
	uint8_t buffer = 0, IEN_status = 0;
	
	buffer = SET_IEN_STATUS(buffer, 0);
	printf("in disableInterruptPin() buffer = 0x%x IEN_status = 0x%x \n", buffer, IEN_status);
	
	status = i2c_write(I2C_SAD_READ_ADDRESS_1, INTR_CFG, REG_DATA_SIZE, &buffer);
	if (status == STATUS_OK)
	{
	    printf("in disableInterruptPin() buffer = 0x%x \n", buffer);
	}
	
	return status;	
}

//Api to read the output data of a specified axis
status_t readAxisOutputData(char axis_index, uint16_t *p_axis_data)
{
	status_t status = STATUS_OK;
	uint8_t buffer = 0, reg_addr_out_L, reg_addr_out_H;
	uint16_t axis_out_data = 0;
	
	if (p_axis_data == NULL)
		return STATUS_ERROR;
	
	printf("in readAxisOutputData() axis_index = %c \n", axis_index);
	
	switch (axis_index)
	{
		case 'x':
		case 'X':
			reg_addr_out_L = OUT_X_L;
			reg_addr_out_H = OUT_X_H;
			break;
		
		case 'y':
		case 'Y':
			reg_addr_out_L = OUT_Y_L;
			reg_addr_out_H = OUT_Y_H;
			break;
		
		case 'z':
		case 'Z':
			reg_addr_out_L = OUT_Z_L;
			reg_addr_out_H = OUT_Z_H;
			break;
		
		default:
			printf("in readAxisOutputData() invalid axis_index = %c \n", axis_index);
			return STATUS_ERROR;
	}
	
	status = i2c_read(I2C_SAD_READ_ADDRESS_1, reg_addr_out_H, REG_DATA_SIZE, &buffer);
	if (status != STATUS_OK)
		return STATUS_ERROR;
	
	printf("in readAxisOutputData() H buffer = 0x%x \n", buffer);
	
	axis_out_data = (buffer << 8);
	printf("in readAxisOutputData() H axis_out_data = 0x%x \n", axis_out_data);

	status = i2c_read(I2C_SAD_READ_ADDRESS_1, reg_addr_out_L, REG_DATA_SIZE, &buffer);
	if (status != STATUS_OK)
		return STATUS_ERROR;
	
	printf("in readAxisOutputData() L buffer = 0x%x \n", buffer);
	
	axis_out_data |= buffer;
	printf("in readAxisOutputData() H | L axis_out_data = 0x%x \n", axis_out_data);
	
	*p_axis_data = axis_out_data;
	
	printf("in readAxisOutputData() *p_axis_data = 0x%x \n", *p_axis_data);
	
	return status;
}
