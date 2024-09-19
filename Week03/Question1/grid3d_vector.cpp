#include "grid3d_vector.h"
#include <stdexcept>

Grid2::Grid2(int nx_, int ny_, int nz_)
    : nx(nx_), ny(ny_), nz(nz_), data(nx_, std::vector<std::vector<double>>(ny_, std::vector<double>(nz_, 0.0)))
{
}

Grid2::~Grid2()
{
}

int Grid2::getSize() const
{
    return nx * ny * nz;
}

int Grid2::getMemory() const
{
    return getSize() * sizeof(double);
}

double Grid2::operator()(int i, int j, int k) const
{
    if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return data[i][j][k];
}

void Grid2::set(int i, int j, int k, double value)
{
    if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz)
    {
        throw std::out_of_range("Index out of bounds");
    }
    data[i][j][k] = value;
}

Grid2 Grid2::operator+(const Grid2& other)
{
    if (nx != other.nx || ny != other.ny || nz != other.nz)
    {
        throw std::invalid_argument("Grid dimensions do not match");
    }

    Grid2 result(nx, ny, nz);
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                result.data[i][j][k] = data[i][j][k] + other.data[i][j][k];
            }
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Grid2& grid)
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
