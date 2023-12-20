// module;
//
// #include <utility>
//
// module world.game_object;
//
// import app.app;
// import world.scene;
// import util.debug;
// import world.factory.base_factory;
//
// unsigned int GameObject::COUNT = 0;
//
// GameObject::GameObject(CollPtr collider /*, RendPtr render*/)
//     : PhysicsObject(10), collider{std::move(collider)},
//       /*render{std::move(render)},*/ ID{COUNT++} {
//   std::cout << std::format("gameobject {} created\n", ID);
// }
// GameObject::~GameObject() {
//   std::cout << std::format("gameobject {} destroyed\n", ID);
// }
//
// Collider &GameObject::getCollider() { return *collider; }
// const Collider &GameObject::getCollider() const { return *collider; }
//// Renderable &GameObject::getRenderable() { return *render; }
// const Renderable &GameObject::getRenderable() const { return *render; }
//
// GameObject &GameObject::from(const BaseFactory &factory,
//                              const Vec3List &coordinates) {
//   return from(factory.createCollidable(coordinates),
//               factory.createRenderable(coordinates));
// }
//
//// GameObject &GameObject::from(CollPtr collider, RendPtr render) {
////   GObjPtr ptr{std::make_unique<GameObject>(std::forward<CollPtr>(collider),
////                                            std::forward<RendPtr>(render))};
////   unsigned int ID = ptr->ID;
////   mainScene.objectMap.emplace(std::make_pair(ID, std::move(ptr)));
////   return *mainScene.objectMap.at(ID);
//// }
//
//// GameObject &GameObject::copy(GameObject &object) {
////   const CollPtr &c{object.collider};
////   const RendPtr &r{object.render};
////
////   return object;
//// }