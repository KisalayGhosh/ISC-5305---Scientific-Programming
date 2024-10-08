#ifndef BRAIN_MESH_H
#define BRAIN_MESH_H

#include "brain_mesh_macros.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>

// Template class definition
BM_TEMPLATE
class BrainMesh {
private:
    Vertices<T> vertices;
    Triangles<INT> triangles;
    std::vector<T> triangleAreas;
    std::vector<T> vertexAreas;
    std::vector<T> edgeLengths;
    T totalArea;
    int nbVertices;
    int nbTriangles;
    std::string name;

public:
    // Constructor
    BrainMesh(const std::string& name) : totalArea(0), nbVertices(0), nbTriangles(0), name(name) {}

    // Copy constructor
    BrainMesh(const BrainMesh& other)
        : vertices(other.vertices), triangles(other.triangles),
          triangleAreas(other.triangleAreas), vertexAreas(other.vertexAreas),
          edgeLengths(other.edgeLengths), totalArea(other.totalArea),
          nbVertices(other.nbVertices), nbTriangles(other.nbTriangles),
          name(other.name) {}

    // Assignment operator
    BrainMesh& operator=(const BrainMesh& other) {
        if (this != &other) {
            vertices = other.vertices;
            triangles = other.triangles;
            triangleAreas = other.triangleAreas;
            vertexAreas = other.vertexAreas;
            edgeLengths = other.edgeLengths;
            totalArea = other.totalArea;
            nbVertices = other.nbVertices;
            nbTriangles = other.nbTriangles;
            name = other.name;
        }
        return *this;
    }

    // Destructor
    ~BrainMesh() {}

    void readData(const std::string& fileName);
    T getTriangleArea(const Triangle<INT>& triangle, std::array<T, 3>& r12, std::array<T, 3>& r13, std::array<T, 3>& cross);
    std::vector<T>& getTriangleAreas();
    std::vector<T>& getEdgeLengths();
    T getTotalArea();
    void computeVertexAreas();
    std::vector<T> getVertexAreas();
    void saveVertexAreas(const std::string& fileName);

    // New methods for edge lengths
    void computeEdgeLengths();
    void saveEdgeLengths(const std::string& fileName);
};

#include "brain_mesh.hxx"

#endif // BRAIN_MESH_H
