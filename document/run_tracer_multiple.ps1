# 设置可执行文件的路径
$executable = ".\ray_tracer.exe"

# 定义要传递的参数数组
$scenes = @("simple_room", "simple_room_bunny", "complex_room_bunny", "room_teapot", "room_material_balls")

# 循环运行可执行文件并传递不同的参数
foreach ($scene in $scenes) {
    Write-Output "正在运行场景: $scene"
    & $executable $scene
    Write-Output "场景 $scene 运行完成"
}

Write-Output "所有场景运行完成"