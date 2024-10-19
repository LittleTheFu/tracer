#ifndef _ROOM_H_
#define _ROOM_H_

#include "geometry.h"
#include <vector>

class Room
{
public:
    Room();

    //auto ptr, maybe? or I will implement a singleton
    //consider it later,maybe.(maybe not,perhaps)
    std::vector<Geometry *> getTris() const;

private:
    void init();

private:
    std::vector<Geometry*> m_tris;
};

#endif