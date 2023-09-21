#include "feature.h"

template <IsPolyhedron T>
Feature<T>::Feature(T &parent, unsigned short ID) : parent{parent}, ID{ID} {};