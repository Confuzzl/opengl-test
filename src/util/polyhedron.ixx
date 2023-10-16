export module util.polyhedron;

export import util.glm;
export import util.vector;
export import util.memory;

export using Vec3List = Vector<Vec3>;

export template <typename T> using SPtrVector = Vector<SPtr<T>>;

export using VertexNeighborList = Vector2D<unsigned char>;
export using EdgeNeighborList = Vector<glm::u8vec2>;
export using FaceNeighborList = Vector2D<unsigned char>;

export using FaceVertexList = Vector2D<unsigned char>;