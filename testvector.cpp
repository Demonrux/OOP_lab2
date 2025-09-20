#include "vector.h"
#include <gtest/gtest.h>

TEST(VectorTest, Constructors) {
    Vector<int> v1;
    EXPECT_EQ(v1.size(), 0);

    Vector<int> v2(5);
    EXPECT_EQ(v2.size(), 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(v2[i], 0);
    }

    Vector<int> v3 = {1, 2, 3};
    EXPECT_EQ(v3.size(), 3);
    EXPECT_EQ(v3[0], 1);
    EXPECT_EQ(v3[1], 2);
    EXPECT_EQ(v3[2], 3);

    Vector<int> v4(v3);
    EXPECT_EQ(v4.size(), 3);

    Vector<int> v5(std::move(v4));
    EXPECT_EQ(v5.size() , 3);
    EXPECT_EQ(v4.isEmpty(), true);
}

TEST(VectorTest, ElementAccess) {
    Vector<int> v = {10, 20, 30};

    EXPECT_EQ(v[0], 10);
    v[1] = 25;
    EXPECT_EQ(v[1], 25);

    v.setElem(2, 35);
    EXPECT_EQ(v.getElem(2), 35);

    EXPECT_THROW(v[3], std::out_of_range);
    EXPECT_THROW(v.getElem(-1), std::out_of_range);
}

TEST(VectorTest, ArithmeticOperations) {
    Vector<int> a = {1, 2, 3};
    Vector<int> b = {4, 5, 6};

    Vector<int> sum = a + b;
    EXPECT_EQ(sum[0], 5);
    EXPECT_EQ(sum[1], 7);
    EXPECT_EQ(sum[2], 9);

    Vector<int> scaled = a * 2;
    EXPECT_EQ(scaled[0], 2);
    EXPECT_EQ(scaled[1], 4);
    EXPECT_EQ(scaled[2], 6);

    Vector<double> c = {4.0, 6.0, 8.0};
    Vector<double> div = c / 2.0;
    EXPECT_DOUBLE_EQ(div[0], 2.0);
    EXPECT_DOUBLE_EQ(div[1], 3.0);
    EXPECT_THROW(div /= 0, std::invalid_argument);
}

TEST(VectorTest, Iterators) {
    Vector<int> v = {1, 2, 3};
    int sum = 0;

    for (const auto& item : v) {
        sum += item;
    }
    EXPECT_EQ(sum, 6);

    auto it = v.begin();
    *it = 10;
    EXPECT_EQ(v[0], 10);
}

TEST(VectorTest, AdditionalMethods) {
    Vector<int> v;

    v.pushBack(10);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 10);

    v.popBack();
    EXPECT_EQ(v.size(), 0);
    EXPECT_THROW(v.popBack(), std::out_of_range);

    v = {1, 2, 3};
    v.clear();
    EXPECT_TRUE(v.isEmpty());
}
