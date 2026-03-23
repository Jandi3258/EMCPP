#include "matrix_test.h"
Matrix::Matrix(Matrix&& other) noexcept : N(other.N), M(other.M), data(other.data) {
    other.data = nullptr;
    other.N = other.M = 0;
    std::cout << "move constructor" << std::endl;
}

Matrix Matrix::operator-() const{ // ani move ani copy
    Matrix m(N, M);
    for (int i = 0; i < N * M; i++) {
        if (this->data[i] != 0)
            m.data[i] = -this->data[i];
    }
    std::cout << "Unary operator" << std::endl;
    return m;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {//Operator przypisania przenoszący (Move Assignment)
    if (this != &other) {//&& - rvalue reference czyli tymczasowy obiekt zaraz do usuniecia
        delete[] data;
        data = other.data;//kradniemy
        N = other.N;
        M = other.M;
        other.data = nullptr; //zerujemy
        other.N = 0;
        other.M = 0;
        std::cout << "move assignment operator" << std::endl;
    }
    return *this;
}