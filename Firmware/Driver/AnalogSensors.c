#include <pic18f4455.h>

void InitializeDistanceSensors()
{
    // --- Distance sensors ---
    // Transmitters
    // Set as output.
    TRISAbits.RA0 = 0;
    TRISAbits.RA2 = 0;
    TRISAbits.RA4 = 0;
    
    // Enable them.
    LATA = 0x15; 
    
    // Receivers
    // Set as input.
    TRISAbits.RA1 = 1; // AN1
    TRISAbits.RA3 = 1; // AN3
    TRISAbits.RA5 = 1; // AN4
    
    // --- Light sensor ---
    TRISBbits.RB3 = 1; // AN9
    
    // --- Microphone ---
    TRISBbits.RB2 = 1; // AN8
    
    ADCON1bits.VCFG0 = 0; // Voltage Reference- (Vss) 
    ADCON1bits.VCFG1 = 0; // Voltage Reference+ (Vdd) 
    ADCON1bits.PCFG = 0x05; // Enable AN0 to AN9
    
    ADCON2bits.ADFM = 0; // Left justified.
}
