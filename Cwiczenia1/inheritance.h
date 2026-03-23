#include "matrix_test.h"
#include <string>
class MatrixWithLabel : public Matrix {
    std::string label;

public:
    using Matrix::Matrix; //dziedziczenie konstruktorow

    MatrixWithLabel(std::string l, int n, int m) : Matrix(n, m), label(l) {}

    MatrixWithLabel(std::string l, std::initializer_list<std::initializer_list<double>> list):Matrix(list), label(l) {}

    std::string getLabel() const { return label; }
    void setLabel(std::string l) { label = l; }
};