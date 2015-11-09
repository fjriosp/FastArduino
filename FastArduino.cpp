#include "FastArduino.h"

const fPin _fGetPin_v(const uint8_t pin) {
	return _fGetPin_c(pin);
}

void _fPinMode_v(const fPin pin, const uint8_t mode) {
	_fPinMode_c(pin, mode);
}

void _fDigitalWrite_v(const fPin pin, const uint8_t value) {
	_fDigitalWrite_c(pin, value);
}

void _fDigitalToggle_v(const fPin pin) {
	_fDigitalToggle_c(pin);
}

uint8_t _fDigitalRead_v(const fPin pin) {
	return _fDigitalRead_c(pin);
}
