#include <avr/io.h>                     ; include lib from avr to use port names instead of direct addresses

        .data                           ; data declaration
        .comm   portdp, 1               ; define portdp variable with 1 byte
        .global portdp                  ; define portd as blogal

        .text                           ; text declaration
        .global setup                   ; define function setup as global
        .global loop                    ; declare function loop as global
        .global TIMER1_COMPA_vect       ; declare function TIMER1_COMPA_vect as global

;     Arduino IDE - setup              ;

setup:

        sts     TCCR1A,     r1          ; Store Direct to SRAM  TCCR1A <- r1                    -> saves the value of register r1 to address labeled as TCCR1A
        ldi     r18,        0b0000100   ; Load Immediate r18 <- 0b00000100                      -> loads the value 0x00000100 to register r18
        sts     TCCR1B,     r18         ; Store Direct to SRAM  TCCR1B <- r18                   -> saves the vale of register r18 to address labeled as TCCR1B
        sts     TCCR1C,     r1          ; Store Direct to SRAM  TCCR1B <- r1                    -> saves the vale of register r1 to address labeled as TCCR1C
        ldi     r18,        0xF4        ; Load Immediate r18 <- 0xF4                            -> loads the value 0xF4 to register r18
        sts     OCR1AH,     r18         ; Store Direct to SRAM OCR1AH <- r18                    -> saves the value of register r18 to address labeled as OCR1AH (the high byte of the address labeled as OCR1A)
        ldi     r18,        0x23        ; Load Immediate r18 <- 0x23                            -> loads the value 0x23 to register r18
        sts     OCR1AL,     r18         ; Store Direct to SRAM OCR1AL <- r18                    -> saves the value of register r1 to address labeled as OCR1AL (the low byte of the address labeled as OCR1A)
        ldi     r18,        0b00000010  ; Load Immediate r18 <- 0b00000010                      -> loads the value 0b00000010 to register r18
        sts     TIMSK1,     r18         ; Store Direct to SRAM TIMSK1 <- r18                    -> saves the value of register r18 to address labeled as TIMSK1
        ldi     r18,        0b01000000  ; Load Immediate r18 <- 0b01000000                      -> loads the value 0b01000000 to register r18
        out     DDRD-0x20,  r18         ; Out to I/O Location DDRD - 0x20                       -> writes the value of register 18 to address DDRD - 0x20 (IO port D) - sets the pin 6 as output
        ldi     r18,        0b00111100  ; Load Immediate r18 <- 0b00111100                      -> loads the value 0b00111100 to register r18
        out     PORTD-0x20, r18         ; Out to I/O Location PORTD - 0x20                      -> writes the value of address PORTD - 0x20 (I/O port D) to register r18 - sets the ports 2, 3 4 and 5 as input with pullup resistors
        in      r18,        PIND-0x20   ; In from I/O Location PIND - 020                       -> read the value of the address PIND - 0x20 (I/O port D) and sets to register r18
        andi    r18,        0b00111100  ; Logical AND Register and Constant r18 & 0b00111100    -> performs an and operation with the value of register r18 and the constant 0b00111100 
        sts     portdp,     r18         ; Store Direct to SRAM  portdp <- r18                   -> writes the value of the register r18 to address labeled as portd
        sei                             ; Global Interrupt Enable                               -> enable global interrupts 
        ret                             ; Subroutine return                                     -> end of the setup routine  
        

;     Arduino IDE - loop                ;

loop:
        ret                             ; Subroutine return                                      -> end of the loop routine

    
;     Arduino IDE - TIMER1_COMPA_vect   ;

TIMER1_COMPA_vect:

        push    r0                      ; Push Register on Stack 
        push    r18                     ; Push Register on Stack
        lds     r18,        SREG        ; Load Direct from SRAM
        push    r18                     ; Push Register on Stack
        push    r19                     ; Push Register on Stack
        in      r18,        PIND-0x20   ; In from I/O Location PIND - 020 
        andi    r18,        0b00111100  ; Logical AND Register and Constant r18 & 0b00111100 
        lds     r19,        portdp      ; Load Direct from SRAM
        sts     portdp,     r18         ; Store Direct to SRAM  portdp <- r18
        eor     r19,        r18         ; Exclusive OR Registers r19 ^ r18
        breq    clearbit6               ; Branch if Equal 
        cpi     r19,        0x20        ; Compare Register with Immediate
        breq    clearbit6               ; Branch if Equal
        cpi     r19,        10          ; Compare Register with Immediate
        breq    clearbit6               ; Branch if Equal
        cpi     r19,        0x08        ; Compare Register with Immediate
        breq    clearbit6               ; Branch if Equal
        cpi     r19,        0x06        ; Compare Register with Immediate
        breq    clearbit6               ; Branch if Equal
        cpi     r19,        0x04        ; Compare Register with Immediate
        breq    clearbit6               ; Branch if Equal


;       setbit6 -  sets the bit 6       ;

setbit6:

        sbi     0x0b,       6
        rjmp    DONE

;       clearbit6 -  clear the bit 6    ;

clearbit6:

        cbi     0x0b,       6

DONE:
        pop     r19
        pop     r18
        sts     SREG,       r18
        pop     r18
        pop     r0
        reti
