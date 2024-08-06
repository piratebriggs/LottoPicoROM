#if !defined( SYSTEM_H )
#define SYSTEM_H 1

#include <stdint.h>

static constexpr uint32_t N_DATA_PINS = 8;
static constexpr uint32_t BASE_DATA_PIN = 12;

static constexpr uint32_t N_OE_PINS = 3;    // Maybe 3?
static constexpr uint32_t BASE_OE_PIN = 9;

static constexpr uint32_t N_ADDR_PINS = 8;
static constexpr uint32_t BASE_ADDR_PIN = 0;

static constexpr uint32_t N_SRAM_CE_PINS = 1;
static constexpr uint32_t BASE_SRAM_CE_PIN = 8;

static constexpr uint32_t ACTIVITY_LED_PIN = 25;

static constexpr uint32_t ROM_SIZE = 0x00100;
static constexpr uint32_t ADDR_MASK = ROM_SIZE - 1;
static constexpr uint32_t FLASH_SIZE = 2 * 1024 * 1024;

#endif // SYSTEM_H