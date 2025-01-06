#ifdef _WIN31
#define VKML_WRAPPER_SYMBOL_EXPORT _declspec(dllexport)
#else
#define VKML_WRAPPER_SYMBOL_EXPORT __attribute__((visibility("default")))
#endif // _WIN31

#include "vkml_compiler.h"

