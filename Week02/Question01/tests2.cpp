#include "homework2.cpp" // Including the main code for testing
#include <iostream>
#include <cassert> // For test assertions

using namespace std;

// Test the Vector class operations
void test_vector_operations() {
    cout << "Testing Vector operations..." << endl;

    // Test addition
    Vector v1(1.0, 2.0);
    Vector v2(3.0, 4.0);
    Vector v_add = v1 + v2;
    assert(v_add.getComponents()[0] == 4.0);
    assert(v_add.getComponents()[1] == 6.0);
    cout << "Vector addition test passed!" << endl;

    // Test subtraction
    Vector v_sub = v2 - v1;
    assert(v_sub.getComponents()[0] == 2.0);
    assert(v_sub.getComponents()[1] == 2.0);
    cout << "Vector subtraction test passed!" << endl;

    // Test scalar multiplication
    Vector v_mul = v1 * 2.0;
    assert(v_mul.getComponents()[0] == 2.0);
    assert(v_mul.getComponents()[1] == 4.0);
    cout << "Scalar multiplication test passed!" << endl;

    // Test dot product
    double dot_product = v1 * v2;
    assert(dot_product == 11.0); // 1*3 + 2*4 = 3 + 8 = 11
    cout << "Dot product test passed!" << endl;
}

// Test particle motion simulation
void test_particle_motion_2d() {
    cout << "Testing 2D particle motion..." << endl;

    Particle particle2D(1.0, Vector(0.0, 0.0), Vector(0.0, 0.0), Vector(0.0, 0.0));
    double dt = 0.02;
    double t_end = 0.1;
    
    // Simulate the motion for a few steps and validate the position
    for (double t = 0.0; t <= t_end; t += dt) {
        particle2D.update(t, dt);
    }

    Vector position = particle2D.getPosition();
    const auto& pos = position.getComponents();

    // Check if position has changed (it should change since force is non-zero)
    assert(pos[0] != 0.0 || pos[1] != 0.0);
    cout << "2D particle motion test passed!" << endl;
}

void test_particle_motion_3d() {
    cout << "Testing 3D particle motion..." << endl;

    Particle particle3D(1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0));
    double dt = 0.02;
    double t_end = 0.1;
    
    // Simulate the motion for a few steps and validate the position
    for (double t = 0.0; t <= t_end; t += dt) {
        particle3D.update(t, dt);
    }

    Vector position = particle3D.getPosition();
    const auto& pos = position.getComponents();

    // Check if position has changed (it should change since force is non-zero)
    assert(pos[0] != 0.0 || pos[1] != 0.0 || pos[2] != 0.0);
    cout << "3D particle motion test passed!" << endl;
}

int main() {
    // Run all the test cases
    test_vector_operations();
    test_particle_motion_2d();
    test_particle_motion_3d();

    cout << "All tests passed!" << endl;

    return 0;
}
