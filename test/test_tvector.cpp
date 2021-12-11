#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TVector<int> v(-3));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
	ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
	TVector<int> v(5);

	ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	TVector<int> v1(3);
	v1[0] = 1, v1[1] = 10, v1[2] = 20;

	TVector<int> v2 = v1;

	EXPECT_EQ(v1, v2);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int> v1(3);
	v1[0] = v1[1] = v1[2] = 1;

	TVector<int> v2 = v1;
	v2[0] = v2[1] = v2[2] = 11;

	for (int i = 0; i < 3; i++)
		ASSERT_TRUE((v1[i] == 1) && (v2[i] == 11));
}

TEST(TVector, can_get_size)
{
	TVector<int> v(3);

	EXPECT_EQ(3, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
	TVector<int> v(3, 2);

	EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
	TVector<int> v(3);
	ASSERT_NO_THROW(v[0] = 3);

	EXPECT_EQ(3, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> v(3);
	ASSERT_ANY_THROW(v[-1] = 10);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(3);
	ASSERT_ANY_THROW(v[4] = 100);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> v(3);
	v[0] = v[1] = v[2] = 1;

	ASSERT_NO_THROW(v = v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> v1(3), v2(3);
	v1[0] = v1[1] = v1[2] = 1;

	ASSERT_NO_THROW(v2 = v1);
	EXPECT_EQ(v2, v1);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> v1(3), v2(4);
	v2 = v1;
	EXPECT_EQ(v2.GetSize(), 3);
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> v1(4), v2(3);

	v1[0] = v1[1] = v1[2] = v1[3] = 1;

	v2 = v1;

	TVector<int> v(4);
	v[0] = v[1] = 1;
	v[2] = v[3] = 1;

	EXPECT_EQ(v2, v);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> v1(4, 0), v2(4, 0);

	v1[0] = 0, v1[1] = 1, v1[2] = 2, v1[3] = 3;

	v2[0] = 0, v2[1] = 1, v2[2] = 2, v2[3] = 3;

	EXPECT_EQ(v1, v2);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> v(3);
	v[0] = v[1] = v[2] = 1;

	EXPECT_EQ(v, v);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> v1(4), v2(5);
	for (int i = 0; i < 3; i++) {
		v1[i] = 10;
	}
	v2[4] = 10;
	ASSERT_TRUE(v1 != v2);
	ASSERT_FALSE(v1 == v2);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> v1(3);
	v1[0] = 0, v1[1] = 1, v1[2] = 2;

	TVector<int> res = v1 + 10;
	TVector<int> v(3);
	v[0] = 10, v[1] = 11, v[2] = 12;
	EXPECT_EQ(res, v);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> v1(3);
	v1[0] = 0, v1[1] = 1, v1[2] = 2;
	TVector<int> res = v1 - 10;
	TVector<int> v(3);
    v[0] = -10, v[1] = -9, v[2] = -8;

	EXPECT_EQ(res, v);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> v(3);
	v[0] = 0, v[1] = 1, v[2] = 2;
	TVector<int> res = v * 10;

	TVector<int> m(3);
	m[0] = 0, m[1] = 10, m[2] = 20;

	EXPECT_EQ(res,m);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> v1(3), v2(3);
	v1[0] = 1, v1[1] = 2, v1[2] = 3;
	v2[0] = 10, v2[1] = 20, v2[2] = 30;

	TVector<int> res = v1 + v2;
	TVector<int> m(3);
	m[0] = 11, m[1] = 22, m[2] = 33;

	EXPECT_EQ(res, m);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> v1(2), v2(3);
	v1[0] = 1, v1[1] = 2;
	v2[0] = 10, v2[1] = 20, v2[2] = 30;

	TVector<int> res;
	ASSERT_ANY_THROW(res = v1 + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> v1(3), v2(3);

	v1[0] = 1, v1[1] = 2, v1[2] = 3;
	v2[0] = 4, v2[1] = 4, v2[2] = 4;
	TVector<int> res = v2 - v1;
	TVector<int> m(3);
	m[0] = 3, m[1] = 2; m[2] = 1;

	EXPECT_EQ(res, m);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> v1(4), v2(5);
	v1[0] = 1, v1[1] = 2, v1[2] = 3;
	v2[0] = 4, v2[1] = 4, v2[2] = 4;
	TVector<int> res;

	ASSERT_ANY_THROW(res == v2 - v1);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> v1(4), v2(4);
	v1[0] = v1[1] = 0;
	v2[0] = v2[1] = 0;
	v1[2] = 10, v1[3] = 30;
	v2[2] = 20, v2[3] = 40;
	const int res = v1 * v2;
	ASSERT_EQ(res, 1400);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> v1(4), v2(5);
	for (int i = 0; i < 3; i++) 
	{
		v1[i] = 10;
		v2[i] = 20;
	}
	v2[4] = 20;
	ASSERT_ANY_THROW(v1 * v2);
}
