/*******************************************************************************************************************************//**
 *
 * @file		AP_funciones.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		23 nov. 2020
 * @author		Taurozzi Nicolás
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef ADC_DR_ADC_H_
#define ADC_DR_ADC_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/

#include"DR_tipos.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define		ADC_BUFF_SIZE	32

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define		ADC_BASE		((volatile ADC_per_t *)(0x40034000))

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
typedef struct {
	uint32_t SEL :8;
	uint32_t CLKDIV :8;
	uint32_t BURST :1;
	uint32_t RESERVED_1 :4;
	uint32_t PDN :1;
	uint32_t RESERVED_2 :2;
	uint32_t START :3;
	uint32_t EDGE :1;
	uint32_t RESERVED_3 :4;
} ADCR_reg_t;

typedef struct {
	uint32_t RESERVED_1 :4;
	uint32_t RESULT :12;
	uint32_t RESERVED_2 :8;
	uint32_t CHN :3;
	uint32_t RESERVED_3 :3;
	uint32_t OVERRUN :1;
	uint32_t DONE :1;
} ADGDR_reg_t;

typedef struct {
	uint32_t ADINTEN0 :1;
	uint32_t ADINTEN1 :1;
	uint32_t ADINTEN2 :1;
	uint32_t ADINTEN3 :1;
	uint32_t ADINTEN4 :1;
	uint32_t ADINTEN5 :1;
	uint32_t ADINTEN6 :1;
	uint32_t ADINTEN7 :1;
	uint32_t ADGINTEN :1;
	uint32_t RESERVED_1 :23;
} ADINTEN_reg_t;

typedef struct {
	uint32_t RESERVED_1 :4;
	uint32_t RESULT :12;
	uint32_t RESERVED_2 :14;
	uint32_t OVERRUN :1;
	uint32_t DONE :1;
} ADDR_reg_t;

typedef struct {
	uint32_t DONE0 :1;
	uint32_t DONE1 :1;
	uint32_t DONE2 :1;
	uint32_t DONE3 :1;
	uint32_t DONE4 :1;
	uint32_t DONE5 :1;
	uint32_t DONE6 :1;
	uint32_t DONE7 :1;
	uint32_t OVERRUN0 :1;
	uint32_t OVERRUN1 :1;
	uint32_t OVERRUN2 :1;
	uint32_t OVERRUN3 :1;
	uint32_t OVERRUN4 :1;
	uint32_t OVERRUN5 :1;
	uint32_t OVERRUN6 :1;
	uint32_t OVERRUN7 :1;
	uint32_t ADINT :1;
	uint32_t RESERVED_1 :15;
} ADSTAT_reg_t;

typedef struct {
	uint32_t RESERVED_1 :4;
	uint32_t ADCOFFS :4;
	uint32_t TRIM :4;
	uint32_t RESERVED_2 :20;
} ADTRM_reg_t;

typedef struct {
	volatile ADCR_reg_t ADCR;
	volatile ADGDR_reg_t ADGDR;
	volatile uint32_t RESERVED_1;
	volatile ADINTEN_reg_t ADINTEN;
	volatile ADDR_reg_t ADDR[8];
	volatile ADSTAT_reg_t ADSTAT;
	volatile ADTRM_reg_t ADTRM;
} ADC_per_t;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
//static volatile uint32_t ADC_buffer[4095];
//static volatile uint32_t ADC_buffer_index = 0;
//static volatile uint32_t ADC_average = 0;
/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

void ADC_init(void);

void ADC_start_conversion(void);

uint32_t ADC_get_average(void);

uint32_t temp (void);

void TimeADC(void);

#endif /* ADC_DR_ADC_H_ */

