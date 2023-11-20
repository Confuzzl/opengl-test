module world.base_polyhedron;

BasePolyhedron::BasePolyhedron(const Vec3List &coordinates)
    : Transformable({}), coordinates{coordinates} {}