#include "brain_mesh.h"
#include <iostream>
#include <iomanip>

int main() {
    std::cout << std::setprecision(14) << std::endl;

    BrainMesh<double, long> brain("brain");
    brain.readData("Cort_lobe_poly.vtk");

    double totalArea = brain.getTotalArea();
    brain.computeVertexAreas();
    brain.saveVertexAreas("vertex_areas.txt");

    brain.computeEdgeLengths();
    brain.saveEdgeLengths("edge_lengths.txt");

    std::cout << "Total brain area: " << totalArea << std::endl;

    double sumVertexAreas = 0;
    for (auto area : brain.getVertexAreas()) {
        sumVertexAreas += area;
    }
    std::cout << "Sum of vertex areas: " << sumVertexAreas << std::endl;

    return 0;
}
