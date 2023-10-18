#include <gtest/gtest.h>
#include "lab_3.cpp"
#include <fstream>

TEST(MyMatrix, SubscriptOverloadingTest) {
    size_t num_rows = 2;
    size_t num_columns = 4;
    Matrix mat1 = Matrix(num_rows, num_columns);
    std::vector<std::vector<int32_t> > test_matrix(num_rows, std::vector<int32_t>(num_columns, 1));

    for (size_t i = 0; i < num_rows; ++i) {

        for (size_t j = 0; j < num_columns; ++j) {
            mat1[i][j] = i + j;
            test_matrix[i][j] = i + j;
        }
    }
    ASSERT_EQ(mat1[1][2], test_matrix[1][2]);
}

TEST(MyMatrix, GetColumnsTest) {
    size_t num_rows = 2;
    size_t num_columns = 4;
    Matrix matrix = Matrix(num_rows, num_columns);
    ASSERT_EQ(matrix.getColumns(), num_columns);
}

TEST(MyMatrix, GetRowTest) {
    size_t num_rows = 2;
    size_t num_columns = 4;
    Matrix matrix = Matrix(num_rows, num_columns);
    ASSERT_EQ(matrix.getRows(), num_rows);
}

TEST(MyMatrix, MultMatrixByNumberTest) {
    size_t num_rows = 2;
    size_t num_columns = 4;
    int32_t mult_num = 8;
    Matrix matrix = Matrix(num_rows, num_columns);

    for (size_t i = 0; i < num_rows; ++i) {

        for (size_t j = 0; j < num_columns; ++j) {
            matrix[i][j] = 1;
        }
    }
    matrix *= mult_num;
    ASSERT_EQ(matrix[1][3], 8);
}

TEST(MyMatrix, OverloadEqualityTest) {
    size_t num_rows = 2;
    size_t num_columns = 4;
    Matrix matrix1 = Matrix(num_rows, num_columns);
    Matrix matrix2 = Matrix(num_rows, num_columns);

    for (size_t i = 0; i < num_rows; ++i) {

        for (size_t j = 0; j < num_columns; ++j) {
            matrix1[i][j] = 1;
            matrix2[i][j] = 1;
        }

    }
    bool res = matrix1 == matrix2;
    ASSERT_TRUE(res);
}

TEST(MyMatrix, OverloadNotEqualityTest) {
    size_t num_rows = 2;
    size_t num_columns = 4;
    Matrix matrix1 = Matrix(num_rows, num_columns);
    Matrix matrix2 = Matrix(num_rows, num_columns);

    for (size_t i = 0; i < num_rows; ++i) {

        for (size_t j = 0; j < num_columns; ++j) {
            matrix1[i][j] = 1;
            matrix2[i][j] = 1;
        }

    }
    bool res = matrix1 != matrix2;
    ASSERT_FALSE(res);
}

TEST(MyMatrix, MatrixSumTest) {
    size_t num_rows = 2;
    size_t num_columns = 4;
    Matrix matrix1 = Matrix(num_rows, num_columns);
    Matrix matrix2 = Matrix(num_rows, num_columns);

    for (size_t i = 0; i < num_rows; ++i) {

        for (size_t j = 0; j < num_columns; ++j) {
            matrix1[i][j] = 1;
            matrix2[i][j] = 1;
        }

    }
    Matrix matrix3 = matrix1 + matrix2;

    for (size_t i = 0; i < num_rows; ++i) {

        for (size_t j = 0; j < num_rows; ++j) {
            ASSERT_EQ(matrix1[i][i] * 2, matrix3[i][j]);
        }

    }
}

TEST(MyMatrix, OstreamOverridingTest) {
    size_t num_rows = 2;
    size_t num_columns = 4;
    Matrix matrix_out = Matrix(num_rows, num_columns);

    for (size_t i = 0; i < num_rows; ++i) {

        for (size_t j = 0; j < num_columns; ++j) {
            matrix_out[i][j] = i + j;
        }
    }

    std::ofstream out("testing_file.bin", std::ios::binary);

    if (out.is_open()) {
        out << matrix_out;
    }

    out.close();

    std::ifstream in("testing_file.bin", std::ios::binary);
    Matrix matrix_in = Matrix(num_rows, num_columns);

    int file_value;
    if (in.is_open()) {
        for (size_t i = 0; i < num_rows; ++i) {

            for (size_t j = 0; j < num_columns; ++j) {
                in >> file_value;
                matrix_in[i][j] = file_value;
            }
        }
    }

    remove("testing_file.bin");

    ASSERT_TRUE(matrix_out == matrix_in);
}

TEST(MyMatrix, OutOfRangeColsTest)
{
    size_t num_rows = 2;
    size_t num_columns = 4;
    Matrix matrix = Matrix(num_rows, num_columns);
    ASSERT_THROW(matrix[1][5], std::out_of_range);
}

TEST(MyMatrix, OutOfRangeRowTest)
{
    size_t num_rows = 2;
    size_t num_columns = 4;
    Matrix matrix = Matrix(num_rows, num_columns);
    ASSERT_THROW(matrix[5][1], std::out_of_range);
}

TEST(MyMatrix, MatrixDimensionsThrowTest)
{
    size_t num_rows1 = 2;
    size_t num_columns1 = 4;
    Matrix matrix1 = Matrix(num_rows1, num_columns1);
    size_t num_rows2 = 3;
    size_t num_columns2 = 4;
    Matrix matrix2 = Matrix(num_rows2, num_columns2);
    ASSERT_THROW(bool res = matrix1==matrix2, std::out_of_range);
}


int main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}