#include <algorithm>
#include <cassert>

#include "bvh.h"
#include "boundBox.h"
#include "mathConstantDef.h"
#include "mathUtility.h"
#include "medium.h"

bool BVH::search(std::shared_ptr<Geometry> geometry) const
{
    if (!m_rootNode)
        return false;

    return _search(m_rootNode, geometry);
}

bool BVH::_search(std::shared_ptr<BVHNode> node, std::shared_ptr<Geometry> geometry) const
{
    if (!node)
        return false;

    if (node->isLeaf())
    {
        for (auto it = node->primitives.begin(); it != node->primitives.end(); it++)
        {
            if ((*it)->getGeometry() == geometry)
                return true;
        }

        return false;
    }

    if (node->leftChild && _search(node->leftChild, geometry))
        return true;

    if (node->rightChild && _search(node->rightChild, geometry))
        return true;

    return false;
}

void BVH::init(std::vector<std::shared_ptr<AreaLight>> lights,
               const std::vector<std::shared_ptr<Primitive>> &primitives,
               std::shared_ptr<SphereVolume> volume)
{
    HitterInterface::init(lights, primitives, volume);
    build();
}

void BVH::build()
{
    m_rootNode = generateTree(primitives_, 0);

    std::cout << "after generateTree" << std::endl;
    printNode(m_rootNode, "");
}

std::shared_ptr<BVHNode> BVH::generateTree(const std::vector<std::shared_ptr<Primitive>> &primitives, int depth)
{
    BoundBox primitivesBoundBox = getBoundBox(primitives);

    std::shared_ptr<BVHNode> node = std::make_shared<BVHNode>();
    node->boundBox = primitivesBoundBox;

    if (depth > DEPTH || primitives.size() <= 1)
    {
        node->primitives = primitives;

        return node;
    }

    // 1.get the main axis
    BoundBox centroidBox = getCentroidBox(primitives);
    Axis axis = centroidBox.getMainAxis();

    // 2.get the position to split along the axis
    // split bound box
    BoundBox leftChildBoundBox, rightChildBoundBox;
    calcBestSplit(primitives, leftChildBoundBox, rightChildBoundBox);

    // 3.split objects into two children
    std::vector<std::shared_ptr<Primitive>> leftPrimitives, rightPrimitives;
    splitObjects(primitives, leftChildBoundBox, rightChildBoundBox, leftPrimitives, rightPrimitives);

    if (leftPrimitives.size() == primitives.size())
    {
        node->primitives = primitives;
        return node;
    }

    if (rightPrimitives.size() == primitives.size())
    {
        node->primitives = primitives;
        return node;
    }

    if (leftPrimitives.size() > 0)
        node->leftChild = generateTree(leftPrimitives, depth + 1);

    if (rightPrimitives.size() > 0)
        node->rightChild = generateTree(rightPrimitives, depth + 1);

    if (!node->leftChild && !node->rightChild)
        node->primitives = primitives;

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
                                 Interaction &interaction,
                                 std::shared_ptr<Primitive> skipPrimitive) const
{
    if (node->isLeaf())
        return hitLeaf(ray, node->primitives, interaction, skipPrimitive);

    BoundBox box = node->boundBox;

    std::shared_ptr<BVHNode> leftChild = node->leftChild;
    std::shared_ptr<BVHNode> rightChild = node->rightChild;

    Interaction leftInteraction;
    Interaction rightInteraction;

    bool isLeftChildHit = false;
    bool isRightChildHit = false;

    float t;

    bool isIn = box.isInBox(ray.origin);
    bool isHit = box.hit(ray, t);

    if (isIn || isHit)
    {
        if (leftChild)
            isLeftChildHit = _hitGeometryObjectOnly(leftChild, ray, leftInteraction, skipPrimitive);

        if (rightChild)
            isRightChildHit = _hitGeometryObjectOnly(rightChild, ray, rightInteraction, skipPrimitive);

        // quick and dirty
        if (!isLeftChildHit && !isRightChildHit)
        {
        }
        else if (isLeftChildHit && !isRightChildHit)
        {
            interaction = leftInteraction;
        }
        else if (!isLeftChildHit && isRightChildHit)
        {
            interaction = rightInteraction;
        }
        else
        {
            if (leftInteraction.t < rightInteraction.t)
                interaction = leftInteraction;
            else
                interaction = rightInteraction;
        }

        bool is_hit = isLeftChildHit || isRightChildHit;
        return is_hit;
    }

    return false;
}

bool BVH::hitGeometryObjectOnly(const Ray &ray, Interaction &interaction, std::shared_ptr<Primitive> skipPrimitive) const
{
    return _hitGeometryObjectOnly(m_rootNode, ray, interaction, skipPrimitive);
}

bool BVH::hitLeaf(const Ray &ray,
                  const std::vector<std::shared_ptr<Primitive>> primitives,
                  Interaction &interaction,
                  std::shared_ptr<Primitive> skipPrimitive) const
{
    assert(primitives.size() > 0);
    bool hit = false;
    float tMin = MathConstant::FLOAT_MAX;

    // for (auto it = objects.begin(); it != objects.end(); it++)
    for (auto it = primitives.begin(); it != primitives.end(); it++)
    {
        if (skipPrimitive == (*it))
            continue;

        Interaction tempInteraction;

        if ((*it)->getGeometry()->hit(ray, tempInteraction))
        {
            if (tempInteraction.t < tMin)
            {
                tMin = tempInteraction.t;
                interaction = tempInteraction;
                interaction.primitive = (*it);
                hit = true;
            }
        }
    }

    // quick and dirty
    //consider to merge this with simpleHitter,later....
    if (hit)
    {
        if (isVolumePrimitive(interaction.primitive))
        {
            interaction.is_volume_boundary_hit = true;
            interaction.is_surface_hit = false;
            interaction.medium = volume_->getMedium();
            interaction.mediumBoundary = interaction.primitive->getMediumBoundary();
        }
        else
        {
            interaction.is_volume_boundary_hit = false;
            interaction.is_surface_hit = true;
            interaction.medium = nullptr;
            interaction.mediumBoundary = interaction.primitive->getMediumBoundary();
        }
    }
    else
    {
        interaction.is_volume_boundary_hit = false;
        interaction.is_surface_hit = false;
        interaction.medium = nullptr;
        interaction.mediumBoundary = interaction.primitive->getMediumBoundary();
    }

    return hit;
}

Color BVH::getColorFromLight(const Ray &ray, int index) const
{
    if (index >= lights_.size())
    {
        return Color::COLOR_BLACK;
    }

    float t;
    Vector3 normal;
    float dot;
    Interaction _interaction;
    if (!lights_.at(index)->getGeometryPrimitive()->getGeometry()->hit(ray, _interaction))
    {
        return Color::COLOR_BLACK;
    }

    Color color = lights_.at(index)->getColor();

    Ray shadowRay(ray);
    float tr = 1.0f;
    while (true)
    {
        Interaction interaction;
        bool isHit = hitGeometryObjectOnly(shadowRay, interaction, nullptr);

        // no other object hit, return light color directly
        if (interaction.primitive == lights_.at(index)->getGeometryPrimitive())
            return tr * color;

        if (interaction.is_volume_boundary_hit)
        {
            if (shadowRay.medium)
            {
                tr *= shadowRay.medium->transmittance(shadowRay, interaction.t);

                shadowRay.medium = nullptr;
                shadowRay.origin = interaction.point + shadowRay.dir * MathConstant::FLOAT_SMALL_NUMBER;
            }
            else
            {
                shadowRay.medium = interaction.medium;
                shadowRay.origin = interaction.point + shadowRay.dir * MathConstant::FLOAT_SMALL_NUMBER;
            }
        }
        else
        {
            return Color::COLOR_BLACK;
        }
    }

    return Color::COLOR_BLACK;
}

BoundBox BVH::getBoundBox(const std::vector<std::shared_ptr<Primitive>> &primitives) const
{
    // assert(objects.size() > 0);
    BoundBox primitivesBoundBox;

    for (auto it = primitives.begin(); it != primitives.end(); it++)
    {
        primitivesBoundBox.update((*it)->getGeometry()->getBoundBox());
    }

    // assert(!primitivesBoundBox.hasInfiniteComponent());

    return primitivesBoundBox;
}

BoundBox BVH::getCentroidBox(const std::vector<std::shared_ptr<Primitive>> &primitives) const
{
    // assert(objects.size() > 0);
    BoundBox primitivesBoundBox;

    for (auto it = primitives.begin(); it != primitives.end(); it++)
    {
        primitivesBoundBox.update((*it)->getGeometry()->getCentroid());
    }

    // assert(!primitivesBoundBox.hasInfiniteComponent());
    return primitivesBoundBox;
}

void BVH::splitObjects(const std::vector<std::shared_ptr<Primitive>> &primitives,
                       const BoundBox &leftBox,
                       const BoundBox &rightBox,
                       std::vector<std::shared_ptr<Primitive>> &outLeftPrimitives,
                       std::vector<std::shared_ptr<Primitive>> &outRightPrimitives) const
{
    // assert(!leftBox.hasInfiniteComponent());
    // assert(!rightBox.hasInfiniteComponent());
    // assert(primitives.size() > 0);

    for (auto it = primitives.begin(); it != primitives.end(); it++)
    {
        Vector3 centroid = (*it)->getGeometry()->getCentroid();

        if (leftBox.isInBox(centroid))
        {
            outLeftPrimitives.push_back(*it);
        }

        if (rightBox.isInBox(centroid))
        {
            outRightPrimitives.push_back(*it);
        }
    }

    // assert(outLeftObjects.size() + outRightObjects.size() >= objects.size());
}

void BVH::calcBestSplit(const std::vector<std::shared_ptr<Primitive>> &primitives,
                        BoundBox &outLeftBox,
                        BoundBox &outRightBox) const
{
    // assert(objects.size() > 0);

    // 1.get main axis
    BoundBox centerBox = getCentroidBox(primitives);
    Axis axis = centerBox.getMainAxis();

    BoundBox boundBox = getBoundBox(primitives);

    // 2.create buckets
    const int BUCKET_NUM = 12;
    Bucket buckets[BUCKET_NUM];

    float percent = 1.0f / BUCKET_NUM;
    for (int i = 0; i < BUCKET_NUM; i++)
    {
        float startPercent = i * percent;
        float endPercent = (i + 1) * percent;

        buckets[i].originBoundBox = boundBox.createSubBox(axis, startPercent, endPercent);
        buckets[i].updatedBoundBox.update(buckets[i].originBoundBox.getCenter());
    }

    // 3.do calc in each bucket
    for (auto it = primitives.begin(); it != primitives.end(); it++)
    {
        for (int i = 0; i < BUCKET_NUM; i++)
        {
            Vector3 centroid = (*it)->getGeometry()->getCentroid();
            if (buckets[i].originBoundBox.isInBox(centroid))
            {
                BoundBox box = (*it)->getGeometry()->getBoundBox();
                buckets[i].num++;
                buckets[i].updatedBoundBox.update(box);
            }
        }
    }

    // 4.get the spilt with smallest cost
    float cost[BUCKET_NUM];
    std::fill_n(cost, BUCKET_NUM, 0.0f);

    BoundBox boundBelow;
    int countBelow = 0;
    for (int i = 0; i < BUCKET_NUM; i++)
    {
        boundBelow.update(buckets[i].updatedBoundBox);
        countBelow += buckets[i].num;
        cost[i] += countBelow * boundBelow.surfaceArea();
    }

    BoundBox boundAbove;
    int countAbove = 0;
    for (int i = BUCKET_NUM - 1; i >= 0; i--)
    {
        boundAbove.update(buckets[i].updatedBoundBox);
        countAbove += buckets[i].num;
        cost[i] += countAbove * boundAbove.surfaceArea();
    }

    float minCost = MathConstant::FLOAT_MAX;
    int splitIndex = -1;
    for (int i = 0; i < BUCKET_NUM; i++)
    {
        if (cost[i] < minCost)
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