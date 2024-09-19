#include "grid3d_new.h"
#include <iostream>
#include <stdexcept>

// Constructor: Initialize the 3D grid using new operator
Grid3::Grid3(int nx_, int ny_, int nz_) : nx(nx_), ny(ny_), nz(nz_) {
    if (nx <= 0 || ny <= 0 || nz <= 0) {
        throw std::invalid_argument("Grid dimensions must be positive.");
    }

    // Allocate memory dynamically for the 3D grid
    data = new double**[nx];
    for (int i = 0; i < nx; ++i) {
        data[i] = new double*[ny];
        for (int j = 0; j < ny; ++j) {
            data[i][j] = new double[nz];
        }
    }
}

// Destructor: Free allocated memory
Grid3::~Grid3() {
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            delete[] data[i][j];  // Free the innermost arrays
        }
        delete[] data[i];  // Free the middle arrays
    }
    delete[] data;  // Free the outermost array
}

// Get the total number of elements in the grid
int Grid3::getSize() const {
    return nx * ny * nz;  // Return product of dimensions
}

// Get the memory used by the grid in bytes
int Grid3::getMemory() const {
    return nx * ny * nz * sizeof(double);  // Calculate memory size
}

// Access the value at the grid location (i, j, k)
double Grid3::operator()(int i, int j, int k) const {
    if (i < 0 || j < 0 || k < 0 || i >= nx || j >= ny || k >= nz) {
        throw std::out_of_range("Index out of range.");
    }
    return data[i][j][k];  // Return the value at (i, j, k)
}

// Set the value at the grid location (i, j, k)
void Grid3::set(int i, int j, int k, double value) {
    if (i < 0 || j < 0 || k < 0 || i >= nx || j >= ny || k >= nz) {
        throw std::out_of_range("Index out of range.");
    }
    data[i][j][k] = value;  // Set the value
}

// Add two grids element-wise
Grid3 Grid3::operator+(const Grid3& grid) {
    Grid3 result(nx, ny, nz);
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
std::ostream& operator<<(std::ostream& os, const Grid3& grid) {
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
