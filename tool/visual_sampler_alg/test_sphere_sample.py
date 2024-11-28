import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

class Vector3:
    @staticmethod
    def sample_uniform_from_sphere():
        u = np.random.uniform(-1, 1)
        v = np.random.uniform(0, 1)

        cos_theta = u
        sin_theta = np.sqrt(1 - cos_theta ** 2)
        phi = 2 * np.pi * v

        x = sin_theta * np.cos(phi)
        y = sin_theta * np.sin(phi)
        z = cos_theta

        return np.array([x, y, z])

# 测试函数
def test_sample_uniform_from_sphere():
    num_samples = 1000  # 生成样本的数量

    samples = [Vector3.sample_uniform_from_sphere() for _ in range(num_samples)]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    x = [vec[0] for vec in samples]
    y = [vec[1] for vec in samples]
    z = [vec[2] for vec in samples]

    ax.scatter(x, y, z, c='r', marker='o')
    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')

    plt.show()

if __name__ == "__main__":
    test_sample_uniform_from_sphere()