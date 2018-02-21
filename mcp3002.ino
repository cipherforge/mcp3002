/***************************************************
Read MCP3002 analog input loop
****************************************************/

#include "MCP3002.h"

//define pin connections
#define CLOCK_PIN 14
#define MOSI_PIN 13
#define MISO_PIN 12
#define CS_PIN 2

MCP3002 adc(CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);

int loopCount = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("MCP3002 simple test.");

}

void loop() {
  
  for (int ch=0; ch<8; ch++) {
    Serial.print(adc.readADC(ch)); Serial.print("\t");
  }

  Serial.print("["); Serial.print(loopCount); Serial.println("]");
  loopCount++;
  
  delay(1000);
}
