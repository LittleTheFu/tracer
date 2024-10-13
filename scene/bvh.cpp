#include "bvh.h"
#include "boundBox.h"
#include "common.h"
#include <cassert>

void BVH::init(const std::vector<Geometry *> objects, const Light *light)
{
    m_objects = objects;
    m_pLight = light;

    build();
}

void BVH::build()
{
    m_rootNode = generateTree(m_objects, 0);

    std::cout << "after generateTree" << std::endl;
    printNode(m_rootNode,"");
}

BVHNode *BVH::generateTree(const std::vector<Geometry *> &objects, int depth)
{
    BoundBox objectsBoundBox = getBoundBox(objects);
    BoundBox centerBox = getCentroidBox(objects);
    int objectNum = objects.size();

    // std::cout << "[" << objectNum << "]" << ":" << depth << std::endl;

    BVHNode *node = new BVHNode();
    node->boundBox = objectsBoundBox;

    if( depth > 20)
    {
        node->objects = objects;
        node->boundBox = objectsBoundBox;

        return node;
    }

    // 1.get the main axis
    BoundBox::Axis axis = centerBox.getMainAxis();

    // 2.get the position to split along the axis
    //split bound box
    BoundBox leftChildBoundBox, rightChildBoundBox;
    objectsBoundBox.split(axis, leftChildBoundBox, rightChildBoundBox);

    // 3.split objects into two children
    std::vector<Geometry *> leftObjects, rightObjects;
    splitObjects(objects, leftChildBoundBox, rightChildBoundBox, leftObjects, rightObjects);

    // 4.stop if needed

    // 5.child->genrateTree()
    int l_size = leftObjects.size();
    if(leftObjects.size() == objectNum)
    {
        node->objects = objects;
        return node;
    }

    int r_size = rightObjects.size();
    if (r_size == objectNum)
    {
        node->objects = objects;
        return node;
    }

    if (l_size > 0)
        node->leftChild = generateTree(leftObjects, depth + 1);
  
    if (r_size > 0)
        node->rightChild = generateTree(rightObjects, depth + 1);

    if(!node->leftChild && !node->rightChild)
        node->objects = objects;

    return node;
}

void BVH::printNode(BVHNode *node, const std::string &prefix)
{
    node->print(prefix);

    if (node->leftChild)
        printNode(node->leftChild, prefix + "~~");

    if (node->rightChild)
        printNode(node->rightChild, prefix + "~~");
}

bool BVH::hit(BVHNode *node,
              const Ray &ray,
              HitRecord &record) const
{
    if (node->isLeaf())
        return hitLeaf(ray, node->objects, record);

    BoundBox box = node->boundBox;

    BVHNode *leftChild = node->leftChild;
    BVHNode *rightChild = node->rightChild;

    HitRecord leftRecord;
    HitRecord rightRecord;

    bool isLeftChildHit = false;
    bool isRightChildHit = false;

    float t;

    bool isIn = box.isInBox(ray.origin);
    bool isHit = box.hit(ray, t);

    if (isIn || isHit)
    {
        if (leftChild)
            isLeftChildHit = hit(leftChild, ray, leftRecord);

        if (rightChild)
            isRightChildHit = hit(rightChild, ray, rightRecord);

        record = leftRecord.getCloserOne(rightRecord);

        bool is_hit = isLeftChildHit || isRightChildHit;
        return is_hit;
    }

    return false;
}

bool BVH::hitSceneWithLight(const Ray &ray,
                            HitRecord &record,
                            bool &out_isLightHit) const
{
    out_isLightHit = false;

    bool isHit = false;
    float tMin = Common::FLOAT_MAX;

    isHit = hit(m_rootNode, ray, record);

    float t;
    Vector3 normal;
    float dotLight;
    bool isLightHit = m_pLight->hit(ray, t, normal, dotLight);
    if (t < tMin)
    {
        out_isLightHit = true;
        isHit = true;

        record.dotLight = dotLight;
    }

    return isHit;
}

bool BVH::hitLeaf(const Ray &ray, const std::vector<Geometry *> objects, HitRecord &record) const
{
    bool hit = false;
    float tMin = Common::FLOAT_MAX;

    for (std::vector<Geometry *>::const_iterator it = objects.begin(); it != objects.end(); it++)
    {
        HitRecord tempRecord;

        if ((*it)->hit(ray, tempRecord))
        {
            if (tempRecord.t < tMin)
            {
                tMin = tempRecord.t;
                record = tempRecord;
                hit = true;
            }
        }
    }

    return hit;
}

Color BVH::getColorFromLight(const Ray &ray) const
{
    float t;
    Vector3 normal;
    float dot;
    if (!m_pLight->hit(ray, t, normal, dot))
    {
        // m_pLight->hit(ray, t, normal, dot);
        return Color::COLOR_BLACK;
    }

    Color color = Color::COLOR_WHITE;

    HitRecord record;
    if (!hit(m_rootNode, ray, record))
    {
        return color * dot;
    }

    if (t < record.t)
    {
        return color * dot;
    }

    return Color::COLOR_BLACK;
}

BoundBox BVH::getBoundBox(const std::vector<Geometry *> &objects) const
{
    BoundBox objectsBoundBox;

    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        objectsBoundBox.update((*it)->getBoundBox());
    }

    return objectsBoundBox;
}

BoundBox BVH::getCentroidBox(const std::vector<Geometry *> &objects) const
{
    BoundBox centerBox;

    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        centerBox.update((*it)->getBoundBox().getCenter());
    }

    return centerBox;
}

void BVH::splitObjects(const std::vector<Geometry *> &objects, const BoundBox &leftBox, const BoundBox &rightBox, std::vector<Geometry *> &outLeftObjects, std::vector<Geometry *> &outRightObjects) const
{
     for(auto it = objects.begin(); it != objects.end(); it++)
    {
        BoundBox bbx = (*it)->getBoundBox();
        if(bbx.isOverlapped(leftBox))
        {
            outLeftObjects.push_back(*it);
        }

        if(bbx.isOverlapped(rightBox))
        {
            outRightObjects.push_back(*it);
        }
    }

    assert(outLeftObjects.size() + outRightObjects.size() >= objects.size());
}