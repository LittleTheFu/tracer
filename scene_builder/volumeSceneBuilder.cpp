#include "config.h"
#include "volumeSceneBuilder.h"
#include "medium.h"

void VolumeSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 40, 290), 10);
    setLightIntensity(0, 60);

    std::shared_ptr<Medium> medium = std::make_shared<Medium>(0.002f, 0.002f);
    std::shared_ptr<SphereVolume> volume = std::make_shared<SphereVolume>(medium, Vector3(0, 0, 320), 40.0f);

    m_pObjectPool->setVolume(volume);

    std::shared_ptr<GeometryPrimitive> primitive = std::make_shared<GeometryPrimitive>(volume->getGeometry(), nullptr);
    m_pObjectPool->addPrimitive(primitive);
    
    // buildVolumeBall(Vector3(0, 0, 320), 100);
}