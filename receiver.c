#include <Arduino.h>
#define RECEIVER_PIN A0

#define THRESHOLD 500  

char receivedBinary[100];
int bitIndex = 0;

char readBit() {
    int lightValue = analogRead(RECEIVER_PIN);

    if (lightValue > THRESHOLD) {
        return '1';
    } else {
        return '0';
    }
}
void printMessage() {
    for (int i = 0; i < bitIndex; i += 8) {
        int asciiValue = 0;

        for (int j = 0; j < 8; j++) {
            if (receivedBinary[i + j] == '1') {
                asciiValue |= (1 << (7 - j));
            }
        }
        Serial.print((char)asciiValue);
    }
    Serial.println();
    bitIndex = 0; 
}

void setup() {
    Serial.begin(9600);
    pinMode(RECEIVER_PIN, INPUT);
    Serial.println("Waiting for message...");
}

void loop() {
    
    receivedBinary[bitIndex++] = readBit();
    delay(500);  
    if (bitIndex % 8 == 0 && bitIndex > 0) {
        printMessage();
    }
}
