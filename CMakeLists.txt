cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project (ray_tracer)

SET (MATHMATIC_DIR "mathmatic")
SET (MATHMATIC_SOURCE_FILES
    ${MATHMATIC_DIR}/frame.cpp
    ${MATHMATIC_DIR}/matrix.cpp
    ${MATHMATIC_DIR}/ray.cpp
    ${MATHMATIC_DIR}/russianRoulette.cpp
    ${MATHMATIC_DIR}/transform.cpp
    ${MATHMATIC_DIR}/vector.cpp
)

SET (INTEGRATOR_DIR "integrator")
SET (INTEGRATOR_SOURCE_FILES
    ${INTEGRATOR_DIR}/integrator.cpp
    ${INTEGRATOR_DIR}/pathIntegrator.cpp
)

SET (GEOMETRY_DIR "geometry")
SET (GEOMETRY_SOURCE_FILES
    ${GEOMETRY_DIR}/ball.cpp
    ${GEOMETRY_DIR}/boundBox.cpp
    ${GEOMETRY_DIR}/circle.cpp
    ${GEOMETRY_DIR}/curve.cpp
    ${GEOMETRY_DIR}/geometry.cpp
    ${GEOMETRY_DIR}/mesh.cpp
    ${GEOMETRY_DIR}/model.cpp
    ${GEOMETRY_DIR}/plane.cpp
    ${GEOMETRY_DIR}/room.cpp
    ${GEOMETRY_DIR}/tri.cpp
    ${GEOMETRY_DIR}/geometryPrimitive.cpp
    ${GEOMETRY_DIR}/interaction.cpp
    ${GEOMETRY_DIR}/primitive.cpp
)

SET (VOLUME_DIR "volume")
SET (VOLUME_SOURCE_FILES
    ${VOLUME_DIR}/volume.cpp
    ${VOLUME_DIR}/sphereVolume.cpp
    ${VOLUME_DIR}/medium.cpp
    ${VOLUME_DIR}/mediumInteraction.cpp
    ${VOLUME_DIR}/perlinNoise.cpp
    ${VOLUME_DIR}/vox.cpp
)

SET (MATERIAL_DIR "material")
SET (MATERIAL_SOURCE_FILES
    ${MATERIAL_DIR}/material.cpp
    ${MATERIAL_DIR}/materialLambertian.cpp
    ${MATERIAL_DIR}/materialMirror.cpp
    ${MATERIAL_DIR}/materialGlass.cpp
    ${MATERIAL_DIR}/materialSilk.cpp
    ${MATERIAL_DIR}/materialTarkinTunic.cpp
    ${MATERIAL_DIR}/materialPVC.cpp
    ${MATERIAL_DIR}/emittingMaterial.cpp
    ${MATERIAL_DIR}/materialTRough.cpp
    ${MATERIAL_DIR}/materialRough.cpp
    ${MATERIAL_DIR}/materialPBR.cpp
)

SET (LIGHT_DIR "light")
SET (LIGHT_SOURCE_FILES
    ${LIGHT_DIR}/areaLight.cpp
)

SET (BXDF_DIR "bxdf")
SET (BXDF_SOURCE_FILES
    ${BXDF_DIR}/bsdf.cpp
    ${BXDF_DIR}/bxdf.cpp
    ${BXDF_DIR}/lambertianBxdf.cpp
    ${BXDF_DIR}/measuredBxdf.cpp
    ${BXDF_DIR}/specularBxdf.cpp
    ${BXDF_DIR}/dielectricBxdf.cpp
    ${BXDF_DIR}/microfacetSpecularBxdf.cpp
    ${BXDF_DIR}/microfacetTransmissionBxdf.cpp
)

SET (CAMERA_DIR "camera")
SET (CAMERA_SOURCE_FILES
    ${CAMERA_DIR}/camera.cpp
    ${CAMERA_DIR}/fishEyeCamera.cpp
    ${CAMERA_DIR}/orthographicCamera.cpp
    ${CAMERA_DIR}/pinholeCamera.cpp
)

SET (COMMON_DIR "common")
SET (COMMON_SOURCE_FILES
    ${COMMON_DIR}/color.cpp
    ${COMMON_DIR}/common.cpp
    ${COMMON_DIR}/config.cpp
    ${COMMON_DIR}/converter.cpp
    ${COMMON_DIR}/mathUtility.cpp
    ${COMMON_DIR}/noise.cpp
    ${COMMON_DIR}/spectrum.cpp
    ${COMMON_DIR}/timeRecorder.cpp
)

SET (SCENE_DIR "scene_management")
SET (SCENE_SOURCE_FILES
    ${SCENE_DIR}/bvh.cpp
    ${SCENE_DIR}/bvhNode.cpp
    ${SCENE_DIR}/simpleHitter.cpp
    ${SCENE_DIR}/hitterInterface.cpp
    ${SCENE_DIR}/objectpool.cpp
    ${SCENE_DIR}/scene.cpp
)

SET (SCENE_BUILDER_DIR "scene_builder")
SET (SCENE_BUILDER_SOURCE_FILES
    ${SCENE_BUILDER_DIR}/curveSceneBuilder.cpp
    ${SCENE_BUILDER_DIR}/complexBunnySceneBuilder.cpp
    ${SCENE_BUILDER_DIR}/simpleBunnySceneBuilder.cpp
    ${SCENE_BUILDER_DIR}/simpleSceneBuilder.cpp
    ${SCENE_BUILDER_DIR}/mtrlSceneBuilder.cpp
    ${SCENE_BUILDER_DIR}/normalMapSceneBuilder.cpp
    ${SCENE_BUILDER_DIR}/sceneBuilder.cpp
    ${SCENE_BUILDER_DIR}/teapotSceneBuilder.cpp
    ${SCENE_BUILDER_DIR}/botSceneBuilder.cpp
    ${SCENE_BUILDER_DIR}/volumeSceneBuilder.cpp
    ${SCENE_BUILDER_DIR}/cubeSceneBuilder.cpp
    ${SCENE_BUILDER_DIR}/cornellSceneBuilder.cpp
)

SET (MANAGER_DIR "manager")
SET (MANAGER_SOURCE_FILES
    ${MANAGER_DIR}/id.cpp
    ${MANAGER_DIR}/materialManager.cpp
    ${MANAGER_DIR}/textureManager.cpp
    ${MANAGER_DIR}/mediumManager.cpp
)

SET (TEXTURE_DIR "texture")
SET (TEXTURE_SOURCE_FILES
    ${TEXTURE_DIR}/chessboardTexture.cpp
    ${TEXTURE_DIR}/constTexture.cpp
    ${TEXTURE_DIR}/imageTexture.cpp
    ${TEXTURE_DIR}/noiseTexture.cpp
    ${TEXTURE_DIR}/normalTexture.cpp
    ${TEXTURE_DIR}/texture.cpp
    ${TEXTURE_DIR}/uvTexture.cpp
)

INCLUDE_DIRECTORIES(
    ${BXDF_DIR}
    ${INTEGRATOR_DIR}
    ${GEOMETRY_DIR}
    ${MATERIAL_DIR}
    ${MANAGER_DIR}
    ${LIGHT_DIR}
    ${MATHMATIC_DIR}
    ${CAMERA_DIR}
    ${COMMON_DIR}
    ${SCENE_DIR}
    ${SCENE_BUILDER_DIR}
    ${VOLUME_DIR}
    ${TEXTURE_DIR}
)

add_library(mylibs STATIC
    ${MATHMATIC_SOURCE_FILES}
    ${INTEGRATOR_SOURCE_FILES}
    ${GEOMETRY_SOURCE_FILES}
    ${MATERIAL_SOURCE_FILES}
    ${MANAGER_SOURCE_FILES}
    ${LIGHT_SOURCE_FILES}
    ${BXDF_SOURCE_FILES}
    ${CAMERA_SOURCE_FILES}
    ${COMMON_SOURCE_FILES}
    ${SCENE_SOURCE_FILES}
    ${SCENE_BUILDER_SOURCE_FILES}
    ${TEXTURE_SOURCE_FILES}
    ${VOLUME_SOURCE_FILES}
)

add_subdirectory(${PROJECT_SOURCE_DIR}/third/assimp/)
include_directories(${PROJECT_SOURCE_DIR}/third/assimp/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/third/assimp/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/third/lodepng/)
include_directories(${PROJECT_SOURCE_DIR}/third/lodepng/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/third/powitacq/)
include_directories(${PROJECT_SOURCE_DIR}/third/powitacq/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/third/googletest)

add_executable(tracer_tests
    test/test.cpp
    # test/vectorTest.cpp
    # test/perlinNoiseTest.cpp
)

target_link_libraries(tracer_tests
    mylibs
    assimp
    lodepng
    powitacq
    GTest::gtest_main
)

enable_testing()
add_test(NAME MyTracerTests COMMAND tracer_tests)

add_executable(ray_tracer main/main.cpp )

target_link_libraries(ray_tracer mylibs)
target_link_libraries(ray_tracer assimp)
target_link_libraries(ray_tracer lodepng)
target_link_libraries(ray_tracer powitacq)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Install path" FORCE)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/resource/ DESTINATION ${CMAKE_BINARY_DIR}/resource/
        FILES_MATCHING PATTERN "*")

install(TARGETS ray_tracer mylibs assimp lodepng RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin/)

if(WIN32)
    configure_file( ${CMAKE_SOURCE_DIR}/document/run_tracer_multiple.ps1 ${CMAKE_BINARY_DIR}/bin/run_tracer_multiple.ps1 COPYONLY)
else()
    configure_file( ${CMAKE_SOURCE_DIR}/document/run_and_mail.sh ${CMAKE_BINARY_DIR}/run_and_mail.sh COPYONLY)
    configure_file( ${CMAKE_SOURCE_DIR}/document/run_tracer_multiple.sh ${CMAKE_BINARY_DIR}/run_tracer_multiple.sh COPYONLY)
endif()