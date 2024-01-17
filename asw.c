#include "asw.h"

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

status_t enableInterruptPin(void)
{
	status_t status = STATUS_OK;
	uint8_t buffer = 0, IEN_status = 1;
	
	buffer = SET_IEN_STATUS(buffer, 1);
	printf("in setOutputDataRate() buffer = 0x%x IEN_status = 0x%x \n", buffer, IEN_status);
	
	status = i2c_write(I2C_SAD_READ_ADDRESS_1, INTR_CFG, REG_DATA_SIZE, &buffer);
	if (status == STATUS_OK)
	{
	    printf("in enableInterruptPin() buffer = 0x%x \n", buffer);

	}
	
	return status;	
}

status_t disableInterruptPin(void)
{
	status_t status = STATUS_OK;
	uint8_t buffer = 0, IEN_status = 0;
	
	buffer = SET_IEN_STATUS(buffer, 0);
	printf("in setOutputDataRate() buffer = 0x%x IEN_status = 0x%x \n", buffer, IEN_status);
	
	status = i2c_write(I2C_SAD_READ_ADDRESS_1, INTR_CFG, REG_DATA_SIZE, &buffer);
	if (status == STATUS_OK)
	{
	    printf("in enableInterruptPin() buffer = 0x%x \n", buffer);

	}
	
	return status;	
}
