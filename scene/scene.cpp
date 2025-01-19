#include <cassert>

#include "common.h"
#include "config.h"
#include "curveSceneBuilder.h"
#include "neeTracer.h"
#include "pinholeCamera.h"
#include "scene.h"
#include "timeRecorder.h"
#include "simpleSceneBuilder.h"
#include "simpleBunnySceneBuilder.h"
#include "teapotSceneBuilder.h"
#include "mtrlSceneBuilder.h"
#include "complexBunnySceneBuilder.h"
#include "normalMapSceneBuilder.h"

Scene::Scene(SceneType sceneType, int resolutionScale, int samplersPerPixel, int depth)
{
    m_pObjectPool = std::make_shared<ObjectPool>(isBVHOn(sceneType));
    
    m_pBuilder = createSceneBuilder(sceneType);
    m_pBuilder->init(m_pObjectPool);

    std::shared_ptr<Tracer> tracer = std::make_shared<NeeTracer>(depth);
    m_pCamera = std::make_shared<PinholeCamera>(tracer, resolutionScale, samplersPerPixel);
}

void Scene::run()
{
    TimeRecorder t;
    t.start();

    preConstructScene();
    constructScene();

    preRender();

    render();
    postRender();

    t.end();
}

void Scene::batchRun()
{
    // Todo:
}

void Scene::preConstructScene()
{
}

void Scene::constructScene()
{
    if (m_pBuilder)
    {
        m_pBuilder->build();
    }
}

void Scene::preRender()
{
    m_pCamera->setPool(m_pObjectPool);
    m_pCamera->build(Vector3(0, 0, 0), Vector3(0, 0, 0));

    Transform t = m_pCamera->getTransform().getInverseTransform();
    m_pObjectPool->applyTransfrom(t);
    m_pObjectPool->log();

    m_pObjectPool->buildBoundBox();
    m_pObjectPool->initHitter();
}

void Scene::render()
{
    m_pCamera->render();
}

void Scene::postRender()
{
    m_pCamera->saveToImage(configOutputImageName);
    Common::printCurrentTime();
}

bool Scene::isBVHOn(SceneType type) const
{
    if (type == SceneType::ROOM_SIMPLE_BUNNY)
        return true;

    if (type == SceneType::ROOM_TEAPOT)
        return true;

    if (type == SceneType::ROOM_COMPLEX_BUNNY)
        return true;

    return false;
}

std::shared_ptr<SceneBuilder> Scene::createSceneBuilder(SceneType type) const
{
    std::shared_ptr<SceneBuilder> builder = nullptr;

    if (type == SceneType::ROOM_SIMPLE_BUNNY)
        builder = std::make_shared<SimpleBunnySceneBuilder>();
    else if (type == SceneType::ROOM_SIMPLE)
        builder = std::make_shared<SimpleSceneBuilder>();
    else if (type == SceneType::ROOM_COMPLEX_BUNNY)
        builder = std::make_shared<ComplexBunnyBuilder>();
    else if (type == SceneType::ROOM_TEAPOT)
        builder = std::make_shared<TeapotSceneBuilder>();
    else if (type == SceneType::ROOM_MATERIAL_BALLS)
        builder = std::make_shared<MtrlSceneBuilder>();
    else if (type == SceneType::ROOM_NORMAL_MAP)
        builder = std::make_shared<NormalMapSceneBuilder>();
    // else if (type == SceneType::ROOM_CURVE)
    //     builder = std::make_shared<CurveSceneBuilder>();
    else
        builder = std::make_shared<SimpleSceneBuilder>();

    return builder;
}
