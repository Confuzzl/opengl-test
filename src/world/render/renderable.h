#pragma once
#include "face_uv_list.h"
#include "world/base_polyhedron.h"
#include "wrapper/program/vertex_formats.h"

class Renderable : public BasePolyhedron {
  using FaceVertexIndexList = Vector2D<unsigned char>;

  const FaceVertexIndexList faceVertexIndices;
  FaceUVList faceTextureList;
  Vector<DefaultVertex> vertexInfo;

  Renderable(const Vec3List &coordinates,
             const FaceVertexIndexList &faceVertexIndices);

  void initializeVertexInfo();
};