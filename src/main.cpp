#include "LinarADC.h"
#include <Arduino.h>

LinarADC abc(34, 19, 18, ".json");
// LinarADC abc;

void setup(){

    Serial.begin(250000);
    delay(1000);
    dac_output_enable(DAC_CHANNEL_1); 
    dac_output_voltage(DAC_CHANNEL_1, 0); 
    abc.debugfcn = [](const char *txt) {
        Serial.printf(txt);
    };

    // Do calbration.Save file
    bool saved = abc.save();

    if (saved) {
        Serial.println("File saved");

    } else {
       Serial.println("Error. File wasn't saved"); 
    }

    //  Load File. begin ADC
    bool adcSuccess = abc.begin();
    
    if (adcSuccess) {
        Serial.println("ADC OK");

    } else {
        Serial.println("ADC error"); 
    }

};

void loop(){

    for (int i = 1; i < 250; i++) {

        dac_output_voltage(DAC_CHANNEL_1, i);
        delayMicroseconds(100);

        Serial.print(F("DAC = "));
        Serial.print(i * 16);
        Serial.print(F(" rawReading = "));
        Serial.print(analogRead(34));
        Serial.print(F(" calibratedReading = "));
        Serial.println(abc.read(34));

    }
    while(1);
}

