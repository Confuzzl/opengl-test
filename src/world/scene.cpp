module world.scene;

import world.game_object;
import world.entity.player;
import app.app;
import util.debug;
import factory.global;
import util.polyhedron;
import util.debug;

import rendering.factory;
import rendering.vertex_formats.types;

Scene::Scene() { println("SCENE CONSTRUCTING"); }
Scene::~Scene() = default;

void Scene::start() {
  try {
    Vec3List coordinates1{
        {-1, -1, +1}, {+1, -1, -1}, {+1, +1, +1}, {-1, +1, -1}};
    for (auto &v : coordinates1)
      v /= 2;

    Vec3List coordinates2{{-1, -1, 1},  {+1, -1, +1}, {+1, +1, +1},
                          {-1, +1, +1}, {-1, +1, -1}, {+1, +1, -1},
                          {+1, -1, -1}, {-1, -1, -1}};
    for (auto &v : coordinates2)
      v /= 2;

    auto &go1 = GameObject::from<VertexFormats::_3D::Col>(Factory::SIMPLEX,
                                                          coordinates1);
    go1.translate({5, 0, 0});
  } catch (const std::runtime_error &e) {
    mainApp.catchException(e);
  }
}