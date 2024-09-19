#include "grid3d_1d_array.h"
#include "grid3d_vector.h"
#include "grid3d_new.h"


#include <iostream> 
using namespace std;

void check_grid_1d_array(int nx, int ny, int nz)
{
    Grid1 grid(nx, ny, nz);
    cout << "grid size: " << grid.getSize() << endl;
    cout << "grid memory: " << grid.getMemory() << " bytes" << endl;
 
    // Note the 1st loop that tests that the indices are within the range 
    for (int i=0; i < nx; i++) {
    for (int j=0; j < ny; j++) {
    for (int k=0; k < nz; k++) {
        grid.set(i, j, k, 100*i+10*j+k);
    }}}

    cout << "Grid 1: " << grid;

    Grid1 grid_sum = grid + grid;
}
//----------------------------------------------------------------------

void check_grid_vector(int nx, int ny, int nz)
{
    Grid2 grid(nx, ny, nz);
    cout << "grid size: " << grid.getSize() << endl;
    cout << "grid memory: " << grid.getMemory() << " bytes" << endl;
 
    // Note the 1st loop that tests that the indices are within the range 
    for (int i=0; i < nx; i++) {
    for (int j=0; j < ny; j++) {
    for (int k=0; k < nz; k++) {
        grid.set(i, j, k, 100*i+10*j+k);
    }}}

    cout << "Grid 2: " << grid;

    Grid2 grid_sum = grid + grid;
}

//----------------------------------------------------------------------
void check_grid_new(int nx, int ny, int nz)
{
    Grid3 grid(nx, ny, nz);
    cout << "grid size: " << grid.getSize() << endl;
    cout << "grid memory: " << grid.getMemory() << " bytes" << endl;
 
    // Note the 1st loop that tests that the indices are within the range 
    for (int i=0; i < nx; i++) {
    for (int j=0; j < ny; j++) {
    for (int k=0; k < nz; k++) {
        grid.set(i, j, k, 100*i+10*j+k);
    }}}

    cout << "Grid 3: " << grid;

    Grid3 grid_sum = grid + grid;
}

//----------------------------------------------------------------------
int main() {
    int nx = 2;
    int ny = 3;
    int nz = 4;

    check_grid_1d_array(nx, ny, nz);
    check_grid_vector(nx, ny, nz);
    check_grid_new(nx, ny, nz);

    return 0;
}
//----------------------------------------------------------------------
