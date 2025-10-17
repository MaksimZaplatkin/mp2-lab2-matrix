#include "tmatrix.h"
#include <gtest.h>


TEST(TDynamicMatrix, can_create_matrix_with_positive_length) {
    ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}


TEST(TDynamicMatrix, cant_create_too_large_matrix) {
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}


TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length) {
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}


TEST(TDynamicMatrix, can_create_copied_matrix) {
    TDynamicMatrix<int> m(5);

    ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}


TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one) {
    TDynamicMatrix<int> source(4);
    source[3][1] = 2;
    source[1][2] = 9;
    TDynamicMatrix<int> copied(source);

    EXPECT_EQ(source, copied);
}


TEST(TDynamicMatrix, copied_matrix_has_its_own_memory) {
    TDynamicMatrix<double> source(5);
    source[3][4] = 2.4;
    TDynamicMatrix<double> copied(source);
    copied[3][4] = 2.5;

    EXPECT_NE(source[3][4], copied[3][4]);
}


TEST(TDynamicMatrix, can_get_size) {
    TDynamicMatrix<int> m(5);
    EXPECT_EQ(5, m.size());
}


TEST(TDynamicMatrix, can_set_and_get_element) {
    TDynamicMatrix<int> m(4);
    m[2][1] = 4;

    EXPECT_EQ(4, m[2][1]);
}


TEST(TDynamicMatrix, throws_when_set_element_with_negative_index) {
    TDynamicMatrix<double> m(3);

    EXPECT_ANY_THROW(m.at(-1, 2) = 3.4);
    EXPECT_ANY_THROW(m.at(2, -1) = -32.1);
}


TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index) {
    TDynamicMatrix<double> m(3);

    EXPECT_ANY_THROW(m.at(1, 4) = 3.4);
    EXPECT_ANY_THROW(m.at(3, 2) = -32.1);
}


TEST(TDynamicMatrix, can_assign_matrix_to_itself) {
    TDynamicMatrix<int> m(10);
    m[3][0] = 2;
    m[9][4] = 1;

    TDynamicMatrix<int> _m(m);

    _m = _m;

    EXPECT_EQ(_m, _m);
}


TEST(TDynamicMatrix, can_assign_matrices_of_equal_size) {
    TDynamicMatrix<double> m(10);
    m[2][4] = 2;
    m[9][0] = 1.2;

    TDynamicMatrix<double> _m(10);
    _m[2][4] = 1.8;
    _m[3][8] = 5.2;

    _m = m;

    EXPECT_EQ(m, _m);
}


TEST(TDynamicMatrix, assign_operator_change_matrix_size) {
    TDynamicMatrix<double> m1(7);
    TDynamicMatrix<double> m2(10);

    m2 = m1;

    EXPECT_EQ(7, m2.size());
}


TEST(TDynamicMatrix, can_assign_matrices_of_different_size) {
    TDynamicMatrix<double> m1(7);
    TDynamicMatrix<double> m2(10);

    m1[0][4] = 3;
    m2[0][4] = 1.3;
    m2[9][3] = 4.1;

    m2 = m1;

    EXPECT_EQ(m1, m2);
}


TEST(TDynamicMatrix, compare_equal_matrices_return_true) {
    TDynamicMatrix<int> m1(10), m2(10);

    m1[0][4] = -1;
    m2[0][4] = -1;
    m1[3][7] = 43;
    m2[3][7] = 43;

    EXPECT_TRUE(m1 == m2);
}


TEST(TDynamicMatrix, compare_matrix_with_itself_return_true) {
    TDynamicMatrix<double> m(5);

    m[1][0] = -3.14;
    m[3][4] = 888.3;

    EXPECT_TRUE(m == m);
}


TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal) {
    TDynamicMatrix<int> m1(9), m2(10);

    EXPECT_FALSE(m1 == m2);

}


TEST(TDynamicMatrix, can_add_matrices_with_equal_size) {
    TDynamicMatrix<int> m1(4), m2(4), _m(4);

    m1[0][2] = m1[1][3] = m1[2][0] = m1[3][1] = 2;
    m2[0][2] = m2[1][3] = m2[2][0] = m2[3][1] = 6;
    _m[0][2] = _m[1][3] = _m[2][0] = _m[3][1] = 8;

    EXPECT_EQ(m1 + m2, _m);
}


TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size) {
    TDynamicMatrix<int> m1(3), m2(4);

    m1[0][1] = m1[1][2] = m1[2][0] = 2;
    m2[0][2] = m2[1][3] = m2[2][0] = m2[3][1] = 3;

    ASSERT_ANY_THROW(m1 + m2);
}


TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size) {
    TDynamicMatrix<int> m1(4), m2(4), _m(4);

    m1[0][2] = m1[1][3] = m1[2][0] = m1[3][1] = 4;
    m2[0][2] = m2[1][3] = m2[2][0] = m2[3][1] = 1;
    _m[0][2] = _m[1][3] = _m[2][0] = _m[3][1] = 3;

    EXPECT_EQ(m1 - m2, _m);
}


TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size) {
    TDynamicMatrix<int> m1(3), m2(4);

    m1[0][1] = m1[1][2] = m1[2][0] = 2;
    m2[0][2] = m2[1][3] = m2[2][0] = m2[3][1] = 3;

    ASSERT_ANY_THROW(m1 - m2);
}