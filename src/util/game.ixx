export module util.game;

import util.memory;

class Renderable;
class Collider;
class GameObject;

export using RendPtr = UPtr<Renderable>;
export using CollPtr = UPtr<Collider>;
export using GObjPtr = UPtr<GameObject>;