#include "tmatrix.h"
#include <gtest.h>


TEST(TDynamicVector, can_create_vector_with_positive_length) {
    ASSERT_NO_THROW(TDynamicVector<int> v(5));
}


TEST(TDynamicVector, cant_create_too_large_vector) {
    ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}


TEST(TDynamicVector, throws_when_create_vector_with_negative_length) {
    ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}


TEST(TDynamicVector, can_create_copied_vector) {
    TDynamicVector<int> v(10);

    ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}


TEST(TDynamicVector, copied_vector_is_equal_to_source_one) {
    TDynamicVector<double> source(5);
    source[3] = 2.4;
    source[1] = 9.12;
    TDynamicVector<double> copied(source);

    EXPECT_EQ(source, copied);
}


TEST(TDynamicVector, copied_vector_has_its_own_memory) {
    TDynamicVector<double> source(5);
    source[3] = 2.4;
    TDynamicVector<double> copied(source);
    copied[3] = 2.5;

    EXPECT_NE(source[3], copied[3]);
}


TEST(TDynamicVector, can_get_size) {
    TDynamicVector<int> v(4);

    EXPECT_EQ(4, v.size());
}


TEST(TDynamicVector, can_set_and_get_element) {
    TDynamicVector<int> v(4);
    v[0] = 4;

    EXPECT_EQ(4, v[0]);
}


TEST(TDynamicVector, throws_when_set_element_with_negative_index) {
    TDynamicVector<char> v(5);

    ASSERT_ANY_THROW(v.at(-2) = 3);
}


TEST(TDynamicVector, throws_when_set_element_with_too_large_index) {
    TDynamicVector<char> v(15);

    ASSERT_ANY_THROW(v.at(15) = 3);
    ASSERT_ANY_THROW(v.at(MAX_VECTOR_SIZE) = 3);
}


TEST(TDynamicVector, can_assign_vector_to_itself) {
    TDynamicVector<double> v(10);
    v[3] = 2;
    v[9] = 1.2;

    TDynamicVector<double> _v(v);

    _v = _v;

    EXPECT_EQ(_v, _v);
}


TEST(TDynamicVector, can_assign_vectors_of_equal_size) {
    TDynamicVector<double> v(10);
    v[3] = 2;
    v[9] = 1.2;

    TDynamicVector<double> _v(10);
    v[3] = 1;
    v[4] = 5.2;

    _v = v;

    EXPECT_EQ(v, _v);
}


TEST(TDynamicVector, assign_operator_change_vector_size) {
    TDynamicVector<double> v1(7);
    TDynamicVector<double> v2(10);

    v2 = v1;

    EXPECT_EQ(7, v2.size());
}


TEST(TDynamicVector, can_assign_vectors_of_different_size) {
    TDynamicVector<double> v1(7);
    TDynamicVector<double> v2(10);

    v1[0] = 3;
    v2[0] = 1.3;
    v2[9] = 4.1;

    v2 = v1;

    EXPECT_EQ(v1, v2);
}


TEST(TDynamicVector, compare_equal_vectors_return_true) {
    TDynamicVector<int> v1(10), v2(10);

    v1[0] = -1;
    v2[0] = -1;
    v1[3] = 43;
    v2[3] = 43;

    EXPECT_TRUE(v1 == v2);
}


TEST(TDynamicVector, compare_vector_with_itself_return_true) {
    TDynamicVector<double> v(5);

    v[1] = -3.14;
    v[3] = 888.3;

    EXPECT_TRUE(v == v);
}


TEST(TDynamicVector, vectors_with_different_size_are_not_equal) {
    TDynamicVector<int> v1(9), v2(10);

    EXPECT_FALSE(v1 == v2);
}


TEST(TDynamicVector, can_add_scalar_to_vector) {
    TDynamicVector<int> v(4), _v(4);

    v[0] = v[1] = v[2] = v[3] = 1;
    _v[0] = _v[1] = _v[2] = _v[3] = 2;

    EXPECT_EQ(v + 1, _v);
}


TEST(TDynamicVector, can_subtract_scalar_from_vector) {
    TDynamicVector<int> v(4), _v(4);

    v[0] = v[1] = v[2] = v[3] = 2;
    _v[0] = _v[1] = _v[2] = _v[3] = 1;

    EXPECT_EQ(v - 1, _v);
}


TEST(TDynamicVector, can_multiply_scalar_by_vector) {
    TDynamicVector<int> v(4), _v(4);

    v[0] = v[1] = v[2] = v[3] = 2;
    _v[0] = _v[1] = _v[2] = _v[3] = 8;

    EXPECT_EQ(v * 4, _v);
}


TEST(TDynamicVector, can_add_vectors_with_equal_size) {
    TDynamicVector<int> v1(4), v2(4), _v(4);

    v1[0] = v1[1] = v1[2] = v1[3] = 2;
    v2[0] = v2[1] = v2[2] = v2[3] = 6;
    _v[0] = _v[1] = _v[2] = _v[3] = 8;

    EXPECT_EQ(v1 + v2, _v);
}


TEST(TDynamicVector, cant_add_vectors_with_not_equal_size) {
    TDynamicVector<int> v1(3), v2(4);

    v1[0] = v1[1] = v1[2] = 2;
    v2[0] = v2[1] = v2[2] = v2[3] = 3;

    ASSERT_ANY_THROW(v1 + v2);
}


TEST(TDynamicVector, can_subtract_vectors_with_equal_size) {
    TDynamicVector<int> v1(4), v2(4), _v(4);

    v1[0] = v1[1] = v1[2] = v1[3] = 9;
    v2[0] = v2[1] = v2[2] = v2[3] = 2;
    _v[0] = _v[1] = _v[2] = _v[3] = 7;

    EXPECT_EQ(v1 - v2, _v);
}


TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size) {
    TDynamicVector<int> v1(3), v2(4);

    v1[0] = v1[1] = v1[2] = 2;
    v2[0] = v2[1] = v2[2] = v2[3] = 3;

    ASSERT_ANY_THROW(v1 - v2);
}


TEST(TDynamicVector, can_multiply_vectors_with_equal_size) {
    TDynamicVector<int> v1(3), v2(3);

    v1[0] = 1;
    v1[1] = 4;
    v1[2] = 2;

    v2[0] = 2;
    v2[1] = -1;
    v2[2] = 3;

    EXPECT_EQ(v1 * v2, 4);
}


TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size) {
    TDynamicVector<int> v1(3), v2(4);

    v1[0] = v1[1] = v1[2] = 2;
    v2[0] = v2[1] = v2[2] = v2[3] = 3;

    ASSERT_ANY_THROW(v1 * v2);
}