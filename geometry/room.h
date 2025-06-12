#ifndef _ROOM_H_
#define _ROOM_H_

#include <memory>
#include <vector>

#include "geometry.h"

class Room
{
public:
    Room();

    std::vector<std::shared_ptr<Geometry>> getTris() const;

private:
    void init();
    void refine();

private:
    std::vector<std::shared_ptr<Geometry>> m_tris;
};

#endif // _ROOM_H_