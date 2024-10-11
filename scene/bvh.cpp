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
    BoundBox rootBox;
    BoundBox rootCenterBox;

    for (std::vector<Geometry *>::const_iterator it = m_objects.begin(); it != m_objects.end(); it++)
    {
        (*it)->buildBoundBox();

        rootBox.update((*it)->getBoundBox());
        rootCenterBox.update((*it)->getBoundBox().getCenter());
    }

    // std::cout << rootBox << std::endl;
    // std::cout << centerBox << std::endl;

    m_rootNode = generateTree(m_objects, 100000, 0);

    std::cout << "after generateTree" << std::endl;
    printNode(m_rootNode,"");
}

BVHNode *BVH::generateTree(const std::vector<Geometry *> &objects,
                           int parentSize,
                           int depth)
{
    BoundBox parentBoundBox;
    BoundBox centerBox;

    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        parentBoundBox.update((*it)->getBoundBox());
        centerBox.update((*it)->getBoundBox().getCenter());
    }

    int num = objects.size();
    parentSize = num;
    std::cout << "[" << num << "]" << ":" << depth << std::endl;

    BVHNode *node = new BVHNode();
    node->boundBox = parentBoundBox;

    if( depth > 20)
    {
        node->objects = objects;
        node->boundBox = parentBoundBox;

        return node;
    }

    // 1.get the main axis
    BoundBox::Axis axis = centerBox.getMainAxis();

    // 2.get the position to split along the axis
    //split bound box
    BoundBox leftChildBoundBox, rightChildBoundBox;
    parentBoundBox.split(axis, leftChildBoundBox, rightChildBoundBox);

    // 3.split objects into two children
    std::vector<Geometry *> leftObjects, rightObjects;
    for(auto it = objects.begin(); it != objects.end(); it++)
    {
        BoundBox bbx = (*it)->getBoundBox();
        if(bbx.isOverlapped(leftChildBoundBox))
        {
            leftObjects.push_back(*it);
        }
        else if(bbx.isOverlapped(rightChildBoundBox))
        {
            rightObjects.push_back(*it);
        }
        else
        {
            assert(0);
        }
    }

    //4.caculate new boundBox of children's
    BoundBox leftBoundBox, leftCenterBox;
    for(auto it = leftObjects.begin(); it != leftObjects.end(); it++)
    {
        leftBoundBox.update((*it)->getBoundBox());
        leftCenterBox.update((*it)->getBoundBox().getCenter());
    }

    BoundBox rightBoundBox, rightCenterBox;
    for(auto it = rightObjects.begin(); it != rightObjects.end(); it++)
    {
        rightBoundBox.update((*it)->getBoundBox());
        rightCenterBox.update((*it)->getBoundBox().getCenter());
    }

    // 4.stop if needed

    // 5.child->genrateTree()
    int l_size = leftObjects.size();
    if(l_size == parentSize)
    {
        node->objects = objects;
        node->boundBox = leftBoundBox;

        return node;
    }

    if (l_size > 0)
    {
        std::cout << " L: ";
        node->leftChild = generateTree(leftObjects, parentSize, depth + 1);
    }

    int r_size = rightObjects.size();
    if (r_size == parentSize)
    {
        node->objects = objects;
        node->boundBox = rightBoundBox;
        
        return node;
    }
    if (r_size > 0)
    {
        std::cout << " R: ";
        node->rightChild = generateTree(rightObjects, parentSize, depth + 1);
    }

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
    if(node->isLeaf())
    {
        return hitLeaf(ray, node->objects,record);
    }

    BoundBox box = node->boundBox;

    float t;

    BVHNode *l = node->leftChild;
    BVHNode *r = node->rightChild;

    HitRecord l_record;
    HitRecord r_record;

    bool b_l_leaf_hit = false;
    bool b_r_leaf_hit = false;

    bool is_in = box.isInBox(ray.origin);
    bool is_hit = box.hit(ray, t);

    if ( is_in || is_hit)
    {
        if (l)
        {
            if (l->isLeaf())
            {
               b_l_leaf_hit = hitLeaf(ray, l->objects, l_record);
            }
            else
            {
                hit(l, ray, l_record);
            }
        }

        if (r)
        {
            if (r->isLeaf())
            {
                b_r_leaf_hit = hitLeaf(ray, r->objects, r_record);
            }
            else
            {
                hit(r, ray, r_record);
            }
        }

        if(l_record.t < r_record.t)
        {
            record = l_record;
        }
        else
        {
            record = r_record;
        }

        bool is_hit = b_l_leaf_hit || b_r_leaf_hit;
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

    if(isHit)
    {
        int a = 333;
    }

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

        if ((*it)->hit(ray, tempRecord, nullptr))
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