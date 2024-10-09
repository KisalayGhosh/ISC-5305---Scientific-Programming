#ifndef BRAIN_MESH_MACROS_H
#define BRAIN_MESH_MACROS_H

// Macro for template declaration to shorten repeated code
#define BM_TEMPLATE template <typename T, typename INT>
// Macro for referring to the class with template parameters
#define BM_CLASS BrainMesh<T, INT>

#include <vector>
#include <array>

// Type alias for a triangle using three vertex indices
template <typename INT>
using Triangle = std::array<INT, 3>;

// Type alias for a collection of triangles
template <typename INT>
using Triangles = std::vector<Triangle<INT>>;

// Type alias for a vertex as a 3D point (x, y, z)
template <typename T>
using Vertex = std::array<T, 3>;

// Type alias for a collection of vertices
template <typename T>
using Vertices = std::vector<Vertex<T>>;

#endif // BRAIN_MESH_MACROS_H
