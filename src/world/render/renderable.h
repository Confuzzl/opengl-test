#pragma once
#include "face_uv_list.h"
#include "world/base_polyhedron.h"
#include "wrapper/program/vertex_formats.h"

class Renderable : public BasePolyhedron {
  const FaceVertexList &faceVertexIndices;
  FaceUVList faceTextureList;
  Vector<DefaultVertex> vertexInfo;

  Renderable(const Vec3List &coordinates,
             const FaceVertexList &faceVertexIndices,
             const FaceUVList &faceTextureList);

  void initializeVertexInfo();
};