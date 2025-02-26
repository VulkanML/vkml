#ifndef UNARY_H
#define UNARY_H


namespace vkml {
    static size_t op_id = 0;
    template<typename T, UNARY_ARITH_TYPE type>
    static tensor<T> unary_operation(tensor<T>& self, bool inplace = false) {
        std::string op_name = "unary_" + std::to_string(op_id++) + " " + self.get_name();
        compInst.addOp((size_t)type, op_name, self.get_name());
        return tensor<T>(self.get_shape(), op_name);
    }

    template<typename T>
    static tensor<T> abs(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_ABS>(self, inplace);
    }

    template<typename T>
    static tensor<T> neg(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_NEG>(self, inplace);
    }

    template<typename T>
    static tensor<T> sqrt(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_SQRT>(self, inplace);
    }

    template<typename T>
    static tensor<T> exp(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_EXP>(self, inplace);
    }

    template<typename T>
    static tensor<T> log(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_LOG>(self, inplace);
    }

    template<typename T>
    static tensor<T> sin(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_SIN>(self, inplace);
    }

    template<typename T>
    static tensor<T> cos(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_COS>(self, inplace);
    }

    template<typename T>
    static tensor<T> tan(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_TAN>(self, inplace);
    }

    template<typename T>
    static tensor<T> asin(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_ASIN>(self, inplace);
    }

    template<typename T>
    static tensor<T> acos(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_ACOS>(self, inplace);
    }

    template<typename T>
    static tensor<T> atan(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_ATAN>(self, inplace);
    }

    template<typename T>
    static tensor<T> sinh(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_SINH>(self, inplace);
    }

    template<typename T>
    static tensor<T> cosh(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_COSH>(self, inplace);
    }

    template<typename T>
    static tensor<T> tanh(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_TANH>(self, inplace);
    }

    template<typename T>
    static tensor<T> asinh(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_ASINH>(self, inplace);
    }

    template<typename T>
    static tensor<T> acosh(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_ACOSH>(self, inplace);
    }

    template<typename T>
    static tensor<T> atanh(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_ATANH>(self, inplace);
    }

    template<typename T>
    static tensor<T> ceil(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_CEIL>(self, inplace);
    }

    template<typename T>
    static tensor<T> floor(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_FLOOR>(self, inplace);
    }

    template<typename T>
    static tensor<T> round(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_ROUND>(self, inplace);
    }

    template<typename T>
    static tensor<T> trunc(tensor<T>& self, bool inplace = false) {
        return unary_operation<T, UNARY_ARITH_TYPE::ARITH_TRUNC>(self, inplace);
    }
}

#endif