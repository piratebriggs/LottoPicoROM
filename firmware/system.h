#if !defined( SYSTEM_H )
#define SYSTEM_H 1

#include <stdint.h>

static constexpr uint32_t N_ADDR_PINS = 10;
static constexpr uint32_t BASE_ADDR_PIN = 0;

static constexpr uint32_t N_DATA_PINS = 8;
static constexpr uint32_t BASE_DATA_PIN = 10;

static constexpr uint32_t N_BNKSEL_PINS = 4;
static constexpr uint32_t BASE_BNKSEL_PIN = 18;

static constexpr uint32_t N_IO_WR_PINS = 1;
static constexpr uint32_t BASE_IO_WR_PIN = 22;

static constexpr uint32_t ACTIVITY_LED_PIN = 25;

static constexpr uint32_t N_OE_PINS = 3;    // OE, CE & ROM EN
static constexpr uint32_t BASE_OE_PIN = 26;

static constexpr uint32_t ROM_SIZE = 0x01000;
static constexpr uint32_t ADDR_MASK = ROM_SIZE - 1;
static constexpr uint32_t FLASH_SIZE = 2 * 1024 * 1024;

#endif // SYSTEM_H