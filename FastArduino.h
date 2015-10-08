#ifndef __FASTARDUINO_H__
#define __FASTARDUINO_H__

#include <stddef.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "FastArduinoBoards.h"

#define INLINE __attribute__((always_inline)) inline

#ifdef __cplusplus
extern "C" {
#endif

// BitMask Macros
CREATE_LOOKUP_TABLE(lt_fBit,uint8_t,
		_BV(0),_BV(1),_BV(2),_BV(3),_BV(4),_BV(5),_BV(6),_BV(7)
)
;

#define fMaskSet(r,m)      ((r) |=  (m))
#define fMaskClear(r,m)    ((r) &= ~(m))
#define fMaskRead(r,m)     ((r) &   (m))
#define fMaskWrite(r,m,v)  ((v) ? fMaskSet(r,m) : fMaskClear(r,m))

#define fBit(b)            (READ_LOOKUP_TABLE(lt_fBit,b))

#define fBitSet(r,b)       (fMaskSet(r,fBit(b)))
#define fBitClear(r,b)     (fMaskClear(r,fBit(b)))
#define fBitRead(r,b)      (fMaskRead(r,fBit(b)))
#define fBitWrite(r,b,v)   (fMaskWrite(r,fBit(b),v))

// IO port macros
#define fPXToPORTXReg(px)  ((volatile uint8_t *)READ_LOOKUP_TABLE(lt_fPXToPORTX,px))
#define fPORTXRegToDDRXReg(portr) (portr-1)
#define fPORTXRegToPINXReg(portr) (portr-2)
#define fPXToPORTX(px)     (*(fPXToPORTXReg(px)  ))
#define fPXToDDRX(px)      (*(fPORTXRegToDDRXReg(fPXToPORTXReg(px))))
#define fPXToPINX(px)      (*(fPORTXRegToPINXReg(fPXToPORTXReg(px))))

#define fPXToPCMSKXReg(px) ((volatile uint8_t *)READ_LOOKUP_TABLE(lt_fPXToPCMSKX,px))
#define fPXToPCMSKX(px)    (*(fPXToPCMSKXReg(px)))

#define fPinToMask(p)      (READ_LOOKUP_TABLE(lt_fPinToMask,p))
#define fPinToPX(p)        (READ_LOOKUP_TABLE(lt_fPinToPX,p))

// Constants
/* fPinMode */
#define fINPUT        0
#define fOUTPUT       1
#define fINPUT_PULLUP 2

/* fDigitalWrite */
#define fHIGH 1
#define fLOW  0

// Public Functions
INLINE void fPinMode(const uint8_t pin, const uint8_t mode);
INLINE void fDigitalWrite(const uint8_t pin, const uint8_t value);
INLINE uint8_t fDigitalRead(const uint8_t pin);

// Internal Functions
INLINE void _fPinMode_c(const uint8_t pin, const uint8_t mode);
void _fPinMode_v(const uint8_t pin, const uint8_t mode);
INLINE void _fDigitalWrite_c(const uint8_t pin, const uint8_t value);
void _fDigitalWrite_v(const uint8_t pin, const uint8_t value);
INLINE uint8_t _fDigitalRead_c(const uint8_t pin);
uint8_t _fDigitalRead_v(const uint8_t pin);

// Inline functions implementation
void _fPinMode_c(const uint8_t pin, const uint8_t mode) {
	const uint8_t mask = fPinToMask(pin);
	const uint8_t port = fPinToPX(pin);

	volatile uint8_t * rport = fPXToPORTXReg(port);
	volatile uint8_t * rddr = fPORTXRegToDDRXReg(rport);

	const uint8_t oldSREG = SREG;
	cli();

	if (mode == fOUTPUT) {
		fMaskSet(*rddr, mask);
	} else {
		fMaskClear(*rddr, mask);
		if (mode == fINPUT_PULLUP) {
			fMaskSet(*rport, mask);
		} else {
			fMaskClear(*rport, mask);
		}
	}

	SREG = oldSREG;
}

void fPinMode(const uint8_t pin, const uint8_t mode) {
	if (__builtin_constant_p(pin)) {
		_fPinMode_c(pin, mode);
	} else {
		_fPinMode_v(pin, mode);
	}
}

void _fDigitalWrite_c(const uint8_t pin, const uint8_t value) {
	const uint8_t mask = fPinToMask(pin);
	const uint8_t port = fPinToPX(pin);

	volatile uint8_t * rport = &fPXToPORTX(port);

	if (value == fLOW) {
		fMaskClear(*rport, mask);
	} else {
		fMaskSet(*rport, mask);
	}
}

void fDigitalWrite(const uint8_t pin, const uint8_t value) {
	if (__builtin_constant_p(pin)) {
		_fDigitalWrite_c(pin, value);
	} else {
		_fDigitalWrite_v(pin, value);
	}
}

uint8_t _fDigitalRead_c(const uint8_t pin) {
	const uint8_t mask = fPinToMask(pin);
	const uint8_t port = fPinToPX(pin);

	volatile uint8_t * rpin = &fPXToPINX(port);

	return fMaskRead(*rpin, mask);
}

uint8_t fDigitalRead(const uint8_t pin) {
	if (__builtin_constant_p(pin)) {
		return _fDigitalRead_c(pin);
	} else {
		return _fDigitalRead_v(pin);
	}
}

#ifdef __cplusplus
}
#endif

#endif
