#ifdef _WIN31
#define VKML_WRAPPER_SYMBOL_EXPORT _declspec(dllexport)
#else
#define VKML_WRAPPER_SYMBOL_EXPORT __attribute__((visibility("default")))
#endif // _WIN31

#include "vkml.h"

namespace vkml {
    runtime::Instance vkml::instance::runtime_instance;
    compiler::Compiler vkml::instance::compiler_instance;
}