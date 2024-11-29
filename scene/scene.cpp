#include "scene.h"
#include "simpleTracer.h"
#include "randomTracer.h"
#include "volTracer.h"
#include "common.h"
#include "timeRecorder.h"
#include "pinholeCamera.h"
#include "config.h"

Scene::Scene(std::shared_ptr<SceneBuilder> pBuilder, TracerType tracerType)
{
    m_pObjectPool = std::make_shared<ObjectPool>();

    m_pBuilder = pBuilder;
    m_pBuilder->init(m_pObjectPool);

    std::shared_ptr<Tracer> tracer = nullptr;
    if (tracerType == TracerType::SIMPLE)
        tracer = std::make_shared<SimpleTracer>();
    else if (tracerType == TracerType::RANDOM)
        tracer = std::make_shared<RandomTracer>();
    else
        tracer = std::make_shared<VolTracer>();

    m_pCamera = std::make_shared<PinholeCamera>(tracer);

    m_MaxBounces = configBatchEndBounces;
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
    TimeRecorder t;
    t.start();
    
    preConstructScene();
    constructScene();

    preRender();

    int bounce = configBatchStartBounce;

    while (true)
    {
        configOutputImageName = std::to_string(bounce);
        m_pCamera->setBounceTime(bounce);

        render();
        postRender();

        bounce++;
        if (bounce > m_MaxBounces)
            break;
    }

    t.end();
}

void Scene::preConstructScene()
{
}

void Scene::constructScene()
{
    if(m_pBuilder)
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