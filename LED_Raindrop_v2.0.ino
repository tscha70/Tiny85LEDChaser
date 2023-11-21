// ATTiny85 @ 1 Mhz
//                    +-\/-+
//          (5) PB5  1|    |8  Vcc (+ 3V)
// LED 5, 6 (3) PB3  2|    |7  PB2 (2) LED 3, 4
// LED 6, 8 (4) PB4  3|    |6  PB1 (1) LED 1, 2
//              GND  4|    |5  PB0 (0) Common Rail
//                    +----+
// @Internal 1 MHz and 5V VCC
// Author: Roger Rabbit, November 2023 
// This tiny Raindrop 8 channel LED chaser was inspired by:
// Hasitha Jayasundara on http://www.youtube.com/c/HAZITECH?sub_confirmation=1
// and https://www.instructables.com/ATTiny-Port-Manipulation/
// the different channels cannot all be on at the same time because they use the same ports in pairs
// therefore the LEDs are multiplexed, that is, they are switched on for a very short time
// for the human eye it looks like if the where on simultaiously.

void setup()
{
  DDRB |= (1 << PB0);      //replaces pinMode(PB0, OUTPUT);
  DDRB |= (1 << PB1);      //replaces pinMode(PB1, OUTPUT);
  DDRB |= (1 << PB2);      //replaces pinMode(PB2, OUTPUT);
  DDRB |= (1 << PB3);      //replaces pinMode(PB3, OUTPUT);
  DDRB |= (1 << PB4);      //replaces pinMode(PB4, OUTPUT);
}

int pattern = 127; // 7 bits are set
// MAIN LOOP ----------------------------- START
void loop()
{
  // in this for-loop, the 7 bits (representing the LEDs) are shifted from left to right
  // this gives the impression of a "raindrop" falling
  for (int i = 0; i <= 15; i++)
  {
    // each pattern is displayed
    Display_LEDS(pattern << i, 7);
  }
  delay(150);
  Switch_LED_On_Or_Off(0); // Clear all LEDs
  delay(2000);

}

// MAIN LOOP ----------------------------- END

void Display_LEDS(int leds, int repetitions)
{
  // the repetions are required to show the same pattern of LEDs for a given time
  for (int k = 0; k < repetitions; k++)
  {
    // this loop turns on all active LEDs one by one (only the upper 8 bits of the 16bit word are displayed (the rest is invisible)
    for (int bits = 15; bits >= 8; bits--) {
      // Compare bits 15-8 in the 15 bit word
      if (leds & (1 << bits)) // if the bit is set then switch the led on
      {
        Switch_LED_On_Or_Off(bits - 8 + 1);
      }
      // the LED must be switched on and off for a certain time otherwize it is constantly glowing
      delayMicroseconds(850);
    }
  }
}

void Switch_LED_On_Or_Off(byte num)
{
  switch (num)
  {
    case 1: // LED 1 ON
      PORTB &= ~(1 << PB0);   //replaces digitalWrite(PB0, LOW);
      PORTB |= (1 << PB1);    //replaces digitalWrite(PB1, HIGH);
      PORTB &= ~(1 << PB2);   //replaces digitalWrite(PB2, LOW);
      PORTB &= ~(1 << PB3);   //replaces digitalWrite(PB3, LOW);
      PORTB &= ~(1 << PB4);   //replaces digitalWrite(PB4, LOW);
      break;
    case 2: // LED 2 ON
      PORTB |= (1 << PB0);    //replaces digitalWrite(PB0, HIGH);
      PORTB &= ~(1 << PB1);   //replaces digitalWrite(PB1, LOW);
      PORTB |= (1 << PB2);    //replaces digitalWrite(PB2, HIGH);
      PORTB |= (1 << PB3);    //replaces digitalWrite(PB3, HIGH);
      PORTB |= (1 << PB4);    //replaces digitalWrite(PB4, HIGH);
      break;
    case 3: // LED 3 ON
      PORTB &= ~(1 << PB0);   //replaces digitalWrite(PB0, LOW);
      PORTB &= ~(1 << PB1);   //replaces digitalWrite(PB1, LOW);
      PORTB |= (1 << PB2);    //replaces digitalWrite(PB2, HIGH);
      PORTB &= ~(1 << PB3);   //replaces digitalWrite(PB3, LOW);
      PORTB &= ~(1 << PB4);   //replaces digitalWrite(PB4, LOW);
      break;
    case 4: // LED 4 ON
      PORTB |= (1 << PB0);    //replaces digitalWrite(PB0, HIGH);
      PORTB |= (1 << PB1);    //replaces digitalWrite(PB1, HIGH);
      PORTB &= ~(1 << PB2);   //replaces digitalWrite(PB2, LOW);
      PORTB |= (1 << PB3);    //replaces digitalWrite(PB3, HIGH);
      PORTB |= (1 << PB4);    //replaces digitalWrite(PB4, HIGH);
      break;
    case 5:
      // LED 5 ON
      PORTB &= ~(1 << PB0);   //replaces digitalWrite(PB0, LOW);
      PORTB &= ~(1 << PB1);   //replaces digitalWrite(PB1, LOW);
      PORTB &= ~(1 << PB2);   //replaces digitalWrite(PB2, LOW);
      PORTB |= (1 << PB3);    //replaces digitalWrite(PB3, HIGH);
      PORTB &= ~(1 << PB4);   //replaces digitalWrite(PB4, LOW);
      break;
    case 6: // LED 6 ON
      PORTB |= (1 << PB0);    //replaces digitalWrite(PB0, HIGH);
      PORTB |= (1 << PB1);    //replaces digitalWrite(PB1, HIGH);
      PORTB |= (1 << PB2);    //replaces digitalWrite(PB2, HIGH);
      PORTB &= ~(1 << PB3);   //replaces digitalWrite(PB3, LOW);
      PORTB |= (1 << PB4);    //replaces digitalWrite(PB4, HIGH);
      break;
    case 7: // LED 7 ON
      PORTB &= ~(1 << PB0);   //replaces digitalWrite(PB0, LOW);
      PORTB &= ~(1 << PB1);   //replaces digitalWrite(PB1, LOW);
      PORTB &= ~(1 << PB2);   //replaces digitalWrite(PB2, LOW);
      PORTB &= ~(1 << PB3);   //replaces digitalWrite(PB3, LOW);
      PORTB |= (1 << PB4);    //replaces digitalWrite(PB4, HIGH);
      break;
    case 8: // LED 8 ON
      PORTB |= (1 << PB0);    //replaces digitalWrite(PB0, HIGH);
      PORTB |= (1 << PB1);    //replaces digitalWrite(PB1, HIGH);
      PORTB |= (1 << PB2);    //replaces digitalWrite(PB2, HIGH);
      PORTB |= (1 << PB3);    //replaces digitalWrite(PB3, HIGH);
      PORTB &= ~(1 << PB4);   //replaces digitalWrite(PB4, LOW);
      break;
    case 0:
    default: // All OFF
      PORTB &= ~(1 << PB0);    //replaces digitalWrite(PB0, LOW);
      PORTB &= ~(1 << PB1);    //replaces digitalWrite(PB1, LOW);
      PORTB &= ~(1 << PB2);    //replaces digitalWrite(PB2, LOW);
      PORTB &= ~(1 << PB3);    //replaces digitalWrite(PB3, LOW);
      PORTB &= ~(1 << PB4);    //replaces digitalWrite(PB4, LOW);
      break;
  }
}
