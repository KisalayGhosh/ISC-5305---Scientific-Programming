#include "grid3d_1d_array.h"
#include "grid3d_vector.h"
#include "grid3d_new.h"
#include <iostream>
#include <chrono>

void test1DArrayGrid()
{
    Grid1 grid(10, 10, 10);
    grid.set(5, 5, 5, 100.0);
    std::cout << "Testing 1D array grid:\n" << grid;

    // Performance test for operator+
    auto start = std::chrono::high_resolution_clock::now();
    Grid1 grid_sum = grid + grid;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to add two 1D array grids: " << diff.count() << " s\n";

    // Print the summed grid
    std::cout << "Summed 1D array grid:\n" << grid_sum;
}

void testVectorGrid()
{
    Grid2 grid(10, 10, 10);
    grid.set(5, 5, 5, 100.0);
    std::cout << "Testing vector-based grid:\n" << grid;

    // Performance test for operator+
    auto start = std::chrono::high_resolution_clock::now();
    Grid2 grid_sum = grid + grid;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to add two vector-based grids: " << diff.count() << " s\n";

    // Print the summed grid
    std::cout << "Summed vector-based grid:\n" << grid_sum;
}

void testNewGrid()
{
    Grid3 grid(10, 10, 10);
    grid.set(5, 5, 5, 100.0);
    std::cout << "Testing new-operator-based grid:\n" << grid;

    // Performance test for operator+
    auto start = std::chrono::high_resolution_clock::now();
    Grid3 grid_sum = grid + grid;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to add two new-operator-based grids: " << diff.count() << " s\n";

    // Print the summed grid
    std::cout << "Summed new-operator-based grid:\n" << grid_sum;
}

int main()
{
    test1DArrayGrid();
    testVectorGrid();
    testNewGrid();
    return 0;
}
