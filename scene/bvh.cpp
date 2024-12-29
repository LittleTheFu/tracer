#include <algorithm>
#include <cassert>

#include "bvh.h"
#include "boundBox.h"
#include "mathConstantDef.h"
#include "mathUtility.h"

bool BVH::search(std::shared_ptr<Geometry> geometry) const
{
    if(!m_rootNode)
        return false;

    return _search(m_rootNode, geometry);
}

bool BVH::_search(std::shared_ptr<BVHNode> node, std::shared_ptr<Geometry> geometry) const
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

void BVH::init(const std::vector<std::shared_ptr<Geometry>> &objects, std::shared_ptr<const Light> light)
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

std::shared_ptr<BVHNode> BVH::generateTree(const std::vector<std::shared_ptr<Geometry>> &objects, int depth)
{
    BoundBox objectsBoundBox = getBoundBox(objects);

    std::shared_ptr<BVHNode> node = std::make_shared<BVHNode>();
    node->boundBox = objectsBoundBox;

    if( depth > DEPTH || objects.size() <= 1)
    {
        node->objects = objects;
        return node;
    }

    // 1.get the main axis
    BoundBox centroidBox = getCentroidBox(objects);
    Axis axis = centroidBox.getMainAxis();

    // 2.get the position to split along the axis
    //split bound box
    BoundBox leftChildBoundBox, rightChildBoundBox;
    calcBestSplit(objects, leftChildBoundBox, rightChildBoundBox);

    // 3.split objects into two children
    std::vector<std::shared_ptr<Geometry>> leftObjects, rightObjects;
    splitObjects(objects, leftChildBoundBox, rightChildBoundBox, leftObjects, rightObjects);

    if(leftObjects.size() == objects.size())
    {
        node->objects = objects;
        return node;
    }

    if(rightObjects.size() == objects.size())
    {
        node->objects = objects;
        return node;
    }

    if (leftObjects.size() > 0)
        node->leftChild = generateTree(leftObjects, depth + 1);
  
    if (rightObjects.size() > 0)
        node->rightChild = generateTree(rightObjects, depth + 1);

    if(!node->leftChild && !node->rightChild)
        node->objects = objects;

    return node;
}

void BVH::printNode(std::shared_ptr<BVHNode> node, const std::string &prefix)
{
    node->print(prefix);

    if (node->leftChild)
        printNode(node->leftChild, prefix + "~~");

    if (node->rightChild)
        printNode(node->rightChild, prefix + "~~");
}

bool BVH::_hitGeometryObjectOnly(std::shared_ptr<BVHNode> node,
              const Ray &ray,
              HitRecord &record) const
{
    if (node->isLeaf())
        return hitLeaf(ray, node->objects, record);

    BoundBox box = node->boundBox;

    std::shared_ptr<BVHNode> leftChild = node->leftChild;
    std::shared_ptr<BVHNode> rightChild = node->rightChild;

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

bool BVH::hitGeometryObjectOnly(const Ray &ray, HitRecord &record, bool skipVolume) const
{
    return _hitGeometryObjectOnly(m_rootNode, ray, record);
}

bool BVH::hitLeaf(const Ray &ray, const std::vector<std::shared_ptr<Geometry>> objects, HitRecord &record) const
{
    assert(objects.size() > 0);
    bool hit = false;
    float tMin = MathConstant::FLOAT_MAX;

    for (auto it = objects.begin(); it != objects.end(); it++)
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

    Color color = m_pLight->getColor();

    HitRecord record;
    if (!_hitGeometryObjectOnly(m_rootNode, ray, record))
    {
        // return color * dot;
        return color;
    }

    if (t < record.t)
    {
        // return color * dot;
        return color;
    }

    return Color::COLOR_BLACK;
}

BoundBox BVH::getBoundBox(const std::vector<std::shared_ptr<Geometry>> &objects) const
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

BoundBox BVH::getCentroidBox(const std::vector<std::shared_ptr<Geometry>> &objects) const
{
    // assert(objects.size() > 0);
    BoundBox centerBox;

    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        centerBox.update((*it)->getCentroid());
    }

    // assert(!centerBox.hasInfiniteComponent());
    return centerBox;
}

void BVH::splitObjects(const std::vector<std::shared_ptr<Geometry>> &objects,
                         const BoundBox &leftBox,
                         const BoundBox &rightBox,
                         std::vector<std::shared_ptr<Geometry>> &outLeftObjects,
                         std::vector<std::shared_ptr<Geometry>> &outRightObjects) const
{
    // assert(!leftBox.hasInfiniteComponent());
    // assert(!rightBox.hasInfiniteComponent());
    // assert(objects.size() > 0);

    for(auto it = objects.begin(); it != objects.end(); it++)
    {
        Vector3 centroid = (*it)->getCentroid();
        
        if(leftBox.isInBox(centroid))
            outLeftObjects.push_back(*it);

        if(rightBox.isInBox(centroid))
            outRightObjects.push_back(*it);
    }

    // assert(outLeftObjects.size() + outRightObjects.size() >= objects.size());
}

void BVH::calcBestSplit(const std::vector<std::shared_ptr<Geometry>> &objects, BoundBox &outLeftBox, BoundBox &outRightBox) const
{
    // assert(objects.size() > 0);

    //1.get main axis
    BoundBox centerBox = getCentroidBox(objects);
    Axis axis = centerBox.getMainAxis();

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

    float minCost = MathConstant::FLOAT_MAX;
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
    assert(MathUtility::is_in_range(splitPercent, 0, 1, true, true));

    boundBox.split(axis, splitPercent, outLeftBox, outRightBox);
}