#pragma warning( disable : 4244 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4834 )
#pragma warning( disable : 4146 )
#pragma warning( disable : 4530 )
#ifndef vkml_H
#define vkml_H
#include "tensor.h"
#include "layers.h"

#include "vkml_compiler.h"
#include "vkrt.h"

auto vkInst = vkrt::Instance();
auto compInst = vkml_compiler::compiler();

void define_device_attributes() {
	
	for (auto i = 0; i < vkInst.get_device_count(); ++i)
	{
		auto dev = vkInst.get_device(i);
		auto capabilities = dev.getDeviceCapabilities();
		auto device_type_id = dev.getDeviceType();
		auto extensions = dev.getSupportedExtensions();
		auto resource_limits = dev.getResourceLimits();

		compInst.addDevice(i, dev.getVendorID(), device_type_id, resource_limits, capabilities, extensions);
	}
}



#endif