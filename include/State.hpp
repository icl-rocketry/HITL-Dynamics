
#pragma once
#include <Eigen/Dense>

//This state struct can represent any number of states, and applies operator overloading for simple state by state operations
struct State {
    Eigen::VectorXd data;

    State() = default;
    State(int size) : data(Eigen::VectorXd::Zero(size)) {}

    int size() const { return static_cast<int>(data.size()); }

    State operator+(const State& other) const {
        State res;
        res.data = this->data + other.data;
        return res;
    }

    State& operator+=(const State& other) {
        this->data += other.data;
        return *this;
    }

    State operator*(double scalar) const {
        State res;
        res.data = this->data * scalar;
        return res;
    }

    double& operator[](int i) { return data[i]; }
    const double& operator[](int i) const { return data[i]; }
};