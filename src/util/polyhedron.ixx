export module util.polyhedron;

import <array>;

export import util.glm;
export import util.vector;
export import util.memory;

export using Vec3List = Vector<Vec3>;

export using VEIndexList = Vector2D<unsigned char>;
export using EVIndexList = Vector<glm::u8vec2>;
export using EFIndexList = Vector<glm::u8vec2>;
export using FEIndexList = Vector2D<unsigned char>;

export template <typename T> using RenTri = Array<T, 3>;
export template <typename T> using RenFace = Vector<RenTri<T>>;
export using UVList = Vector<RenFace<Vec2>>;
export using RenCoordinateIndexList = Vector<RenFace<unsigned short>>;