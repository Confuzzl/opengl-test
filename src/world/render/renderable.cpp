#include "renderable.h"

Renderable::Renderable(const Vec3List &coordinates,
                       const FaceVertexIndexList &faceVertexIndices)
    : BasePolyhedron(coordinates), faceVertexIndices{faceVertexIndices} {}

void Renderable::initializeVertexInfo() {}