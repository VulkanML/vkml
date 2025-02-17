#pragma warning( disable : 4244 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4834 )
#pragma warning( disable : 4146 )
#pragma warning( disable : 4530 )
#ifndef vkml_H
#define vkml_H
#include "compiler.h"
#include "runtime.h"


auto vkInst = runtime::Instance();
auto compInst = compiler::Compiler();

void define_device_attributes() {
	
	for (auto i = 0; i < vkInst.get_device_count(); ++i)
	{
		auto& dev = vkInst.get_device(i);
		compInst.addDevice(i, 
			dev.getVendorID(), 
			dev.getDeviceType(),
			dev.getResourceLimits(),
			dev.getDeviceCapabilities(),
			dev.getSupportedExtensions() );
	}

}

void compile_module() {
	compInst.run();
	compInst.dump();
}

#include "tensor.h"
#include "layers.h"


#endif