/* PCrazy shit 8-bit symphony generator                   
 
   inspired by:
   http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html
   more on the 8 bit MixTape
   http://wiki.sgmk-ssam.ch/index.php/8bit_Mix_Tape
   
 modified 14 Feb 2015
 By dusjagr for use with Attiny85 
 
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

 
int speakerPin = PB4;
 
long t = 0; 
int v = 0; 
 
void setup () {
 
  TCCR0B = TCCR0B & 0b11111001; //no timer pre-scaler, fast PWM
 
  pinMode (speakerPin, OUTPUT);
 
}
 
 
void loop () {
  
  v = t * ((t>>12|t>>7)&47&t>>(13>>3));
  digitalWrite (speakerPin, v);
  delayMicroseconds(200);
  t++;
}

