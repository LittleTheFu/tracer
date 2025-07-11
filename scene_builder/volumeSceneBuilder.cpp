#include "config.h"
#include "volumeSceneBuilder.h"
#include "medium.h"

void VolumeSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(configLightIntensityScale);

    std::shared_ptr<Medium> medium = std::make_shared<Medium>(0.000f, 0.000f);
    std::shared_ptr<SphereVolume> volume = std::make_shared<SphereVolume>(medium, Vector3(0, -20, 320), 50.0f);

    m_pObjectPool->setVolume(volume);

    std::shared_ptr<GeometryPrimitive> primitive = std::make_shared<GeometryPrimitive>(volume->getGeometry(), nullptr);
    m_pObjectPool->addPrimitive(primitive);
}