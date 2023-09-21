#pragma once
#include "texture_tile.h"
#include "transformable.h"
#include "wrapper/buffer_objects.h"
#include "wrapper/program/vertex_formats.h"

class Prism : public Transformable {
public:
  static bool buffersInitialized;
  static EBO ebo;
  static VBO sharedVBO;

  const unsigned int ID;

  DefaultVertex vertexInfo[6 * 2 * 3]{};

  Prism(const float width, const float height, const float depth);
  ~Prism();

  void writeToVBO();
  void printVertices();
  void printVertex(const int index);

private:
  enum Direction { Z_PLUS, X_PLUS, Z_MINUS, X_MINUS, Y_PLUS, Y_MINUS };

  static unsigned int COUNT;

  static const GLuint indices[36];
  static const vec3 maps[6][2][3];

  vec3 halfsize;

  static void initializeBuffers();
  static void initializeEBO();
  static void allocateVBO();

  void setFace(const Direction direction);
  void setTri(const Direction direction, const int tri);
  void setVertexInfo(const Direction direction, const int tri,
                     const int vertex);
};