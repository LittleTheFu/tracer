import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def sample_exponential(lambda_):
    r = -np.log(1.0 - np.random.rand()) / lambda_
    return r

# 测试函数
def test_sample_exponential():
    lambda_ = 4000.0  # 可以根据需要调整lambda值
    num_samples = 1000  # 生成样本的数量

    samples = [sample_exponential(lambda_) for _ in range(num_samples)]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # 为了可视化3D效果，我们假设这些样本分布在x-y平面上
    x = np.random.rand(num_samples)
    y = np.random.rand(num_samples)
    z = samples

    ax.scatter(x, y, z, c='r', marker='o')
    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')

    plt.show()

if __name__ == "__main__":
    test_sample_exponential()