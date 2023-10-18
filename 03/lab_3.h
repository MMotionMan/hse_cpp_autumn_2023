#pragma once
#include <iostream>

class Matrix
        {
    class ProxyRow
    {
    private:
        int32_t *data_;
        size_t n_cols;
    public:
        ProxyRow(int32_t *data, size_t n_cols);
        int32_t& operator[](size_t j) const;
    };
private:
    int32_t *rows_;
    size_t num_rows;
    size_t num_columns;

public:
    Matrix(size_t num_rows, size_t num_columns);
    ~Matrix();
    size_t getColumns() const;
    size_t getRows() const;
    ProxyRow operator [](size_t i) const;
    void operator*=(int32_t num);
    bool operator==(Matrix const &rightMatrix) const;
    bool operator!=(Matrix const &rightMatrix) const;
    friend Matrix operator+(Matrix &lhs, Matrix &rhs);
    friend std::ostream& operator<<(std::ostream& out, Matrix &matrix);

};