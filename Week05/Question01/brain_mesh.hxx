#include "brain_mesh.h"

// Constructor: Initializes mesh properties and sets initial values
BM_TEMPLATE
BM_CLASS::BrainMesh(const std::string& name) : totalArea(0), nbVertices(0), nbTriangles(0), name(name) {}

// Copy constructor: Copies mesh data from another instance
BM_TEMPLATE
BM_CLASS::BrainMesh(const BrainMesh& other)
    : vertices(other.vertices), triangles(other.triangles),
      triangleAreas(other.triangleAreas), vertexAreas(other.vertexAreas),
      edgeLengths(other.edgeLengths), totalArea(other.totalArea),
      nbVertices(other.nbVertices), nbTriangles(other.nbTriangles),
      name(other.name) {}

// Assignment operator: Assigns data from another instance to this one
BM_TEMPLATE
BM_CLASS& BM_CLASS::operator=(const BrainMesh& other) {
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

// Reads data from a VTK file and populates vertices and triangles
BM_TEMPLATE
void BM_CLASS::readData(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        // If file can't be opened, throw an exception
        throw std::runtime_error("Error: Cannot open file " + fileName);
    }

    std::string line;
    try {
        // Skip the header lines (assume fixed number for VTK format)
        for (int i = 0; i < 5; ++i) {
            std::getline(file, line);
        }

        // Read vertices until the "POLYGONS" section
        while (std::getline(file, line) && line.find("POLYGONS") == std::string::npos) {
            std::istringstream iss(line);
            T x, y, z;
            if (!(iss >> x >> y >> z)) {
                throw std::runtime_error("Error: Invalid vertex data format in file " + fileName);
            }
            vertices.push_back({x, y, z});
        }

        // Read triangles based on vertex indices
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            INT ignore, v1, v2, v3;
            if (!(iss >> ignore >> v1 >> v2 >> v3)) {
                throw std::runtime_error("Error: Invalid triangle data format in file " + fileName);
            }
            triangles.push_back({v1, v2, v3});
        }
    } catch (const std::exception& e) {
        // Close the file and rethrow the exception for error handling
        file.close();
        throw;
    }

    file.close();
    nbVertices = vertices.size();
    nbTriangles = triangles.size();
}

// Computes the area of a triangle using its vertices
BM_TEMPLATE
T BM_CLASS::getTriangleArea(const Triangle<INT>& triangle, std::array<T, 3>& r12, std::array<T, 3>& r13, std::array<T, 3>& cross) {
    auto& p1 = vertices[triangle[0]];
    auto& p2 = vertices[triangle[1]];
    auto& p3 = vertices[triangle[2]];

    // Calculate vectors for the cross product
    for (int i = 0; i < 3; ++i) {
        r12[i] = p2[i] - p1[i];
        r13[i] = p3[i] - p1[i];
    }

    // Calculate the cross product
    cross[0] = r12[1] * r13[2] - r12[2] * r13[1];
    cross[1] = r12[2] * r13[0] - r12[0] * r13[2];
    cross[2] = r12[0] * r13[1] - r12[1] * r13[0];

    // Calculate and return the triangle area
    T area = 0.5 * std::sqrt(cross[0] * cross[0] + cross[1] * cross[1] + cross[2] * cross[2]);
    return area;
}

// Computes the total surface area of the mesh
BM_TEMPLATE
T BM_CLASS::getTotalArea() {
    totalArea = 0;
    std::array<T, 3> r12, r13, cross;
    for (const auto& triangle : triangles) {
        totalArea += getTriangleArea(triangle, r12, r13, cross);
    }
    return totalArea;
}

// Computes the area associated with each vertex based on surrounding triangles
BM_TEMPLATE
void BM_CLASS::computeVertexAreas() {
    vertexAreas.resize(vertices.size(), 0);
    std::array<T, 3> r12, r13, cross;
    for (const auto& triangle : triangles) {
        T area = getTriangleArea(triangle, r12, r13, cross);
        for (int i = 0; i < 3; ++i) {
            vertexAreas[triangle[i]] += area / 3.0;
        }
    }
}

// Returns the computed vertex areas
BM_TEMPLATE
std::vector<T> BM_CLASS::getVertexAreas() {
    return vertexAreas;
}

// Saves vertex areas to a file
BM_TEMPLATE
void BM_CLASS::saveVertexAreas(const std::string& fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Cannot open file " + fileName);
    }

    for (const auto& area : vertexAreas) {
        file << area << "\n";
    }
    file.close();
}

// Computes the lengths of all edges in the mesh
BM_TEMPLATE
void BM_CLASS::computeEdgeLengths() {
    edgeLengths.clear();
    for (const auto& triangle : triangles) {
        auto& p1 = vertices[triangle[0]];
        auto& p2 = vertices[triangle[1]];
        auto& p3 = vertices[triangle[2]];

        // Calculate lengths for each of the three edges
        T length1 = std::sqrt(std::pow(p2[0] - p1[0], 2) + std::pow(p2[1] - p1[1], 2) + std::pow(p2[2] - p1[2], 2));
        T length2 = std::sqrt(std::pow(p3[0] - p2[0], 2) + std::pow(p3[1] - p2[1], 2) + std::pow(p3[2] - p2[2], 2));
        T length3 = std::sqrt(std::pow(p1[0] - p3[0], 2) + std::pow(p1[1] - p3[1], 2) + std::pow(p1[2] - p3[2], 2));

        // Store the calculated edge lengths
        edgeLengths.push_back(length1);
        edgeLengths.push_back(length2);
        edgeLengths.push_back(length3);
    }
}

// Saves edge lengths to a file
BM_TEMPLATE
void BM_CLASS::saveEdgeLengths(const std::string& fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Cannot open file " + fileName);
    }

    for (const auto& length : edgeLengths) {
        file << length << "\n";
    }
    file.close();
}
