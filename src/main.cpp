#include "LinarADC.h"
#include <Arduino.h>

// LinarADC abc(34, ".bin", 14, 26);
LinarADC abc;

void setup(){

    Serial.begin(115200);
    delay(1000);

    //to print messages 
    abc.debugfcn = [](const char *txt) {
        Serial.printf(txt);
    };

    // Do calbration.Save file
    if (abc.save()) {
        Serial.println("File saved");

    } else {
       Serial.println("Error. File wasn't saved"); 
    }

    //  Load File. begin ADC    
    if (abc.begin()) {
        Serial.println("ADC OK");

    } else {
        Serial.println("ADC error"); 
    }
    dac_output_enable(DAC_CHANNEL_1); 

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


