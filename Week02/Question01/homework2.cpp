#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

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

    size_t size() const {
        return components_.size();  // Return size as size_t
    }

    const vector<double>& getComponents() const {
        return components_;
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

    // Output stream operator
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

// Simulation for 2D and 3D particle trajectory
void simulateAndPlot(const string& filename, Particle& particle, double dt, double t_end) {
    ofstream file(filename);

    // Write the header to the file
    if (particle.getPosition().size() == 2) {
        file << "time,x,y\n";
    } else {
        file << "time,x,y,z\n";
    }

    // Time loop for Euler integration
    for (double t = 0.0; t <= t_end; t += dt) {
        particle.update(t, dt);

        const auto& pos = particle.getPosition().getComponents();
        file << t;
        for (double comp : pos) {
            file << "," << comp;
        }
        file << "\n";
    }
    file.close();
}

#ifndef TEST_MODE
int main() {
    // Your existing main code for the actual program
    // Create and simulate 2D and 3D particles, etc.
    Particle particle2D(1.0, Vector(0.0, 0.0), Vector(0.0, 0.0), Vector(0.0, 0.0));
    simulateAndPlot("traject_2d.txt", particle2D, 0.02, 4.0);

    Particle particle3D(1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0));
    simulateAndPlot("traject_3d.txt", particle3D, 0.02, 4.0);

    return 0;
}
#endif