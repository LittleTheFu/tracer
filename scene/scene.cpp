#include "scene.h"
#include "simpleTracer.h"
#include "randomTracer.h"
#include "common.h"
#include "timeRecorder.h"

Scene::Scene(SceneBuilder *pBuilder, bool useSimpleTracer)
{
    m_pBvh = new BVH();
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
    render();
    postRender();

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
    m_pCamera->setPool(m_pObjectPool, m_pBvh);
    m_pCamera->build(Vector3(0, 0, 0), Vector3(0, 0, 0));

    Transform t = m_pCamera->getTransform().getInverseTransform();
    m_pObjectPool->applyTransfrom(t);

    m_pObjectPool->buildBoundBox();
    m_pObjectPool->initHitter();
    // m_pBvh->init(m_pObjectPool->getObjects(), m_pObjectPool->m_pLight);
}

void Scene::render()
{
    m_pCamera->render();
}

void Scene::postRender()
{
    m_pCamera->saveToImage("img");
    Common::printCurrentTime();
}