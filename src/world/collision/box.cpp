#include "box.h"

Box::Box(const std::vector<vec3> &coordinates) : Polyhedron(coordinates) {}
consteval unsigned short Box::triCount() { return 12; }