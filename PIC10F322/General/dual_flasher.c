/*
 * File:  dual_flasher.c
 * Author: Jamie Starling - GizoFoundry.com 
 *
 * Created on:  September 2, 2021, 7:45 PM
 * 
 * Code provided as-is.
 */

#include <xc.h>
#include <stdint.h>

//Device Configuration
#pragma config FOSC = INTOSC  // Oscillator Selection 
#pragma config BOREN = ON    // Brown-out Reset
#pragma config WDTE = OFF    // Watchdog Timer
#pragma config PWRTE = ON    // Power-up Timer
#pragma config MCLRE = OFF   // MCLR Pin Function Select bit->MCLR pin function is digital input, MCLR internally tied to VDD
#pragma config CP = OFF      // Code Protection 
#pragma config LVP = OFF     // Low-Voltage Programming 
#pragma config LPBOR = ON    // Brown-out Reset Selection bits
#pragma config BORV = LO    // Brown-out Reset Voltage Selection
#pragma config WRT = OFF    // Flash Memory Self-Write Protection

//Used to calculate the delay time - Change depending on processor Speed
#define _XTAL_FREQ 8000000  //8 MHz (default after Reset)

#define DELAY_TIME 1000   //delay time value


//Prototypes
void setup(void);
void blink_led(void);


void main(void)
{
    setup();
    
    while(1)
    {
      blink_led(); 
    }
}

void setup(void)
{
    ANSELAbits.ANSA0 = 0; //Disable Analog A0
    ANSELAbits.ANSA1 = 0; //Disable Analog A1
    
    TRISAbits.TRISA0 = 0; //Set Port.A0 as output
    TRISAbits.TRISA1 = 0; //Set Port.A1 as output
}

void blink_led(void)
{
    
    LATAbits.LATA0 = 1;  //Set Port.A0 High (turn on LED)     
    LATAbits.LATA1 = 0;  //Set Port.A1 Low  (turn off LED)    
    __delay_ms(DELAY_TIME);  //delay
        
   
    LATAbits.LATA0 = 0;  //Set Port.A0 Low  (turn off LED)
    LATAbits.LATA1 = 1;  //Set Port.A1 High (turn on LED)     
    __delay_ms(DELAY_TIME); //delay
}