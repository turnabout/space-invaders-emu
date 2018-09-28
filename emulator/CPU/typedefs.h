// Typedefs used by CPU files
#include <stdint.h>

// Function returning pointer to a byte in emulated memory at the specified 
// offset
typedef uint8_t *(*API_Access_Memory)(uint16_t offset);