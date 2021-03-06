#include <pic18f4455.h>
#include "AnalogSensors.h"
#include "LEDs.h"

// Add global variables here.

// Add local variables here.
const uint8_t AdInputChannel[5] = {0x01, 0x03, 0x04, 0x08, 0x09 };
static uint16_t mConversionResults[5];
static AnalogSensor mCurrentSensor;

typedef enum UPDATE_SENSOR_STATE
{
    Idle,
    StartNextConversion,
    WaitOnResult,
} enmUpdateSensorState;

static enmUpdateSensorState mUpdateSensorState;

// Add function prototypes here.
void InitUpdateAnalogSensors();
void UpdateAnalogSensorReadings();
void StartAcquisition(AnalogSensor sensor);
uint8_t GetResultIndex(uint8_t An);

/**
 * Interrupt handler for the A/D convertor.
 */
void HandleAdInterrupts()
{
    if (PIE1bits.ADIE && PIR1bits.ADIF)
    {
        PIR1bits.ADIF = 0;
        ADCON0bits.ADON = 0; // Turn off A/D module
        mConversionResults[GetResultIndex(ADCON0bits.CHS)] = ADRES;     
        UpdateAnalogSensorReadings();
    }
}

/**
 * Initializes the PIC to be able to read all of the buggy's analog sensors.
 */
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
    
    ADCON2bits.ADFM = 1; // Right justified.
    ADCON2bits.ACQT = 0x01; // Acquisition time (2 Tad)
    ADCON2bits.ADCS = 0x06; // A/D Conversion Clock Select bits (Fosc/64)
    
    IPR1bits.ADIP = 0; // A/D Converter Interrupt to low priority.
    PIR1bits.ADIF = 0; // Reset interrupt flag.
    PIE1bits.ADIE = 1; // Enables the A/D interrupt
    
    // Initialize the state machine for automatic sensor reading.
    InitUpdateAnalogSensors();
}
  
void StartAcquisition(AnalogSensor sensor)
{
    ADCON0bits.CHS = AdInputChannel[sensor];
    ADCON0bits.ADON = 1; // Turn on A/D module
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

/**
 * Initialize the analog sensor reading routine.
 */
void InitUpdateAnalogSensors()
{
    mUpdateSensorState = Idle;
    mCurrentSensor = 0;
}

/**
 * Start reading all analog sensors. Should be linked to a 1ms timer.
 * Only fires once every x ms.
 */
void StartUpdateAnalogSensors()
{
    // Sample the sensors each 100 mSec.
    static uint8_t counter = 0;
    
    if (counter > 100)    
    {
        if (mUpdateSensorState == Idle)
        {
            mUpdateSensorState = StartNextConversion;
            UpdateAnalogSensorReadings();
        }
        else
        {
#warning Test if this ever occurs.     
        }
                
        counter = 0;
    }
    
    counter++;
}

/**
 * Read the next sensor or stop when all sensors have been read.
 */
void UpdateAnalogSensorReadings()
{    
    // Light is the last sensor.
    if (mCurrentSensor > Light)
    {
        mUpdateSensorState = Idle;
        mCurrentSensor = 0;
    }
    else
    {
        StartAcquisition(mCurrentSensor++);
        mUpdateSensorState = WaitOnResult;        
    }
}

uint16_t GetLastReading(AnalogSensor sensor)
{
    return mConversionResults[sensor];
}
