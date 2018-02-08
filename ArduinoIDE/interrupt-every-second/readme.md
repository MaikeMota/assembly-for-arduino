# Problem 1

Set up an interrupt that triggers every 1.0 seconds;

## In the ISR

1. _PORTD_ pins 2, 3 4 and 5 are to be read.

2. if _any two_ of the pins have changed since the last time, then pin 6 is set to 1, otherwise it is set to 0.


### Register Settings

    TCCR1A:     00000000    (normal, normal)
    TCCR1B:     00000100    (no icr, 256)
    TCCR1C:     00000000    (no force)
    OCR1AH:     0xF4
    OCR1AL:     0x23
    TIMSK1:     00000010    (OCIE1A)
    DDRD:       01000000    (pins 0 ~ 6 and 7 - INPUT, pin 6 - OUTPUT)
    PPORTD:     00111100    (set pullup resistors)