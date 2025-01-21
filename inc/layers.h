#include "tensor.h"


namespace arithmetic {
    enum BINARY_ARITH_TYPE {
        ARITH_ADD,
        ARITH_SUB,
        ARITH_MUL,
        ARITH_DIV,
        ARITH_MAX,
        ARITH_MIN,
        ARITH_POW,
        ARITH_MOD
    };

	enum REDUCTION_TYPE {
		REDUCTION_SUM,
		REDUCTION_MAX,
		REDUCTION_MIN,
		REDUCTION_MEAN,
		REDUCTION_PROD,
		REDUCTION_L0,
		REDUCTION_L1
	};

    enum UNARY_ARITH_TYPE {
        ARITH_ABS,
        ARITH_NEG,
        ARITH_SQRT,
        ARITH_EXP,
        ARITH_LOG,
        ARITH_SIN,
        ARITH_COS,
        ARITH_TAN,
        ARITH_ASIN,
        ARITH_ACOS,
        ARITH_ATAN,
        ARITH_SINH,
        ARITH_COSH,
        ARITH_TANH,
        ARITH_ASINH,
        ARITH_ACOSH,
        ARITH_ATANH,
        ARITH_CEIL,
        ARITH_FLOOR,
        ARITH_ROUND,
        ARITH_TRUNC       
    };
}

namespace logical {
    enum LOGICAL_TYPE {
        LOGICAL_AND,
        LOGICAL_OR,
        LOGICAL_XOR
    };
}

namespace relational {
    enum RELATIONAL_TYPE {
        RELATIONAL_LT,
        RELATIONAL_LE,
        RELATIONAL_GT,
        RELATIONAL_GE,
        RELATIONAL_EQ,
        RELATIONAL_NE
    };
}

namespace index {
    enum INDEX_TYPE{
        FOLD,
        FLATTEN,
        RESHAPE,
        SLICE,
        TRANSPOSE,
        REVERSE,
        REPEAT,
        EXPAND
    };
}

#include "layers/unary.h"
#include "layers/binary.h"