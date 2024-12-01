#ifndef _BVH_H_
#define _BVH_H_

#include <vector>
#include "geometry.h"
#include "bvhNode.h"
#include "hitterInterface.h"
#include <memory>

class BVH : public HitterInterface
{
public:
    //for debug
    bool search(std::shared_ptr<Geometry> geometry) const;
    bool _search(std::shared_ptr<BVHNode> node, std::shared_ptr<Geometry> geometry) const;

public:
    virtual void init(const std::vector<std::shared_ptr<Geometry>> &objects, std::shared_ptr<const Light> light) override;
    virtual bool hitGeometryObjectOnly(const Ray &ray, HitRecord &record) const override;
    
public:
    virtual Color getColorFromLight(const Ray &ray) const override;

private:
    bool _hitGeometryObjectOnly(std::shared_ptr<BVHNode> node, const Ray &ray, HitRecord &record) const;

    void build();

    std::shared_ptr<BVHNode> generateTree(const std::vector<std::shared_ptr<Geometry>> &objects, int depth);
    void printNode(std::shared_ptr<BVHNode> node, const std::string &prefix);

    bool hitLeaf(const Ray &ray, const std::vector<std::shared_ptr<Geometry> > objects, HitRecord &record) const;

    BoundBox getBoundBox(const std::vector<std::shared_ptr<Geometry>> &objects) const;
    BoundBox getCentroidBox(const std::vector<std::shared_ptr<Geometry>> &objects) const;

    void splitObjects(const std::vector<std::shared_ptr<Geometry>> &objects,
                      const BoundBox &leftBox,
                      const BoundBox &rightBox,
                      std::vector<std::shared_ptr<Geometry>> &outLeftObjects, 
                      std::vector<std::shared_ptr<Geometry>> &outRightObjects) const;

    class Bucket
    {
    public:
        Bucket() : num(0){};

        int num;
        BoundBox originBoundBox;
        BoundBox updatedBoundBox;
    };

    void calcBestSplit(const std::vector<std::shared_ptr<Geometry>> &objects, BoundBox &outLeftBox, BoundBox &outRightBox) const;

private:
    std::shared_ptr<BVHNode> m_rootNode;
    inline const static int DEPTH = 18;
};

#endif