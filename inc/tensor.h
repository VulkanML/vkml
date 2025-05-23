#ifndef TENSOR_H
#define TENSOR_H

#include "type.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

namespace vkml {
    class Expression {
        static std::unordered_map<std::string, std::unique_ptr<Expression>> _cache;

    public:
        Expression() {}
        /*
        virtual void* eval() = 0;
        virtual std::unique_ptr<Expression> deriv(const std::vector<Expression*>& vars) = 0;
        virtual std::unique_ptr<Expression> clone() const = 0;
        */
        virtual ~Expression() {}

        Expression(Expression&& other) noexcept
        {
            if (this != &other)
                *this = std::move(other);
        }

        Expression& operator=(Expression&& other) noexcept
        {
            if (this != &other)
                *this = std::move(other);
            return *this;
        }

        //virtual std::string get_key() const = 0;
        //std::unique_ptr<Expression> memoized_deriv(const std::vector<Expression*>& vars)  {
        //    std::string key = get_key() + "_deriv";
        //    for(const auto& var: vars)
        //        key += "_" + var->get_key();
        //    auto it = _cache.find(key);
        //    if(it != _cache.end())
        //        return it->second->clone();
        //    auto result = deriv(vars);
        //    _cache[key] = result->clone();
        //    return result;
        //}

      

    };

    static size_t tensor_id = 0;       
    template<typename T>
    class tensor : public Expression {
        std::vector<int64_t> shape;
        T value = T(); // Initialize value
        std::string name;
    public:
        tensor() {}
        auto get_shape() const { return shape; }
        auto get_name() const { return name; }
        tensor(const std::vector<int64_t>& shape) : shape(shape), name("tensor_" + std::to_string(tensor_id++)) {
            vkml::vkml_instance.addEmptyTensor(name, this->shape, (uint32_t)get_type(), (uint32_t)0);
        };
        tensor(const std::vector<int64_t>& shape, std::string name) : shape(shape), name(name) { };
        TYPES get_type();
    };

    TYPES tensor<char>::get_type() {
        return TYPES::CHAR;
    }

    TYPES tensor<unsigned char>::get_type() {
        return TYPES::UCHAR;
    }

    TYPES tensor<short int>::get_type() {
        return TYPES::SHORT;
    }

    TYPES tensor<unsigned short int>::get_type() {
        return TYPES::USHORT;
    }

    TYPES tensor<int>::get_type() {
        return TYPES::INT;
    }

    TYPES tensor<unsigned int>::get_type() {
        return TYPES::UINT;
    }

    TYPES tensor<long int>::get_type() {
        return TYPES::LONG;
    }

    TYPES tensor<unsigned long int>::get_type() {
        return TYPES::ULONG;
    }

    TYPES tensor<long long int>::get_type() {
        return TYPES::LONGLONG;
    }

    TYPES tensor<unsigned long long int>::get_type() {
        return TYPES::ULONGLONG;
    }

    TYPES tensor<float>::get_type() {
        return TYPES::FLOAT;
    }

    TYPES tensor<double>::get_type() {
        return TYPES::DOUBLE;
    }

    TYPES tensor<long double>::get_type() {
        return TYPES::LDOUBLE;
    }

    template<typename T>
    class sparse_tensor : public tensor<T> {
        SparseFormat format;
        tensor<int> indices;

    public:
        sparse_tensor(SparseFormat format, const std::vector<int>& shape, const std::vector<int>& indices) :
            tensor<T>(shape), format(format), indices(tensor<int>(indices)) {};
        SparseFormat get_format() const { return format; }
    };

}

#endif // TENSOR_H