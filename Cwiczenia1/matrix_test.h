//
// Created by Pawel Jandula on 03/03/2026.
//

#ifndef COPYMOVEWLASNAIMPLEMENTACJA_MATRIX_TEST_H
#define COPYMOVEWLASNAIMPLEMENTACJA_MATRIX_TEST_H
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <string>
class Matrix {
protected:
    int N, M;
    double* data;
public:
    Matrix(): N(0), M(0), data(nullptr) {
        std::cout << "constructor of blank matrix" << std::endl;
    }

    Matrix(int N, int M): N(N), M(M) {
        data = new double[N*M];
        std::fill(data, data + (N * M), 0.0);
        std::cout << "constructor of " << N << "x" << M << " matrix" << std::endl;
    }
    Matrix(std::initializer_list<std::initializer_list<double>> list) {
        N = list.size();
        M = 0;
        for (const auto& row : list) {
            if (row.size() > M) M = row.size();
        }
        data = new double[N * M];
        std::fill(data, data + (N * M), 0.0);
        int i = 0;
        for (const auto& row : list) {
            int j = 0;
            for (double val : row) {
                data[i * M + j] = val;
                j++;
            }
            i++;
        }
        std::cout << "constructor of " << N << "x" << M << " matrix from initializer_list" << std::endl;
    }
    ~Matrix() {
        std::cout << "destructor" << std::endl;
        delete[] data;
    }
    double& operator()(int i, int j) {
        return data[(i - 1) * M + j - 1]; //nawiaski
    }
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        for (int i = 0; i < m.N; i++) {
            os << "{";
            for (int j = 0; j < m.M; j++) {
                os << m.data[(i) * m.M + j];
                if (j == m.M - 1) {
                    os << "";
                }
                else {
                    os << ", ";
                }

            }
            os << "}";
            os << std::endl;
        }
        return os;
    }
    //ponizej w innych plikach
    Matrix operator-() const;
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix&& other) noexcept;




};
#endif //COPYMOVEWLASNAIMPLEMENTACJA_MATRIX_TEST_H