#include <stdint.h>

#include "../Export.h"

// Convert two uint8_t (separated into hi/lo) into a single uint16_t
EXPORT uint16_t uint8_To_uint16(uint8_t hi, uint8_t lo);