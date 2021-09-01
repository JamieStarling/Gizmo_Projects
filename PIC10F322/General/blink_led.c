/*
 * File:  blink_led.h
 * Author: Jamie Starling - GizoFoundry.com 
 *
 * Created on:  September 1, 2021, 9:45 AM
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

//Prototypes
void setup (void);
void blink_led(void);


//Main Code Entry 
void main(void)
{
    setup();  //Device Setup
    
    while(1) //Loop Here forever and do blink_led
    {
      blink_led(); 
    } //End of while
} //End of Main


void setup (void)
{
    ANSELAbits.ANSA0 = 0; //Disable Analog
    //Set Pin 0 PortA.0 as output
    TRISAbits.TRISA0 = 0;
}//End of setup


void blink_led(void)
{
    //Set PortA.0 High (turn on LED)
    LATAbits.LATA0 = 1;      
        
    //Wait 1 second - delay macro is in ms so 1000ms = 1 second
    __delay_ms(1000);
        
    //Set PortA.0 Low  (turn off LED)
    LATAbits.LATA0 = 0;
        
    //Wait 1 second
    __delay_ms(1000); 
}//End of blink_led
