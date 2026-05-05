#pragma once

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <iterator>
using namespace std;

template <typename T, size_t N, size_t M>
class Matrix {

    T data[N * M];

public:
    // ── size queries ────────────────────────────────────────────────────────
    constexpr size_t numberOfRows()    const noexcept { return N; }
    constexpr size_t numberOfColumns() const noexcept { return M; }

    // ── constructors ────────────────────────────────────────────────────────
    constexpr explicit Matrix(T initValue = T{}) {
        std::fill_n(data, N * M, initValue);
    }

    // Non-explicit: nested init-list cannot be confused with a scalar
    constexpr Matrix(const std::initializer_list<std::initializer_list<T>>& list) {
        T* p = data;
        for (const auto& row : list) {
            T* p2 = std::copy_n(row.begin(), min(row.size(), M), p);
            std::fill(p2, p += M, T{});
        }
        std::fill(p, data + N * M, T{});
    }

    constexpr Matrix(const Matrix& m) {
        std::copy_n(m.data, N * M, data);
    }

    constexpr Matrix& operator=(const Matrix& m) {
        if (&m != this)
            std::copy_n(m.data, N * M, data);
        return *this;
    }

    // explicit: prevents m2 = 4; from compiling
    constexpr Matrix& operator=(const std::initializer_list<std::initializer_list<T>>& list) {
        T* p = data;
        for (const auto& row : list) {
            T* p2 = std::copy_n(row.begin(), min(row.size(), M), p);
            std::fill(p2, p += M, T{});
        }
        std::fill(p, data + N * M, T{});
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
    friend Matrix operator+(const Matrix& a, const Matrix& b) {
        Matrix r;
        for (int i = 1; i <= (int)N; ++i)
            for (int j = 1; j <= (int)M; ++j)
                r(i, j) = a(i, j) + b(i, j);
        return r;
    }

    // ════════════════════════════════════════════════════════════════════════
    //  iterator  –  row-major traversal
    // ════════════════════════════════════════════════════════════════════════
    class iterator {
        T* ptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        explicit iterator(T* p) : ptr(p) {}
        T& operator*()  const noexcept { return *ptr; }
        T* operator->() const noexcept { return ptr; }
        iterator& operator++() noexcept { ++ptr; return *this; }
        iterator  operator++(int) noexcept { iterator tmp = *this; ++ptr; return tmp; }
        bool operator==(const iterator& o) const noexcept { return ptr == o.ptr; }
        bool operator!=(const iterator& o) const noexcept { return ptr != o.ptr; }
    };

    // ════════════════════════════════════════════════════════════════════════
    //  const_iterator  –  row-major traversal (read-only)
    // ════════════════════════════════════════════════════════════════════════
    class const_iterator {
        const T* ptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        explicit const_iterator(const T* p) : ptr(p) {}
        const T& operator*()  const noexcept { return *ptr; }
        const T* operator->() const noexcept { return ptr; }
        const_iterator& operator++() noexcept { ++ptr; return *this; }
        const_iterator  operator++(int) noexcept { const_iterator tmp = *this; ++ptr; return tmp; }
        bool operator==(const const_iterator& o) const noexcept { return ptr == o.ptr; }
        bool operator!=(const const_iterator& o) const noexcept { return ptr != o.ptr; }
    };

    // ════════════════════════════════════════════════════════════════════════
    //  row_iterator  –  iterates a single row
    // ════════════════════════════════════════════════════════════════════════
    class row_iterator {
        T* ptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        explicit row_iterator(T* p) : ptr(p) {}
        T& operator*()  const noexcept { return *ptr; }
        T* operator->() const noexcept { return ptr; }
        row_iterator& operator++() noexcept { ++ptr; return *this; }
        row_iterator  operator++(int) noexcept { row_iterator tmp = *this; ++ptr; return tmp; }
        bool operator==(const row_iterator& o) const noexcept { return ptr == o.ptr; }
        bool operator!=(const row_iterator& o) const noexcept { return ptr != o.ptr; }
    };

    // ════════════════════════════════════════════════════════════════════════
    //  col_iterator  –  iterates a single column (stride = M)
    // ════════════════════════════════════════════════════════════════════════
    class col_iterator {
        T*     ptr;
        size_t stride; // = M
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        col_iterator(T* p, size_t s) : ptr(p), stride(s) {}
        T& operator*()  const noexcept { return *ptr; }
        T* operator->() const noexcept { return ptr; }
        col_iterator& operator++() noexcept { ptr += stride; return *this; }
        col_iterator  operator++(int) noexcept { col_iterator tmp = *this; ptr += stride; return tmp; }
        bool operator==(const col_iterator& o) const noexcept { return ptr == o.ptr; }
        bool operator!=(const col_iterator& o) const noexcept { return ptr != o.ptr; }
    };

    // ── whole-matrix begin/end ───────────────────────────────────────────────
    iterator       begin()        noexcept { return iterator(data); }
    iterator       end()          noexcept { return iterator(data + N * M); }
    const_iterator begin()  const noexcept { return const_iterator(data); }
    const_iterator end()    const noexcept { return const_iterator(data + N * M); }
    const_iterator cbegin() const noexcept { return const_iterator(data); }
    const_iterator cend()   const noexcept { return const_iterator(data + N * M); }

    // ── row begin/end  (1-based row index n) ────────────────────────────────
    row_iterator row_begin(int n) noexcept { return row_iterator(data + (n - 1) * M); }
    row_iterator row_end  (int n) noexcept { return row_iterator(data + n * M); }

    // ── col begin/end  (1-based column index n) ─────────────────────────────
    col_iterator col_begin(int n) noexcept { return col_iterator(data + (n - 1), M); }
    col_iterator col_end  (int n) noexcept { return col_iterator(data + (n - 1) + N * M, M); }
};

// ── free printMatrix ─────────────────────────────────────────────────────────
template <typename T, size_t N, size_t M>
void printMatrix(const Matrix<T, N, M>& m, int width = 10) {
    for (int i = 1; i <= (int)m.numberOfRows(); ++i) {
        for (int j = 1; j <= (int)m.numberOfColumns(); ++j) {
            if (j != 1) cout << " ";
            cout << setw(width) << m(i, j);
        }
        cout << endl;
    }
}