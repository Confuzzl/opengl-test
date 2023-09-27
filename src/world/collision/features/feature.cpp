#include "feature.h"

template <typename T>
Feature<T>::Feature(T &parent, unsigned short ID) : parent{parent}, ID{ID} {};