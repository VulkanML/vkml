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


namespace vkml {
	class instance {
		static runtime::Instance runtime_instance;
		static runtime::Instance& rt() {
			return runtime_instance;
		}

		static compiler::Compiler compiler_instance;
		static compiler::Compiler& comp() {
			return compiler_instance;
		}

		static void iniitalize_device_compiler_attributes() {
			for (auto i = 0; i < rt().get_device_count(); ++i)
			{
				auto& dev = rt().get_device(i);
				comp().addDevice(i,
					dev.getVendorID(),
					dev.getDeviceType(),
					dev.getResourceLimits(),
					dev.getDeviceCapabilities(),
					dev.getSupportedExtensions());
			}
		}
		
		void initalize() {
			comp();
			rt();
			iniitalize_device_compiler_attributes();
		}

     public:
		 instance() {
			 initalize();
		 }


        void dump() {
			comp().run();
            comp().dump();
        }

		void addEmptyTensor(std::string name, std::vector<int64_t> shape, uint32_t type, uint32_t alignment) {
			comp().addTensor(name, shape, type, alignment);
		}

		void addBinaryOp(size_t operator_type, std::string op_name, std::string input_0_name, std::string input_1_name) {
			comp().addBitwiseOp(operator_type, op_name, input_0_name, input_1_name);
		}

		void addBitwiseOp(size_t operator_type, std::string op_name, std::string input_0_name, std::string input_1_name) {
			comp().addBitwiseOp(operator_type, op_name, input_0_name, input_1_name);
		}

		void addLogicalOp(size_t operator_type, std::string op_name, std::string input_0_name, std::string input_1_name) {
			comp().addLogicalOp(operator_type, op_name, input_0_name, input_1_name);
		}

		void addReductionOp(size_t operator_type, std::string op_name, std::string input_name) {
			comp().addReductionOp(operator_type, op_name, input_name);
		}

		void addRelationalOp(size_t operator_type, std::string op_name, std::string input_0_name, std::string input_1_name) {
			comp().addRelationalOp(operator_type, op_name, input_0_name, input_1_name);
		}

		void addUnaryOp(size_t operator_type, std::string op_name, std::string input_name) {
			comp().addUnaryOp(operator_type, op_name, input_name);
		}
	};

	// Define a static variable of the instance class named vkml_instance
	static instance vkml_instance;
}


#include "tensor.h"
#include "layers.h"


#endif