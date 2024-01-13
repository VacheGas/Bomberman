#pragma once

#include <array>
#include <string>
#include <cmath>

/**
 * @class Vec
 * @brief Represents a mathematical vector of a fixed size with various operations.
 * @tparam SIZE The size of the vector.
 * @tparam TYPE The type of elements in the vector.
 */
template<size_t SIZE, typename TYPE = float>
class Vec {
public:
    /**
     * @brief Default constructor for the Vec class.
     */
    Vec() = default;

    /**
     * @brief Constructor for the Vec class, initializing with an array.
     * @param vec The array to initialize the vector.
     */
    Vec(const std::array<TYPE, SIZE>& vec);

    /**
     * @brief Accessor to retrieve the element at the specified index.
     * @param index The index of the element to retrieve.
     * @return A constant reference to the element at the specified index.
     */
    const TYPE& operator[](size_t index) const;

    /**
     * @brief Mutator to retrieve the element at the specified index.
     * @param index The index of the element to retrieve.
     * @return A reference to the element at the specified index.
     */
    TYPE& operator[](size_t index);

    /**
     * @brief Returns the size of the vector.
     * @return The size of the vector.
     */
    size_t size() const;

    /**
     * @brief Calculates the length (magnitude) of the vector.
     * @return The length of the vector.
     */
    TYPE length() const;

    /**
     * @brief Returns a normalized version of the vector.
     * @return A normalized vector.
     */
    Vec normalized() const;

    /**
     * @brief Checks if the vector is equal to another vector.
     * @param other The vector to compare with.
     * @return True if the vectors are equal, false otherwise.
     */
    bool equals(const Vec& other) const;

    /**
     * @brief Checks if the vector is approximately equal to another vector within a specified epsilon.
     * @param other The vector to compare with.
     * @param epsilon The tolerance for equality.
     * @return True if the vectors are approximately equal, false otherwise.
     */
    bool equalsWithEpsilon(const Vec& other, TYPE epsilon = std::numeric_limits<TYPE>::epsilon()) const;

public:
    /**
     * @brief Adds another vector to the current vector.
     * @param rhs The vector to add.
     * @return A reference to the modified vector.
     */
    Vec& operator+=(const Vec& rhs);

    /**
     * @brief Subtracts another vector from the current vector.
     * @param rhs The vector to subtract.
     * @return A reference to the modified vector.
     */
    Vec& operator-=(const Vec& rhs);

    /**
     * @brief Multiplies the current vector element-wise by another vector.
     * @param rhs The vector to multiply by.
     * @return A reference to the modified vector.
     */
    Vec& operator*=(const Vec& rhs);

    /**
     * @brief Divides the current vector element-wise by another vector.
     * @param rhs The vector to divide by.
     * @return A reference to the modified vector.
     */
    Vec& operator/=(const Vec& rhs);

    /**
     * @brief Adds a scalar value to each element of the vector.
     * @param number The scalar value to add.
     * @return A reference to the modified vector.
     */
    Vec& operator+=(TYPE number);

    /**
     * @brief Subtracts a scalar value from each element of the vector.
     * @param number The scalar value to subtract.
     * @return A reference to the modified vector.
     */
    Vec& operator-=(TYPE number);

    /**
     * @brief Multiplies each element of the vector by a scalar value.
     * @param number The scalar value to multiply by.
     * @return A reference to the modified vector.
     */
    Vec& operator*=(TYPE number);

    /**
     * @brief Divides each element of the vector by a scalar value.
     * @param number The scalar value to divide by.
     * @return A reference to the modified vector.
     */
    Vec& operator/=(TYPE number);

private:
    void checkIndexValidity(size_t index) const;

private:
    std::array<TYPE, SIZE> _vec{};
};

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE> Vec<SIZE, TYPE>::normalized() const {
    return *this / length();
}

template <size_t SIZE, typename TYPE>
bool Vec<SIZE, TYPE>::equals(const Vec<SIZE, TYPE>& other) const {
    if (_vec.size() != other._vec.size()) {
        return false;
    }

    for (size_t i{}; i < _vec.size(); ++i) {
        if (_vec[i] != other._vec[i]) {
            return false;
        }
    }
    return true;
}

template <size_t SIZE, typename TYPE>
bool Vec<SIZE, TYPE>::equalsWithEpsilon(const Vec<SIZE, TYPE>& other, TYPE epsilon) const {
    if (_vec.size() != other._vec.size()) {
        return false;
    }

    // TODO: find a better way than 10 * epsilon
    for (size_t i{}; i < _vec.size(); ++i) {
        // std::cout << std::abs(_vec[i] - other._vec[i]) << std::endl;
        if (std::abs(_vec[i] - other._vec[i]) > 10 * epsilon) {
            return false;
        }
    }
    return true;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>::Vec(const std::array<TYPE, SIZE>& vec) 
    : _vec{vec} {}

template <size_t SIZE, typename TYPE>
TYPE& Vec<SIZE, TYPE>::operator[](size_t index) {
    checkIndexValidity(index);
    return _vec[index];
}

template <size_t SIZE, typename TYPE>
const TYPE& Vec<SIZE, TYPE>::operator[](size_t index) const {
    checkIndexValidity(index);
    return _vec[index];
}

template <size_t SIZE, typename TYPE>
size_t Vec<SIZE, TYPE>::size() const {
    return SIZE;
}

template <size_t SIZE, typename TYPE>
TYPE Vec<SIZE, TYPE>::length() const {
    TYPE resultSquared{};
    for (size_t i{}; i < _vec.size(); ++i) {
        resultSquared += std::pow(_vec[i], 2);
    }
    return std::sqrt(resultSquared);
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator+=(const Vec<SIZE, TYPE>& rhs) {
    for (size_t i{}; i < SIZE; ++i) {
        this->operator[](i) += rhs[i];
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator-=(const Vec<SIZE, TYPE>& rhs) {
    for (size_t i{}; i < SIZE; ++i) {
        this->operator[](i) -= rhs[i];
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator*=(const Vec<SIZE, TYPE>& rhs) {
    for (size_t i{}; i < SIZE; ++i) {
        this->operator[](i) *= rhs[i];
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator/=(const Vec<SIZE, TYPE>& rhs) {
    for (size_t i{}; i < SIZE; ++i) {
        if (rhs[i] == 0) {
            throw std::runtime_error("division by zero");
        }
        this->operator[](i) /= rhs[i];
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator+=(TYPE num) {
    for (size_t i{}; i < SIZE; ++i) {
        this->operator[](i) += num;
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator-=(TYPE num) {
    for (size_t i{}; i < SIZE; ++i) {
        this->operator[](i) -= num;
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator*=(TYPE num) {
    for (size_t i{}; i < SIZE; ++i) {
        this->operator[](i) *= num;
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
Vec<SIZE, TYPE>& Vec<SIZE, TYPE>::operator/=(TYPE num) {
    if (num == 0) {
        throw std::runtime_error("division by zero");
    }
    for (size_t i{}; i < SIZE; ++i) {
        this->operator[](i) /= num;
    }
    return *this;
}

template <size_t SIZE, typename TYPE>
void Vec<SIZE, TYPE>::checkIndexValidity(size_t index) const {
    if (index < 0 || index >= _vec.size()) {
        throw std::runtime_error("invalid index " + std::to_string(index) +
                                 " for vec with size " + std::to_string(SIZE));
    }
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator+(const Vec<SIZE, TYPE>& lhs,
                          const Vec<SIZE, TYPE>& rhs) {
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        result[i] = lhs[i] + rhs[i];
    }
    return result;
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator-(const Vec<SIZE, TYPE>& lhs,
                          const Vec<SIZE, TYPE>& rhs) {
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        result[i] = lhs[i] - rhs[i];
    }
    return result;
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator*(const Vec<SIZE, TYPE>& lhs,
                          const Vec<SIZE, TYPE>& rhs) {
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        result[i] = lhs[i] * rhs[i];
    }
    return result;
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator/(const Vec<SIZE, TYPE>& lhs,
                          const Vec<SIZE, TYPE>& rhs) {
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        if (rhs[i] == 0) {
            throw std::runtime_error("division by zero");
        }
        result[i] = lhs[i] / rhs[i];
    }
    return result;
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator+(const Vec<SIZE, TYPE>& lhs, TYPE num) {
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        result[i] = lhs[i] + num;
    }
    return result;
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator-(const Vec<SIZE, TYPE>& lhs, TYPE num) {
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        result[i] = lhs[i] - num;
    }
    return result;
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator*(const Vec<SIZE, TYPE>& lhs, TYPE num) {
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        result[i] = lhs[i] * num;
    }
    return result;
}

template <size_t SIZE, typename TYPE = float>
Vec<SIZE, TYPE> operator/(const Vec<SIZE, TYPE>& lhs, TYPE num) {
    if (num == 0) {
        throw std::runtime_error("division by zero");
    }
    Vec<SIZE, TYPE> result;
    for (size_t i{}; i < SIZE; ++i) {
        result[i] = lhs[i] / num;
    }
    return result;
}

using Vec2 = Vec<2, float>;
using Vec4 = Vec<4, float>;