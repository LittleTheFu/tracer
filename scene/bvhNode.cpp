#include "bvhNode.h"

BVHNode::BVHNode()
{
    leftChild = nullptr;
    rightChild = nullptr;

    // geometry = nullptr;
}

void BVHNode::print(const std::string &prefix) const
{
    std::string l = leftChild ? " L " : " N ";
    std::string r = rightChild ? " R " : " N ";
    std::size_t num = getSize();

    std::cout << prefix << "|" << l << r << num << std::endl;
    // std::cout << boundBox << std::endl;
    // for(auto it = objects.begin(); it != objects.end(); it++)
    // {
    //     std::cout <<(*it)->getClassName() << "  ";
    // }
    // std::cout << std::endl;
}

bool BVHNode::isLeaf() const
{
    return !leftChild && !rightChild;
}

std::size_t BVHNode::getSize() const
{
    if (isLeaf())
        return objects.size();

    std::size_t leftNum = 0;
    if (leftChild)
        leftNum = leftChild->getSize();

    std::size_t rightNum = 0;
    if (rightChild)
        rightNum = rightChild->getSize();

    return leftNum + rightNum;
}
