#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

// Vector class to represent both 2D and 3D vectors
class Vector {
private:
    vector<double> components_; // Holds the components of the vector

public:
    /**
     * Constructor to initialize the vector with a given set of components.
     * @param components A vector of doubles representing the components of the vector.
     */
    Vector(vector<double> components) : components_(components) {}

    /**
     * Constructor to initialize a 2D vector with x and y components.
     * @param x The x component of the vector.
     * @param y The y component of the vector.
     */
    Vector(double x, double y) : components_{x, y} {}

    /**
     * Constructor to initialize a 3D vector with x, y, and z components.
     * @param x The x component of the vector.
     * @param y The y component of the vector.
     * @param z The z component of the vector.
     */
    Vector(double x, double y, double z) : components_{x, y, z} {}

    /**
     * Destructor for the Vector class.
     */
    ~Vector() {}

    /**
     * Returns the number of components in the vector (size).
     * @return The size of the vector as a size_t.
     */
    size_t size() const {
        return components_.size();  // Return the number of components
    }

    /**
     * Returns the components of the vector as a reference.
     * @return A reference to the vector of components.
     */
    const vector<double>& getComponents() const {
        return components_;
    }

    /**
     * Overloaded addition operator to add two vectors element-wise.
     * Throws an error if the vector sizes do not match.
     * @param other The vector to add to the current vector.
     * @return A new vector that is the element-wise sum of the two vectors.
     */
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

    /**
     * Overloaded subtraction operator to subtract one vector from another element-wise.
     * Throws an error if the vector sizes do not match.
     * @param other The vector to subtract from the current vector.
     * @return A new vector that is the element-wise difference of the two vectors.
     */
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

    /**
     * Overloaded multiplication operator to scale a vector by a scalar.
     * @param scalar The scalar value to multiply each component of the vector by.
     * @return A new vector with each component scaled by the scalar.
     */
    Vector operator*(const double &scalar) const {
        vector<double> result(components_.size());
        for (size_t i = 0; i < components_.size(); ++i) {
            result[i] = components_[i] * scalar;
        }
        return Vector(result);
    }

    /**
     * Overloaded multiplication operator to compute the dot product of two vectors.
     * Throws an error if the vector sizes do not match.
     * @param other The vector to compute the dot product with.
     * @return The scalar result of the dot product.
     */
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

    /**
     * Overloaded output stream operator to print the vector in the form (x, y) or (x, y, z).
     * @param os The output stream.
     * @param v The vector to be printed.
     * @return The output stream with the formatted vector.
     */
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

// Particle class for simulating motion in 2D or 3D
class Particle {
public:
    /**
     * Constructor to initialize a particle with its mass, position, velocity, and force.
     * @param mass The mass of the particle.
     * @param position The initial position vector of the particle.
     * @param velocity The initial velocity vector of the particle.
     * @param force The initial force vector acting on the particle.
     */
    Particle(double mass, const Vector &position, const Vector &velocity, const Vector &force)
        : mass_(mass), position_(position), velocity_(velocity), force_(force) {
        cout << "Particle created at position " << position_ << endl;
    }

    /**
     * Destructor for the Particle class.
     */
    ~Particle() {
        cout << "Particle destroyed at position " << position_ << endl;
    }

    /**
     * Updates the particle's position using Euler's method.
     * The new position is computed based on the velocity and time step.
     * @param dt The time step for updating the position.
     */
    void updatePosition(double dt) {
        position_ = position_ + velocity_ * dt;  // Update position using velocity and time step
    }

    /**
     * Prints the current state of the particle, including its position and velocity.
     */
    void printState() const {
        cout << "Particle - Position: " << position_ << ", Velocity: " << velocity_ << endl;
    }

    /**
     * Updates the particle's velocity and position based on sinusoidal forces.
     * For 2D particles, the force follows the pattern (sin(2t), cos(2t)).
     * For 3D particles, the force follows the pattern (sin(2t), cos(2t), cos(1.5t)).
     * @param t The current time.
     * @param dt The time step for updating velocity and position.
     */
    void update(double t, double dt) {
        // Set sinusoidal force based on the dimension (2D or 3D)
        if (position_.size() == 2) {
            force_ = Vector(sin(2.0 * t), cos(2.0 * t));  // 2D case
        } else if (position_.size() == 3) {
            force_ = Vector(sin(2.0 * t), cos(2.0 * t), cos(1.5 * t));  // 3D case
        }

        // Update velocity using Euler's method: v_{n+1} = v_n + dt * F_n
        velocity_ = velocity_ + force_ * dt;

        // Update position using Euler's method: P_{n+1} = P_n + dt * v_n
        updatePosition(dt);
    }

    /**
     * Returns the current position of the particle.
     * @return A reference to the position vector of the particle.
     */
    const Vector& getPosition() const {
        return position_;
    }

private:
    double mass_;     // The mass of the particle
    Vector position_; // The current position of the particle
    Vector velocity_; // The current velocity of the particle
    Vector force_;    // The force acting on the particle
};

/**
 * Simulates the motion of a particle and writes the trajectory to a file.
 * @param filename The name of the file to write the trajectory data to.
 * @param particle The particle object being simulated.
 * @param dt The time step for the simulation.
 * @param t_end The end time for the simulation.
 */
void simulateAndPlot(const string& filename, Particle& particle, double dt, double t_end) {
    ofstream file(filename);  // Open the file to write data

    // Write the header (time, x, y[, z]) depending on whether it's 2D or 3D
    if (particle.getPosition().size() == 2) {
        file << "time,x,y\n";  // 2D case
    } else {
        file << "time,x,y,z\n";  // 3D case
    }

    // Loop over time and update the particle's position and velocity
    for (double t = 0.0; t <= t_end; t += dt) {
        particle.update(t, dt);  // Update the particle's state

        const auto& pos = particle.getPosition().getComponents();  // Get the current position
        file << t;  // Write the current time
        for (double comp : pos) {
            file << "," << comp;  // Write each position component
        }
        file << "\n";  // Newline for the next time step
    }
    file.close();  // Close the file after writing
}

#ifndef TEST_MODE
/**
 * Main function to create and simulate 2D and 3D particles.
 */
int main() {
    // Create and simulate 2D particle
    Particle particle2D(1.0, Vector(0.0, 0.0), Vector(0.0, 0.0), Vector(0.0, 0.0));
    simulateAndPlot("traject_2d.txt", particle2D, 0.02, 4.0);

    // Create and simulate 3D particle
    Particle particle3D(1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0));
    simulateAndPlot("traject_3d.txt", particle3D, 0.02, 4.0);

    return 0;
}
#endif
