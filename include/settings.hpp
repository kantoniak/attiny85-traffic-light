#include <Arduino.h>

constexpr uint8_t PIN_BUTTON = 2;
constexpr uint8_t PIN_LED_RED = 3;
constexpr uint8_t PIN_LED_YELLOW = 1;
constexpr uint8_t PIN_LED_GREEN = 0;

constexpr unsigned long SLEEP_TIMEOUT = 10 * 60 * 1000UL;

constexpr unsigned long STOP_TIMEOUT = 20 * 1000;
constexpr unsigned long STOP_END_TIMEOUT = 1000;
constexpr unsigned long GO_TIMEOUT = 20 * 1000;
constexpr unsigned long GO_END_TIMEOUT = 3 * 1000;

void init_sleep_mode();
void init_leds();
void attach_button_interrupt(uint8_t pin, void(*handler)(void));
void detach_button_interrupt(uint8_t pin);
void enter_sleep();
