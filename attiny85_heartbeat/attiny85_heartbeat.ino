/*
 Fading Heartbeat

 Created 1 Nov 2008
 By David A. Mellis
 modified 30 Aug 2011
 By Tom Igoe
 modified 14 Feb 2015
 By dusjagr for use with Attiny85 
 
 http://arduino.cc/en/Tutorial/Fading
 
 This example code is in the public domain.
 
 */
 
// ATMEL ATTINY85 / ARDUINO
//
// Download the Attiny cores for compatibility to the Arduino IDE from:
// http://highlowtech.org/?p=1695
//
//                        +-\/-+
//  Reset Ain0 (D 5) PB5 1|    |8  Vcc
//        Ain3 (D 3) PB3 2|    |7  PB2 (D 2) Ain1
//   Ain2 pwm4 (D 4) PB4 3|    |6  PB1 (D 1) pwm1
//                   GND 4|    |5  PB0 (D 0) pwm0
//                        +----+

int ledPin = PB4;    // LED connected to digital pin 4
int fadeSpeed = 3;   // define variable to control the fade speed

void setup()  { 

  //TCCR0B = TCCR0B & 0b11111001; //timer pre-scaler divided by 1, full speed of the processor
  TCCR0B = TCCR0B & 0b11111011; //timer pre-scaler divided by 8, slower speed of the processor
  
  pinMode (ledPin, OUTPUT); // set pin as output

} 

void loop()  { 
  
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=1) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);         
    // wait for 3 milliseconds to see the dimming effect    
    delay(fadeSpeed);                            
  } 

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=1) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);         
    // wait for 3 milliseconds to see the dimming effect    
    delay(fadeSpeed);                            
  } 
}


