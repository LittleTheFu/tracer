cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project (ray_tracer)

SET (RAY_TRACER_SOURCE
    brdf/brdf.cpp
    brdf/conductorBrdf.cpp
    brdf/DummyBrdf.cpp
    brdf/refreactorBsdf.cpp
    brdf/measuredBrdf.cpp
    brdf/diffuseBrdf.cpp
    brdf/microfacet.cpp
    brdf/mirror.cpp
    camera/camera.cpp
    camera/fishEyeCamera.cpp
    camera/orthographicCamera.cpp
    camera/pinholeCamera.cpp
    common/color.cpp
    common/common.cpp
    common/config.cpp
    common/converter.cpp
    common/hitrecord.cpp
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
    material/conductorMaterial.cpp
    material/dummyMaterial.cpp
    material/refreactorMaterial.cpp
    material/diffuseMaterial.cpp
    material/material.cpp
    material/materialManager.cpp
    material/measuredMaterial.cpp
    material/microMaterial.cpp
    material/mirrorMaterial.cpp
    material/dielectricMaterial.cpp
    mathmatic/frame.cpp
    mathmatic/matrix.cpp
    mathmatic/ray.cpp
    mathmatic/russianRoulette.cpp
    mathmatic/transform.cpp
    mathmatic/vector.cpp
    media/media.cpp
    scene/bvh.cpp
    scene/bvhNode.cpp
    scene/simpleHitter.cpp
    scene/hitterInterface.cpp
    scene/objectpool.cpp
    scene/scene.cpp
    scene_builder/complexBunnySceneBuilder.cpp
    scene_builder/simpleBunnySceneBuilder.cpp
    scene_builder/simpleSceneBuilder.cpp
    scene_builder/mtrlSceneBuilder.cpp
    scene_builder/sceneBuilder.cpp
    scene_builder/teapotSceneBuilder.cpp
    scene_builder/volumeSceneBuilder.cpp
    volume/vox.cpp
    texture/chessboardTexture.cpp
    texture/constTexture.cpp
    texture/imageTexture.cpp
    texture/noiseTexture.cpp
    texture/texture.cpp
    texture/uvTexture.cpp
    tracer/neeTracer.cpp
    tracer/neeVolTracer.cpp
    tracer/tracer.cpp
    tracer/volTracer.cpp
)

SET (RAY_TRACER_HEADER
    brdf/brdf.h
    brdf/conductorBrdf.h
    brdf/DummyBrdf.h
    brdf/refreactorBsdf.h
    brdf/measuredBrdf.h
    brdf/diffuseBrdf.h
    brdf/microfacet.h
    brdf/mirror.h
    camera/camera.h
    camera/fishEyeCamera.h
    camera/orthographicCamera.h
    camera/pinholeCamera.h
    common/axisDef.h
    common/color.h
    common/common.h
    common/config.h
    common/converter.h
    common/hitrecord.h
    common/mathConstantDef.h
    common/mathUtility.h
    common/noise.h
    common/resourceDef.h
    common/sceneDef.h
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
    material/conductorMaterial.h
    material/dummyMaterial.h
    material/refreactorMaterial.h
    material/diffuseMaterial.h
    material/material.h
    material/materialDef.h
    material/materialManager.h
    material/measuredMaterial.h
    material/microMaterial.h
    material/mirrorMaterial.h
    material/dielectricMaterial.h
    mathmatic/frame.h
    mathmatic/matrix.h
    mathmatic/ray.h
    mathmatic/russianRoulette.h
    mathmatic/transform.h
    mathmatic/vector.h
    media/media.h
    scene/bvh.h
    scene/bvhNode.h
    scene/simpleHitter.h
    scene/hitterInterface.h
    scene/objectpool.h
    scene/scene.h
    scene_builder/complexBunnySceneBuilder.h
    scene_builder/simpleBunnySceneBuilder.h
    scene_builder/simpleSceneBuilder.h
    scene_builder/mtrlSceneBuilder.h
    scene_builder/sceneBuilder.h
    scene_builder/volumeSceneBuilder.h
    scene_builder/teapotSceneBuilder.h
    volume/vox.h
    texture/chessboardTexture.h
    texture/constTexture.h
    texture/imageTexture.h
    texture/noiseTexture.h
    texture/texture.h
    texture/uvTexture.h
    tracer/neeTracer.h
    tracer/neeVolTracer.h
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
                    scene_builder  
                    volume
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

add_subdirectory(${PROJECT_SOURCE_DIR}/third/powitacq/)
include_directories(${PROJECT_SOURCE_DIR}/third/powitacq/include)

add_executable(ray_tracer main/main.cpp )

target_link_libraries(ray_tracer mylibs)
target_link_libraries(ray_tracer assimp)
target_link_libraries(ray_tracer lodepng)
target_link_libraries(ray_tracer powitacq)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Install path" FORCE)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/resource/ DESTINATION ${CMAKE_BINARY_DIR}/resource/
        FILES_MATCHING PATTERN "*")

install(TARGETS ray_tracer  mylibs assimp lodepng RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin/)


if(WIN32)
    configure_file( ${CMAKE_SOURCE_DIR}/document/run_tracer_multiple.ps1 ${CMAKE_BINARY_DIR}/bin/run_tracer_multiple.ps1 COPYONLY)
else()
    configure_file( ${CMAKE_SOURCE_DIR}/document/run_and_mail.sh ${CMAKE_BINARY_DIR}/run_and_mail.sh COPYONLY)
    configure_file( ${CMAKE_SOURCE_DIR}/document/run_tracer_multiple.sh ${CMAKE_BINARY_DIR}/run_tracer_multiple.sh COPYONLY)
endif()