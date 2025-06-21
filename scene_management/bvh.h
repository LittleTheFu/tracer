#ifndef _BVH_H_
#define _BVH_H_

#include <memory>
#include <vector>

#include "bvhNode.h"
#include "geometry.h"
#include "hitterInterface.h"
#include "interaction.h"

class BVH : public HitterInterface
{
public:
    //for debug
    bool search(std::shared_ptr<Geometry> geometry) const;
    bool _search(std::shared_ptr<BVHNode> node, std::shared_ptr<Geometry> geometry) const;

public:
    virtual void init(std::vector<std::shared_ptr<AreaLight>> lights,
                       const std::vector<std::shared_ptr<Primitive>> &primitives,
                       std::shared_ptr<SphereVolume> volume) override;
    virtual bool hitGeometryObjectOnly(const Ray &ray, Interaction &interaction, std::shared_ptr<Primitive> skipPrimitive = nullptr) const override;

    
public:
    virtual Color getColorFromLight(const Ray &ray, int index) const override;

private:
    bool _hitGeometryObjectOnly(std::shared_ptr<BVHNode> node,
                                const Ray &ray,
                                Interaction &interaction,
                                std::shared_ptr<Primitive> skipPrimitive = nullptr) const;


    void build();

    std::shared_ptr<BVHNode> generateTree(const std::vector<std::shared_ptr<Primitive>> &primitives,
                                          int depth);
    void printNode(std::shared_ptr<BVHNode> node, const std::string &prefix);

    bool hitLeaf(const Ray &ray,
                 const std::vector<std::shared_ptr<Primitive>> primitives,
                 Interaction &interaction,
                 std::shared_ptr<Primitive> skipPrimitive = nullptr) const;


    BoundBox getBoundBox(const std::vector<std::shared_ptr<Primitive>> &primitives) const;
    BoundBox getCentroidBox(const std::vector<std::shared_ptr<Primitive>> &primitives) const;

    void splitObjects(const std::vector<std::shared_ptr<Primitive>> &primitives,
                      const BoundBox &leftBox,
                      const BoundBox &rightBox,
                      std::vector<std::shared_ptr<Primitive>> &outLeftPrimitives, 
                      std::vector<std::shared_ptr<Primitive>> &outRightPrimitives) const;

    class Bucket
    {
    public:
        Bucket() : num(0){};

        int num;
        BoundBox originBoundBox;
        BoundBox updatedBoundBox;
    };

    void calcBestSplit(const std::vector<std::shared_ptr<Primitive>> &primitives,
                       BoundBox &outLeftBox,
                       BoundBox &outRightBox) const;

private:
    std::shared_ptr<BVHNode> m_rootNode;
    inline const static int DEPTH = 18;
};

#endif