#include "grid3d_new.h"
#include <stdexcept>

Grid3::Grid3(int nx_, int ny_, int nz_)
    : nx(nx_), ny(ny_), nz(nz_)
{
    data = new double**[nx];
    for (int i = 0; i < nx; ++i)
    {
        data[i] = new double*[ny];
        for (int j = 0; j < ny; ++j)
        {
            data[i][j] = new double[nz];
            for (int k = 0; k < nz; ++k)
            {
                data[i][j][k] = 0.0;
            }
        }
    }
}

Grid3::~Grid3()
{
    for (int i = 0; i < nx; ++i)
    {
        for (int j = 0; j < ny; ++j)
        {
            delete[] data[i][j];
        }
        delete[] data[i];
    }
    delete[] data;
}

int Grid3::getSize() const
{
    return nx * ny * nz;
}

int Grid3::getMemory() const
{
    return getSize() * sizeof(double);
}

double Grid3::operator()(int i, int j, int k) const
{
    if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return data[i][j][k];
}

void Grid3::set(int i, int j, int k, double value)
{
    if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz)
    {
        throw std::out_of_range("Index out of bounds");
    }
    data[i][j][k] = value;
}

Grid3 Grid3::operator+(const Grid3& other)
{
    if (nx != other.nx || ny != other.ny || nz != other.nz)
    {
        throw std::invalid_argument("Grid dimensions do not match");
    }

    Grid3 result(nx, ny, nz);
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

std::ostream& operator<<(std::ostream& os, const Grid3& grid)
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
