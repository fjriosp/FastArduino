#ifndef __FASTARDUINOBOARDS_H__
#define __FASTARDUINOBOARDS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define CREATE_LOOKUP_TABLE(name , type,  ...)     \
  const type PROGMEM name##_PGM[] = {__VA_ARGS__}; \
  const type         name[]       = {__VA_ARGS__};

#define READ_LOOKUP_TABLE(name,idx)   \
  (__builtin_constant_p(idx)          \
  ? (name[idx])                       \
  : pgm_read_byte(name##_PGM+(idx)))

// Ports
#define fPA 0
#define fPB 1
#define fPC 2
#define fPD 3
#define fPE 4
#define fPF 5

// Specific data
#if defined(__AVR_ATmega328P__)

#define fMAXPORT fPD

CREATE_LOOKUP_TABLE(lt_fPinToPX,uint8_t,
		/*  0 */fPD,fPD,fPD,fPD,fPD,fPD,fPD,fPD,
		/*  8 */fPB,fPB,fPB,fPB,fPB,fPB,
		/* 14 */fPC,fPC,fPC,fPC,fPC,fPC,
)
;

CREATE_LOOKUP_TABLE(lt_fPinToMask,uint8_t,
		/*  0 */_BV(0),_BV(1),_BV(2),_BV(3),_BV(4),_BV(5),_BV(6),_BV(7),
		/*  8 */_BV(0),_BV(1),_BV(2),_BV(3),_BV(4),_BV(5),
		/* 14 */_BV(0),_BV(1),_BV(2),_BV(3),_BV(4),_BV(5),
)
;

CREATE_LOOKUP_TABLE(lt_fPXToPORTX,uint16_t,
		(uint16_t)NULL,
		(uint16_t)&PORTB,
		(uint16_t)&PORTC,
		(uint16_t)&PORTD,
		(uint16_t)NULL,
		(uint16_t)NULL,
)
;

CREATE_LOOKUP_TABLE(lt_fPXToPCMSKX,uint16_t,
		(uint16_t)NULL,
		(uint16_t)&PCMSK0,
		(uint16_t)&PCMSK1,
		(uint16_t)&PCMSK2,
		(uint16_t)NULL,
		(uint16_t)NULL,
)
;

#elif defined(__AVR_ATtiny85__)

#define fMAXPORT fPB

CREATE_LOOKUP_TABLE(lt_fPinToPX,uint8_t,
		/*  0 */fPB,fPB,fPB,fPB,fPB,fPB,
)
;

CREATE_LOOKUP_TABLE(lt_fPinToMask,uint8_t,
		/*  0 */_BV(0),_BV(1),_BV(2),_BV(3),_BV(4),_BV(5),
)
;

CREATE_LOOKUP_TABLE(lt_fPXToPORTX,uint16_t,
		(uint16_t)NULL,
		(uint16_t)&PORTB,
		(uint16_t)NULL,
		(uint16_t)NULL,
		(uint16_t)NULL,
		(uint16_t)NULL,
)
;

CREATE_LOOKUP_TABLE(lt_fPXToPCMSKX,uint16_t,
		(uint16_t)NULL,
		(uint16_t)&PCMSK,
		(uint16_t)NULL,
		(uint16_t)NULL,
		(uint16_t)NULL,
		(uint16_t)NULL,
)
;

#elif defined(__AVR_ATmega32U4__)

#define fMAXPORT fPF

CREATE_LOOKUP_TABLE(lt_fPinToPX,uint8_t,
		/*  0 */fPD,fPD,fPD,fPD,fPD,
		/*  5 */fPC,
		/*  6 */fPD,
		/*  7 */fPE,
		/*  8 */fPB,fPB,fPB,fPB,
		/* 12 */fPD,
		/* 13 */fPC,
		/* 14 */fPB,fPB,fPB,fPB,
		/* 18 */fPF,fPF,fPF,fPF,fPF,fPF,
		/* 24 */fPD,fPD,
		/* 26 */fPB,fPB,fPB,
		/* 29 */fPD,
)
;

CREATE_LOOKUP_TABLE(lt_fPinToMask,uint8_t,
		/*  0 */_BV(2),_BV(3),_BV(1),_BV(0),_BV(4),
		/*  5 */_BV(6),
		/*  6 */_BV(7),
		/*  7 */_BV(6),
		/*  8 */_BV(4),_BV(5),_BV(6),_BV(7),
		/* 12 */_BV(6),
		/* 13 */_BV(7),
		/* 14 */_BV(3),_BV(1),_BV(2),_BV(0),
		/* 18 */_BV(7),_BV(6),_BV(5),_BV(4),_BV(1),_BV(0),
		/* 24 */_BV(4),_BV(7),
		/* 26 */_BV(4),_BV(5),_BV(6),
		/* 29 */_BV(6),
)
;

CREATE_LOOKUP_TABLE(lt_fPXToPORTX,uint16_t,
		(uint16_t)NULL,
		(uint16_t)&PORTB,
		(uint16_t)&PORTC,
		(uint16_t)&PORTD,
		(uint16_t)&PORTE,
		(uint16_t)&PORTF,
)
;

CREATE_LOOKUP_TABLE(lt_fPXToPCMSKX,uint16_t,
		(uint16_t)NULL,
		(uint16_t)&PCMSK0,
		(uint16_t)NULL,
		(uint16_t)NULL,
		(uint16_t)NULL,
		(uint16_t)NULL,
)
;

#else
#error Unknown board (FastArduinoBoards.h)
#endif

#ifdef __cplusplus
}
#endif

#endif
