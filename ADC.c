/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC.c
 *
 * Description: Source file for ADC .
 *
 * Author: Abdelrhman Hesham
 ******************************************************************************/

#include "ADC.h"
#include "TM4C123GH6PM.h"
#include "Common_Macros.h"

volatile uint32 delay = 0;
void ADC_Init(ADC_configuration* ptr2config) 
{
  
  switch(ptr2config->ADC_num)
  {
  case 0 :
    SET_BIT(SYSCTL_RCGCADC_R, 0);          /* enable clock to ADC0 */
    SET_BIT(SYSCTL_RCGC0_R, 16);
    delay = SYSCTL_RCGCADC_R;
    delay  = SYSCTL_RCGCADC_R;
    ADC0_ACTSS_R &= ~ (0x4);             /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~SOFTWARE_TRIGGER_CONFERSION;         /* software trigger conversion */
    //ADC0_EMUX_R |= TIMER_TRIGGER_CONFERSION_SEQ;          /* timer trigger conversion seq 0 */ 
    ADC0_SSCTL2_R |= SET_FLAG_AT_TIME;             /* take one sample at a time, set flag at 1st sample */
    ADC0_IM_R |= UN_MASK_ADC0;          // unmask ADC0 seq 3 interrupt
    ADC0_ACTSS_R |= ADC0_SEQUENCER2;              /* enable ADC0 sequencer 3 */
    ADC0_ISC_R = 0x08;
    break;
  case 1:
    SYSCTL_RCGCADC_R |= ENABLE_ADC1_CLOCK;
    ADC1_ACTSS_R &= ~SS2_DURING_CONFIG;             /* disable SS3 during configuration */
    ADC1_EMUX_R &= ~SOFTWARE_TRIGGER_CONFERSION;           /* software trigger conversion */
    ADC1_EMUX_R |= TIMER_TRIGGER_CONFERSION_SEQ;            /* timer trigger conversion seq 0 */
    ADC1_SSMUX3_R = INPUT_FROM_CHANNEL0;               /* get input from channel 0 */
    ADC1_SSCTL3_R |= SET_FLAG_AT_TIME;              /* take one sample at a time, set flag at 1st sample */
    ADC1_IM_R |= UN_MASK_ADC0;             // unmask ADC1 seq 3 interrupt
    ADC1_ACTSS_R |= ADC1_SEQUENCER2;               /* enable ADC1 sequencer 3 */
    
    
    break ; 
    
  }
  
  
}


/*voltage*/
uint32 ADC_Value(ADC_configuration* ptr2config, uint16 channel) 
{
  uint32 Temp;
  switch(ptr2config->ADC_num)
  {
  case 0:
     ADC0_SSMUX2_R = channel;
     ADC0_PSSI_R |= 0x04;
     while((ADC0_RIS_R & 0x04 )==0) ; 
     Temp = ADC0_SSFIFO2_R ; 
    break ; 
  case 1 :
  
     ADC1_PSSI_R |=0x08;
     while((ADC1_RIS_R & 0x08 )==0) ; 
     Temp = ADC1_SSFIFO3_R ;
     break;
    }
return Temp;
}
/*tempreture sensor */
uint32 ADC_Value_PE2(ADC_configuration* ptr2config) 
{
    uint32 Temp1;
  switch(ptr2config->ADC_num)
  {
  case 0:
  
    ADC0_PSSI_R |= 0x08;    
    while ((ADC0_RIS_R & 0x0) == 0);
    Temp1 = ADC0_SSFIFO3_R;   
      /* ADC0_ISC_R = 0x04  ;    matnsash t3ml clear ll value bel register da b3d ay operation tst5dm feha el value bta3t el adc    */
   
    break ; 
  case 1: 
   
    ADC1_PSSI_R |= ENABLE_PSSI_1;    
    while ((ADC1_RIS_R & ENABLE_PSSI_1) == 0);  
    Temp1 = ADC1_SSFIFO2_R;   
    /* ADC1_ISC_R = 0x04  ;    matnsash t3ml clear ll value bel register da b3d ay operation tst5dm feha el value bta3t el adc    */
    break ; 
    
}
 return Temp1;
}

