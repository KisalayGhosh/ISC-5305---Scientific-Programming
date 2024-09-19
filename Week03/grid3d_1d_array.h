#ifndef __GRID3D_1D_ARRAY_H__
#define __GRID3D_1D_ARRAY_H__

#include <iostream>

/**
 * @class Grid1
 * @brief A class for managing a 3D grid using a 1D array.
 */
class Grid1
{
public:
    /**
     * @brief Constructor to initialize the 3D grid.
     * @param nx_ Number of grid points in the x direction.
     * @param ny_ Number of grid points in the y direction.
     * @param nz_ Number of grid points in the z direction.
     */
    Grid1(int nx_=1, int ny_=1, int nz_=1);

    /**
     * @brief Destructor to clean up the allocated memory.
     */
    ~Grid1();

    /**
     * @brief Get the total number of elements in the grid.
     * @return Total number of elements in the grid.
     */
    int getSize() const;

    /**
     * @brief Get the total memory used by the grid (in bytes).
     * @return Memory usage of the grid in bytes.
     */
    int getMemory() const;

    /**
     * @brief Overloaded () operator to get the value at a specific grid point.
     * @param i The x index.
     * @param j The y index.
     * @param k The z index.
     * @return The value at the grid point (i, j, k).
     */
    double operator()(int i, int j, int k) const;

    /**
     * @brief Set the value at a specific grid point.
     * @param i The x index.
     * @param j The y index.
     * @param k The z index.
     * @param value The value to set.
     */
    void set(int i, int j, int k, double value);

    /**
     * @brief Overloaded + operator to add two grids element-wise.
     * @param grid The grid to add to the current grid.
     * @return A new grid with the sum of the two grids.
     */
    Grid1 operator+(const Grid1& grid);

    /**
     * @brief Overloaded << operator for printing the grid.
     * @param os The output stream.
     * @param grid The grid to print.
     * @return The output stream with grid data.
     */
    friend std::ostream& operator<<(std::ostream& os, const Grid1& grid);

private:
    double* data;  ///< Pointer to the 1D array storing grid data.
    int nx, ny, nz;  ///< Dimensions of the grid.
};

#endif
