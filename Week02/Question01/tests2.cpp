#include <iostream>
#include <cassert>
#include "homework2.cpp"  

using namespace std;

// Test function to validate vector operations
void test_vector_operations() {
    cout << "Running vector operations tests..." << endl;

    Vector v1(1.0, 2.0);
    Vector v2(3.0, 4.0);

    // Test addition
    Vector v_add = v1 + v2;
    cout << "Addition result: " << v_add << endl;
    assert(v_add.getComponents()[0] == 4.0);
    assert(v_add.getComponents()[1] == 6.0);

    // Test subtraction
    Vector v_sub = v2 - v1;
    cout << "Subtraction result: " << v_sub << endl;
    assert(v_sub.getComponents()[0] == 2.0);
    assert(v_sub.getComponents()[1] == 2.0);

    // Test scalar multiplication
    Vector v_mul_scalar = v1 * 2.0;
    cout << "Scalar multiplication result: " << v_mul_scalar << endl;
    assert(v_mul_scalar.getComponents()[0] == 2.0);
    assert(v_mul_scalar.getComponents()[1] == 4.0);

    // Test dot product
    double dot_product = v1 * v2;
    cout << "Dot product result: " << dot_product << endl;
    assert(dot_product == 11.0);

    cout << "Vector operations tests passed!" << endl;
}

// Test function to validate 2D particle motion
void test_particle_motion_2d() {
    cout << "Running 2D particle motion test..." << endl;

    Particle particle2D(1.0, Vector(0.0, 0.0), Vector(0.0, 0.0), Vector(0.0, 0.0));
    particle2D.update(1.0, 0.02);

    const auto& pos = particle2D.getPosition().getComponents();
    cout << "2D Particle position after update: (" << pos[0] << ", " << pos[1] << ")" << endl;
    assert(pos[0] != 0.0);
    assert(pos[1] != 0.0);

    cout << "2D particle motion test passed!" << endl;
}

// Test function to validate 3D particle motion
void test_particle_motion_3d() {
    cout << "Running 3D particle motion test..." << endl;

    Particle particle3D(1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0));
    particle3D.update(1.0, 0.02);

    const auto& pos = particle3D.getPosition().getComponents();
    cout << "3D Particle position after update: (" << pos[0] << ", " << pos[1] << ", " << pos[2] << ")" << endl;
    assert(pos[0] != 0.0);
    assert(pos[1] != 0.0);
    assert(pos[2] != 0.0);

    cout << "3D particle motion test passed!" << endl;
}

// Main test function to run all the tests
int main() {
    cout << "Starting tests..." << endl;

    // Run the vector operation tests
    test_vector_operations();

    // Run the 2D particle motion tests
    test_particle_motion_2d();

    // Run the 3D particle motion tests
    test_particle_motion_3d();

    cout << "All tests passed successfully!" << endl;

    return 0;
}
