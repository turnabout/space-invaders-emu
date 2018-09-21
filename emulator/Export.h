#pragma once

// Export functions from DLL so they're available for unit tests
#ifdef _DEBUG
	#define EXPORT __declspec(dllexport)
#else
	#define EXPORT
#endif