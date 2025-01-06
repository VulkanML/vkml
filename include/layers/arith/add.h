

template<typename T>
struct ADD {
	tensor<T> a;
	tensor<T> b;

	tensor<T> out;

	ADD(const tensor<T>& a, const tensor<T>& b) : a(a), b(b) {
		out = tensor<T>(a.shape);
	}


};

template<typename T>
void CoreOperation(ADD<T> op, mlir::MLIRContext* ctx) {

}
