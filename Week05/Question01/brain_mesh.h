#ifndef BRAIN_MESH_H
#define BRAIN_MESH_H

#include "brain_mesh_macros.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <stdexcept> // For throwing exceptions

// Template class for handling brain mesh data
BM_TEMPLATE
class BrainMesh {
private:
    Vertices<T> vertices; // Stores vertices as 3D points
    Triangles<INT> triangles; // Stores triangles as sets of vertex indices
    std::vector<T> triangleAreas; // Stores areas of each triangle
    std::vector<T> vertexAreas; // Stores areas associated with each vertex
    std::vector<T> edgeLengths; // Stores lengths of all edges in the mesh
    T totalArea; // Stores the total surface area of the mesh
    int nbVertices; // Number of vertices in the mesh
    int nbTriangles; // Number of triangles in the mesh
    std::string name; // Name identifier for the mesh

public:
    // Constructor: Initializes the mesh with a name and sets default values
    BrainMesh(const std::string& name);

    // Copy constructor: Allows deep copying of mesh data
    BrainMesh(const BrainMesh& other);

    // Assignment operator: Assigns data from another instance to this one
    BrainMesh& operator=(const BrainMesh& other);

    // Destructor (no dynamic memory allocation here, so it's empty)
    ~BrainMesh() {}

    // Reads vertex and triangle data from a VTK file
    void readData(const std::string& fileName);

    // Computes the area of a given triangle
    T getTriangleArea(const Triangle<INT>& triangle, std::array<T, 3>& r12, std::array<T, 3>& r13, std::array<T, 3>& cross);

    // Calculates the total surface area of the mesh
    T getTotalArea();

    // Computes the area associated with each vertex based on surrounding triangles
    void computeVertexAreas();

    // Returns a vector containing the vertex areas
    std::vector<T> getVertexAreas();

    // Saves the computed vertex areas to a file
    void saveVertexAreas(const std::string& fileName);

    // Computes the lengths of all edges in the mesh
    void computeEdgeLengths();

    // Saves the computed edge lengths to a file
    void saveEdgeLengths(const std::string& fileName);
};

// Include the implementation of the BrainMesh class
#include "brain_mesh.hxx"

#endif // BRAIN_MESH_H
