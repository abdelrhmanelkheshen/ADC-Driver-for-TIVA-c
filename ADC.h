/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC.h
 *
 * Description: Header file for ADC .
 *
 * Author: Abdelrhman Hesham
 ******************************************************************************/


#ifndef ADC_H_
#define ADC_H_

#include "Std_Types.h"


#define ENABLE_ADC0_CLOCK  (0x1)
#define ENABLE_ADC1_CLOCK  (0x2)
#define SS2_DURING_CONFIG  (0x4)
#define SOFTWARE_TRIGGER_CONFERSION  (0xF00)
#define TIMER_TRIGGER_CONFERSION_SEQ  (0x5000)
#define SET_FLAG_AT_TIME  (0x6)
#define UN_MASK_ADC0  (1 << 3)
#define ADC0_SEQUENCER2 (0x4)
#define ADC1_SEQUENCER2 (0x4)
#define INPUT_FROM_CHANNEL0 (0x00)   
#define ENABLE_PSSI (0x04)
#define ENABLE_PSSI_1 (0x04)


/*/
tyedef enum{
    PE3,
    PE2,
    PE1,
    PE0,
    PD3,
    PD2,
    PD1,
    PD0,
    PE5,
    PE4,
    PB4,
    PB5

}ADC_PIN_ID;
  
*/



typedef enum{
    ADC0,
    ADC1
}ADC_ID;




typedef struct 
 {
   ADC_ID ADC_num ;     //ADC 0 OR ADC 1 
 // ADC_PIN_ID ADC_port ;  // PORT ON ADC 
}ADC_configuration ;



// void ADC_PinInit(ADC_PIN_ID PIN);
void ADC_Init(ADC_configuration* ptr2config);
uint32 ADC_Value_PE2(ADC_configuration* ptr2config) ; 
uint32 ADC_Value(ADC_configuration* ptr2config, uint16 channel) ;
 


#endif 
