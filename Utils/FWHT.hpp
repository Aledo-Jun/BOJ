//
// Created by june0 on 2024-07-09.
//

#ifndef BOJ_FWHT_HPP
#define BOJ_FWHT_HPP

#include <vector>

/**
 * Fast Walsh Hadamard Transform
 * @see <a href=https://gina65.tistory.com/30>Reference</a>
 */
namespace FWHT {
    enum Conv_Type {OR, AND, XOR};

    // NOTE: using std::enable_if_t<> for function specialization
    //       might have better performance (not significantly faster)
    template<Conv_Type type, typename T = int>
    void _fwht(std::vector<T> &_v, bool _is_inv) {
        int n = (int) _v.size();
        int sgn = _is_inv ? -1 : 1;
        for (int i = 1; i < n; i <<= 1) {
            for (int j = 0; j < n; j += i << 1) {
                for (int k = 0; k < i; k++) {
                    if constexpr (type == OR) {
                        _v[i + j + k] += sgn * _v[j + k];
                    } else if constexpr (type == AND) {
                        _v[j + k] += sgn * _v[i + j + k];
                    } else if constexpr (type == XOR) {
                        T tmp = _v[i + j + k];
                        _v[i + j + k] = _v[j + k] - tmp;
                        _v[j + k] += tmp;

                        if (_is_inv) {
                            _v[i + j + k] >>= 1;
                            _v[j + k] >>= 1;
                        }
                    }
                }
            }
        }
    }

    /// @code ::FWHT::FWHT<Conv_Type, Value_Type>::mem_func();
    template<Conv_Type type, typename Value_Type = int>
    class FWHT {
        using T = Value_Type;

        static std::vector<T> _convolution(std::vector<T> &&_a, std::vector<T> &&_b) {
            int n = (int) _a.size();
            int m = (int) _b.size();
#if __has_builtin(__builtin_clz)
            int l = 32 - __builtin_clz(n + m), len = 1 << l;
#else
            int len = 1;
            while (len < n + m) len <<= 1;
#endif
            _a.resize(len);
            _fwht<type>(_a, false);
            _b.resize(len);
            _fwht<type>(_b, false);

            for (int i = 0; i < len; i++)
                _a[i] *= _b[i];

            _fwht<type>(_a, true);
            return _a;
        }

        static std::vector<T> _convolution_pow(std::vector<T> &&_a, int _exp) {
            int n = (int) _a.size();
#if __has_builtin(__builtin_clz)
            int l = 32 - __builtin_clz(n + n), len = 1 << l;
#else
            int len = 1;
            while (len < n + n) len <<= 1;
#endif
            _a.resize(len);
            _fwht<type>(_a, false);

            for (int i = 0; i < len; i++)
                _a[i] *= pow(_a[i], _exp - 1);

            _fwht<type>(_a, true);
            return _a;
        }

    public:
        static void fwht(std::vector<T> &a) {
            _fwht<type>(a, false);
        }
        static void inv_fwht(std::vector<T> &a) {
            _fwht<type>(a, true);
        }

        static std::vector<T> convolution(const std::vector<T> &a,
                                          const std::vector<T> &b) {
            int n = (int) a.size();
            int m = (int) b.size();
            if (n == 0 || m == 0) return {};

            std::vector<T> _a(a.begin(), a.end()), _b(b.begin(), b.end());
            return _convolution(std::move(_a), std::move(_b));
        }

        static std::vector<T> convolution_pow(const std::vector<T> &a, int exp) {
            int n = (int) a.size();
            if (n == 0) return {};

            std::vector<T> _a(a.begin(), a.end());
            return _convolution_pow(std::move(_a), exp);
        }
    };
}
using namespace FWHT;

#endif //BOJ_FWHT_HPP
