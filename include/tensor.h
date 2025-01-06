#ifndef TENSOR_H
#define TENSOR_H
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>



enum class TYPES {
    UNKOWN,
    BOOL,
    CHAR,
    UCHAR,
    SHORT,
    USHORT,
    INT,
	UINT,
    LONG,
    ULONG,
	LONGLONG,
	ULONGLONG,
	FLOAT,
	DOUBLE,
	LDOUBLE,
    COUNT
};


class Expression {
    static std::unordered_map<std::string, std::unique_ptr<Expression>> _cache;

public:
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

template<typename T>
class constant : public Expression {
    T value;
public: 
    constant(T value) : value(value) {}
};

template<typename T>
class tensor : public Expression {
    std::vector<int> shape;   
    T value;

    public:
        tensor(){}
        tensor(const std::vector<int> &shape) : shape(shape) {};
        TYPES get_type(); 
};


TYPES tensor<bool>::get_type() {
    return TYPES::BOOL;
}


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

#endif