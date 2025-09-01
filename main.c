// Program Name: L298N 12v Dual Motor PWM Driver with TI's MSP430FR5969
// Author: Fayyaz Nisar Shaikh
// Date: 30th August 2025
// Email: fayyaz.shaikh7862005@gmail.com
// LinkedIn: https://www.linkedin.com/in/fayyaz-shaikh-7646312a3/



#include <msp430.h>

void motorA_pwm(unsigned char dir, unsigned int duty);
void motorB_pwm(unsigned char dir, unsigned int duty);
void motorA_control(unsigned char cmd);
void motorB_control(unsigned char cmd);

void delay_cycles_var(unsigned int cycles) {
    while (cycles--) {
        __no_operation();   
    }
}



int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

  CSCTL0_H = CSKEY_H;                   // Unlock CS Registers for clock speed configuration
  CSCTL1 = DCOFSEL_0;
  CSCTL2 = SELS__DCOCLK | SELM__DCOCLK;
  CSCTL3 = DIVS__1 | DIVS__1;
  CSCTL0_H = 0;                             // Lock the CS Registers again

  PM5CTL0 &= ~LOCKLPM5; 


  P1DIR |= BIT2 | BIT3 | BIT0;
  P1SEL0 |= BIT2 | BIT3;

  P1SEL1 &= ~(BIT2 | BIT3);

  P3DIR |= BIT0;
  P1DIR |= BIT6 | BIT7 | BIT4;

  P3OUT &= ~BIT0;
  P1OUT &= ~(BIT6 | BIT7 | BIT4);

  TA0CCR0 = 1000 -1;

  TA0CCTL1 = OUTMOD_7;
  TA0CCR1 = 0;

  TA0CCTL2 = OUTMOD_7;
  TA0CCR2 = 0;

  TA0CTL = TASSEL_2 | MC_1 | TACLR;

  TA0CCR1 = 1000;
  TA0CCR2 = 1000;
unsigned int i;

  while(1)
  {
    
    
    motorA_control(1); // forward
    motorB_control(1);
    __delay_cycles(2000000);

    motorA_control(0); // stop
    motorB_control(0);
    __delay_cycles(2000000);


    motorA_control(3); // right
    motorB_control(3);
    __delay_cycles(2000000);

    motorA_control(0); // stop
    motorB_control(0);
    __delay_cycles(2000000);

    motorA_control(4); // left
    motorB_control(4);
    __delay_cycles(2000000);

    motorA_control(0); // stop
    motorB_control(0);
    __delay_cycles(2000000);

    motorA_control(2); // reverse
    motorB_control(2);
    __delay_cycles(2000000);

    motorA_control(0); // stop
    motorB_control(0);
    __delay_cycles(2000000);


    P1OUT ^= BIT0;                // Toggle LED
    __delay_cycles(100000);
  }
}


void motorA_control(unsigned char cmd){

  switch(cmd){

    case 0:
      P3OUT &= ~BIT0;
      P1OUT &= ~BIT6;
      break; // stop

    case 1: 
      P3OUT |= BIT0;
      P1OUT &= ~BIT6;
      break; // forward

    case 2: 
      P3OUT &= ~BIT0;
      P1OUT |= BIT6;
      break; // backward

    case 3: 
      P3OUT |= BIT0;
      P1OUT &= ~BIT6;
      break; // turn right

    case 4: 
      P3OUT &= ~BIT0;
      P1OUT |= BIT6;
      break; // turn left
  }
}

void motorB_control(unsigned char cmd){

  switch(cmd){

    case 0:
      P1OUT &= ~(BIT7 | BIT4);
      break; // stop

    case 1: 
      P1OUT |= BIT7;
      P1OUT &= ~BIT4;
      break; // forward 
    
    case 2:
      P1OUT &= ~BIT7;
      P1OUT |= BIT4;
      break; // reverse
    
    case 3: 
      P1OUT &= ~BIT7;
      P1OUT |= BIT4;
      break; // turn right

    case 4:
      P1OUT |= BIT7;
      P1OUT &= ~BIT4;
      break; // turn left
  }
}
