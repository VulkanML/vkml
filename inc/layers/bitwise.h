#ifndef BITWISE_H
#define BITWISE_H

#include <type_traits>

namespace vkml {
    static size_t op_id = 0;

    template<typename T, BITWISE_TYPE type>
    static typename std::enable_if<std::is_integral<T>::value, tensor<T>>::type 
    bitwise_operation(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        std::string op_name = "bitwise_" + std::to_string(op_id++) + " " + self.get_name();
        vkml_instance.addBitwiseOp((size_t)type, op_name, self.get_name(), other.get_name());
        return tensor<T>(self.get_shape(), op_name);
    }

    template<typename T>
    static typename std::enable_if<std::is_integral<T>::value, tensor<T>>::type
    bitwise_and(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        return bitwise_operation<T, BITWISE_TYPE::BITWISE_AND>(self, other, inplace);
    }

    template<typename T>
    static typename std::enable_if<std::is_integral<T>::value, tensor<T>>::type
    bitwise_or(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        return bitwise_operation<T, BITWISE_TYPE::BITWISE_OR>(self, other, inplace);
    }

    template<typename T>
    static typename std::enable_if<std::is_integral<T>::value, tensor<T>>::type
    bitwise_xor(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        return bitwise_operation<T, BITWISE_TYPE::BITWISE_XOR>(self, other, inplace);
    }

    template<typename T>
    static typename std::enable_if<std::is_integral<T>::value, tensor<T>>::type
    bitwise_not(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_NOT>(self, inplace);
    }

    template<typename T>
    static typename std::enable_if<std::is_integral<T>::value, tensor<T>>::type
    bitwise_lshift(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        return bitwise_operation<T, BITWISE_TYPE::BITWISE_LSHIFT>(self, other, inplace);
    }

    template<typename T>
    static typename std::enable_if<std::is_integral<T>::value, tensor<T>>::type
    bitwise_rshift(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        return bitwise_operation<T, BITWISE_TYPE::BITWISE_RSHIFT>(self, other, inplace);
    }
} // namespace vkml

#endif // BITWISE_H