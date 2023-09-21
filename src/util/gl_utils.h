#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
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