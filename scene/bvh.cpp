#include "bvh.h"
#include "boundBox.h"

void BVH::init(const std::vector<Geometry *> objects)
{
    m_objects = objects;

    build();
}

void BVH::build()
{
    BoundBox rootBox;
    BoundBox centerBox;

    for (std::vector<Geometry *>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
    {
        (*it)->buildBoundBox();

        rootBox.update((*it)->getBoundBox());
        centerBox.update((*it)->getBoundBox().getCenter());
    }

    // std::cout << rootBox << std::endl;
    // std::cout << centerBox << std::endl;
    
    generateTree();
}

void BVH::generateTree()
{
}
