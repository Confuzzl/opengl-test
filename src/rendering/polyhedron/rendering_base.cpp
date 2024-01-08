module;

#include "util/gl_utils.hpp"

module rendering.base;

import util.debug;

std::map<unsigned int, Renderable::Polyhedron *> Renderable::System::objects{};

unsigned int Renderable::Polyhedron::COUNT = 0;

Renderable::Polyhedron::Polyhedron(Shaders::Base &program, const EBO &ebo,
                                   const VBO &vbo, const Vec3List &coordinates)
    : BasePolyhedron(coordinates), ID{COUNT++}, program{program}, ebo{ebo},
      vbo{vbo} {
  System::objects.emplace(ID, this);
}

Renderable::Polyhedron::~Polyhedron() { System::objects.erase(ID); }