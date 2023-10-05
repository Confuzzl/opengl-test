#pragma once
#include "face_uv_list.h"
#include "world/base_polyhedron.h"
#include "wrapper/program/vertex_formats.h"
#include <memory>
#include <vector>

class Renderable : public BasePolyhedron {
  typedef std::vector<std::vector<unsigned char>> FaceVertexIndexList;
  const FaceVertexIndexList faceVertexIndices;
  FaceUVList faceTextureList;
  std::vector<DefaultVertex> vertexInfo;

  Renderable(const Vec3List &coordinates,
             const FaceVertexIndexList &faceVertexIndices);

  void initializeVertexInfo();
};