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

where `r12` and `r13` are vectors formed from the triangle vertices. This approach ensures accurate computation, and the program supports both single and double precision.

## 3. Calculating Vertex Areas
The function `computeVertexAreas()` calculates the area associated with each vertex as one-third of the areas of the triangles sharing that vertex. The vertex areas are stored and later saved using `saveVertexAreas(const std::string& fileName)`. The sum of all vertex areas matches the total surface area, confirming the correctness of the implementation.

## 4. Calculating and Visualizing Edge Lengths
The program calculates edge lengths using `computeEdgeLengths()`. For each triangle, it computes the lengths of its three edges using the Euclidean distance formula. The computed edge lengths are then saved using `saveEdgeLengths(const std::string& fileName)`. The histograms for edge lengths and vertex areas are generated using Python and are saved as images.

### Statistical Analysis
The mean and standard deviation of the edge lengths are computed:


## 5. Running the Program
To run the program, follow these steps:

1. Open the terminal and navigate to the project directory.
2. Compile the program using the Makefile:
    ```bash
    make
    ```
3. Run the executable:
    ```bash
    ./brain_mesh
    ```
4. The program outputs the total area and saves the vertex areas and edge lengths to `vertex_areas.txt` and `edge_lengths.txt` respectively.
5. To visualize the histograms, run the Python script:
    ```bash
    python plot.py
    ```

## 6. Verification and Testing Strategy
The program verifies the correctness by comparing the total area computed from the triangles with the sum of vertex areas. Additionally, visual inspection of the histograms confirms the expected distributions based on the mesh data.

## 7. Code Documentation
Each function in the codebase is documented to explain its purpose and functionality. Inline comments provide further clarity on the calculations and logic used.

## Conclusion
The program successfully computes and validates the brain mesh’s total surface area, vertex areas, and edge lengths. The visualizations and statistical analyses offer comprehensive insights into the mesh structure, ensuring that all criteria for the assignment are met.

Mean Edge Length = 0.8998 Standard Deviation = 0.2425

Plots
![vertex_areas_histogram](https://github.com/user-attachments/assets/f5254105-ff3c-4385-80f7-7bdc1a61b288)
![edge_lengths_histogram](https://github.com/user-attachments/assets/0c714a41-1df8-4d0d-8b2e-929bc338571e)
