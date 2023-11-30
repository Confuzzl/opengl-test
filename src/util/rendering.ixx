export module util.rendering;

import util.glm;
import util.vector;

export namespace render {
export template <typename T> using RenTri = Array<T, 3>;
export template <typename T> using RenFace = Vector<RenTri<T>>;

export using IndexList = Vector<RenFace<unsigned short>>;
export using ColList = Vector<RenFace<glm::u8vec3>>;
export using TexList = Vector<RenFace<Vec2>>;

} // namespace render