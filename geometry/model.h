#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>
#include <string>
#include "vector.h"

class Mesh;

class Model
{
public:
    Model(const std::string fileName,
          const Vector3 pos,
          float scale);

    std::vector<std::shared_ptr<Mesh>> getMeshes() const { return meshes; }

private:
    std::vector<std::shared_ptr<Mesh>> meshes;
};


#endif