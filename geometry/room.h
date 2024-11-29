#ifndef _ROOM_H_
#define _ROOM_H_

#include "geometry.h"
#include <vector>
#include <memory>

class Room
{
public:
    Room();

    //auto ptr, maybe? or I will implement a singleton
    //consider it later,maybe.(maybe not,perhaps)
    std::vector<std::shared_ptr<Geometry>> getTris() const;

private:
    void init();
    void refine();

private:
    std::vector<std::shared_ptr<Geometry>> m_tris;
};

#endif // _ROOM_H_