#include "gtest/gtest.h"
#include "vector.h" // 包含你的 Vector3 头文件
#include "mathUtility.h" // 包含你的 MathUtility 头文件，因为 Vector3 依赖它
#include "mathConstantDef.h" // 包含你的 MathConstant::FLOAT_SMALL_NUMBER 等

// 定义一个常用于浮点数比较的误差容忍度
const float EPSILON = 1e-6f; 

// ============================================================================
// 测试夹具 (可选，但对于 Vector3，有些测试可能不需要，但为了演示，我们可以创建一个)
// ============================================================================
class Vector3BasicOpsTest : public ::testing::Test {
protected:
    // 在每个测试前运行
    void SetUp() override {
        v1 = Vector3(1.0f, 2.0f, 3.0f);
        v2 = Vector3(4.0f, 5.0f, 6.0f);
        v_zero = Vector3::ZERO;
        v_one = Vector3::ONE;
    }

    // 在每个测试后运行 (此处无特殊清理)
    void TearDown() override {
    }

    Vector3 v1, v2, v_zero, v_one;
};

// ============================================================================
// 构造函数测试
// ============================================================================
TEST(Vector3ConstructorTest, DefaultConstructor) {
    Vector3 v;
    ASSERT_NEAR(v.x, 0.0f, EPSILON);
    ASSERT_NEAR(v.y, 0.0f, EPSILON);
    ASSERT_NEAR(v.z, 0.0f, EPSILON);
}

TEST(Vector3ConstructorTest, ParametrizedConstructor) {
    Vector3 v(1.23f, 4.56f, 7.89f);
    ASSERT_NEAR(v.x, 1.23f, EPSILON);
    ASSERT_NEAR(v.y, 4.56f, EPSILON);
    ASSERT_NEAR(v.z, 7.89f, EPSILON);
}

// ============================================================================
// 基本算术运算符测试
// ============================================================================
TEST_F(Vector3BasicOpsTest, Addition) {
    Vector3 result = v1 + v2;
    ASSERT_NEAR(result.x, 5.0f, EPSILON);
    ASSERT_NEAR(result.y, 7.0f, EPSILON);
    ASSERT_NEAR(result.z, 9.0f, EPSILON);
}

TEST_F(Vector3BasicOpsTest, Subtraction) {
    Vector3 result = v1 - v2;
    ASSERT_NEAR(result.x, -3.0f, EPSILON);
    ASSERT_NEAR(result.y, -3.0f, EPSILON);
    ASSERT_NEAR(result.z, -3.0f, EPSILON);
}

TEST_F(Vector3BasicOpsTest, UnaryMinus) {
    Vector3 result = -v1;
    ASSERT_NEAR(result.x, -1.0f, EPSILON);
    ASSERT_NEAR(result.y, -2.0f, EPSILON);
    ASSERT_NEAR(result.z, -3.0f, EPSILON);
}

TEST_F(Vector3BasicOpsTest, ScalarMultiplication) {
    Vector3 result = v1 * 2.0f;
    ASSERT_NEAR(result.x, 2.0f, EPSILON);
    ASSERT_NEAR(result.y, 4.0f, EPSILON);
    ASSERT_NEAR(result.z, 6.0f, EPSILON);

    result = 3.0f * v2; // 友元函数测试
    ASSERT_NEAR(result.x, 12.0f, EPSILON);
    ASSERT_NEAR(result.y, 15.0f, EPSILON);
    ASSERT_NEAR(result.z, 18.0f, EPSILON);
}

TEST_F(Vector3BasicOpsTest, ScalarDivision) {
    Vector3 result = v1 / 2.0f;
    ASSERT_NEAR(result.x, 0.5f, EPSILON);
    ASSERT_NEAR(result.y, 1.0f, EPSILON);
    ASSERT_NEAR(result.z, 1.5f, EPSILON);
}

TEST_F(Vector3BasicOpsTest, MultiplicationAssignment) {
    Vector3 test_v = v1;
    test_v *= 2.0f;
    ASSERT_NEAR(test_v.x, 2.0f, EPSILON);
    ASSERT_NEAR(test_v.y, 4.0f, EPSILON);
    ASSERT_NEAR(test_v.z, 6.0f, EPSILON);
}

TEST_F(Vector3BasicOpsTest, DivisionAssignment) {
    Vector3 test_v = v1;
    test_v /= 2.0f;
    ASSERT_NEAR(test_v.x, 0.5f, EPSILON);
    ASSERT_NEAR(test_v.y, 1.0f, EPSILON);
    ASSERT_NEAR(test_v.z, 1.5f, EPSILON);
}

// ============================================================================
// 点积和叉积测试
// ============================================================================
TEST_F(Vector3BasicOpsTest, DotProduct) {
    float result = v1 * v2; // operator* 重载为点积
    ASSERT_NEAR(result, 1.0f*4.0f + 2.0f*5.0f + 3.0f*6.0f, EPSILON); // 4 + 10 + 18 = 32
    ASSERT_NEAR(result, 32.0f, EPSILON);

    // 零向量点积
    ASSERT_NEAR(v1 * v_zero, 0.0f, EPSILON);
    ASSERT_NEAR(v_zero * v_one, 0.0f, EPSILON);
}

TEST(Vector3CrossProductTest, BasicCrossProduct) {
    Vector3 v_x(1.0f, 0.0f, 0.0f);
    Vector3 v_y(0.0f, 1.0f, 0.0f);
    Vector3 v_z(0.0f, 0.0f, 1.0f);

    Vector3 result_xy = v_x.cross(v_y);
    ASSERT_NEAR(result_xy.x, v_z.x, EPSILON);
    ASSERT_NEAR(result_xy.y, v_z.y, EPSILON);
    ASSERT_NEAR(result_xy.z, v_z.z, EPSILON);

    Vector3 result_yz = v_y.cross(v_z);
    ASSERT_NEAR(result_yz.x, v_x.x, EPSILON);
    ASSERT_NEAR(result_yz.y, v_x.y, EPSILON);
    ASSERT_NEAR(result_yz.z, v_x.z, EPSILON);

    Vector3 result_zx = v_z.cross(v_x);
    ASSERT_NEAR(result_zx.x, v_y.x, EPSILON);
    ASSERT_NEAR(result_zx.y, v_y.y, EPSILON);
    ASSERT_NEAR(result_zx.z, v_y.z, EPSILON);

    // 反向叉积
    Vector3 result_yx = v_y.cross(v_x);
    ASSERT_NEAR(result_yx.x, -v_z.x, EPSILON);
    ASSERT_NEAR(result_yx.y, -v_z.y, EPSILON);
    ASSERT_NEAR(result_yx.z, -v_z.z, EPSILON);

    // 平行向量叉积为零向量
    Vector3 parallel_v1(1.0f, 2.0f, 3.0f);
    Vector3 parallel_v2(2.0f, 4.0f, 6.0f);
    Vector3 zero_cross = parallel_v1.cross(parallel_v2);
    ASSERT_NEAR(zero_cross.x, 0.0f, EPSILON);
    ASSERT_NEAR(zero_cross.y, 0.0f, EPSILON);
    ASSERT_NEAR(zero_cross.z, 0.0f, EPSILON);
}

// ============================================================================
// 分量操作测试
// ============================================================================
TEST_F(Vector3BasicOpsTest, AbsComponentWise) {
    Vector3 neg_v(-1.0f, -2.0f, -3.0f);
    Vector3 result = neg_v.abs();
    ASSERT_NEAR(result.x, 1.0f, EPSILON);
    ASSERT_NEAR(result.y, 2.0f, EPSILON);
    ASSERT_NEAR(result.z, 3.0f, EPSILON);

    Vector3 mixed_v(-1.0f, 2.0f, -3.0f);
    result = mixed_v.abs();
    ASSERT_NEAR(result.x, 1.0f, EPSILON);
    ASSERT_NEAR(result.y, 2.0f, EPSILON);
    ASSERT_NEAR(result.z, 3.0f, EPSILON);
}

TEST_F(Vector3BasicOpsTest, DivComponentWise) {
    Vector3 result = v2.div_component_wise(v1); // (4/1, 5/2, 6/3) = (4, 2.5, 2)
    ASSERT_NEAR(result.x, 4.0f, EPSILON);
    ASSERT_NEAR(result.y, 2.5f, EPSILON);
    ASSERT_NEAR(result.z, 2.0f, EPSILON);
}

TEST_F(Vector3BasicOpsTest, MaxComponentWise) {
    Vector3 result = v1.max_component_wise(v2);
    ASSERT_NEAR(result.x, 4.0f, EPSILON);
    ASSERT_NEAR(result.y, 5.0f, EPSILON);
    ASSERT_NEAR(result.z, 6.0f, EPSILON);
}

TEST_F(Vector3BasicOpsTest, MinComponentWise) {
    Vector3 result = v1.min_component_wise(v2);
    ASSERT_NEAR(result.x, 1.0f, EPSILON);
    ASSERT_NEAR(result.y, 2.0f, EPSILON);
    ASSERT_NEAR(result.z, 3.0f, EPSILON);
}

TEST_F(Vector3BasicOpsTest, LessOrEqualComponentWise) {
    Vector3 smaller_v(0.5f, 1.5f, 2.5f);
    Vector3 equal_v(1.0f, 2.0f, 3.0f);

    ASSERT_TRUE(smaller_v.less_or_equal_component_wise(v1));
    ASSERT_TRUE(v1.less_or_equal_component_wise(equal_v));
    ASSERT_FALSE(v2.less_or_equal_component_wise(v1)); // 4,5,6 <= 1,2,3 应该为假
}

// ============================================================================
// 比较运算符测试
// ============================================================================
TEST(Vector3ComparisonTest, Equality) {
    Vector3 v_a(1.0f, 2.0f, 3.0f);
    Vector3 v_b(1.0f, 2.0f, 3.0f);
    Vector3 v_c(1.0f, 2.0f, 3.0000001f); // 接近相等
    Vector3 v_d(1.0f, 2.0f, 4.0f);

    ASSERT_TRUE(v_a == v_b);
    ASSERT_TRUE(v_a == v_c); // 依赖 MathUtility::is_float_equal 的精度
    ASSERT_FALSE(v_a == v_d);
    ASSERT_TRUE(Vector3::ZERO == Vector3(0.0f, 0.0f, 0.0f));
}

TEST(Vector3ComparisonTest, Inequality) {
    Vector3 v_a(1.0f, 2.0f, 3.0f);
    Vector3 v_b(1.0f, 2.0f, 3.0f);
    Vector3 v_c(1.0f, 2.0f, 4.0f);

    ASSERT_FALSE(v_a != v_b);
    ASSERT_TRUE(v_a != v_c);
}

// ============================================================================
// 访问器测试
// ============================================================================
TEST_F(Vector3BasicOpsTest, IndexOperatorConst) {
    ASSERT_NEAR(v1[0], 1.0f, EPSILON);
    ASSERT_NEAR(v1[1], 2.0f, EPSILON);
    ASSERT_NEAR(v1[2], 3.0f, EPSILON);
    // 负面测试（断言触发）在发布版本可能不起作用，但在调试版本中，如果访问越界，会立即崩溃
    // GTEST_DEATH_TEST(Vector3DeathTest, IndexOperatorOutOfBounds) {
    //     Vector3 v(1,2,3);
    //     ASSERT_DEATH(v[3], "");
    // }
}

TEST(Vector3AccessorTest, IndexOperatorMutable) {
    Vector3 v(1.0f, 2.0f, 3.0f);
    v[0] = 10.0f;
    v[1] = 20.0f;
    v[2] = 30.0f;
    ASSERT_NEAR(v.x, 10.0f, EPSILON);
    ASSERT_NEAR(v.y, 20.0f, EPSILON);
    ASSERT_NEAR(v.z, 30.0f, EPSILON);
}

// ============================================================================
// 属性与辅助方法测试
// ============================================================================
TEST_F(Vector3BasicOpsTest, IsZero) {
    ASSERT_TRUE(Vector3::ZERO.isZero());
    ASSERT_FALSE(v1.isZero());
}

TEST_F(Vector3BasicOpsTest, IsPerpendicular) {
    Vector3 v_x(1.0f, 0.0f, 0.0f);
    Vector3 v_y(0.0f, 1.0f, 0.0f);
    Vector3 v_z(0.0f, 0.0f, 1.0f);

    ASSERT_TRUE(v_x.isPerpendicular(v_y));
    ASSERT_TRUE(v_y.isPerpendicular(v_x));
    ASSERT_TRUE(v_x.isPerpendicular(v_z));
    ASSERT_TRUE(v_y.isPerpendicular(v_z));
    
    // 平行向量不垂直
    Vector3 non_perp_v1(1.0f, 1.0f, 0.0f);
    Vector3 non_perp_v2(2.0f, 2.0f, 0.0f);
    ASSERT_FALSE(non_perp_v1.isPerpendicular(non_perp_v2));

    // 任意非垂直向量
    ASSERT_FALSE(v1.isPerpendicular(v2));
}

TEST(Vector3LengthTest, LengthAndLengthSq) {
    Vector3 v(3.0f, 0.0f, 4.0f); // Length should be 5
    ASSERT_NEAR(v.lenthSq(), 25.0f, EPSILON);
    ASSERT_NEAR(v.length(), 5.0f, EPSILON);

    Vector3 zero_v(0.0f, 0.0f, 0.0f);
    ASSERT_NEAR(zero_v.lenthSq(), 0.0f, EPSILON);
    ASSERT_NEAR(zero_v.length(), 0.0f, EPSILON);
}

TEST(Vector3NormalizationTest, Normalize) {
    Vector3 v_norm(3.0f, 0.0f, 4.0f); // Length 5
    v_norm.normalize();
    ASSERT_NEAR(v_norm.x, 0.6f, EPSILON);
    ASSERT_NEAR(v_norm.y, 0.0f, EPSILON);
    ASSERT_NEAR(v_norm.z, 0.8f, EPSILON);
    ASSERT_NEAR(v_norm.length(), 1.0f, EPSILON);

    Vector3 zero_v(0.0f, 0.0f, 0.0f);
    zero_v.normalize(); // 零向量归一化后仍为零向量
    ASSERT_NEAR(zero_v.x, 0.0f, EPSILON);
    ASSERT_NEAR(zero_v.y, 0.0f, EPSILON);
    ASSERT_NEAR(zero_v.z, 0.0f, EPSILON);
}

TEST(Vector3NormalizationTest, Dir) {
    Vector3 v_dir(3.0f, 0.0f, 4.0f);
    Vector3 result = v_dir.dir();
    ASSERT_NEAR(result.x, 0.6f, EPSILON);
    ASSERT_NEAR(result.y, 0.0f, EPSILON);
    ASSERT_NEAR(result.z, 0.8f, EPSILON);
    ASSERT_NEAR(result.length(), 1.0f, EPSILON);

    Vector3 zero_v(0.0f, 0.0f, 0.0f);
    result = zero_v.dir(); // 零向量的 dir() 应该返回零向量
    ASSERT_NEAR(result.x, 0.0f, EPSILON);
    ASSERT_NEAR(result.y, 0.0f, EPSILON);
    ASSERT_NEAR(result.z, 0.0f, EPSILON);
}

TEST(Vector3DirectionTest, IsSameDir) {
    Vector3 v1(1.0f, 1.0f, 0.0f);
    Vector3 v2(2.0f, 2.0f, 0.0f); // 同向
    Vector3 v3(-1.0f, -1.0f, 0.0f); // 反向
    Vector3 v4(1.0f, -1.0f, 0.0f); // 垂直
    Vector3 v_zero(0.0f, 0.0f, 0.0f);

    ASSERT_TRUE(v1.isSameDir(v2));
    ASSERT_FALSE(v1.isSameDir(v3));
    // ASSERT_TRUE(v1.isSameDir(v_zero)); // 点积为0，返回true
    ASSERT_FALSE(v1.isSameDir(v4)); // 点积为0，但不是同向。这里需要注意 isSameDir的定义，如果点积为0算不同向，那断言是false
                                    // 根据你的实现 `r >= 0`，点积为0是算作 `isSameDir` 的
}

TEST(Vector3FaceForwardTest, FaceForward) {
    Vector3 v_normal(0.0f, 0.0f, 1.0f);
    Vector3 v_incoming(0.0f, 0.0f, -1.0f); // 与法线同向，点积 < 0
    Vector3 v_outgoing(0.0f, 0.0f, 1.0f);  // 与法线反向，点积 > 0

    Vector3 test_normal = v_normal;
    test_normal.faceForward(v_incoming); // 点积 < 0，法线应该翻转
    ASSERT_NEAR(test_normal.x, 0.0f, EPSILON);
    ASSERT_NEAR(test_normal.y, 0.0f, EPSILON);
    ASSERT_NEAR(test_normal.z, -1.0f, EPSILON);

    test_normal = v_normal;
    test_normal.faceForward(v_outgoing); // 点积 > 0，法线不翻转
    ASSERT_NEAR(test_normal.x, 0.0f, EPSILON);
    ASSERT_NEAR(test_normal.y, 0.0f, EPSILON);
    ASSERT_NEAR(test_normal.z, 1.0f, EPSILON);
}

TEST(Vector3TangentTest, GetTangentVector) {
    // 轴对齐向量
    Vector3 x_axis(1.0f, 0.0f, 0.0f);
    Vector3 tangent_x = x_axis.getTangentVector();
    // 理论上应得到 (0, 1, 0) 或 (0, 0, 1) 等，取决于实现
    // 根据你的getTangentVector实现，如果x轴不为0，idx[0]=0, idx[1]=0, j=1
    // r[0]=0, r[1]=x_axis.x (1), r[2]=0
    ASSERT_NEAR(tangent_x.x, 0.0f, EPSILON);
    ASSERT_NEAR(tangent_x.y, 1.0f, EPSILON);
    ASSERT_NEAR(tangent_x.z, 0.0f, EPSILON);
    ASSERT_NEAR(tangent_x * x_axis, 0.0f, EPSILON); // 验证正交

    Vector3 y_axis(0.0f, 1.0f, 0.0f);
    Vector3 tangent_y = y_axis.getTangentVector();
    // 根据你的getTangentVector实现，idx[0]=1, j=1
    // r[1]=0, r[(1+1)%3]=y_axis.y (1), 即r[2]=1
    ASSERT_NEAR(tangent_y.x, 0.0f, EPSILON);
    ASSERT_NEAR(tangent_y.y, 0.0f, EPSILON);
    ASSERT_NEAR(tangent_y.z, 1.0f, EPSILON);
    ASSERT_NEAR(tangent_y * y_axis, 0.0f, EPSILON); // 验证正交

    Vector3 z_axis(0.0f, 0.0f, 1.0f);
    Vector3 tangent_z = z_axis.getTangentVector();
    // 根据你的getTangentVector实现，idx[0]=2, j=1
    // r[2]=0, r[(2+1)%3]=z_axis.z (1), 即r[0]=1
    ASSERT_NEAR(tangent_z.x, 1.0f, EPSILON);
    ASSERT_NEAR(tangent_z.y, 0.0f, EPSILON);
    ASSERT_NEAR(tangent_z.z, 0.0f, EPSILON);
    ASSERT_NEAR(tangent_z * z_axis, 0.0f, EPSILON); // 验证正交

    // 非轴对齐向量 (1,1,0)
    Vector3 v_non_axis(1.0f, 1.0f, 0.0f);
    Vector3 tangent_non_axis = v_non_axis.getTangentVector();
    // r[idx[0]] = -v_non_axis[idx[1]] => r[0] = -v_non_axis[1] = -1.0
    // r[idx[1]] = v_non_axis[idx[0]]  => r[1] = v_non_axis[0] = 1.0
    // => (-1, 1, 0)
    ASSERT_NEAR(tangent_non_axis.x, -1.0f, EPSILON);
    ASSERT_NEAR(tangent_non_axis.y, 1.0f, EPSILON);
    ASSERT_NEAR(tangent_non_axis.z, 0.0f, EPSILON);
    ASSERT_NEAR(tangent_non_axis * v_non_axis, 0.0f, EPSILON); // 验证正交

    // 零向量
    Vector3 zero_v(0.0f, 0.0f, 0.0f);
    Vector3 tangent_zero = zero_v.getTangentVector();
    ASSERT_TRUE(tangent_zero.isZero());
}

TEST(Vector3SideTest, IsInSameSide) {
    Vector3 v1(1.0f, 0.0f, 0.0f);
    Vector3 v2(2.0f, 0.0f, 0.0f);  // 同侧
    Vector3 v3(-1.0f, 0.0f, 0.0f); // 异侧
    Vector3 v4(0.0f, 1.0f, 0.0f);  // 垂直（点积为0）

    ASSERT_TRUE(v1.isInSameSide(v2));
    ASSERT_FALSE(v1.isInSameSide(v3));
    ASSERT_FALSE(v1.isInSameSide(v4)); // 点积为0，不大于0，所以为false
}


// ============================================================================
// 反射 (reflect) 测试 - 基于你修改后的实现
// ============================================================================
// 测试夹具，用于设置入射光线和法线
class Vector3ReflectTest : public ::testing::Test {
protected:
    void SetUp() override {
        incident_ray = Vector3(0.0f, 0.0f, -1.0f); // 从上方垂直射向xy平面
        normal_up = Vector3(0.0f, 0.0f, 1.0f);     // 表面法线向上
        normal_down = Vector3(0.0f, 0.0f, -1.0f);   // 表面法线向下
    }

    Vector3 incident_ray;
    Vector3 normal_up;
    Vector3 normal_down;
};

TEST_F(Vector3ReflectTest, PerpendicularIncidenceNormalUp) {
    // 入射光线 (0,0,-1) 垂直射向法线 (0,0,1)
    Vector3 reflected = incident_ray.reflect(normal_up);
    // 期望反射光线垂直向上 (0,0,1)
    ASSERT_NEAR(reflected.x, 0.0f, EPSILON);
    ASSERT_NEAR(reflected.y, 0.0f, EPSILON);
    ASSERT_NEAR(reflected.z, 1.0f, EPSILON);
    ASSERT_NEAR(reflected.length(), 1.0f, EPSILON);
}

TEST_F(Vector3ReflectTest, PerpendicularIncidenceNormalDown) {
    // 入射光线 (0,0,-1) 垂直射向法线 (0,0,-1)
    // 根据你的 reflect 实现，法线会被翻转为 (0,0,1)
    // 结果仍然是反射向上 (0,0,1)
    Vector3 reflected = incident_ray.reflect(normal_down);
    ASSERT_NEAR(reflected.x, 0.0f, EPSILON);
    ASSERT_NEAR(reflected.y, 0.0f, EPSILON);
    ASSERT_NEAR(reflected.z, 1.0f, EPSILON);
    ASSERT_NEAR(reflected.length(), 1.0f, EPSILON);
}

TEST_F(Vector3ReflectTest, AngledIncidenceNormalUp) {
    Vector3 incoming_angled = Vector3(1.0f, 0.0f, -1.0f).dir(); // 45度角入射
    Vector3 reflected = incoming_angled.reflect(normal_up);
    // 期望反射为 (-1, 0, -1) 的归一化向量，即 (-sqrt(2)/2, 0, sqrt(2)/2)
    // 反射公式 R = I - 2 * (I . N) * N
    // I = (1/sqrt(2), 0, -1/sqrt(2))
    // N = (0, 0, 1)
    // I . N = -1/sqrt(2)
    // R = (1/sqrt(2), 0, -1/sqrt(2)) - 2 * (-1/sqrt(2)) * (0, 0, 1)
    // R = (1/sqrt(2), 0, -1/sqrt(2)) + (2/sqrt(2)) * (0, 0, 1)
    // R = (1/sqrt(2), 0, -1/sqrt(2)) + (0, 0, 2/sqrt(2))
    // R = (1/sqrt(2), 0, 1/sqrt(2))
    ASSERT_NEAR(reflected.x, incoming_angled.x, EPSILON); // X分量不变
    ASSERT_NEAR(reflected.y, incoming_angled.y, EPSILON); // Y分量不变
    ASSERT_NEAR(reflected.z, -incoming_angled.z, EPSILON); // Z分量反向
    ASSERT_NEAR(reflected.length(), 1.0f, EPSILON);
}

TEST_F(Vector3ReflectTest, GrazingIncidenceNormalUp) {
    Vector3 incoming_grazing = Vector3(1.0f, 0.0f, -0.0001f).dir(); // 近乎掠射
    Vector3 reflected = incoming_grazing.reflect(normal_up);
    // 期望反射光线也近乎掠射
    ASSERT_NEAR(reflected.x, incoming_grazing.x, EPSILON);
    ASSERT_NEAR(reflected.y, incoming_grazing.y, EPSILON);
    ASSERT_NEAR(reflected.z, -incoming_grazing.z, EPSILON);
    ASSERT_NEAR(reflected.length(), 1.0f, EPSILON);
}

// ============================================================================
// 折射 (refract) 测试
// ============================================================================
// 折射测试夹具
class Vector3RefractTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 标准测试场景：光线从空气 (eta=1.0) 进入玻璃 (eta=1.5)
        air_eta = 1.0f;
        glass_eta = 1.5f;

        // 标准入射光线和法线
        incident_ray_straight = Vector3(0.0f, 0.0f, -1.0f); // 垂直入射 (从上向下)
        normal_up = Vector3(0.0f, 0.0f, 1.0f);              // 表面法线向上 (从物体向外)
        normal_down = Vector3(0.0f, 0.0f, -1.0f);             // 表面法线向下 (从物体向内)
    }

    float air_eta;
    float glass_eta;
    Vector3 incident_ray_straight;
    Vector3 normal_up;
    Vector3 normal_down;
};

// IOR 相等时，应直穿，无反射
TEST_F(Vector3RefractTest, IOREqualNoRefractionOrReflection) {
    float fresnel;
    bool totalReflect;
    Vector3 refracted = incident_ray_straight.refract(normal_up, air_eta, air_eta, totalReflect, fresnel);

    // 期望结果：没有全内反射
    ASSERT_FALSE(totalReflect);
    // 期望结果：菲涅尔反射率为 0
    ASSERT_NEAR(fresnel, 0.0f, EPSILON);
    // 期望结果：光线直穿，方向与入射光线相同
    ASSERT_NEAR(refracted.x, incident_ray_straight.x, EPSILON);
    ASSERT_NEAR(refracted.y, incident_ray_straight.y, EPSILON);
    ASSERT_NEAR(refracted.z, incident_ray_straight.z, EPSILON);
    ASSERT_NEAR(refracted.length(), 1.0f, EPSILON); // 确保是单位向量
}

// 垂直入射：光线应直穿，无偏折，菲涅尔为 0
TEST_F(Vector3RefractTest, PerpendicularIncidence) {
    float fresnel;
    bool totalReflect;

    // 光线从空气进入玻璃 (incident_ray_straight . normal_up < 0)
    Vector3 refracted_entering = incident_ray_straight.refract(normal_up, air_eta, glass_eta, totalReflect, fresnel);
    ASSERT_FALSE(totalReflect);
    ASSERT_NEAR(fresnel, 0.04f, EPSILON); // 垂直入射，菲涅尔为0
    ASSERT_NEAR(refracted_entering.x, incident_ray_straight.x, EPSILON);
    ASSERT_NEAR(refracted_entering.y, incident_ray_straight.y, EPSILON);
    ASSERT_NEAR(refracted_entering.z, incident_ray_straight.z, EPSILON);
    ASSERT_NEAR(refracted_entering.length(), 1.0f, EPSILON);

    // 光线从玻璃进入空气 (incident_ray_straight . normal_down < 0)
    // 但在refract内部会翻转n_internal为normal_up，并swap etaI/etaT
    Vector3 refracted_exiting = incident_ray_straight.refract(normal_down, glass_eta, air_eta, totalReflect, fresnel);
    ASSERT_FALSE(totalReflect);
    ASSERT_NEAR(fresnel, 0.04f, EPSILON); // 垂直入射，菲涅尔为0
    ASSERT_NEAR(refracted_exiting.x, incident_ray_straight.x, EPSILON);
    ASSERT_NEAR(refracted_exiting.y, incident_ray_straight.y, EPSILON);
    ASSERT_NEAR(refracted_exiting.z, incident_ray_straight.z, EPSILON);
    ASSERT_NEAR(refracted_exiting.length(), 1.0f, EPSILON);
}

// 倾斜入射（从空气到玻璃）：应该发生折射，菲涅尔不为0
TEST_F(Vector3RefractTest, AngledIncidenceAirToGlass) {
    Vector3 incident_angled = Vector3(0.707f, 0.0f, -0.707f).dir();
    float fresnel;
    bool totalReflect;

    Vector3 refracted = incident_angled.refract(normal_up, air_eta, glass_eta, totalReflect, fresnel);

    ASSERT_FALSE(totalReflect);
    ASSERT_GT(fresnel, 0.0f);

    // 重新计算精确的期望值（或使用更精确的常量）
    // 从空气到玻璃，入射向量的Z是负的，法线是正的。
    // 光线进入后，Z分量应该仍然是负的。
    // 假设 air_eta = 1.0f, glass_eta = 1.5f
    // incident_angled.x = 0.70710678f, incident_angled.z = -0.70710678f (这是 sqrt(2)/2 的值)
    // normal_up = (0,0,1)

    // incident_angle_cos_val = incident_angled.dot(normal_up) = -0.70710678f
    // sin_incident_angle = sqrt(1 - incident_angle_cos_val^2) = 0.70710678f
    // eta_ratio = 1.0f / 1.5f = 0.66666667f
    // sin_refracted_angle = eta_ratio * sin_incident_angle = 0.66666667f * 0.70710678f = 0.47140452f
    // cos_refracted_angle = sqrt(1 - sin_refracted_angle^2) = sqrt(1 - 0.47140452^2) = 0.88195171f

    // expected_refracted_x = incident_angled.x * eta_ratio = 0.70710678f * 0.66666667f = 0.47140452f
    // expected_refracted_z = -cos_refracted_angle = -0.88195171f (关键的负号)

    // 因此，你需要这样修改断言：
    ASSERT_NEAR(refracted.x, 0.47140452f, EPSILON); // 使用更精确的值
    ASSERT_NEAR(refracted.y, 0.0f, EPSILON);
    ASSERT_NEAR(refracted.z, -0.88195171f, EPSILON); // **符号从正变为负**
    ASSERT_NEAR(refracted.length(), 1.0f, EPSILON);
}

// 全内反射 (TIR) 测试：从玻璃到空气，大角度入射
TEST_F(Vector3RefractTest, TotalInternalReflection) {
    Vector3 incident_angled = Vector3(0.9f, 0.0f, -0.43589f).dir(); // 大于临界角的入射光线 (sin(theta)=0.9)
    float fresnel;
    bool totalReflect;

    // 光线从玻璃到空气：
    // current_etaI = glass_eta = 1.5, current_etaT = air_eta = 1.0
    // incident_angled . normal_up = -0.43589 (小于0，表示光线进入)
    // 但在refract内部，因为要从高密到低密，n_internal会是-normal_up=(0,0,-1)
    // 并且etaI和etaT会交换 (current_etaI=1.5, current_etaT=1.0)
    // 所以dot是 incident_angled . (-normal_up) = (0.9, 0, -0.43589) . (0,0,-1) = 0.43589
    // sin_theta_in_sqr = 1 - dot*dot = 1 - 0.43589^2 = 1 - 0.190 = 0.81
    // eta_ratio = 1.5 / 1.0 = 1.5
    // sin_theta_out_sqr = sin_theta_in_sqr * (eta_ratio * eta_ratio) = 0.81 * (1.5 * 1.5) = 0.81 * 2.25 = 1.8225
    // 因为 1.8225 > 1.0，所以应该发生全内反射
    Vector3 reflected_tir = incident_angled.refract(normal_up, glass_eta, air_eta, totalReflect, fresnel);

    ASSERT_TRUE(totalReflect); // 应该发生全内反射
    ASSERT_NEAR(fresnel, 1.0f, EPSILON); // 全内反射时菲涅尔为 1.0

    // 验证反射方向：此时 refract 应该返回反射方向
    // incident_angled = (0.9, 0, -0.43589)
    // normal_for_reflect = normal_up = (0,0,1) 因为 cos_theta_incident_raw < 0, 用的就是 N_outward
    // 期望反射光线 x 保持，z 反向：(0.9, 0, 0.43589)
    ASSERT_NEAR(reflected_tir.x, incident_angled.x, EPSILON);
    ASSERT_NEAR(reflected_tir.y, incident_angled.y, EPSILON);
    ASSERT_NEAR(reflected_tir.z, -incident_angled.z, EPSILON); // Z 分量反向
    ASSERT_NEAR(reflected_tir.length(), 1.0f, EPSILON);
}

// 光线从玻璃到空气，小角度入射（非 TIR）
TEST_F(Vector3RefractTest, AngledIncidenceGlassToAir) {
    // 重新设定一个离开物体的入射光线和法线
    // 入射向量 I = (0.5, 0, 0.866025)
    // 这是一个与Z轴正向夹角约30度的向量，表示光线从物体内部射出。
    // sin(30) = 0.5, cos(30) = 0.866025
    Vector3 incident_from_inside = Vector3(0.5f, 0.0f, std::sqrt(1.0f - 0.5f*0.5f)).dir();
    
    float fresnel;
    bool totalReflect;

    // normal_up = (0,0,1) 是外向法线，指向物体外部
    // 调用 refract 时，normal 参数应是当前面的外向法线，即 (0,0,1)
    // 传入 glass_eta 作为当前介质，air_eta 作为目标介质
    // incident_from_inside . normal_up (0.866) > 0, 所以 refract 内部会 n_internal = -normal_up (即(0,0,-1))
    // 并且不再进行 eta 的 swap (因为我们已经修复了 refract 函数)
    Vector3 refracted = incident_from_inside.refract(normal_up, glass_eta, air_eta, totalReflect, fresnel);

    // 验证是否发生全内反射
    // 入射角约30度，临界角约为41.81度 (arcsin(1.0/1.5))
    // 30 < 41.81，所以不会发生全内反射，光线会折射
    ASSERT_FALSE(totalReflect);
    // 应该有菲涅尔反射（任何折射都会伴随反射）
    ASSERT_GT(fresnel, 0.0f); 

    // 验证折射方向 (基于正确的 refract 逻辑和计算)
    // 内部计算推导：
    // I = (0.5, 0, 0.866025)
    // N_outward = (0,0,1)
    // cos_theta_incident_raw = I . N_outward = 0.866025
    // n_internal = -N_outward = (0,0,-1)
    // current_etaI (用于Snell公式) = glass_eta = 1.5
    // current_etaT (用于Snell公式) = air_eta = 1.0
    // dot (I . n_internal) = -0.866025
    // sin_theta_in_sqr = 1 - (-0.866025)^2 = 0.25
    // eta_ratio = current_etaI / current_etaT = 1.5 / 1.0 = 1.5
    // sin_theta_out_sqr = sin_theta_in_sqr * eta_ratio^2 = 0.25 * 1.5^2 = 0.25 * 2.25 = 0.5625
    // cos_theta_out_sqr = 1 - 0.5625 = 0.4375
    // cos_theta_out = sqrt(0.4375) = 0.6614378...

    // T_perp = eta_ratio * (I - dot * n_internal)
    //        = 1.5 * ((0.5, 0, 0.866025) - (-0.866025)*(0,0,-1))
    //        = 1.5 * ((0.5, 0, 0.866025) - (0,0,0.866025))
    //        = 1.5 * (0.5, 0, 0) = (0.75, 0, 0)

    // T_parallel = -cos_theta_out * n_internal (根据你代码中的负号)
    //            = -0.6614378 * (0,0,-1)
    //            = (0, 0, 0.6614378)

    // out = T_perp + T_parallel
    //     = (0.75, 0, 0) + (0, 0, 0.6614378)
    //     = (0.75, 0, 0.6614378)

    // 最终断言：
    ASSERT_NEAR(refracted.x, 0.75f, EPSILON);
    ASSERT_NEAR(refracted.y, 0.0f, EPSILON);
    // Z 分量现在是正值，因为法线反向，且 T_parallel 公式带负号
    ASSERT_NEAR(refracted.z, 0.661437f, EPSILON); // <-- 修正为正数
    ASSERT_NEAR(refracted.length(), 1.0f, EPSILON); // 验证折射向量是单位向量
}

// ============================================================================
// 随机向量采样测试 (基本的功能性测试，分布测试通常需要统计方法)
// ============================================================================
// 注意：随机数生成器 MathUtility::genRandomDecimal() 应该是伪随机的，
// 所以这里只能测试返回值是否在预期范围内，不能测试其统计分布。
TEST(Vector3RandomTest, GetRandomVector) {
    Vector3 vec = Vector3::getRandomVector();
    ASSERT_NEAR(vec.length(), 1.0f, EPSILON); // 应该返回单位向量
}

TEST(Vector3RandomTest, SampleUniformFromHemisphere) {
    Vector3 vec = Vector3::sampleUniformFromHemisphere();
    ASSERT_NEAR(vec.length(), 1.0f, EPSILON); // 应该返回单位向量
    ASSERT_GE(vec.z, 0.0f); // 应该在上半球 (z >= 0)
}

TEST(Vector3RandomTest, SampleUniformFromSphere) {
    Vector3 vec = Vector3::sampleUniformFromSphere();
    ASSERT_NEAR(vec.length(), 1.0f, EPSILON); // 应该返回单位向量
}

TEST(Vector3RandomTest, SampleUniformFromCone) {
    float thetaMax = MathConstant::PI / 4.0f; // 45度锥角
    Vector3 vec = Vector3::sampleUniformFromCone(thetaMax);
    ASSERT_NEAR(vec.length(), 1.0f, EPSILON); // 应该返回单位向量
    // 验证在锥角范围内
    float cosTheta = vec.z; // 假设锥体沿Z轴正向
    ASSERT_GE(cosTheta, std::cos(thetaMax) - EPSILON); // cos(theta) >= cos(thetaMax)
}

// 由于 std::ostream& operator<<(std::ostream& os, const Vector3& v);
// 这个函数主要用于调试输出，通常不需要单元测试来验证其格式。
// 如果你想测试，可以捕获 cout 的输出，但这通常更复杂且收益不大。