#include "brain_mesh.h"

BM_TEMPLATE
void BM_CLASS::readData(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << fileName << std::endl;
        return;
    }

    std::string line;
    // Skip the header lines (assume they are fixed in number for VTK format)
    for (int i = 0; i < 5; ++i) {
        std::getline(file, line);
    }

    // Read vertices
    while (std::getline(file, line) && line.find("POLYGONS") == std::string::npos) {
        std::istringstream iss(line);
        T x, y, z;
        iss >> x >> y >> z;
        vertices.push_back({x, y, z});
    }

    // Read triangles
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        INT ignore, v1, v2, v3;
        iss >> ignore >> v1 >> v2 >> v3;
        triangles.push_back({v1, v2, v3});
    }

    file.close();
    nbVertices = vertices.size();
    nbTriangles = triangles.size();
}

BM_TEMPLATE
T BM_CLASS::getTriangleArea(const Triangle<INT>& triangle, std::array<T, 3>& r12, std::array<T, 3>& r13, std::array<T, 3>& cross) {
    auto& p1 = vertices[triangle[0]];
    auto& p2 = vertices[triangle[1]];
    auto& p3 = vertices[triangle[2]];

    for (int i = 0; i < 3; ++i) {
        r12[i] = p2[i] - p1[i];
        r13[i] = p3[i] - p1[i];
    }

    cross[0] = r12[1] * r13[2] - r12[2] * r13[1];
    cross[1] = r12[2] * r13[0] - r12[0] * r13[2];
    cross[2] = r12[0] * r13[1] - r12[1] * r13[0];

    T area = 0.5 * std::sqrt(cross[0] * cross[0] + cross[1] * cross[1] + cross[2] * cross[2]);
    return area;
}

BM_TEMPLATE
T BM_CLASS::getTotalArea() {
    totalArea = 0;
    std::array<T, 3> r12, r13, cross;
    for (const auto& triangle : triangles) {
        totalArea += getTriangleArea(triangle, r12, r13, cross);
    }
    return totalArea;
}

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

BM_TEMPLATE
std::vector<T> BM_CLASS::getVertexAreas() {
    return vertexAreas;
}

BM_TEMPLATE
void BM_CLASS::saveVertexAreas(const std::string& fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << fileName << std::endl;
        return;
    }

    for (const auto& area : vertexAreas) {
        file << area << "\n";
    }
    file.close();
}

BM_TEMPLATE
void BM_CLASS::computeEdgeLengths() {
    edgeLengths.clear();
    for (const auto& triangle : triangles) {
        auto& p1 = vertices[triangle[0]];
        auto& p2 = vertices[triangle[1]];
        auto& p3 = vertices[triangle[2]];

        T length1 = std::sqrt(std::pow(p2[0] - p1[0], 2) + std::pow(p2[1] - p1[1], 2) + std::pow(p2[2] - p1[2], 2));
        T length2 = std::sqrt(std::pow(p3[0] - p2[0], 2) + std::pow(p3[1] - p2[1], 2) + std::pow(p3[2] - p2[2], 2));
        T length3 = std::sqrt(std::pow(p1[0] - p3[0], 2) + std::pow(p1[1] - p3[1], 2) + std::pow(p1[2] - p3[2], 2));

        edgeLengths.push_back(length1);
        edgeLengths.push_back(length2);
        edgeLengths.push_back(length3);
    }
}

BM_TEMPLATE
void BM_CLASS::saveEdgeLengths(const std::string& fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << fileName << std::endl;
        return;
    }

    for (const auto& length : edgeLengths) {
        file << length << "\n";
    }
    file.close();
}
