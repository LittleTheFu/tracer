#include "volume.h"

Volume::Volume(std::shared_ptr<Medium> medium)
{
    medium_ = medium;
}

std::shared_ptr<Medium> Volume::getMedium() const
{
    return medium_;
}
