#ifndef _MEDIUM_MANAGER_H_
#define _MEDIUM_MANAGER_H_

#include <unordered_map>
#include <string>
#include <memory>

class Medium;

enum class MediumType
{
    VACUUM = 0,
    GLASS,
};

class MediumManager
{
public:
    MediumManager();
    ~MediumManager() = default;

    static MediumManager &getInstance();

    std::shared_ptr<Medium> getMedium(MediumType type);

private:
    void init();

private:
    std::unordered_map<MediumType, std::shared_ptr<Medium>> m_mediums;
};

#endif
