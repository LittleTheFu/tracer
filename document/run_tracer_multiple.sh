#!/bin/bash

# 设置可执行文件的路径
EXECUTABLE=./ray_tracer  # 假设可执行文件名为 binary_tracer 并位于当前目录下

# 定义要传递的参数数组
SCENES=(simple_room simple_room_bunny complex_room_bunny room_teapot room_material_balls)

# 循环运行可执行文件并传递不同的参数
for SCENE in "${SCENES[@]}"; do
    echo "正在运行场景 $SCENE"
    "$EXECUTABLE" "$SCENE"
    if [ $? -ne 0 ]; then
        echo "场景 $SCENE 运行失败"
        exit 1
    fi
    echo "场景 $SCENE 运行完成"
done

echo "所有场景运行完成"