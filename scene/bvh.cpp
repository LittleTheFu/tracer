#include "bvh.h"
#include "boundBox.h"
#include <cassert>

void BVH::init(const std::vector<Geometry *> objects)
{
    m_objects = objects;

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

    m_rootNode = generateTree(m_objects, rootBox, rootCenterBox, 100000, 0);

    std::cout << "after generateTree" << std::endl;
    printNode(m_rootNode,"");
}

BVHNode* BVH::generateTree(const std::vector<Geometry *> &objects,
                       const BoundBox &boundBox,
                       const BoundBox &centerBox,
                       int parentSize,
                       int depth)
{
    int num = objects.size();
    parentSize = num;
    std::cout << "[" << num << "]" << ":" << depth << std::endl;
    BVHNode *node = new BVHNode();

    if(objects.size() <= 200 || depth > 10)
    {
        node->m_objects = objects;
        return node;
    }

    // 1.get the main axis
    BoundBox::Axis axis = centerBox.getMainAxis();

    // 2.get the position to split along the axis
    //split bound box
    BoundBox leftChildBoundBox, rightChildBoundBox;
    boundBox.split(axis, leftChildBoundBox, rightChildBoundBox);

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
        node->m_objects = objects;
        return node;
    }

    if (l_size > 0)
    {
        std::cout << " L: ";
        node->leftChild = generateTree(leftObjects, leftBoundBox, leftCenterBox, parentSize, depth + 1);
    }

    int r_size = rightObjects.size();
    if (r_size == parentSize)
    {
        node->m_objects = objects;
        return node;
    }
    if (r_size > 0)
    {
        std::cout << " R: ";
        node->rightChild = generateTree(rightObjects, rightBoundBox, rightCenterBox, parentSize, depth + 1);
    }

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
