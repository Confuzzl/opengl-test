#include "box.h"

Box::Box(const Vec3List &coordinates) : Polyhedron(coordinates) {}

consteval unsigned short Box::triCount() { return 12; }