// ATTiny85 @ 1 Mhz
//
//                    +-\/-+
//          (5) PB5  1|    |8  Vcc (+ 3V)
// LED 5, 6 (3) PB3  2|    |7  PB2 (2) LED 3, 4
// LED 6, 8 (4) PB4  3|    |6  PB1 (1) LED 1, 2
//              GND  4|    |5  PB0 (0) Common Rail
//                    +----+
//
// @Internal 1 MHz and 3 to 5V VCC - can be powered by CR2032 battery or USB power supply
//
// Author: Roger Rabbit, November 2023
// This tiny raindrop 8-channel LED chaser was inspired by:
// Hasitha Jayasundara on http://www.youtube.com/c/HAZITECH?sub_confirmation=1
// and https://www.instructables.com/ATTiny-Port-Manipulation/
// The different channels cannot all be on at the same time because they use the same ports in pairs.
// Therefore, the LEDs are multiplexed, meaning they are switched on and off very quickly.
// To the human eye, it appears as if they are all on simultaneously.

void setup()
{
  DDRB |= (1 << PB0);      //replaces pinMode(PB0, OUTPUT);
  DDRB |= (1 << PB1);      //replaces pinMode(PB1, OUTPUT);
  DDRB |= (1 << PB2);      //replaces pinMode(PB2, OUTPUT);
  DDRB |= (1 << PB3);      //replaces pinMode(PB3, OUTPUT);
  DDRB |= (1 << PB4);      //replaces pinMode(PB4, OUTPUT);
}

#define REPETITIONS 6
#define MULTIPLEXDELAY_MS 850 // in microseconds
#define PATTERN 127 // 7 consecutive bits are set

void loop()
{
  // In this for loop, the 7 bits (representing the LEDs) are shifted from left to right.
  // This gives the impression of a raindrop falling.
  for (byte i = 0; i <= 15; i++)
  {
    // Let's gradually slow down towards the end by increasing the number of repetitions
    DisplayLeds(PATTERN << i, REPETITIONS + (i*i) / 16);
  }

  // Pause for a while before starting it all over again. ;)
  delay(2000);
}

void DisplayLeds(int pattern, byte repetitions)
{
  // the repetions are required to show the same pattern of LEDs for a given time
  for (byte k = 0; k < repetitions; k++)
  {
    // this loop turns on all active LEDs one by one (only the upper 8 bits of the 16-bit word are displayed, the rest is invisible)
    for (int bits = 15; bits >= 8; bits--) {
      
      // compare bits 15-8 of the 16-bit word
      if (pattern & (1 << bits)) // if the bit is set then switch the led on
      {
        SetPortPattern(bits - 7);
      }
      else
      {
        SetPortPattern(0);
      }
      
      // the LED must be switched on and off for a certain time otherwise it is constantly glowing
      delayMicroseconds(MULTIPLEXDELAY_MS);
    }
  }
}

void SetPortPattern(byte ledNumber)
{
  switch (ledNumber)
  {
    case 1: // LED 1 ON
      PORTB = 0b00000010;
      break;
    case 2: // LED 2 ON
      PORTB = 0b00011101;
      break;
    case 3: // LED 3 ON
      PORTB = 0b00000100;
      break;
    case 4: // LED 4 ON
      PORTB = 0b00011011;
      break;
    case 5:
      // LED 5 ON
      PORTB = 0b00001000;
      break;
    case 6: // LED 6 ON
      PORTB = 0b00010111;
      break;
    case 7: // LED 7 ON
      PORTB = 0b00010000;
      break;
    case 8: // LED 8 ON
      PORTB = 0b00001111;
      break;
    case 0:
    default: // All LEDS OFF
      PORTB = 0b00000000;
      break;
  }
}
