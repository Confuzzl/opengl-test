#pragma once
#include "glm_utils.h"
#include "memory_utils.h"
#include "vector_utils.h"

using Vec3List = Vector<Vec3>;

template <typename T> using SPtrVector = Vector<SPtr<T>>;

using VertexNeighborList = Vector2D<unsigned char>;
using EdgeNeighborList = Vector<glm::u8vec2>;
using FaceNeighborList = Vector2D<unsigned char>;

using FaceVertexList = Vector2D<unsigned char>;