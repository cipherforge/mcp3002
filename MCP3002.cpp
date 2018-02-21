
#include "MCP3002.h"
#include "Arduino.h"

#include "MCP3002.h"

MCP3002::MCP3002(int clockpin, int mosipin, int misopin, int cspin) {
    
    // define SPI outputs and inputs for bitbanging
    
    _cspin = cspin;
    _clockpin = clockpin;
    _mosipin = mosipin;
    _misopin = misopin;
    
    pinMode(_cspin, OUTPUT);
    pinMode(_clockpin, OUTPUT);
    pinMode(_mosipin, OUTPUT);
    pinMode(_misopin, INPUT);

 }


// read SPI data from MCP3002 chip, 2 possible adc's (0 thru 1)
int MCP3002::readADC(int adcnum) {

  if ((adcnum > 1) || (adcnum < 0)) return -1; // Wrong adc address return -1

  // algo
  digitalWrite(_cspin, HIGH);
  digitalWrite(_clockpin, LOW); //  # start clock low
  digitalWrite(_cspin, LOW); //     # bring CS low

  int commandout = adcnum;

  commandout |= 0x6 ;     //  start bit + single-ended bit | with input0 / input1 
  commandout <<= 1;       //  shift to add fsb bit
  commandout += 0x1;      //  Send FSB
  commandout <<= 3;       //  shift 3 more to make 8 bits
  
  for (int i=0; i<4; i++) {

    if (commandout & 0x80) {
      digitalWrite(_mosipin, HIGH);
    } else { 
      digitalWrite(_mosipin, LOW);
    } 
    commandout <<= 1;
    
    digitalWrite(_clockpin, HIGH);
    digitalWrite(_clockpin, LOW);

  }

  int adcout = 0;
  // read in one empty bit, one null bit and 10 ADC bits
  for (int i=0; i<12; i++) {
    digitalWrite(_clockpin, HIGH);
    digitalWrite(_clockpin, LOW);
    adcout <<= 1;
    if (digitalRead(_misopin))
      adcout |= 0x1;
  } 
  
  digitalWrite(_cspin, HIGH);
 
  adcout >>= 1; //      # first bit is 'null' so drop it
  
  return adcout;
}



