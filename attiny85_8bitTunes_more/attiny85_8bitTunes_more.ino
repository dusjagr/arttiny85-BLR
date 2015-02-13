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
int potiPin = A3;

long t = 0; 
int v = 0; 
 
void setup () {
 
  TCCR0B = TCCR0B & 0b11111001; //no timer pre-scaler, fast PWM
 
  pinMode (speakerPin, OUTPUT);
 
}
 
 
void loop () {
  
  int P1 = ((analogRead(potiPin)>>6) + 1);
  //int P1 = ((analogRead(potiPin)>>2) + 1);
  
  v = t * ((t>>12|t>>P1)&47&t>>(13>>3));
  //v = t * ((t>>15|t>>P1)&83&t>>(P1>>3));
  //v = (t|3) * ((t>>1|t>>6)&P1&t>>3);  
  //v = (t|P1) * ((t>>15|t>>11)&47&t>>3);
  //v = t>>4&1?t>>5:-t>>P1 ;
  
  digitalWrite (speakerPin, v);
  //analogWrite (speakerPin, v);
  
  delayMicroseconds(200);
  t++;
}

