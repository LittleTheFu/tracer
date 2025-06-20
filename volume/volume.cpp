#include "volume.h"

Volume::Volume(std::shared_ptr<const Medium> medium)
{
    medium_ = medium;
}

std::shared_ptr<const Medium> Volume::getMedium() const
{
    return medium_;
}
