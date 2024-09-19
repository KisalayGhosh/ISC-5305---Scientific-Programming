#include "grid3d_1d_array.h"
#include <stdexcept>
#include <iostream>

Grid1::Grid1(int nx_, int ny_, int nz_)
    : nx(nx_), ny(ny_), nz(nz_)
{
    data = new double[nx * ny * nz]();
}

Grid1::~Grid1()
{
    delete[] data;
}

int Grid1::getSize() const
{
    return nx * ny * nz;
}

int Grid1::getMemory() const
{
    return getSize() * sizeof(double);
}

double Grid1::operator()(int i, int j, int k) const
{
    if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return data[i * (ny * nz) + j * nz + k];
}

void Grid1::set(int i, int j, int k, double value)
{
    if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz)
    {
        throw std::out_of_range("Index out of bounds");
    }
    data[i * (ny * nz) + j * nz + k] = value;
}

Grid1 Grid1::operator+(const Grid1& other)
{
    if (nx != other.nx || ny != other.ny || nz != other.nz)
    {
        throw std::invalid_argument("Grid dimensions do not match");
    }

    Grid1 result(nx, ny, nz);
    for (int i = 0; i < nx * ny * nz; ++i)
    {
        result.data[i] = this->data[i] + other.data[i];
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Grid1& grid)
{
    for (int i = 0; i < grid.nx; i++)
    {
        for (int j = 0; j < grid.ny; j++)
        {
            for (int k = 0; k < grid.nz; k++)
            {
                os << grid(i, j, k) << " ";
            }
            os << std::endl;
        }
        os << std::endl;
    }
    return os;
}
