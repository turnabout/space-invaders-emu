//
// Functions used by the CPU internally
//

#include "typedefs.h"

// Contains all 8080 functions that were defined externally (memory access, io,
// etc) from 'Initialize_CPU'.
typedef struct API8080 {
	API_Access_Memory accessMem;
} API8080;

// Get access to the CPU's externally-defined API functions
API8080 *Get_API();