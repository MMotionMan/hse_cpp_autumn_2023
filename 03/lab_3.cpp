#include "lab_3.h"

Matrix::Matrix(size_t num_rows, size_t num_columns) : num_rows(num_rows), num_columns(num_columns) {
    this->rows_ = new int32_t[num_rows * num_columns];
}

Matrix::~Matrix() {
    delete[] this->rows_;
}

size_t Matrix::getColumns() const {
    return this->num_columns;
}

size_t Matrix::getRows() const {
    return this->num_rows;
}

int32_t &Matrix::ProxyRow::operator[](size_t j) const {
    if (j >= this->n_cols) {
        throw std::out_of_range("column index out of range");
    }
    return data_[j];
}


Matrix::ProxyRow::ProxyRow(int32_t *data, size_t n_cols) : data_(data), n_cols(n_cols) {}

Matrix::ProxyRow Matrix::operator[](size_t i) const {
    if (i >= this->num_columns) {
        throw std::out_of_range("row index out of range");
    }
    return Matrix::ProxyRow(&this->rows_[this->num_columns * i], this->num_columns);
}

void Matrix::operator*=(int32_t num) {
    for (size_t index = 0; index < this->num_columns * this->num_rows; ++index) {
        this->rows_[index] *= num;
    }
}

bool Matrix::operator==(Matrix const &rightMatrix) const {
    if (rightMatrix.getColumns() != this->num_columns || rightMatrix.getRows() != this->num_rows) {
        throw std::out_of_range("matrix dimensions don't match");
    }

    for (size_t i = 0; i < this->num_rows; ++i) {
        for (size_t j = 0; j < this->num_columns; ++j) {
            if (rightMatrix[i][j] != this->rows_[i * j]) {
                return false;
            }
        }
    }
    return true;

}

bool Matrix::operator!=(Matrix const &rightMatrix) const {
    return !Matrix::operator==(rightMatrix);
}

Matrix operator+(Matrix &leftMatrix, Matrix &rightMatrix) {
    if (rightMatrix.getRows() != leftMatrix.getRows() || rightMatrix.getColumns() != leftMatrix.getColumns())
        throw std::out_of_range("matrix dimensions don't match");

    Matrix ans_matrix = Matrix(rightMatrix.getRows(), rightMatrix.getColumns());

    for (size_t i = 0; i < rightMatrix.getRows(); ++i) {
        for (size_t j = 0; j < rightMatrix.getColumns(); ++j) {
            ans_matrix[i][j] = leftMatrix[i][j] + rightMatrix[i][j];
        }
    }

    return ans_matrix;
}

std::ostream &operator<<(std::ostream &out, Matrix &matrix) {
    out << std::endl;

    for (size_t i = 0; i < matrix.getRows(); ++i) {

        for (size_t j = 0; j < matrix.getColumns(); ++j) {
            out << matrix.rows_[i * j] << " ";
        }
        out << std::endl;
    }

    return out;
}