// #define STB_IMAGE_IMPLEMENTATION
#include "app.h"
#include "util/debug_utils.h"
#include "wrapper/program/vertex_formats.h"
#include <numeric>

const Mat4 App::UI_MAT{glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT)};

App::App()
    : loopCycle{0}, updateCycle{120}, frameCycle{60}, defaultProgram{},
      fontProgram{}, atlas{"atlas"} {
  std::cout << "app constructing\n";
  glfwInit();
  frameCycle.setRate(std::min(
      frameCycle.rate,
      (unsigned short)glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate));

  createWindow();

  defaultProgram.create();
  fontProgram.create();

  try {
    atlas.initTexture();
    consolas.initAtlas();
  } catch (const TexObject::FailedTextureLoadException &e) {
    catchException(e);
  }

  std::cout << "app finished constructing\n";
}
App::~App() {
  glfwDestroyWindow(window);
  glfwTerminate();
  std::cout << "app terminated\n";
}

static void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
  if (!app.cursorSnap) {
    app.prevX = xpos;
    app.prevY = ypos;
    app.cursorSnap = true;
  }
  const float dx = (float)(app.prevX - xpos);
  const float dy = (float)(app.prevY - ypos);
  app.prevX = xpos;
  app.prevY = ypos;

  const float magnitude =
      (float)(app.updateCycle.delta * app.scene.camera.sensitivity);
  app.scene.camera.rotate(dx * magnitude, dy * magnitude);
}
static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                        int mods) {}

void App::createWindow() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_SAMPLES, 4);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Test", NULL, NULL);

  if (window == NULL) {
    glfwTerminate();
    throw FailedWindowCreationException{"WINDOW FAILED TO BE CREATED"};
  }
  glfwMakeContextCurrent(window);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetKeyCallback(window, keyCallback);

  gladLoadGL();
  glViewport(0, 0, WIDTH, HEIGHT);
}

void App::catchException(const std::runtime_error &e) {
  std::cout << e.what();
  glfwSetWindowShouldClose(app.window, GL_TRUE);
}

void App::processInput() {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE))
    glfwSetWindowShouldClose(window, GL_TRUE);

  {
    scene.camera.velocity = {};
    const float magnitude = (float)(app.updateCycle.delta * scene.camera.speed);
    if (glfwGetKey(window, GLFW_KEY_W))
      scene.camera.velocity += scene.camera.forward * magnitude;
    if (glfwGetKey(window, GLFW_KEY_A))
      scene.camera.velocity += scene.camera.right * -magnitude;
    if (glfwGetKey(window, GLFW_KEY_S))
      scene.camera.velocity += scene.camera.forward * -magnitude;
    if (glfwGetKey(window, GLFW_KEY_D))
      scene.camera.velocity += scene.camera.right * magnitude;
    if (glfwGetKey(window, GLFW_KEY_SPACE))
      scene.camera.velocity += Y_PLUS * magnitude;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
      scene.camera.velocity += Y_PLUS * -magnitude;
  }

  {
    const float magnitude =
        (float)(app.updateCycle.delta * scene.camera.sensitivity);
    if (glfwGetKey(window, GLFW_KEY_UP))
      scene.camera.rotate(0, magnitude);
    if (glfwGetKey(window, GLFW_KEY_LEFT))
      scene.camera.rotate(magnitude, 0);
    if (glfwGetKey(window, GLFW_KEY_DOWN))
      scene.camera.rotate(0, -magnitude);
    if (glfwGetKey(window, GLFW_KEY_RIGHT))
      scene.camera.rotate(-magnitude, 0);
  }

  scene.camera.update();
}

void App::drawScene() {
  defaultProgram.useProgram();
  defaultProgram.setMat4("projection", scene.camera.projection);
  for (auto obj : scene.objects) {
    defaultProgram.setMat4("model", obj->getTransform());
    defaultProgram.setMat4("view", scene.camera.view);

    obj->writeToVBO();

    atlas.bindTextureUnit();
    defaultProgram.vao.bindVertexArray();
    glDrawElements(GL_TRIANGLES, (GLsizei)defaultProgram.vao.boundedEBO.size,
                   GL_UNSIGNED_INT, 0);
  }
}
void App::drawTextBottomLeft(const float x, const float y, const float scale,
                             const std::string msg) {
  const size_t vertexCount = 6 * msg.size();

  std::vector<GLuint> indices{};
  indices.resize(vertexCount);
  std::iota(indices.begin(), indices.end(), 0);

  EBO ebo{};
  ebo.allocateBufferObject(vertexCount * sizeof(GLuint));
  glNamedBufferSubData(ebo.ID, 0, ebo.size, indices.data());

  std::vector<FontVertex> vertices{};
  vertices.reserve(vertexCount);
  float xOffset = x;
  const float width = FontProgram::CHAR_WIDTH * scale,
              height = FontProgram::CHAR_HEIGHT * scale;
  for (const char &c : msg) {
    TexTile tex = consolas.getTile(c);
    for (int tri = 0; tri < 2; tri++) {
      for (int vertex = 0; vertex < 3; vertex++) {
        const Vec2 pos{xOffset + width * quadUV[tri][vertex][0],
                       y + height * quadUV[tri][vertex][1]};
        const glm::lowp_u16vec2 uv{tex.coordinates +
                                   tex.dimensions * quadUV[tri][vertex]};
        vertices.push_back({{pos[0], pos[1]}, {uv[0], uv[1]}});
        // vertices.emplace_back(pos[0], pos[1], uv[0], uv[1]);
      }
    }

    xOffset += width * 1;
  }

  VBO vbo{};
  vbo.allocateBufferObject(vertexCount * FontVertex::WIDTH);
  GLintptr offset = 0;
  for (const FontVertex &vertex : vertices) {
    glNamedBufferSubData(vbo.ID, offset, FontVertex::POS_WIDTH, vertex.posInfo);
    offset += FontVertex::POS_WIDTH;
    glNamedBufferSubData(vbo.ID, offset, FontVertex::TEX_WIDTH, vertex.texInfo);
    offset += FontVertex::TEX_WIDTH;
  }

  fontProgram.vao.bindEBO(ebo);
  fontProgram.vao.bindVBO(vbo);

  fontProgram.useProgram();
  fontProgram.setMat4("projection", UI_MAT);

  consolas.atlas.bindTextureUnit();
  fontProgram.vao.bindVertexArray();
  glDrawElements(GL_TRIANGLES, (GLsizei)fontProgram.vao.boundedEBO.size,
                 GL_UNSIGNED_INT, 0);
}
void App::drawTextTopLeft(const float x, const float y, const float scale,
                          const std::string msg) {
  drawTextBottomLeft(x, App::HEIGHT - FontProgram::CHAR_HEIGHT - y, scale, msg);
}

App app{};