cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

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
    common/hitrecord.cpp
    common/lodepng.cpp
    common/noise.cpp
    common/spectrum.cpp
    common/timeRecorder.cpp
    geometry/ball.cpp
    geometry/boundBox.cpp
    geometry/circle.cpp
    geometry/geometry.cpp
    geometry/mesh.cpp
    geometry/plane.cpp
    geometry/triangle.cpp
    geometry/tri.cpp
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
    scene/alphaSceneBuilder.cpp
    scene/betaSceneBuilder.cpp
    scene/bvh.cpp
    scene/bvhNode.cpp
    scene/hitter.cpp
    scene/objectpool.cpp
    scene/scene.cpp
    scene/sceneBuilder.cpp
    test/tester.cpp
    texture/chessboardTexture.cpp
    texture/constTexture.cpp
    texture/imageTexture.cpp
    texture/noiseTexture.cpp
    texture/texture.cpp
    texture/uvTexture.cpp
    tracer/randomTracer.cpp
    tracer/simpleTracer.cpp
    tracer/tracer.cpp
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
    common/timeRecorder.h
    geometry/ball.h
    geometry/boundBox.h
    geometry/circle.h
    geometry/geometry.h
    geometry/mesh.h
    geometry/plane.h
    geometry/tri.h
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
    scene/alphaSceneBuilder.h
    scene/betaSceneBuilder.h
    scene/bvh.h
    scene/bvhNode.h
    scene/hitter.h
    scene/objectpool.h
    scene/scene.h
    scene/sceneBuilder.h
    test/tester.h
    texture/chessboardTexture.h
    texture/constTexture.h
    texture/imageTexture.h
    texture/noiseTexture.h
    texture/texture.h
    texture/uvTexture.h
    tracer/randomTracer.h
    tracer/simpleTracer.h
    tracer/tracer.h
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
                    test
                    texture 
                    tracer
                    )

add_library(mylibs STATIC ${RAY_TRACER_SOURCE} ${RAY_TRACER_HEADER})

include_directories(${PROJECT_SOURCE_DIR}/assimp_lib/include)
link_directories(${PROJECT_SOURCE_DIR}/assimp_lib/lib)

add_executable(ray_tracer main/main.cpp resource/lena.png)

target_link_libraries(ray_tracer mylibs)

if(WIN32)
    target_link_libraries(ray_tracer assimp-vc143-mtd.lib)
else()
    target_link_libraries(ray_tracer assimp)
endif()

# 添加资源文件
set(RESOURCE_FILES 
        resource/lena.png 
        resource/bunny.obj
        resource/simple_bunny.obj
        resource/low_bunny.obj
        resource/low_low_bunny.obj)

# 将资源文件复制到构建目录
foreach(RESOURCE ${RESOURCE_FILES})
    configure_file(${RESOURCE} ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE} COPYONLY)
endforeach()


if(WIN32)
    if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/Debug)
        file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    endif()

    configure_file(${PROJECT_SOURCE_DIR}/assimp_lib/lib/assimp-vc143-mtd.lib
                    ${CMAKE_CURRENT_BINARY_DIR}/Debug/
                    COPYONLY)

    configure_file(${PROJECT_SOURCE_DIR}/assimp_lib/lib/assimp-vc143-mtd.dll
                    ${CMAKE_CURRENT_BINARY_DIR}/Debug/
                    COPYONLY)
else()
    if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/bin)
        file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
    endif()

    configure_file(${PROJECT_SOURCE_DIR}/assimp_lib/lib/libassimp.so
        ${CMAKE_CURRENT_BINARY_DIR}/bin/
        COPYONLY)
    configure_file(${PROJECT_SOURCE_DIR}/assimp_lib/lib/libassimp.so.5
        ${CMAKE_CURRENT_BINARY_DIR}/bin/
        COPYONLY)
    configure_file(${PROJECT_SOURCE_DIR}/assimp_lib/lib/libassimp.so.5.4.3
        ${CMAKE_CURRENT_BINARY_DIR}/bin/
        COPYONLY)
endif()