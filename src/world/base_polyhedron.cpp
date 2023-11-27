module world.base_polyhedron;

BasePolyhedron::BasePolyhedron(const Vec3List &coordinates)
    : coordinates{coordinates} {}

Vec3 BasePolyhedron::getSampleVertex() const { return coordinates[0]; }