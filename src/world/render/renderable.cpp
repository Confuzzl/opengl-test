#include "renderable.h"
#include "util/debug_utils.h"

Renderable::Renderable(const Vec3List &coordinates,
                       const FaceVertexList &faceVertexIndices,
                       const UVListFactory::UVList &faceTextureList)
    : BasePolyhedron(coordinates), faceVertexIndices{faceVertexIndices},
      faceTextureList{faceTextureList} {
  if (faceVertexIndices.size() != faceTextureList.size())
    throw FaceUVMismatchException{
        std::format("UV LIST SIZE DOES NOT MATCH FACE COUNT ({} != {})\n",
                    faceVertexIndices.size(), faceTextureList.size())};
}

void Renderable::initializeVertexInfo() {}