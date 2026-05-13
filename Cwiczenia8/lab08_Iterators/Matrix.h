#pragma once

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <iterator>

using namespace std;

template <typename T, size_t N, size_t M>
class Matrix {
    T data[N * M];

    //chcemy umożliwić tworzenie macierzy jako "stałych kompilacji ->constexpr
    //by cos bylo constexpr argumenty tej funkcji tez musza byc constexprr
    //Operacje wejścia/wyjścia (I/O) nie mogą być constexpr
    //constexpr - constexpr, kompilator nie generuje kodu, który "wyciąga"
    //tę wartość z pamięci RAM podczas działania programu. Zamiast tego, kompilator sam wykonuje obliczenie

public:
    // ── size queries ────────────────────────────────────────────────────────
    constexpr size_t numberOfRows()    const noexcept { return N; }
    constexpr size_t numberOfColumns() const noexcept { return M; }

    // ── constructors ────────────────────────────────────────────────────────
    constexpr explicit Matrix(T initValue = T{}) {
        for (size_t i = 0; i < N * M; ++i) data[i] = initValue;
    }

    constexpr Matrix(const std::initializer_list<std::initializer_list<T>>& list) {
        for (size_t i = 0; i < N * M; ++i) data[i] = T{};
        size_t r = 0;
        for (const auto& row : list) {
            if (r >= N) break;
            size_t c = 0;
            for (const auto& val : row) {
                if (c >= M) break;
                data[r * M + c] = val;
                ++c;
            }
            ++r;
        }
    }

    constexpr Matrix(const Matrix& m) {
        for (size_t i = 0; i < N * M; ++i) data[i] = m.data[i];
    }

    constexpr Matrix& operator=(const Matrix& m) {
        if (&m != this) {
            for (size_t i = 0; i < N * M; ++i) data[i] = m.data[i];
        }
        return *this;
    }

    constexpr Matrix& operator=(const std::initializer_list<std::initializer_list<T>>& list) {
        for (size_t i = 0; i < N * M; ++i) data[i] = T{};
        size_t r = 0;
        for (const auto& row : list) {
            if (r >= N) break;
            size_t c = 0;
            for (const auto& val : row) {
                if (c >= M) break;
                data[r * M + c] = val;
                ++c;
            }
            ++r;
        }
        return *this;
    }

    // ── element access ──────────────────────────────────────────────────────
    constexpr T& operator()(int i, int j) noexcept {
        return data[(i - 1) * M + j - 1];
    }
    constexpr const T& operator()(int i, int j) const noexcept {
        return data[(i - 1) * M + j - 1];
    }

    // ── arithmetic ──────────────────────────────────────────────────────────
    constexpr friend Matrix operator+(const Matrix& a, const Matrix& b) {// czy lyknie constexpr czy policzy na etapie kompilacji
        Matrix r;
        for (size_t i = 1; i <= N; ++i)
            for (size_t j = 1; j <= M; ++j)
                r(i, j) = a(i, j) + b(i, j);
        return r;
    }

    // ════════════════════════════════════════════════════════════════════════
    //  Iteratory (Klasy wewnętrzne)
    // ════════════════════════════════════════════════════════════════════════

    // Standardowy iterator (row-major)
    class iterator {
        T* ptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        constexpr explicit iterator(T* p) noexcept : ptr(p) {}
        constexpr reference operator*()  const noexcept { return *ptr; }
        constexpr pointer   operator->() const noexcept { return ptr; }
        constexpr iterator& operator++() noexcept { ++ptr; return *this; }
        constexpr iterator  operator++(int) noexcept { iterator tmp = *this; ++ptr; return tmp; }
        constexpr bool operator==(const iterator& o) const noexcept { return ptr == o.ptr; }
        constexpr bool operator!=(const iterator& o) const noexcept { return ptr != o.ptr; }
    };

    // Standardowy const_iterator
    class const_iterator {
        const T* ptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;
        constexpr explicit const_iterator(const T* p) noexcept : ptr(p) {}
        constexpr reference operator*()  const noexcept { return *ptr; }
        constexpr pointer   operator->() const noexcept { return ptr; }
        constexpr const_iterator& operator++() noexcept { ++ptr; return *this; }
        constexpr const_iterator  operator++(int) noexcept { const_iterator tmp = *this; ++ptr; return tmp; }
        constexpr bool operator==(const const_iterator& o) const noexcept { return ptr == o.ptr; }
        constexpr bool operator!=(const const_iterator& o) const noexcept { return ptr != o.ptr; }
    };

    // Row iterator
    class row_iterator {
        T* ptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        constexpr explicit row_iterator(T* p) noexcept : ptr(p) {}
        constexpr reference operator*()  const noexcept { return *ptr; }
        constexpr pointer   operator->() const noexcept { return ptr; }
        constexpr row_iterator& operator++() noexcept { ++ptr; return *this; }
        constexpr row_iterator  operator++(int) noexcept { row_iterator tmp = *this; ++ptr; return tmp; }
        constexpr bool operator==(const row_iterator& o) const noexcept { return ptr == o.ptr; }
        constexpr bool operator!=(const row_iterator& o) const noexcept { return ptr != o.ptr; }
    };

    // Column iterator (Stride = M)
    class col_iterator {
        T* ptr;
        size_t stride;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        constexpr col_iterator(T* p, size_t s) noexcept : ptr(p), stride(s) {}
        constexpr reference operator*()  const noexcept { return *ptr; }
        constexpr pointer   operator->() const noexcept { return ptr; }
        constexpr col_iterator& operator++() noexcept { ptr += stride; return *this; }
        constexpr col_iterator  operator++(int) noexcept { col_iterator tmp = *this; ptr += stride; return tmp; }
        constexpr bool operator==(const col_iterator& o) const noexcept { return ptr == o.ptr; }
        constexpr bool operator!=(const col_iterator& o) const noexcept { return ptr != o.ptr; }
    };

    // ── Metody begin/end ───────────────────────────────────────────────────
    constexpr iterator       begin()        noexcept { return iterator(data); }
    constexpr iterator       end()          noexcept { return iterator(data + N * M); }
    constexpr const_iterator begin()  const noexcept { return const_iterator(data); }
    constexpr const_iterator end()    const noexcept { return const_iterator(data + N * M); }

    // Wiersze (z przeciążeniem const)
    constexpr row_iterator       row_begin(int n)       noexcept { return row_iterator(data + (n - 1) * M); }
    constexpr row_iterator       row_end  (int n)       noexcept { return row_iterator(data + n * M); }
    constexpr const_iterator     row_begin(int n) const noexcept { return const_iterator(data + (n - 1) * M); }
    constexpr const_iterator     row_end  (int n) const noexcept { return const_iterator(data + n * M); }

    // Kolumny (z przeciążeniem const)
    constexpr col_iterator       col_begin(int n)       noexcept { return col_iterator(data + (n - 1), M); }
    constexpr col_iterator       col_end  (int n)       noexcept { return col_iterator(data + (n - 1) + N * M, M); }

    // Wersja const dla col_iterator – uproszczona poprzez użycie wskaźnika const T*
    class const_col_iterator {
        const T* ptr;
        size_t stride;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;
        constexpr const_col_iterator(const T* p, size_t s) noexcept : ptr(p), stride(s) {}
        constexpr reference operator*()  const noexcept { return *ptr; }
        constexpr pointer   operator->() const noexcept { return ptr; }
        constexpr const_col_iterator& operator++() noexcept { ptr += stride; return *this; }
        constexpr bool operator==(const const_col_iterator& o) const noexcept { return ptr == o.ptr; }
        constexpr bool operator!=(const const_col_iterator& o) const noexcept { return ptr != o.ptr; }
    };

    constexpr const_col_iterator col_begin(int n) const noexcept { return const_col_iterator(data + (n - 1), M); }
    constexpr const_col_iterator col_end  (int n) const noexcept { return const_col_iterator(data + (n - 1) + N * M, M); }
};

template <typename T, size_t N, size_t M>
void printMatrix(const Matrix<T, N, M>& m, int width = 10) {
    for (size_t i = 1; i <= m.numberOfRows(); ++i) {
        for (size_t j = 1; j <= m.numberOfColumns(); ++j) {
            if (j != 1) cout << " ";
            cout << setw(width) << m(i, j);
        }
        cout << endl;
    }
}