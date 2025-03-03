#ifndef RELATIONAL_H
#define RELATIONAL_H

#include <type_traits>

namespace vkml {
    static size_t relational_op_id = 0;

    template<typename T, RELATIONAL_TYPE type>
    static typename std::enable_if<std::is_integral<T>::value, tensor<T>>::type 
    relational_operation(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        std::string op_name = "relational_" + std::to_string(relational_op_id++) + " " + self.get_name();
        vkml_instance.addRelationalOp((size_t)type, op_name, self.get_name(), other.get_name());
        return tensor<bool>(self.get_shape(), op_name);
    }

    template<typename T>
    tensor<bool> relational_lt(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        return relational_operation<T, RELATIONAL_TYPE::RELATIONAL_LT>(self, other, inplace);
    }

    template<typename T>
    tensor<bool> relational_le(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        return relational_operation<T, RELATIONAL_TYPE::RELATIONAL_LE>(self, other, inplace);
    }

    template<typename T>
    tensor<bool> relational_gt(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        return relational_operation<T, RELATIONAL_TYPE::RELATIONAL_GT>(self, other, inplace);
    }

    template<typename T>
    tensor<bool> relational_ge(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        return relational_operation<T, RELATIONAL_TYPE::RELATIONAL_GE>(self, other, inplace);
    }

    template<typename T>
    tensor<bool> relational_eq(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        return relational_operation<T, RELATIONAL_TYPE::RELATIONAL_EQ>(self, other, inplace);
    }

    template<typename T>
    tensor<bool> relational_ne(tensor<T>& self, tensor<T>& other, bool inplace = false) {
        return relational_operation<T, RELATIONAL_TYPE::RELATIONAL_NE>(self, other, inplace);
    }
}
#endif // RELATIONAL_H