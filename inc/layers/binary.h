#ifndef BINARY_H
#define BINARY_H

namespace vkml {
    static size_t bin_op_id = 0;
    template<typename T, typename T2, BINARY_ARITH_TYPE type>
    static tensor<T> binary_operation(tensor<T>& self, tensor<T2>& other, bool inplace = false) {
        std::string op_name = "binary_" + std::to_string(bin_op_id++) + " " + self.get_name();
        vkml_instance.addBinaryOp((size_t)type, op_name, self.get_name(), other.get_name());
        return tensor<T>(self.get_shape(), op_name);
    }

    template<typename T, typename T2>
    static tensor<T> add(tensor<T>& self, tensor<T2>& other, bool inplace = false) {
        return binary_operation<T, T2, BINARY_ARITH_TYPE::ARITH_ADD>(self, other, inplace);
    }

    template<typename T, typename T2>
    static tensor<T> sub(tensor<T>& self, tensor<T2>& other, bool inplace = false) {
        return binary_operation<T, T2, BINARY_ARITH_TYPE::ARITH_SUB>(self, other, inplace);
    }

    template<typename T, typename T2>
    static tensor<T> mul(tensor<T>& self, tensor<T2>& other, bool inplace = false) {
        return binary_operation<T, T2, BINARY_ARITH_TYPE::ARITH_MUL>(self, other, inplace);
    }

    template<typename T, typename T2>
    static tensor<T> div(tensor<T>& self, tensor<T2>& other, bool inplace = false) {
        return binary_operation<T, T2, BINARY_ARITH_TYPE::ARITH_DIV>(self, other, inplace);
    }

    template<typename T, typename T2>
    static tensor<T> Max(tensor<T>& self, tensor<T2>& other, bool inplace = false) {
        return binary_operation<T, T2, BINARY_ARITH_TYPE::ARITH_MAX>(self, other, inplace);
    }

    template<typename T, typename T2>
    static tensor<T> Min(tensor<T>& self, tensor<T2>& other, bool inplace = false) {
        return binary_operation<T, T2, BINARY_ARITH_TYPE::ARITH_MIN>(self, other, inplace);
    }

    template<typename T, typename T2>
    static tensor<T> pow(tensor<T>& self, tensor<T2>& other, bool inplace = false) {
        return binary_operation<T, T2, BINARY_ARITH_TYPE::ARITH_POW>(self, other, inplace);
    }

    template<typename T, typename T2>
    static tensor<T> mod(tensor<T>& self, tensor<T2>& other, bool inplace = false) {
        return binary_operation<T, T2, BINARY_ARITH_TYPE::ARITH_MOD>(self, other, inplace);
    }
}

#endif // BINARY_H