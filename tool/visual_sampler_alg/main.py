import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# 创建数据
x = np.linspace(-5, 5, 100)
y = np.linspace(-5, 5, 100)
x, y = np.meshgrid(x, y)
z = np.sin(np.sqrt(x**2 + y**2))

# 创建图形
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# 绘制三维曲面
ax.plot_surface(x, y, z, cmap='viridis')

# 显示图形
plt.show()