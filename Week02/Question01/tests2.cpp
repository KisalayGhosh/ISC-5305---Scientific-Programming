#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

// Vector class to represent both 2D and 3D vectors
class Vector {
private:
    vector<double> components_;

public:
    Vector(vector<double> components) : components_(components) {}

    Vector(double x, double y) : components_{x, y} {}
    Vector(double x, double y, double z) : components_{x, y, z} {}
    
    ~Vector() {}

    const vector<double>& getComponents() const {
        return components_;
    }

    int size() const {
        return components_.size();
    }

    // Addition operator
    Vector operator+(const Vector &other) const {
        if (components_.size() != other.size()) {
            throw runtime_error("Vector sizes must match for addition.");
        }
        vector<double> result(components_.size());
        for (size_t i = 0; i < components_.size(); ++i) {
            result[i] = components_[i] + other.components_[i];
        }
        return Vector(result);
    }

    // Subtraction operator
    Vector operator-(const Vector &other) const {
        if (components_.size() != other.size()) {
            throw runtime_error("Vector sizes must match for subtraction.");
        }
        vector<double> result(components_.size());
        for (size_t i = 0; i < components_.size(); ++i) {
            result[i] = components_[i] - other.components_[i];
        }
        return Vector(result);
    }

    // Scalar multiplication operator
    Vector operator*(const double &scalar) const {
        vector<double> result(components_.size());
        for (size_t i = 0; i < components_.size(); ++i) {
            result[i] = components_[i] * scalar;
        }
        return Vector(result);
    }

    // Dot product operator
    double operator*(const Vector &other) const {
        if (components_.size() != other.size()) {
            throw runtime_error("Vector sizes must match for dot product.");
        }
        double result = 0.0;
        for (size_t i = 0; i < components_.size(); ++i) {
            result += components_[i] * other.components_[i];
        }
        return result;
    }

    friend ostream &operator<<(ostream &os, const Vector &v) {
        os << "(";
        for (size_t i = 0; i < v.size(); ++i) {
            os << v.components_[i];
            if (i < v.size() - 1) os << ", ";
        }
        os << ")";
        return os;
    }
};

// Particle class for motion simulation
class Particle {
public:
    Particle(double mass, const Vector &position, const Vector &velocity, const Vector &force)
        : mass_(mass), position_(position), velocity_(velocity), force_(force) {
        cout << "Particle created at position " << position_ << endl;
    }

    ~Particle() {
        cout << "Particle destroyed at position " << position_ << endl;
    }

    // Update particle's position using Euler's method
    void updatePosition(double dt) {
        position_ = position_ + velocity_ * dt;
    }

    void printState() const {
        cout << "Particle - Position: " << position_ << ", Velocity: " << velocity_ << endl;
    }

    // Update particle's velocity and position based on sinusoidal forces
    void update(double t, double dt) {
        if (position_.size() == 2) {
            force_ = Vector(sin(2.0 * t), cos(2.0 * t)); // 2D case
        } else if (position_.size() == 3) {
            force_ = Vector(sin(2.0 * t), cos(2.0 * t), cos(1.5 * t)); // 3D case
        }

        // Update velocity: v_{n+1} = v_n + dt * F_n
        velocity_ = velocity_ + force_ * dt;

        // Update position: P_{n+1} = P_n + dt * v_n
        updatePosition(dt);
    }

    // Add this method to access the position
    const Vector& getPosition() const {
        return position_;
    }

private:
    double mass_;
    Vector position_;
    Vector velocity_;
    Vector force_;
};

// Function to test vector operations
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

// Function to test particle motion in 2D
void test_particle_motion_2d() {
    cout << "Running 2D particle motion test..." << endl;

    Particle particle2D(1.0, Vector(0.0, 0.0), Vector(0.0, 0.0), Vector(0.0, 0.0));
    particle2D.update(1.0, 0.02);

    const auto& pos = particle2D.getPosition().getComponents();
    cout << "2D Particle position after update: (" << pos[0] << ", " << pos[1] << ")" << endl;
    assert(pos[0] != 0.0);  // Expecting non-zero position after update
    assert(pos[1] != 0.0);

    cout << "2D particle motion test passed!" << endl;
}

// Function to test particle motion in 3D
void test_particle_motion_3d() {
    cout << "Running 3D particle motion test..." << endl;

    Particle particle3D(1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0));
    particle3D.update(1.0, 0.02);

    const auto& pos = particle3D.getPosition().getComponents();
    cout << "3D Particle position after update: (" << pos[0] << ", " << pos[1] << ", " << pos[2] << ")" << endl;
    assert(pos[0] != 0.0);  // Expecting non-zero position after update
    assert(pos[1] != 0.0);
    assert(pos[2] != 0.0);

    cout << "3D particle motion test passed!" << endl;
}

// Main function to run all the tests
int main() {
    cout << "Starting tests..." << endl;

    // Test vector operations
    test_vector_operations();

    // Test 2D particle motion
    test_particle_motion_2d();

    // Test 3D particle motion
    test_particle_motion_3d();

    cout << "All tests passed successfully!" << endl;

    return 0;
}
