#include "test_utils/gtest_main.hpp"

#include <vec.hpp>

TEST(Engine, VecAddition) {
    Vec2 vec1({1.1, 2.2});
    Vec2 vec2({3.3, 4.4});
    EXPECT_TRUE((vec1 + vec2).equalsWithEpsilon(Vec2({4.4, 6.6})));

    Vec4 vec3({1.2, 2.4, 3.6, 4.8});
    Vec4 vec4({3.3, 4.5, 5.7, 6.9});
    vec3 += vec4;
    EXPECT_TRUE(vec3.equalsWithEpsilon(Vec4({4.5, 6.9, 9.3, 11.7})));
}

TEST(Engine, VecSubtraction) {
    Vec2 vec1({1.1, 2.2});
    Vec2 vec2({3.3, 4.4});
    EXPECT_TRUE((vec1 - vec2).equalsWithEpsilon(Vec2({-2.2, -2.2})));

    Vec4 vec3({1.0, 2.3, 3.2, 4.1});
    Vec4 vec4({3.5, 4.1, 5.0, 6.01});
    vec3 -= vec4;
    EXPECT_TRUE(vec3.equalsWithEpsilon(Vec4({-2.5, -1.8, -1.8, -1.91})));
}

TEST(Engine, VecMultiplication) {
    Vec2 vec1({1.1, 2.2});
    Vec2 vec2({3.3, 4.4});
    EXPECT_TRUE((vec1 * vec2).equalsWithEpsilon(Vec2({3.63, 9.68})));

    Vec4 vec3({1.1, 2.2, 3.3, 4.4});
    Vec4 vec4({3.3, 4.4, 5.5, 6.6});
    vec3 *= vec4;
    EXPECT_TRUE(vec3.equalsWithEpsilon(Vec4({3.63, 9.68, 18.15, 29.04})));
}

TEST(Engine, VecDivision) {
    Vec2 vec1({3.3, 4.4});
    Vec2 vec2({1.1, 2.2});
    EXPECT_TRUE((vec1 / vec2).equalsWithEpsilon(Vec2({3, 2})));

    Vec4 vec3({3.3, 4.4, 5.5, 6.4});
    Vec4 vec4({1.1, 2.2, 2.0, 4.0});
    vec3 /= vec4;
    EXPECT_TRUE(vec3.equalsWithEpsilon(Vec4({3, 2, 2.75, 1.6})));
}

TEST(Engine, VecNormalization) {
    Vec2 vec1({3.0, 4.0});
    EXPECT_FLOAT_EQ(vec1[0], 3.0);
    EXPECT_FLOAT_EQ(vec1[1], 4.0);
    EXPECT_THROW(vec1[2], std::runtime_error);

    EXPECT_TRUE(vec1.size() == 2);
    EXPECT_TRUE(vec1.length() == 5.0);

    auto normalized1 = vec1.normalized();
    EXPECT_TRUE(normalized1.equalsWithEpsilon(Vec2({0.6, 0.8})));
}