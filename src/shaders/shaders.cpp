// module;
//
// #include "util/gl_utils.hpp"
// #include <fstream>
// #include <numeric>
//
module shaders;
//
// import app.app;
// import util.glm;
// import util.debug;
//
// Shaders::ShaderProgram::~ShaderProgram() {
//   glDeleteProgram(ID);
//   std::cout << "shader program deleted\n";
// }
//
// void Shaders::ShaderProgram::useProgram() {
//   if (not allocated)
//     throw UnallocatedGLObjectUsageException{
//         std::format("PROGRAM {} WAS BOUND BEFORE INITIALIZATION\n", ID)};
//   glUseProgram(ID);
// }
//
// void Shaders::ShaderProgram::setVec3(const char *name, const Vec3 vec) const
// {
//   glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(vec));
// }
// void Shaders::ShaderProgram::setMat4(const char *name,
//                                      const Mat4 matrix) const {
//   glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE,
//                      glm::value_ptr(matrix));
// }
//
// void Shaders::ShaderProgram::create() {
//   ID = glCreateProgram();
//   createShaders(vertexSource, fragmentSource);
//   defineVAO();
// }
//
// void Shaders::ShaderProgram::defineVAO() {}
//
// static std::string sourceToString(const std::string &name) {
//   std::ifstream in{name};
//   return {std::istreambuf_iterator<char>(in),
//   std::istreambuf_iterator<char>()};
// }
// void Shaders::ShaderProgram::createShaders(const std::string &vertex,
//                                            const std::string &fragment) {
//   GLuint vertexID = 0, fragmentID = 0;
//   try {
//     createShader(GL_VERTEX_SHADER, vertexID,
//                  std::format("assets/shader/{}.vert", vertex));
//     createShader(GL_FRAGMENT_SHADER, fragmentID,
//                  std::format("assets/shader/{}.frag", fragment));
//   } catch (const FailedShaderCompilationException &e) {
//     mainApp.catchException(e);
//   }
//   glAttachShader(ID, vertexID);
//   glAttachShader(ID, fragmentID);
//   glLinkProgram(ID);
//   glDeleteShader(vertexID);
//   glDeleteShader(fragmentID);
//
//   markAsAllocated();
// }
//
// void Shaders::ShaderProgram::createShader(const GLenum type, GLuint &ID,
//                                           const std::string &source) {
//   std::cout << std::format("ATTEMPING TO COMPILE {}\n", source);
//   GLint success = 0;
//   ID = glCreateShader(type);
//   std::string temp = sourceToString(source);
//   const char *chars = temp.c_str();
//   glShaderSource(ID, 1, &chars, NULL);
//   glCompileShader(ID);
//   glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
//   if (not success) {
//     GLint logSize = 0;
//     glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logSize);
//     errorLog.resize(logSize);
//     glGetShaderInfoLog(ID, 512, NULL, errorLog.data());
//     throw FailedShaderCompilationException{
//         std::format("{} FAILED TO COMPILE\n{}\n", source, errorLog)};
//   }
// }
