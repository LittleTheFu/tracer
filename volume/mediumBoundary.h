#ifndef _MEDIUM_INTERFACE_H_
#define _MEDIUM_INTERFACE_H_

#include <memory>

class Medium;

class MediumBoundary
{
public:
    std::shared_ptr<Medium> mediumOutside_ = nullptr;
    std::shared_ptr<Medium> mediumInside_ = nullptr;
};

#endif