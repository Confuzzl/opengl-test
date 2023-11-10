module world.scene;

import app.app;
import util.debug;
import world.factory.factories;
import world.game_object;
import util.polyhedron;
import util.debug;

Scene::Scene() { std::cout << "scene constructing\n"; }

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

    auto &go1{GameObject::from(SIMPLEX_FACTORY, coordinates1)};

    auto &go2{GameObject::from(PRISM_FACTORY, coordinates2)};
    go2.translate({0, -2, 0});
  } catch (const std::runtime_error &e) {
    app.catchException(e);
  }
}