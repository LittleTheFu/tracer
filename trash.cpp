#include <random>   // 包含随机数生成器和分布的头文件
#include <chrono>   // 用于获取时间作为随机数种子

// 声明一个全局或静态的随机数生成器和分布
// 最好是只初始化一次，而不是每次调用函数都初始化
static std::mt19937_64 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
// 解释：
// std::mt19937_64 是一个 Mersenne Twister 引擎，它是一个高质量的伪随机数生成器。
// std::chrono::high_resolution_clock::now().time_since_epoch().count()
// 用当前高精度时间作为种子，确保每次程序运行的随机序列不同。

static std::uniform_real_distribution<double> dist(0.0, 1.0);
// 解释：
// std::uniform_real_distribution<double> 定义了一个均匀分布，
// 它会生成指定范围 [a, b) 内的浮点数。
// 这里是 [0.0, 1.0)，表示包含 0.0，但不包含 1.0。

// 你的 MathUtility 类或者一个独立的函数
namespace MathUtility {

    /**
     * @brief 生成一个 [0, 1) 范围内的浮点随机数。
     * 使用 C++11 的 <random> 库，提供高质量的伪随机数。
     * @return 0.0 到 1.0 之间（不包含 1.0）的浮点数。
     */
    double genRandomDecimal() {
        return dist(rng); // 从生成器 rng 中获取一个符合 dist 分布的随机数
    }

} // namespace MathUtility

// ----------------------------------------------------
// 如何在你的代码中使用：
// 确保你的 MathUtility.h 或 .cpp 文件中包含了上述的 #include 和静态变量定义。
// 然后在任何需要随机数的地方直接调用：
// float rand_val = static_cast<float>(MathUtility::genRandomDecimal());
// 注意：如果你的随机数生成器不是全局或静态的，
// 而是每次都创建新的 rng 和 dist 对象，那你会得到重复的序列。
// 务必只初始化一次！