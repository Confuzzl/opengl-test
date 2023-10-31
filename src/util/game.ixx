export module util.game;

import util.memory;

export class Renderable;
export class Collider;
export class GameObject;

export using RendPtr = UPtr<Renderable>;
export using CollPtr = UPtr<Collider>;
export using GObjPtr = UPtr<GameObject>;