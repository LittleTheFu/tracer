cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
#   DOWNLOAD_EXTRACT_TIMESTAMP TRUE
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

project (ray_tracer)

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
    common/config.cpp
    common/hitrecord.cpp
    # common/lodepng.cpp
    common/mathUtility.cpp
    common/noise.cpp
    common/spectrum.cpp
    common/timeRecorder.cpp
    geometry/ball.cpp
    geometry/boundBox.cpp
    geometry/circle.cpp
    geometry/geometry.cpp
    geometry/mesh.cpp
    geometry/plane.cpp
    geometry/room.cpp
    geometry/tri.cpp
    light/light.cpp
    # main/main.cpp
    material/combinedMaterial.cpp
    material/dummyMaterial.cpp
    material/glassMaterial.cpp
    material/lambertianMaterial.cpp
    material/material.cpp
    material/materialManager.cpp
    material/mirrorMaterial.cpp
    material/mixMaterial.cpp
    mathmatic/frame.cpp
    mathmatic/matrix.cpp
    mathmatic/ray.cpp
    mathmatic/russianRouletter.cpp
    mathmatic/transform.cpp
    mathmatic/vector.cpp
    media/media.cpp
    scene/bunnySceneBuilder.cpp
    scene/betaSceneBuilder.cpp
    scene/bvh.cpp
    scene/bvhNode.cpp
    scene/hitter.cpp
    scene/hitterInterface.cpp
    scene/objectpool.cpp
    scene/scene.cpp
    scene/sceneBuilder.cpp
    scene/volumeSceneBuilder.cpp
    shape/vox.cpp
    texture/chessboardTexture.cpp
    texture/constTexture.cpp
    texture/imageTexture.cpp
    texture/noiseTexture.cpp
    texture/texture.cpp
    texture/uvTexture.cpp
    tracer/neeTracer.cpp
    tracer/randomTracer.cpp
    tracer/simpleTracer.cpp
    tracer/tracer.cpp
    tracer/volTracer.cpp
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
    common/axisDef.h
    common/color.h
    common/common.h
    common/config.h
    common/hitrecord.h
    # common/lodepng.h
    common/mathConstantDef.h
    common/mathUtility.h
    common/noise.h
    common/resourceDef.h
    common/spectrum.h
    common/tagDef.h
    common/timeRecorder.h
    common/tracerDef.h
    geometry/ball.h
    geometry/boundBox.h
    geometry/circle.h
    geometry/geometry.h
    geometry/mesh.h
    geometry/plane.h
    geometry/room.h
    geometry/tri.h
    light/light.h
    material/combinedMaterial.h
    material/dummyMaterial.h
    material/glassMaterial.h
    material/lambertianMaterial.h
    material/material.h
    material/materialDef.h
    material/materialManager.h
    material/mirrorMaterial.h
    material/mixMaterial.h
    mathmatic/frame.h
    mathmatic/matrix.h
    mathmatic/ray.h
    mathmatic/russianRouletter.h
    mathmatic/transform.h
    mathmatic/vector.h
    media/media.h
    scene/bunnySceneBuilder.h
    scene/betaSceneBuilder.h
    scene/bvh.h
    scene/bvhNode.h
    scene/hitter.h
    scene/hitterInterface.h
    scene/objectpool.h
    scene/scene.h
    scene/sceneBuilder.h
    scene/volumeSceneBuilder.h
    shape/vox.h
    texture/chessboardTexture.h
    texture/constTexture.h
    texture/imageTexture.h
    texture/noiseTexture.h
    texture/texture.h
    texture/uvTexture.h
    tracer/neeTracer.h
    tracer/randomTracer.h
    tracer/simpleTracer.h
    tracer/tracer.h
    tracer/volTracer.h
)

INCLUDE_DIRECTORIES(brdf 
                    camera
                    common 
                    geometry 
                    light 
                    material
                    mathmatic 
                    media
                    scene  
                    shape
                    test
                    texture 
                    tracer
                    )
                    
add_library(mylibs STATIC ${RAY_TRACER_SOURCE} ${RAY_TRACER_HEADER})

add_subdirectory(${PROJECT_SOURCE_DIR}/third/assimp/)
include_directories(${PROJECT_SOURCE_DIR}/third/assimp/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/third/assimp/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/third/lodepng/)
include_directories(${PROJECT_SOURCE_DIR}/third/lodepng/include)

add_executable(ray_tracer main/main.cpp )

target_link_libraries(ray_tracer mylibs)
target_link_libraries(ray_tracer assimp)
target_link_libraries(ray_tracer lodepng)

# enable_testing()

# add_executable(hello_test  test/test.cpp)
# target_link_libraries(hello_test GTest::gtest_main)

# include(GoogleTest)
# gtest_discover_tests(hello_test)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Install path" FORCE)

# 安装整个资源目录
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resource/ DESTINATION ${CMAKE_BINARY_DIR}/resource
        FILES_MATCHING PATTERN "*")  # 安装所有文件

install(TARGETS ray_tracer  mylibs assimp lodepng RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin)


if( NOT WIN32)
    configure_file( ${CMAKE_SOURCE_DIR}/document/run_and_mail.sh ${CMAKE_BINARY_DIR} COPYONLY)
endif()

# install(TARGETS ray_tracer mylibs assimp
# RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin
# LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/lib
# ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/lib
# )