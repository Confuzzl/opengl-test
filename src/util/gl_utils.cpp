<<<<<<< HEAD
#include "gl_utils.h"
=======
#include "gl_utils.h"
FailedShaderCompilationException::FailedShaderCompilationException(
    const char *message)
    : std::runtime_error(message) {}
FailedTextureLoadException::FailedTextureLoadException(const char *message)
    : std::runtime_error(message) {}
FailedWindowCreationException::FailedWindowCreationException(
    const char *message)
    : std::runtime_error(message) {}
UnallocatedGLObjectUsageException::UnallocatedGLObjectUsageException(
    const char *message)
    : std::runtime_error(message) {}
InvalidFaceTextureListException::InvalidFaceTextureListException(
    const char *message)
    : std::runtime_error(message) {}
>>>>>>> 62d31c1e128095c58d893cd591ff692249d10ad0
