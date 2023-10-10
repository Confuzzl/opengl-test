#include "renderable.h"

Renderable::Renderable(const Vec3List &coordinates,
                       const FaceVertexList &faceVertexIndices,
                       const FaceUVList &faceTextureList)
    : BasePolyhedron(coordinates), faceVertexIndices{faceVertexIndices},
      faceTextureList{faceTextureList} {}

void Renderable::initializeVertexInfo() {}