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
#define _XTAL_FREQ 500000  //500Khz

//Funcation Prototypes
void setup(void);
void check_button(void);


void main(void){
    setup();  //Setups everything
    
    while(1) //We loop here forever
    {
        check_button();  //Check the reset button for press
        
    } //END Of Main While Loop
}//END of MAIN Function 

void setup(void){
    //Ran once on power on - Setup the pins and clock output
   
    //Pin RA0 connects to the Z80 Reset pin    
    //On Startup this is set to Low - This will keep the z80 in reset mode until RA0 goes high. 
    ANSELAbits.ANSA0 = 0; //Disable analog for A.0
    TRISAbits.TRISA0 = 0; //Pin RA0 Set to Output
    LATAbits.LATA0 = 0;  //Put RA0 low Z80 in reset
    
    //Pin RA2 outputs the clock pulse
    //Set the System Clock - You can change this to match the setting you are looking for
    //OSCCONbits.IRCF = 0b010;  //Set PIC10F322 System Clock to 500Khz  This will output a 125Khz pulse on RA2 - Math is FOSC/4 = 125Khz
    //Other Possible Values - Uncomment as needed
    OSCCONbits.IRCF = 0b000; //31Khz FOSC/4 = 7.75Khz
    //OSCCONbits.IRCF = 0b001; //250Khz FOSC/4 = 62.5Khz
    //OSCCONbits.IRCF = 0b010; //500Khz FOSC/4 = 125Khz
    //OSCCONbits.IRCF = 0b011; //1Mhz FOSC/4 = 250Khz
    //OSCCONbits.IRCF = 0b100; //2Mhz FOSC/4 = 500Khz
    //OSCCONbits.IRCF = 0b101; //4Mhz FOSC/4 = 1Mhz
    //OSCCONbits.IRCF = 0b110; //8Mhz FOSC/4 = 2Mhz
    //OSCCONbits.IRCF = 0b110; //16Mhz FOSC/4 =4Mhz
    
       
    
    CLKRCONbits.CLKROE = 1; //Enable Clock Reference out on RA2
    
    //RA3 is the reset button    
    WPUAbits.WPUA3 = 1; //Enable Weakpull up on Pin RA3   
    OPTION_REGbits.nWPUEN = 0; //Requires being enabled in option reg as well
    
    __delay_ms(50); //50ms delay
     LATAbits.LATA0 = 1; //Take RA0 high and Z80 out of reset
    
}//END of setup function

void check_button(void){
    //Resets the Z80 CPU
    //Keep in mind a pullup keeps the pin logic high. TO test for button press - the button when pressed with bring the pin to logic 0 or low.
    
    if (PORTAbits.RA3 == 0)  //If Pin RA3 is low..
    {
        __delay_ms(50); //50ms delay checking for button bonce
        
        if (PORTAbits.RA3 == 0)  //If Pin RA3 is still slow.. reset the Z80 CPU
        {
            LATAbits.LATA0 = 0;  //Put RA0 low -  Z80 in reset
            
            while (PORTAbits.RA3 == 0){} //Going to wait here if the button is still being pressed - button needs to be released before moving on            
             
            __delay_ms(100); //100ms delay  
            
            LATAbits.LATA0 = 1; //Take RA0 high and Z80 out of reset           
        }  //END of Inner check button         
    } //END of outter button
}//END of check_button function
