#include <pic18f4455.h>
#include "AnalogSensors.h"

const uint8_t AdInputChannel[5] = {0x01, 0x03, 0x04, 0x08, 0x09 };
uint16_t ConversionResults[5];

void StartAcquisition(AnalogSensor sensor);
uint8_t GetResultIndex(uint8_t An);

void InitAnalogSensors()
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
    
    
    // --- A/D Conversion configuration
    ADCON1bits.VCFG0 = 0; // Voltage Reference- (Vss) 
    ADCON1bits.VCFG1 = 0; // Voltage Reference+ (Vdd) 
    ADCON1bits.PCFG = 0x05; // Enable AN0 to AN9
    
    ADCON2bits.ADFM = 0; // Left justified.
    ADCON2bits.ACQT = 0; // Acquisition time (0 Tad)
    ADCON2bits.ADCS = 0; // A/D Conversion Clock Select bits (Fosc/2)
    
    PIR1bits.ADIF = 0; // Reset interrupt flag.
    PIE1bits.ADIE = 1; // Enables the A/D interrupt
}

uint16_t ReadSensor(AnalogSensor sensor)
{
    return 0; 
}
    
void StartAcquisition(AnalogSensor sensor)
{
    ADCON0bits.CHS = AdInputChannel[sensor];
    ADCON0bits.ADON = 1; // Turn on A/D module
    // Wait acquisition time
    ADCON0bits.GODONE = 1; // Start conversion.
    // When the conversion is done the ADIF will be triggered.
}

uint8_t GetResultIndex(uint8_t An)
{
    uint8_t result = 0;
    for (int index= 0; (index < 5) && !result; index++)
    {
        if (AdInputChannel[index] == An)
        {
            result = index;
        }
    }
    
    return result;
}

void HandleAdInterrupts()
{
    if (PIE1bits.ADIE && PIR1bits.ADIF)
    {
        PIR1bits.ADIF = 0;
        ConversionResults[GetResultIndex(ADCON0bits.CHS)] = ADRES;
    }
}
