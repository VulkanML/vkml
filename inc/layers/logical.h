#ifndef LOGICAL_H
#define LOGICAL_H

#include <type_traits>

namespace vkml {
    static size_t logical_op_id = 0;
    template<typename T, LOGICAL_TYPE type> 
     static typename std::enable_if<std::is_integral<T>::value, tensor<T>>::type
    logical_operation(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        std::string op_name = "logical_" + std::to_string(logical_op_id++) + " " + self.get_name();
        vkml_instance.addLogicalOp((size_t)type, op_name, self.get_name(), other.get_name());
        return tensor<T>(self.get_shape(), op_name);
    }

    template<typename T>
      static typename std::enable_if<std::is_integral<T>::value, tensor<T>>::type
    logical_and(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        return logical_operation<T, LOGICAL_TYPE::LOGICAL_AND>(self, other, inplace);
    }

    template<typename T> 
     static typename std::enable_if<std::is_integral<T>::value, tensor<T>>::type
    logical_or(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        return logical_operation<T, LOGICAL_TYPE::LOGICAL_OR>(self, other, inplace);
    }

    template<typename T>  
    static typename std::enable_if<std::is_integral<T>::value, tensor<T>>::type
    logical_xor(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        return logical_operation<T, LOGICAL_TYPE::LOGICAL_XOR>(self, other, inplace);
    }

   /* template<typename T>  
    static typename std::enable_if<std::is_integral<T>::value, tensor<T>>::type
    logical_not(tensor<T>& self, bool inplace = false) {
        return logical_operation<T, LOGICAL_TYPE::NOT>(self);
    }*/
}

#endif // LOGICAL_H