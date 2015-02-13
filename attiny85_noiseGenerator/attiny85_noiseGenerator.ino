/* 
Pseudo-Random Bit Sequence Generator                     2009-11-25 
2009 John Honniball, Dorkbot Bristol                  

For a discussion of PRBS generators, see The Art Of Electronics, by 
Horowitz and Hill, Second Edition, pages 655 to 660. For more info 
on Linear Feedback Shift Registers, see Wikipedia:
http://en.wikipedia.org/wiki/Linear_feedback_shift_register
For the actual shift register taps, refer to this article on noise generation for synthesisers:
http://www.electricdruid.net/index.php?page=techniques.practicalLFSRs
 
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

int speakerPin = PB4;     // Connect a piezo sounder between Ground and this pin
int potiPin = A3;         // Potentiometer connected to AnalogIn pin 3

unsigned int analogValue; // define variable to store the sensor value
int samplingDelay;        
unsigned long int reg;

void setup() {
  
  TCCR0B = TCCR0B & 0b11111001; //timer pre-scaler divided by 1, full speed of the processor
  //TCCR0B = TCCR0B & 0b11111011; //timer pre-scaler divided by 8, slower speed of the processor
  
  pinMode (speakerPin, OUTPUT);
  
  // Arbitrary inital value; must not be zero
  reg = 0x551155aaL;
}

void loop() {
  
  unsigned long int newr;
  unsigned char lobit;
  unsigned char b31, b29, b25, b24;
  
  // Extract four chosen bits from the 32-bit register
  b31 = (reg & (1L << 31)) >> 31;
  b29 = (reg & (1L << 29)) >> 29;
  b25 = (reg & (1L << 25)) >> 25;
  b24 = (reg & (1L << 24)) >> 24;
  
  // EXOR the four bits together
  lobit = b31 ^ b29 ^ b25 ^ b24;
  
  // Shift and incorporate new bit at bit position 0
  newr = (reg << 1) | lobit;
  
  // Replace register with new value
  reg = newr;
  
  // Drive speaker pin from bit 0 of 'reg'
  digitalWrite (speakerPin, reg & 1);
  
  samplingDelay = 1 + ((analogRead(potiPin)>>0));
  // Delay corresponds to 20kHz, but the actual frequency of updates
  // will be lower, due to computation time and loop overhead
  delayMicroseconds (samplingDelay);
  
  // If the above delay is increased to a few tens of milliseconds,
  // and the piezo sounder is replaced by an LED and a suitable series
  // resistor, a randomly flashing light will result. Several LEDs
  // could be driven from various bits of the shift register.

}
