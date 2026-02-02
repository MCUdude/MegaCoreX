#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

void yield(void);

#define LOW            0
#define HIGH           1

#define FALLING        2
#define RISING         3
#define CHANGE         4

#define INPUT          0
#define OUTPUT         1
#define INPUT_PULLUP   2
//#define INPUT_PULLDOWN 3

#define LSBFIRST       0
#define MSBFIRST       1

#define PI             3.1415926535897932384626433832795
#define HALF_PI        1.5707963267948966192313216916398
#define TWO_PI         6.283185307179586476925286766559
#define DEG_TO_RAD     0.017453292519943295769236907684886
#define RAD_TO_DEG     57.295779513082320876798154814105
#define EULER          2.718281828459045235360287471352

#define SERIAL         0
#define DISPLAY        1

typedef void (*voidFuncPtr)(void);

#ifdef __cplusplus
enum pwm_timers_t : uint8_t;
#else
typedef uint8_t pwm_timers_t;
#endif

// interrupts() / noInterrupts() must be defined by the core

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#ifndef bit
#define bit(b) (1UL << (b))
#endif

/* TODO: request for removal */
typedef bool      boolean;
typedef uint8_t   byte;
typedef uint16_t  word;

void init(void);
void initVariant(void);

int atexit(void (*func)()) __attribute__((weak));
int main() __attribute__((weak));

#ifdef EXTENDED_PIN_MODE
// Platforms who wnat to declare more than 256 pins need to define EXTENDED_PIN_MODE globally
typedef uint32_t pin_size_t;
#else
typedef uint8_t pin_size_t;
#endif

void pinMode(pin_size_t pinNumber, uint8_t pinMode);
void digitalWrite(pin_size_t pinNumber, uint8_t status);
void digitalWriteFast(pin_size_t pinNumber, uint8_t status);
uint8_t digitalRead(pin_size_t pinNumber);
uint8_t digitalReadFast(pin_size_t pinNumber);
int analogRead(pin_size_t pinNumber);
uint8_t analogReadResolution(uint8_t res);
void analogReference(uint8_t mode);
void analogWrite(pin_size_t pinNumber, int value);
void analogWriteFrequency(uint8_t kHz);

unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long);
void delayMicroseconds(unsigned int us);
unsigned long pulseIn(pin_size_t pin, uint8_t state, unsigned long timeout);
unsigned long pulseInLong(pin_size_t pin, uint8_t state, unsigned long timeout);

void shiftOut(pin_size_t dataPin, pin_size_t clockPin, uint8_t bitOrder, uint8_t val);
pin_size_t shiftIn(pin_size_t dataPin, pin_size_t clockPin, uint8_t bitOrder);

void attachInterrupt(pin_size_t interruptNumber, voidFuncPtr callback, uint8_t mode);
void detachInterrupt(pin_size_t interruptNumber);

void setup(void);
void loop(void);

// Constant checks error handler
void badArg(const char*) __attribute__((error("")));
inline __attribute__((always_inline)) void check_constant_pin(pin_size_t pin)
{
  if(!__builtin_constant_p(pin))
    badArg("Digital pin must be a constant");
}

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
#ifndef min
	template<class T, class L>
	auto min(const T& a, const L& b) -> decltype((b < a) ? b : a) {
		return (b < a) ? b : a;
	}
#endif

#ifndef max
	template<class T, class L>
	auto max(const T& a, const L& b) -> decltype((a < b) ? b : a) {
		return (a < b) ? b : a;
	}
#endif

#ifndef round
	template<class T>
	long round(const T& x) {
		return (long)(x >= 0 ? (x + 0.5) : (x - 0.5));
	}
#endif

#ifndef max
	template<class T>
	auto sq(const T& x) -> decltype(x * x) {
		return x * x;
	}
#endif

#ifndef radians
  template<class T>
  auto radians(const T& deg) -> decltype(deg * DEG_TO_RAD) {
    return deg * DEG_TO_RAD;
  }
#endif

#ifndef degrees
  template<class T>
  auto degrees(const T& rad) -> decltype(rad * RAD_TO_DEG) {
    return rad * RAD_TO_DEG;
  }
#endif
#ifndef constrain
  template<class T, class L, class H>
	auto constrain(const T& x, const L& l, const H& h) -> decltype((x < l) ? l : (x > h) ? h : x) {
		return (x < l) ? l : (x > h) ? h : x;
	}
#endif

#else
  #ifndef min
    #define min(a,b)     ({ typeof (a) _a = (a); typeof (b) _b = (b); _a < _b ? _a : _b; })
  #endif
  #ifndef max
    #define max(a,b)     ({ typeof (a) _a = (a); typeof (b) _b = (b); _a > _b ? _a : _b; })
  #endif
  #ifndef sq
    #define sq(x)        ({ typeof (x) _x = (x); _x * _x; })
  #endif
  #ifndef radians
    #define radians(deg) ((deg) * DEG_TO_RAD)
  #endif
  #ifndef degrees
    #define degrees(rad) ((rad) * RAD_TO_DEG)
  #endif
  #ifndef constrain
    #define constrain(x,low,high)     ({ \
    typeof (x) _x = (x);               \
    typeof (low) _l = (low);           \
    typeof (high) _h = (high);         \
    _x < _l ? _l : _x > _h ? _h : _x; })
  #endif
#endif // __cplusplus

#ifdef __cplusplus

/* C++ prototypes */
uint16_t makeWord(uint16_t w);
uint16_t makeWord(byte h, byte l);

#define word(...) makeWord(__VA_ARGS__)

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration = 0);
void noTone(uint8_t _pin);

// WMath prototypes
long random(long);
long random(long, long);
void randomSeed(unsigned long);
long map(long, long, long, long, long);

#endif // __cplusplus
