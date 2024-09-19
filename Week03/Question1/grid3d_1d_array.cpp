#include "grid3d_1d_array.h"
#include <iostream>
#include <stdexcept>

// Constructor: Initialize the 3D grid using a 1D array
Grid1::Grid1(int nx_, int ny_, int nz_) : nx(nx_), ny(ny_), nz(nz_) {
    // Ensure valid grid dimensions
    if (nx <= 0 || ny <= 0 || nz <= 0) {
        throw std::invalid_argument("Grid dimensions must be positive.");
    }
    
    // Allocate memory for the 1D array
    data = new double[nx * ny * nz];
}

// Destructor: Free allocated memory for the grid
Grid1::~Grid1() {
    delete[] data;  // Clean up dynamically allocated memory
}

// Get the total number of elements in the grid
int Grid1::getSize() const {
    return nx * ny * nz;  // Return product of dimensions
}

// Get the memory used by the grid in bytes
int Grid1::getMemory() const {
    return nx * ny * nz * sizeof(double);  // Calculate memory size
}

// Access the value at the grid location (i, j, k)
double Grid1::operator()(int i, int j, int k) const {
    if (i < 0 || j < 0 || k < 0 || i >= nx || j >= ny || k >= nz) {
        throw std::out_of_range("Index out of range.");
    }
    return data[i * ny * nz + j * nz + k];  // Convert 3D indices to 1D
}

// Set the value at the grid location (i, j, k)
void Grid1::set(int i, int j, int k, double value) {
    if (i < 0 || j < 0 || k < 0 || i >= nx || j >= ny || k >= nz) {
        throw std::out_of_range("Index out of range.");
    }
    data[i * ny * nz + j * nz + k] = value;  // Set the value
}

// Add two grids element-wise
Grid1 Grid1::operator+(const Grid1& grid) {
    Grid1 result(nx, ny, nz);
    for (int i = 0; i < nx * ny * nz; ++i) {
        result.data[i] = this->data[i] + grid.data[i];
    }
    return result;
}

// Output the grid values
std::ostream& operator<<(std::ostream& os, const Grid1& grid) {
    for (int i = 0; i < grid.nx; ++i) {
        for (int j = 0; j < grid.ny; ++j) {
            for (int k = 0; k < grid.nz; ++k) {
                os << grid(i, j, k) << " ";
            }
            os << std::endl;
        }
        os << std::endl;
    }
    return os;
}
