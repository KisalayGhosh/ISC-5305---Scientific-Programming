#include "grid3d_vector.h"
#include <iostream>
#include <stdexcept>

// Constructor: Initialize the 3D grid using std::vector
Grid2::Grid2(int nx_, int ny_, int nz_) : nx(nx_), ny(ny_), nz(nz_) {
    if (nx <= 0 || ny <= 0 || nz <= 0) {
        throw std::invalid_argument("Grid dimensions must be positive.");
    }
    // Allocate memory for the 3D vector
    data.resize(nx, std::vector<std::vector<double>>(ny, std::vector<double>(nz)));
}

// Destructor: Automatically frees memory for the std::vector
Grid2::~Grid2() {
    // No need for manual memory management with std::vector
}

// Get the total number of elements in the grid
int Grid2::getSize() const {
    return nx * ny * nz;  // Return product of dimensions
}

// Get the memory used by the grid in bytes
int Grid2::getMemory() const {
    return nx * ny * nz * sizeof(double);  // Calculate memory size
}

// Access the value at the grid location (i, j, k)
double Grid2::operator()(int i, int j, int k) const {
    if (i < 0 || j < 0 || k < 0 || i >= nx || j >= ny || k >= nz) {
        throw std::out_of_range("Index out of range.");
    }
    return data[i][j][k];  // Return the value at (i, j, k)
}

// Set the value at the grid location (i, j, k)
void Grid2::set(int i, int j, int k, double value) {
    if (i < 0 || j < 0 || k < 0 || i >= nx || j >= ny || k >= nz) {
        throw std::out_of_range("Index out of range.");
    }
    data[i][j][k] = value;  // Set the value
}

// Add two grids element-wise
Grid2 Grid2::operator+(const Grid2& grid) {
    Grid2 result(nx, ny, nz);
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            for (int k = 0; k < nz; ++k) {
                result.data[i][j][k] = this->data[i][j][k] + grid.data[i][j][k];
            }
        }
    }
    return result;
}

// Output the grid values
std::ostream& operator<<(std::ostream& os, const Grid2& grid) {
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
