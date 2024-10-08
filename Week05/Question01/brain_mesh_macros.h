#ifndef BRAIN_MESH_MACROS_H
#define BRAIN_MESH_MACROS_H

#define BM_TEMPLATE template <typename T, typename INT>
#define BM_CLASS BrainMesh<T, INT>

#include <vector>
#include <array>

// Type aliases for vertices and triangles
template <typename INT>
using Triangle = std::array<INT, 3>;

template <typename INT>
using Triangles = std::vector<Triangle<INT>>;

template <typename T>
using Vertex = std::array<T, 3>;

template <typename T>
using Vertices = std::vector<Vertex<T>>;

#endif // BRAIN_MESH_MACROS_H
