#include "bvh.h"
#include "boundBox.h"
#include "common.h"
#include <cassert>
#include <algorithm>

bool BVH::search(Geometry *geometry) const
{
    if(!m_rootNode)
        return false;

    return _search(m_rootNode, geometry);
}

bool BVH::_search(BVHNode *node, Geometry *geometry) const
{
    if(!node)
        return false;

    if (node->isLeaf())
    {
        auto it = std::find(node->objects.begin(), node->objects.end(), geometry);

        if (it != node->objects.end())
            return true;
        else
            return false;
    }

    if(node->leftChild && _search(node->leftChild, geometry))
        return true;

    if(node->rightChild && _search(node->rightChild, geometry))
        return true;

    return false;
}

void BVH::init(const std::vector<Geometry *> &objects, const Light *light)
{
    HitterInterface::init(objects, light);
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

    BVHNode *node = new BVHNode();
    node->boundBox = objectsBoundBox;

    if( depth > 18 || objects.size() <= 1)
    {
        node->objects = objects;
        return node;
    }

    // 1.get the main axis
    BoundBox centroidBox = getCentroidBox(objects);
    Common::Axis axis = centroidBox.getMainAxis();

    // 2.get the position to split along the axis
    //split bound box
    BoundBox leftChildBoundBox, rightChildBoundBox;
    objectsBoundBox.split(axis, 0.5, leftChildBoundBox, rightChildBoundBox);
    // calcBestSplit(objects, leftChildBoundBox, rightChildBoundBox);

    // 3.split objects into two children
    std::vector<Geometry *> leftObjects, rightObjects;
    splitObjects(objects, leftChildBoundBox, rightChildBoundBox, leftObjects, rightObjects);

    if (leftObjects.size() > 0)
        node->leftChild = generateTree(leftObjects, depth + 1);
  
    if (rightObjects.size() > 0)
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

bool BVH::_hitGeometryObjectOnly(BVHNode *node,
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
            isLeftChildHit = _hitGeometryObjectOnly(leftChild, ray, leftRecord);

        if (rightChild)
            isRightChildHit = _hitGeometryObjectOnly(rightChild, ray, rightRecord);

        record = leftRecord.getCloserOne(rightRecord);

        bool is_hit = isLeftChildHit || isRightChildHit;
        return is_hit;
    }

    return false;
}

bool BVH::hitGeometryObjectOnly(const Ray &ray, HitRecord &record) const
{
    return _hitGeometryObjectOnly(m_rootNode, ray, record);
}

bool BVH::hitSceneWithLight(const Ray &ray,
                            HitRecord &record,
                            bool &out_isLightHit) const
{
    out_isLightHit = false;

    bool isHit = false;

    isHit = _hitGeometryObjectOnly(m_rootNode, ray, record);
    float tMin = record.t;

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
    assert(objects.size() > 0);
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
    if (!_hitGeometryObjectOnly(m_rootNode, ray, record))
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
    // assert(objects.size() > 0);
    BoundBox objectsBoundBox;

    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        objectsBoundBox.update((*it)->getBoundBox());
    }

    // assert(!objectsBoundBox.hasInfiniteComponent());

    return objectsBoundBox;
}

BoundBox BVH::getCentroidBox(const std::vector<Geometry *> &objects) const
{
    // assert(objects.size() > 0);
    BoundBox centerBox;

    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        centerBox.update((*it)->getBoundBox().getCenter());
    }

    // assert(!centerBox.hasInfiniteComponent());
    return centerBox;
}

void BVH::splitObjects(const std::vector<Geometry *> &objects, const BoundBox &leftBox, const BoundBox &rightBox, std::vector<Geometry *> &outLeftObjects, std::vector<Geometry *> &outRightObjects) const
{
    // assert(!leftBox.hasInfiniteComponent());
    // assert(!rightBox.hasInfiniteComponent());
    // assert(objects.size() > 0);

    for(auto it = objects.begin(); it != objects.end(); it++)
    {
        bool b_l = false;
        bool b_r = false;
        Vector3 centroid = (*it)->getBoundBox().getCenter();
        if(leftBox.isInBox(centroid))
            outLeftObjects.push_back(*it);

        if(rightBox.isInBox(centroid))
            outRightObjects.push_back(*it);
    }

    // assert(outLeftObjects.size() + outRightObjects.size() >= objects.size());
}

void BVH::calcBestSplit(const std::vector<Geometry *> &objects, BoundBox &outLeftBox, BoundBox &outRightBox) const
{
    // assert(objects.size() > 0);

    //1.get main axis
    BoundBox centerBox = getCentroidBox(objects);
    Common::Axis axis = centerBox.getMainAxis();

    BoundBox boundBox = getBoundBox(objects);
    
    //2.create buckets
    const int BUCKET_NUM = 12;
    Bucket buckets[BUCKET_NUM];

    float percent = 1.0f / BUCKET_NUM;
    for(int i = 0; i < BUCKET_NUM; i++)
    {
        float startPercent = i * percent;
        float endPercent = (i + 1) * percent;

        buckets[i].originBoundBox = boundBox.createSubBox(axis, startPercent, endPercent);
        buckets[i].updatedBoundBox.update(buckets[i].originBoundBox.getCenter());
    }

    //3.do calc in each bucket
    for(auto it = objects.begin(); it != objects.end(); it++)
    {
        for(int i = 0; i < BUCKET_NUM; i++)
        {
            Vector3 centroid = (*it)->getBoundBox().getCenter();
            if(buckets[i].originBoundBox.isInBox(centroid))
            {
                BoundBox box = (*it)->getBoundBox();
                buckets[i].num++;
                buckets[i].updatedBoundBox.update(box);
            }
        }
    }

    //4.get the spilt with smallest cost
    float cost[BUCKET_NUM];
    std::fill_n(cost, BUCKET_NUM, 0.0f);

    BoundBox boundBelow;
    int countBelow = 0;
    for(int i = 0; i < BUCKET_NUM; i++)
    {
        boundBelow.update(buckets[i].updatedBoundBox);
        countBelow += buckets[i].num;
        cost[i] += countBelow * boundBelow.surfaceArea();
    }

    BoundBox boundAbove;
    int countAbove = 0;
    for(int i = BUCKET_NUM - 1; i >= 0; i--)
    {
        boundAbove.update(buckets[i].updatedBoundBox);
        countAbove += buckets[i].num;
        cost[i] += countAbove * boundAbove.surfaceArea();
    }

    float minCost = Common::FLOAT_MAX;
    int splitIndex = -1;
    for(int i = 0; i < BUCKET_NUM; i++)
    {
        if(cost[i] < minCost)
        {
            minCost = cost[i];
            splitIndex = i;
        }
    }

    assert(splitIndex != -1);

    float splitPercent = percent * (splitIndex + 1);
    assert(Common::is_in_range(splitPercent, 0, 1, true, true));

    boundBox.split(axis, splitPercent, outLeftBox, outRightBox);
}