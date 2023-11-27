module world.transform.translatable;

Vec3 Translatable::getPosition() const { return transform[3]; }

void Translatable::setPosition(const Vec3 &v) { transform[3] = {v, 1}; }
void Translatable::translate(const Vec3 &v) { transform[3] += Vec4{v, 0}; }