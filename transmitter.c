#include <Arduino.h>  
#define LED_PIN 9

const char* message = "HELLO";
char binaryMessage[100];

void convertMessageToBinary() {
    int index = 0;
    for (int i = 0; message[i] != '\0'; i++) {
        char letter = message[i];
        for (int j = 7; j >= 0; j--) {
            binaryMessage[index++] = (letter & (1 << j)) ? '1' : '0';
        }
    }
    binaryMessage[index] = '\0';  
}
void setup() {
    pinMode(LED_PIN, OUTPUT); 
    Serial.begin(9600);       
    convertMessageToBinary();
    Serial.print("Transmitting: ");
    Serial.println(binaryMessage);
}

void sendBit(char bit) {
    if (bit == '1') {
        digitalWrite(LED_PIN, HIGH);  
    } else {
        digitalWrite(LED_PIN, LOW);   
    }
    delay(500);
}

void loop() {
    for (int i = 0; binaryMessage[i] != '\0'; i++) {
        sendBit(binaryMessage[i]);
    }
    delay(2000);
}
