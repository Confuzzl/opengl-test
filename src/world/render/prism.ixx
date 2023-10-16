export module world.collision.prism;

import <string>;
import world.transformable;
import wrapper.buffer_object;
import wrapper.program.vertex_formats;
import util.glm;

export class Prism : public Transformable {
public:
  static bool buffersInitialized;
  static EBO ebo;
  static VBO sharedVBO;

  SimpleVertex vertexInfo[6 * 2 * 3]{};

  Prism(const float width, const float height, const float depth);
  ~Prism();

  void writeToVBO();
  void printVertices();
  void printVertex(const int index);

private:
  enum Direction { Z_PLUS, X_PLUS, Z_MINUS, X_MINUS, Y_PLUS, Y_MINUS };

  static unsigned int COUNT;
  const unsigned int ID;

  static const GLuint indices[36];
  static const Vec3 maps[6][2][3];

  Vec3 halfsize;

  static void initializeBuffers();
  static void initializeEBO();
  static void allocateVBO();

  void setFace(const Direction direction, std::string texture);
  void setTri(const Direction direction, const int tri, std::string texture);
  void setVertexInfo(const Direction direction, const int tri, const int vertex,
                     std::string texture);
};