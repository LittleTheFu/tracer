#include "scene.h"
#include "simpleTracer.h"
#include "randomTracer.h"
#include "common.h"
#include "timeRecorder.h"
#include "pinholeCamera.h"
#include "config.h"

Scene::Scene(SceneBuilder *pBuilder, bool useSimpleTracer)
{
    m_pObjectPool = new ObjectPool();

    m_pBuilder = pBuilder;
    m_pBuilder->init(m_pObjectPool);

    Tracer *tracer = nullptr;
    if (useSimpleTracer)
        tracer = new SimpleTracer();
    else
        tracer = new RandomTracer();

    m_pCamera = new PinholeCamera(tracer);
}

void Scene::run()
{
    TimeRecorder t;
    t.start();
    
    preConstructScene();
    constructScene();

    preRender();

    while (true)
    {
        configOutputImageName = std::to_string(configBounceTime);
        m_pCamera->setBounceTime(configBounceTime);

        render();
        postRender();
        configBounceTime++;
        if (configBounceTime > 20)
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