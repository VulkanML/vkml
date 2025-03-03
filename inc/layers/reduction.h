#ifndef REDUCTION_H
#define REDUCTION_H

#include <type_traits>

namespace vkml {
    static size_t reduction_op_id = 0;
    template<typename T, REDUCTION_TYPE type>
    static tensor<T> reduction(tensor<T>& self, bool inplace = false) {
        std::string op_name = "reduction_" + std::to_string(reduction_op_id++) + " " + self.get_name();
        vkml_instance.addReductionOp((size_t)type, op_name, self.get_name());
        return tensor<T>(self.get_shape(), op_name);
    }

    template<typename T>
    static tensor<T> sum(tensor<T>& self, bool inplace = false) {
        return reduction<T, REDUCTION_TYPE::REDUCTION_SUM>(self, inplace);
    }

    template<typename T>
    static tensor<T> prod(tensor<T>& self, bool inplace = false) {
        return reduction<T, REDUCTION_TYPE::REDUCTION_PROD>(self, inplace);
    }

    template<typename T>
    static tensor<T> l0(tensor<T>& self, bool inplace = false) {
        return reduction<T,REDUCTION_TYPE::REDUCTION_L0>(self, inplace);
    }

    template<typename T>
    static tensor<T> l1(tensor<T>& self, bool inplace = false) {
        return reduction<T, REDUCTION_TYPE::REDUCTION_L1>(self, inplace);
    }
}

#endif // REDUCTION_H