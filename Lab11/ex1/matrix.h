#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <array>

// Forward declaration for specialization
template <typename T, size_t Rows, size_t Cols>
class Matrix;

// Question 1: Basic Matrix Template
template <typename T, size_t Rows, size_t Cols>
class Matrix {
public:
    // Zero initialization
    Matrix() {
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                data_[i][j] = T();
            }
        }
    }

    // Constructor from 2D array
    Matrix(const std::array<std::array<T, Cols>, Rows>& data) : data_(data) {}
    
    // Constructor from nested initializer list
    Matrix(std::initializer_list<std::initializer_list<T>> init) {
        size_t i = 0;
        for (auto row : init) {
            if (i >= Rows) break;
            
            size_t j = 0;
            for (auto val : row) {
                if (j >= Cols) break;
                data_[i][j] = val;
                j++;
            }
            i++;
        }
        
        // Zero-fill any remaining elements
        while (i < Rows) {
            for (size_t j = 0; j < Cols; j++) {
                data_[i][j] = T();
            }
            i++;
        }
    }

    // Element access - non-const version
    T& at(size_t i, size_t j) {
        return data_[i][j];
    }

    // Element access - const version
    const T& at(size_t i, size_t j) const {
        return data_[i][j];
    }

    // Question 2: Operator Overloading
    
    // Addition operator
    Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result.data_[i][j] = data_[i][j] + other.data_[i][j];
            }
        }
        return result;
    }

    // Multiplication operator
    template<size_t OtherCols>
    Matrix<T, Rows, OtherCols> operator*(const Matrix<T, Cols, OtherCols>& other) const {
        Matrix<T, Rows, OtherCols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < OtherCols; ++j) {
                result.at(i, j) = T();
                for (size_t k = 0; k < Cols; ++k) {
                    result.at(i, j) += data_[i][k] * other.at(k, j);
                }
            }
        }
        return result;
    }

    // Scalar multiplication (matrix * scalar)
    Matrix operator*(const T& scalar) const {
        Matrix result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result.data_[i][j] = data_[i][j] * scalar;
            }
        }
        return result;
    }

    // Subscript operator (returns a row)
    std::array<T, Cols>& operator[](size_t i) {
        return data_[i];
    }

    // Const version of subscript operator
    const std::array<T, Cols>& operator[](size_t i) const {
        return data_[i];
    }

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (size_t i = 0; i < Rows; ++i) {
            os << "[";
            for (size_t j = 0; j < Cols; ++j) {
                os << matrix.data_[i][j];
                if (j < Cols - 1) os << ", ";
            }
            os << "]" << std::endl;
        }
        return os;
    }

private:
    std::array<std::array<T, Cols>, Rows> data_;
};

// Non-member scalar multiplication (for expressions like 2 * matrix)
template<typename T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols> operator*(const T& scalar, const Matrix<T, Rows, Cols>& matrix) {
    return matrix * scalar;
}

// Question 3: Template Specialization for 2x2 matrices
template <typename T>
class Matrix<T, 2, 2> {
public:
    // Zero initialization
    Matrix() : data_{{{T(), T()}, {T(), T()}}} {}

    // Constructor from 2D array
    Matrix(const std::array<std::array<T, 2>, 2>& data) : data_(data) {}
    
    // Constructor from nested initializer list
    Matrix(std::initializer_list<std::initializer_list<T>> init) {
        size_t i = 0;
        for (auto row : init) {
            if (i >= 2) break;
            
            size_t j = 0;
            for (auto val : row) {
                if (j >= 2) break;
                data_[i][j] = val;
                j++;
            }
            i++;
        }
        
        // Zero-fill any remaining elements
        while (i < 2) {
            for (size_t j = 0; j < 2; j++) {
                data_[i][j] = T();
            }
            i++;
        }
    }

    // Element access - non-const version
    T& at(size_t i, size_t j) {
        return data_[i][j];
    }

    // Element access - const version
    const T& at(size_t i, size_t j) const {
        return data_[i][j];
    }

    // Addition operator
    Matrix operator+(const Matrix& other) const {
        Matrix result;
        result.data_[0][0] = data_[0][0] + other.data_[0][0];
        result.data_[0][1] = data_[0][1] + other.data_[0][1];
        result.data_[1][0] = data_[1][0] + other.data_[1][0];
        result.data_[1][1] = data_[1][1] + other.data_[1][1];
        return result;
    }

    // Matrix multiplication (optimized for 2x2)
    Matrix operator*(const Matrix& other) const {
        Matrix result;
        result.data_[0][0] = data_[0][0] * other.data_[0][0] + data_[0][1] * other.data_[1][0];
        result.data_[0][1] = data_[0][0] * other.data_[0][1] + data_[0][1] * other.data_[1][1];
        result.data_[1][0] = data_[1][0] * other.data_[0][0] + data_[1][1] * other.data_[1][0];
        result.data_[1][1] = data_[1][0] * other.data_[0][1] + data_[1][1] * other.data_[1][1];
        return result;
    }

    // Scalar multiplication (matrix * scalar)
    Matrix operator*(const T& scalar) const {
        Matrix result;
        result.data_[0][0] = data_[0][0] * scalar;
        result.data_[0][1] = data_[0][1] * scalar;
        result.data_[1][0] = data_[1][0] * scalar;
        result.data_[1][1] = data_[1][1] * scalar;
        return result;
    }

    // Subscript operator (returns a row)
    std::array<T, 2>& operator[](size_t i) {
        return data_[i];
    }

    // Const version of subscript operator
    const std::array<T, 2>& operator[](size_t i) const {
        return data_[i];
    }

    // Optimized determinant calculation for 2x2 matrix
    T determinant() const {
        return data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];
    }

    // Matrix inverse operation
    Matrix inverse() const {
        T det = determinant();
        // No exception handling without stdexcept
        
        T invDet = T(1) / det;
        Matrix result;
        result.data_[0][0] = data_[1][1] * invDet;
        result.data_[0][1] = -data_[0][1] * invDet;
        result.data_[1][0] = -data_[1][0] * invDet;
        result.data_[1][1] = data_[0][0] * invDet;
        return result;
    }

    // Solve linear system Ax = b using Cramer's rule
    std::array<T, 2> solve(const std::array<T, 2>& b) const {
        T det = determinant();
        // No exception handling without stdexcept
        
        // Create matrices for Cramer's rule
        Matrix detX;
        detX.data_[0][0] = b[0];
        detX.data_[0][1] = data_[0][1];
        detX.data_[1][0] = b[1];
        detX.data_[1][1] = data_[1][1];
        
        Matrix detY;
        detY.data_[0][0] = data_[0][0];
        detY.data_[0][1] = b[0];
        detY.data_[1][0] = data_[1][0];
        detY.data_[1][1] = b[1];

        // Solve using Cramer's rule
        std::array<T, 2> solution = {
            detX.determinant() / det,
            detY.determinant() / det
        };

        return solution;
    }

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        os << "[" << matrix.data_[0][0] << ", " << matrix.data_[0][1] << "]" << std::endl;
        os << "[" << matrix.data_[1][0] << ", " << matrix.data_[1][1] << "]" << std::endl;
        return os;
    }

private:
    std::array<std::array<T, 2>, 2> data_;
};

// Non-member scalar multiplication for 2x2 specialization
template<typename T>
Matrix<T, 2, 2> operator*(const T& scalar, const Matrix<T, 2, 2>& matrix) {
    Matrix<T, 2, 2> result;
    result.at(0, 0) = scalar * matrix.at(0, 0);
    result.at(0, 1) = scalar * matrix.at(0, 1);
    result.at(1, 0) = scalar * matrix.at(1, 0);
    result.at(1, 1) = scalar * matrix.at(1, 1);
    return result;
}

#endif // MATRIX_H