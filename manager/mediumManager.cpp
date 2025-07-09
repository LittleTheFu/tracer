#include "mediumManager.h"
#include "medium.h"
#include <assert.h>

MediumManager::MediumManager()
{
    init();
}

MediumManager &MediumManager::getInstance()
{
    static MediumManager instance;
    return instance;
}


std::shared_ptr<Medium> MediumManager::getMedium(MediumType type)
{
    if (m_mediums.find(type) == m_mediums.end())
    {
        assert(0);
        return nullptr;
    }

    return m_mediums[type];
}

void MediumManager::init()
{
    //add default medium
    std::shared_ptr<Medium> vacuum = std::make_shared<Medium>(0.0f, 0.0f, 1.0f);
    m_mediums[MediumType::VACUUM] = vacuum;

    std::shared_ptr<Medium> glass = std::make_shared<Medium>(0.0f, 0.0f, 1.5f);
    m_mediums[MediumType::GLASS] = glass;
}
