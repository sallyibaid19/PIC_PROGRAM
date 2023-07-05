#include <xc.h>

#define _XTAL_FREQ 4000000
// PIC16F84A Configuration Bit Settings
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (Power-up Timer is enabled)
#pragma config CP = OFF          // Code Protection bit (All program memory is code protected)
//--------------------------------------------
unsigned int TIM0_count = 0;
//--------------------------------------------
unsigned char CheckButton(void) {
    unsigned char result = 0;
    unsigned int butcount = 0;
    while (!RA2) {
        if (butcount < 10000) {
            butcount++;
        } else {
            result = 1;
            break;
        }
    }
    return result;
}
void interrupt timer0() {
    switch(TIM0_count % 10) {
        case 0:
            PORTAbits.RA1 = 0;
            PORTBbits.RB0 = 1;
            break;
        case 1:
            PORTBbits.RB0 = 0;
            PORTBbits.RB1 = 1;
            break;
        case 2:
            PORTBbits.RB1 = 0;
            PORTBbits.RB2 = 1;
            break;
        case 3:
            PORTBbits.RB2 = 0;
            PORTBbits.RB3 = 1;
            break;
        case 4:
            PORTBbits.RB3 = 0;
            PORTBbits.RB4 = 1;
            break;
        case 5:
            PORTBbits.RB4 = 0;
            PORTBbits.RB5 = 1;
            break;
        case 6:
            PORTBbits.RB5 = 0;
            PORTBbits.RB6 = 1;
            break;
        case 7:
            PORTBbits.RB6 = 0;
            PORTBbits.RB7 = 1;
            break;
        case 8:
            PORTBbits.RB7 = 0;
            PORTAbits.RA0 = 1;
            break;
        case 9:
            PORTAbits.RA0 = 0;
            PORTAbits.RA1 = 1;
            break;
    }
    TIM0_count++;
    if (TIM0_count > 3999) 
    {
        TIM0_count = 0;
    }
    T0IF=0;
}
//--------------------------------------------

void main(void) {
    TRISB = 0x00;
    PORTB = 0x00;
    TRISA &= ~0x03;
    PORTA &= ~0x03;
    TRISA |= 0x04; // Set RA2 As Input  
    OPTION_REG = 0x07;
    INTCON = 0xA0;
    TMR0 = 0;

    while (1) {
        if (CheckButton()) {
            PORTBbits.RB0 = 1;
            __delay_ms(100);
            PORTBbits.RB0 = 0;
            PORTBbits.RB1 = 1;
            __delay_ms(100);
            PORTBbits.RB1 = 0;
            PORTBbits.RB2 = 1;
            __delay_ms(100);
            PORTBbits.RB2 = 0;
            PORTBbits.RB3 = 1;
            __delay_ms(100);
            PORTBbits.RB3 = 0;
            PORTBbits.RB4 = 1;
            __delay_ms(100);
            PORTBbits.RB4 = 0;
            PORTBbits.RB5 = 1;
            __delay_ms(100);
            PORTBbits.RB5 = 0;
            PORTBbits.RB6 = 1;
            __delay_ms(100);
            PORTBbits.RB6 = 0;
            PORTBbits.RB7 = 1;
            __delay_ms(100);
            PORTBbits.RB7 = 0;
            PORTAbits.RA0 = 1;
            __delay_ms(100);
            PORTAbits.RA0 = 0;
            PORTAbits.RA1 = 1;
            __delay_ms(100);
            PORTAbits.RA1 = 0; //start point

        }
    }
    return;
}
