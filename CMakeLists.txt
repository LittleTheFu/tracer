cmake_minimum_required(VERSION 3.5)

project (ray_tracer)

INCLUDE_DIRECTORIES (brdf)
INCLUDE_DIRECTORIES (camera)
INCLUDE_DIRECTORIES (common)
INCLUDE_DIRECTORIES (geometroy)
INCLUDE_DIRECTORIES (light)
INCLUDE_DIRECTORIES (main)
INCLUDE_DIRECTORIES (material)
INCLUDE_DIRECTORIES (math)
INCLUDE_DIRECTORIES (media)
INCLUDE_DIRECTORIES (resource)
INCLUDE_DIRECTORIES (scene)
INCLUDE_DIRECTORIES (texture)
INCLUDE_DIRECTORIES (tracer)

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
    geometry/trangle.cpp
    light/light.cpp
    main/main.cpp
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
    geometry/trangle.h
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

ADD_LIBRARY ( ray_tracer STATIC
  ${RAY_TRACER_SOURCE}
  ${RAY_TRACER_HEADER}
)

add_executable(ray_tracer main/main.cpp)