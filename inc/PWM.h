/*
 * PWM_h
 *
 *  Created on: 24 ago_ 2019
 *      Author: NicoCampos
 */

#ifndef PWM_H_
#define PWM_H_

//#define FUNC1_PWM		1
//#define FUNC2_PWM		2
//#define FUNC3_PWM		3

// Declaracion de bits para el registro PCR
#define SEL_MR2	2
#define SEL_MR3	3
#define SEL_MR4	4
#define SEL_MR5	5
#define SEL_MR6	6

#define MENA_MR1	9
#define MENA_MR2	10
#define MENA_MR3	11
#define MENA_MR4	12
#define MENA_MR5	13
#define MENA_MR6	14

// Declaracion de bits para el registro LER
#define	LER_MR0	0
#define	LER_MR1	1
#define	LER_MR2	2
#define	LER_MR3	3
#define	LER_MR4	4
#define	LER_MR5	5
#define	LER_MR6	6

// Declaracion de bits para el registro MCR
#define	MR0I	0
#define	MR0R	1
#define	MR0S	2
#define	MR1I	3
#define	MR1R	4
#define	MR1S	5
#define	MR2I	6
#define	MR2R	7
#define	MR2S	8
#define	MR3I	9
#define	MR3R	10
#define	MR3S	11
#define	MR4I	12
#define	MR4R	13
#define	MR4S	14
#define	MR5I	15
#define	MR5R	16
#define	MR5S	17
#define	MR6I	18
#define	MR6R	19
#define	MR6S	20

// Declaracion de pines de salida de PWM1

#define PIN_PWM1_1_P1	1,18,2	// funcion 2
#define PIN_PWM1_1_P2	2,0,1	// funcion 1

#define PIN_PWM1_2_P1	1,20,2	// funcion 2
#define PIN_PWM1_2_P2	2,1,1	// funcion 1
#define PIN_PWM1_2_P3	3,25,3	// funcion 3

#define PIN_PWM1_3_P1	1,21,2	// funcion 2
#define PIN_PWM1_3_P2	2,2,1	// funcion 1
#define PIN_PWM1_3_P3	3,26,3	// funcion 3

#define PIN_PWM1_4_P1	1,23,2	// funcion 2
#define PIN_PWM1_4_P2	2,3,1	// funcion 1

#define PIN_PWM1_5_P1	1,24,2	// funcion 2
#define PIN_PWM1_5_P2	2,4,1	// funcion 1

#define PIN_PWM1_6_P1	1,26,2	// funcion 2
#define PIN_PWM1_6_P2	2,5,1	// funcion 1

#endif /* PWM_H_ */
