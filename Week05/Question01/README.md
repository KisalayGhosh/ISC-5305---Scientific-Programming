# Brain Mesh Structure Analysis

## Introduction
This project analyzes a brain mesh structure using the dataset provided in `Cort_lobe_poly.vtk`. The goal is to compute the total surface area of the brain mesh, calculate areas associated with each vertex, determine the lengths of all edges, and visualize the results through histograms. The implementation leverages C++ for computation and Python (with `matplotlib`) for visualization.

## 1. Reading Data from the File
The function `readData(const std::string& fileName)` reads vertex and triangle data from the file. The file format specifies:
- **Vertices**: Lines 6 through 191729 contain coordinates (x, y, z) for each vertex.
- **Triangles**: Lines 191731 through 574971 contain triangle information, each defined by three vertex indices.

The program parses this data and stores it in appropriate containers:
- **Vertices**: Stored as 3D points in a vector of `std::array<T, 3>`.
- **Triangles**: Stored as sets of indices in a vector of `std::array<INT, 3>`.

## 2. Calculating the Total Surface Area
The function `getTotalArea()` calculates the total surface area of the mesh by summing the areas of all triangles. Each triangle's area is computed using the cross product of vectors formed by its vertices:
