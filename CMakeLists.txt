cmake_minimum_required(VERSION 3.5)

project (ray_tracer)


# INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}/brdf)
# INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}/camera)
# INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}/common)
# INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}/geometroy)
# INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}/light)
# INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}/main)
# INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}/material)
# INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}/math)
# INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}/media)
# INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}/resource)
# INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}/scene)
# INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}/texture)
# INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR}/tracer)

SET (RAY_TRACER_SOURCE
    brdf/brdf.cpp
    brdf/brdfMgr.cpp
    brdf/DummyBrdf.cpp
    brdf/glass.cpp
    brdf/lambertian.cpp
    brdf/mirror.cpp
    camera/camera.cpp
    camera/fishEyeCamera.cpp
    camera/orthographicCamera.cpp
    camera/pinholeCamera.cpp
    common/color.cpp
    common/common.cpp
    common/hitrecord.cpp
    common/lodepng.cpp
    common/noise.cpp
    common/spectrum.cpp
    geometry/ball.cpp
    geometry/circle.cpp
    geometry/plane.cpp
    geometry/triangle.cpp
    light/light.cpp
    # main/main.cpp
    material/dummyMaterial.cpp
    material/glassMaterial.cpp
    material/lambertianMaterial.cpp
    material/material.cpp
    material/mirrorMaterial.cpp
    material/mixMaterial.cpp
    mathmatic/frame.cpp
    mathmatic/matrix.cpp
    mathmatic/ray.cpp
    mathmatic/transform.cpp
    mathmatic/vector.cpp
    media/media.cpp
    media/mist.cpp
)

SET (RAY_TRACER_HEADER
    brdf/brdf.h
    brdf/brdfMgr.h
    brdf/DummyBrdf.h
    brdf/glass.h
    brdf/lambertian.h
    brdf/mirror.h
    camera/camera.h
    camera/fishEyeCamera.h
    camera/orthographicCamera.h
    camera/pinholeCamera.h
    common/color.h
    common/common.h
    common/hitrecord.h
    common/lodepng.h
    common/noise.h
    common/spectrum.h
    geometry/ball.h
    geometry/circle.h
    geometry/plane.h
    geometry/triangle.h
    light/light.h
    material/dummyMaterial.h
    material/glassMaterial.h
    material/lambertianMaterial.h
    material/material.h
    material/mirrorMaterial.h
    material/mixMaterial.h
    mathmatic/frame.h
    mathmatic/matrix.h
    mathmatic/ray.h
    mathmatic/transform.h
    mathmatic/vector.h
    media/media.h
    media/mist.h
)

# message(${RAY_TRACER_HEADER})

INCLUDE_DIRECTORIES(brdf camera common geometry light material
mathmatic media resource scene texture tracer)

add_library(libs STATIC ${RAY_TRACER_SOURCE} ${RAY_TRACER_HEADER})
target_include_directories( libs
    PUBLIC scene}
)

# ADD_LIBRARY ( ray_tracer 
#   ${RAY_TRACER_SOURCE}
#   ${RAY_TRACER_HEADER}
# )


add_executable(ray_tracer main/main.cpp)


target_link_libraries(ray_tracer PUBLIC libs)
# target_include_directories(ray_tracer PUBLIC ${RAY_TRACER_HEADER})