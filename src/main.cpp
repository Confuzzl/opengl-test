import app.app;
import util.glm;
import util.debug;
import <functional>;

int main() {
  mainApp.start();

  // Mat4 pos{1.0f};
  // pos[3] = {1, 2, 3, 1};
  // std::cout << std::format("POS :\n{}\n", glm::to_string(pos));
  // Mat4 rot = glm::rotate(Mat4{1.0f}, glm::radians(45.0f), {0, 1, 0});
  // std::cout << std::format("ROT :\n{}\n", glm::to_string(rot));

  // std::cout << std::format("T :\n{}\n",
  //                          glm::to_string(glm::translate(rot,
  //                          Vec3{pos[3]})));
  // std::cout << std::format("P * R :\n{}\n", glm::to_string(pos * rot));
  // std::cout << std::format("R * P :\n{}\n", glm::to_string(rot * pos));

  //   transform = pos * rot;
  //   std::cout << glm::to_string(transform) << "\n";
  //    transform = glm::translate(transform, {1, 1, 1});
  //     std::cout << glm::to_string(translateVector({1, 0, 0}, transform)) <<
  //     "\n";
  //    transform = glm::rotate(transform, glm::radians(90.0f), {0, 1, 0});
  //    std::cout << glm::to_string(Vec3{transform * Vec4{v, 0}}) << "\n";
  //    const auto r{glm::quat_cast(transform)};
  //    std::cout << glm::to_string(r * v) << "\n";
}
