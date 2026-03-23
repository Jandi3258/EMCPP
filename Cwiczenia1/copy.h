#include "matrix_test.h"
Matrix::Matrix(const Matrix& other) : N(other.N), M(other.M) {//jeszcze dane trzeba przekopiowac
    data = new double[N*M];
    //memcpy(data, other.data, N*M*sizeof(double));
    for (int i = 0; i < N*M; i++) {
        data[i] = other.data[i];
    }
    std::cout << "copy constructor" << std::endl;
}

Matrix& Matrix::operator=(const Matrix& other) {//deep copy - bez usuwania
    if (this != &other) {//musimy usunac poprzednie
        delete[] data;//inne wymiary
        N = other.N;
        M = other.M;
        data = new double[N * M];
        for (int i = 0; i < N * M; i++) {
            this->data[i] = other.data[i];
        }
    }
    std::cout << "copy assignment operator" << std::endl;
    return *this;
}
