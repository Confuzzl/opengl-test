#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
<<<<<<< HEAD
#include <glad/glad.h>
=======
#include <glad/glad.h>
#include <stdexcept>
struct FailedShaderCompilationException : public std::runtime_error {
  FailedShaderCompilationException(const char *message);
};
struct FailedTextureLoadException : public std::runtime_error {
  FailedTextureLoadException(const char *message);
};
struct FailedWindowCreationException : public std::runtime_error {
  FailedWindowCreationException(const char *message);
};
struct UnallocatedGLObjectUsageException : public std::runtime_error {
  UnallocatedGLObjectUsageException(const char *message);
};
struct InvalidFaceTextureListException : public std::runtime_error {
  InvalidFaceTextureListException(const char *message);
};
>>>>>>> 62d31c1e128095c58d893cd591ff692249d10ad0
