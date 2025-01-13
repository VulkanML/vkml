





template<typename T>
struct ABS {
	tensor<T> a;
	tensor<T> out;

	ABS(const tensor<T>& a) : a(a) {
		out = tensor<T>(a.shape);
	}

};

