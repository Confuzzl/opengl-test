#pragma once
#include "uv_list_factory.h"
#include "world/base_polyhedron.h"
#include "wrapper/program/vertex_formats.h"
#include <stdexcept>

class Renderable : public BasePolyhedron {
  struct FaceUVMismatchException : std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  const FaceVertexList &faceVertexIndices;
  UVListFactory::UVList faceTextureList;
  Vector<DefaultVertex> vertexInfo;

  void initializeVertexInfo();

public:
  Renderable(const Vec3List &coordinates,
             const FaceVertexList &faceVertexIndices,
             const UVListFactory::UVList &faceTextureList);
};