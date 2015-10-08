#include "FastArduino.h"

void _fPinMode_v(const uint8_t pin, const uint8_t mode) {
	_fPinMode_c(pin, mode);
}

void _fDigitalWrite_v(const uint8_t pin, const uint8_t value) {
	_fDigitalWrite_c(pin, value);
}

uint8_t  _fDigitalRead_v(const uint8_t pin) {
	return _fDigitalRead_c(pin);
}
