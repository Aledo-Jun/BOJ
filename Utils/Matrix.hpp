//
// Created by june0 on 2024-02-16.
//

#ifndef BOJ_MATRIX_HPP
#define BOJ_MATRIX_HPP

#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <cassert>
#include "TypeTraits.hpp"

using namespace std;

namespace Utils
{
namespace TypeTraits
{
    struct matrix_base { };

    template<typename T>
    using is_matrix = std::is_base_of<matrix_base, T>;

    template<typename T>
    using is_matrix_t = std::enable_if_t<is_matrix<T>::value>;

} // namespace TypeTraits

namespace Matrix
{
    using namespace TypeTraits;

    struct matrix_shape {
        int n_rows, n_cols;

        bool operator==(const matrix_shape& other) const {
            return (n_rows == other.n_rows) && (n_cols == other.n_cols);
        }

        bool operator!=(const matrix_shape& other) const { return !(*this == other); }
    };

    template<typename T,
            int n_rows,
            int n_cols,
            std::enable_if_t<supports_arithmetic<T>::value && 0 < n_rows && 0 < n_cols> * = nullptr>
    class Matrix : matrix_base {
        using value_type = T;

    private:
        T Data[n_rows][n_cols];

        static constexpr matrix_shape _shape{n_rows, n_cols};

    public:
        [[nodiscard]]
        static constexpr matrix_shape shape() { return _shape; }

        static constexpr int get_n_rows(){ return n_rows; }

        static constexpr int get_n_cols(){ return n_cols; }

        template<std::enable_if_t<n_rows == n_cols> * = nullptr>
        static constexpr Matrix identity() {
            Matrix result;
            for (int i = 0; i < n_rows; i++) result[i][i] = value_type(1);
            return result;
        }

        ////////////////////////////////
        // Constructors
        ////////////////////////////////

        Matrix() = default;

        template<typename U>
        explicit Matrix(const std::vector<std::vector<U>> &data) {
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < data[i].size(); j++) {
                    Data[i][j] = value_type(data[i][j]);
                }
                for (int j = data[i].size(); j < n_cols; j++) {
                    Data[i][j] = value_type(0);
                }
            }
        }

        Matrix(initializer_list<initializer_list<value_type>> data) {
            auto row = data.begin();
            for (int i = 0; i < n_rows && row != data.end(); i++, row++) {
                auto _cur = std::begin(Data[i]);
                auto _first = row->begin();
                auto _last = row->end();
                for (; _first != _last && _cur != std::end(Data[i]); _cur++, _first++) {
                    *_cur = *_first;
                }
                for (; _cur != std::end(Data[i]); _cur++) *_cur = value_type(0);
            }
            for (int i = data.size(); i < n_rows; i++) {
                std::fill(std::begin(Data[i]), std::end(Data[i]), value_type(0));
            }
        }

        ////////////////////////////////////////
        // Operators
        ////////////////////////////////////////

        // Subscription operator
        value_type*  operator[](int idx) {
            return Data[idx];
        }

        const value_type* operator[](int idx) const {
            return Data[idx];
        }

        // Unary plus
        Matrix operator+() {
            return *this;
        }

        // Unary minus
        Matrix operator-() {
            Matrix result;
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < n_cols; j++) {
                    result[i][j] = -this->Data[i][j];
                }
            }
            return result;
        }

        // Matrix + Matrix
        template<class MatrixType,
                class MatrixType2,
                is_matrix_t<MatrixType> * = nullptr,
                is_matrix_t<MatrixType2> * = nullptr,
                std::enable_if_t<MatrixType::get_n_rows() == MatrixType2::get_n_rows() &&
                                 MatrixType::get_n_cols() == MatrixType2::get_n_cols()> * = nullptr>
        friend MatrixType
        operator+(const MatrixType &a, const MatrixType2 &b) {
            MatrixType result;
            int rows = MatrixType::get_n_rows();
            int cols = MatrixType::get_n_cols();
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    result[i][j] = a[i][j] + b[i][j];
                }
            }
            return result;
        }

        // Matrix += Matrix
        template<class MatrixType,
                is_matrix_t<MatrixType> * = nullptr,
                std::enable_if_t<MatrixType::get_n_rows() == n_rows &&
                                 MatrixType::get_n_cols() == n_cols> * = nullptr>
        Matrix operator+=(const MatrixType &rhs) {
            return *this = (*this + rhs);
        }

        // Matrix - Matrix
        template<class MatrixType,
                class MatrixType2,
                is_matrix_t<MatrixType> * = nullptr,
                is_matrix_t<MatrixType2> * = nullptr,
                std::enable_if_t<MatrixType::get_n_rows() == MatrixType2::get_n_rows() &&
                                 MatrixType::get_n_cols() == MatrixType2::get_n_cols()> * = nullptr>
        friend MatrixType
        operator-(const MatrixType &a, const MatrixType2 &b) {
            return a + (-b);
        }

        // Matrix -= Matrix
        template<class MatrixType,
                is_matrix_t<MatrixType> * = nullptr,
                std::enable_if_t<MatrixType::get_n_rows() == n_rows &&
                                 MatrixType::get_n_cols() == n_cols> * = nullptr>
        Matrix operator-=(const MatrixType &rhs) {
            return *this = (*this - rhs);
        }

        // Matrix * Matrix
        template<class MatrixType,
                class MatrixType2,
                is_matrix_t<MatrixType> * = nullptr,
                is_matrix_t<MatrixType2> * = nullptr,
                std::enable_if_t<MatrixType::get_n_cols() == MatrixType2::get_n_rows()> * = nullptr>
        friend auto
        operator*(const MatrixType &a, const MatrixType2 &b) {
            Matrix<typename MatrixType::value_type,
                    MatrixType2::get_n_rows(),
                    MatrixType::get_n_cols()> result;
            int rows = MatrixType2::get_n_rows();
            int cols = MatrixType::get_n_cols();
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    result[i][j] = value_type(0);
                    for (int k = 0; k < rows; ++k) {
                        result[i][j] += a[i][k] * b[k][j];
                    }
                }
            }
            return result;
        }

        // Matrix *= Matrix
        template<class MatrixType,
                is_matrix_t<MatrixType> * = nullptr,
                std::enable_if_t<n_cols == MatrixType::get_n_rows()> * = nullptr>
        Matrix operator*=(const MatrixType &rhs) {
            return *this = (*this * rhs);
        }

        // Matrix + scalar
        template<typename S,
                std::enable_if_t<std::is_scalar_v<S>> * = nullptr>
        Matrix operator+(S scalar) {
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < n_cols; j++) {
                    this->Data[i][j] += scalar;
                }
            }
        }

        // Matrix - scalar
        template<typename S>
        Matrix operator-(S scalar) {
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < n_cols; j++) {
                    this->Data[i][j] -= scalar;
                }
            }
        }

        // Matrix * scalar
        template<typename S,
                std::enable_if_t<!is_matrix<S>::value> * = nullptr>
        Matrix operator*(S scalar) {
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < n_cols; j++) {
                    this->Data[i][j] *= scalar;
                }
            }
        }

        // Matrix / scalar
        template<typename S>
        Matrix operator/(S scalar) {
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < n_cols; j++) {
                    this->Data[i][j] /= scalar;
                }
            }
        }

        // Matrix += scalar
        template<typename S>
        Matrix operator+=(S scalar) {
            return *this = (*this + scalar);
        }

        // Matrix -= scalar
        template<typename S>
        Matrix operator-=(S scalar) {
            return *this = (*this - scalar);
        }

        // Matrix *= scalar
        template<typename S,
                std::enable_if_t<std::is_scalar_v<S>> * = nullptr>
        Matrix operator*=(S scalar) {
            return *this = (*this * scalar);
        }

        // Matrix /= scalar
        template<typename S>
        Matrix operator/=(S scalar) {
            return *this = (*this / scalar);
        }

        // Matrix == Matrix
        template<class MatrixType,
                is_matrix_t<MatrixType> * = nullptr>
        bool operator==(const Matrix& rhs) const {
            if (this->shape() != rhs.shape()) return false;
            for (int i = 0; i < n_rows; i++){
                for (int j = 0; j < n_cols; j++){
                    if (this->Data[i][j] != rhs[i][j]) return false;
                }
            }
            return true;
        }

        ////////////////////////////////////////////////////////////////
        // Mathematical operations
        ////////////////////////////////////////////////////////////////

        Matrix<value_type, n_cols, n_rows>
        transpose() {
            Matrix < value_type, n_cols, n_rows > result;
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < n_cols; j++) {
                    result[j][i] = this->Data[i][j];
                }
            }
            return result;
        }

        template<std::enable_if_t<n_rows == n_cols> * = nullptr>
        std::size_t trace() {
            std::size_t result = 0;
            for (int i = 0; i < n_rows; i++) result += this->Data[i][i];
            return result;
        }

        template<std::enable_if_t<n_rows == n_cols> * = nullptr>
        std::size_t determinant() {
            throw std::runtime_error("Not implemented");
            // TODO: move implementation from Math.hpp
        }

    }; // class Matrix

    // Some helper templates
    template<typename T>
    struct is_square_matrix : std::false_type { };

    template<typename T, int n_rows, int n_cols>
    struct is_square_matrix<Matrix<T, n_rows, n_cols>>
            : std::conditional<n_rows == n_cols, std::true_type, std::false_type>::type { };

    template<typename T>
    using is_square_matrix_t = std::enable_if_t<is_square_matrix<T>::value>;

    template<class MatrixType,
            is_square_matrix_t<MatrixType> * = nullptr>
    MatrixType pow(const MatrixType& a, int n){
        MatrixType base = a;
        MatrixType result = MatrixType::identity();
        while (n) {
            if (n & 1) result *= base;
            base *= base;
            n >>= 1;
        }
        return result;
    }

    // TODO: implement Dynamic Matrix using std::vector
} // namespace Matrix

} // namespace Utils

#endif //BOJ_MATRIX_HPP
