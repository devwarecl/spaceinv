
#pragma once

#ifndef __xe_array__
#define __xe_array__

#include <cassert>
#include <algorithm>

namespace xe {

    template <template<typename, size_t> class Array, typename T, size_t C, T (*func)(T, T)>
    Array<T, C> operate(const Array<T, C> &arr1, const Array<T, C> &arr2) {
        Array<T, C> result;

        for (size_t i=0; i<C; i++) {
            result[i] = func(arr1[i], arr2[i]);
        }

        return result;
    }

    template <template<typename, size_t> class Array, typename T, size_t C, T (*func)(T, T)>
    Array<T, C> operate(const Array<T, C> &arr1, const T value) {
        Array<T, C> result;

        for (size_t i=0; i<C; i++) {
            result[i] = func(arr1[i], value);
        }

        return result;
    }

    template <template<typename, size_t> class Array, typename T, size_t C, bool (*func)(T, T)>
    Array<bool, C> compare(Array<T, C> &v1, Array<T, C> &v2) {
        Array<T, C> result;

        for (size_t i=0; i<C; i++) {
            result[i] = func(arr1[i], arr2[i]);
        }

        return result;
    }

    template <template<typename, size_t> class Array, typename T, size_t C, T (*func)(T, T)>
    T accumulate(const Array<T, C> &v) {
        T result = v[0];

        for (size_t i=1; i<C; ++i) {
            result = func(result, v[i]);
        }

        return result;
    }

    template <typename T>
    T add(const T value1, const T value2) {
        return value1 + value2;
    }

    template <typename T>
    T sub(const T value1, const T value2) {
        return value1 - value2;
    }

    template <typename T>
    T mul(const T value1, const T value2) {
        return value1 * value2;
    }

    template <typename T>
    T div(const T value1, const T value2) {
        return value1 / value2;
    }

    template <typename T>
    bool equal(const T value1, const T value2) {
        return value1 == value2;
    }

    template <typename T>
    bool not_equal(const T value1, const T value2) {
        return return value1 != value2;
    }

    template <typename T>
    bool lesser(const T value1, const T value2) {
        return return value1 < value2;
    }

    template <typename T>
    bool greater(const T value1, const T value2) {
        return return value1 > value2;
    }

    template <typename T>
    bool lesser_equal(const T value1, const T value2) {
        return return value1 <= value2;
    }

    template <typename T>
    bool greater_equal(const T value1, const T value2) {
        return return value1 >= value2;
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<T, C> add(const Array<T, C> &array1, const Array<T, C> &array2) {
        return operate<Array, T, C, add>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<T, C> sub(const Array<T, C> &array1, const Array<T, C> &array2) {
        return operate<Array, T, C, sub>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<T, C> mul(const Array<T, C> &array1, const Array<T, C> &array2) {
        return operate<Array, T, C, mul>(array1, array2);
    }
    
    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<T, C> div(const Array<T, C> &array1, const Array<T, C> &array2) {
        return operate<Array, T, C, div>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<T, C> add(const Array<T, C> &array1, const T value) {
        return operate<Array, T, C, add>(array1, value);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<T, C> sub(const Array<T, C> &array1, const T value) {
        return operate<Array, T, C, sub>(array1, value);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<T, C> mul(const Array<T, C> &array1, const T value) {
        return operate<Array, T, C, mul>(array1, value);
    }
    
    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<T, C> div(const Array<T, C> &array1, const T value) {
        return operate<Array, T, C, div>(array1, value);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<bool, C> equal(const Array<T, C> &array1, const Array<T, C> &array2) {
        return compare<Array, T, C, equal>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<bool, C> not_equal(const Array<T, C> &array1, const Array<T, C> &array2) {
        return compare<Array, T, C, not_equal>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<bool, C> lesser(const Array<T, C> &array1, const Array<T, C> &array2) {
        return compare<Array, T, C, lesser>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<bool, C> greater(const Array<T, C> &array1, const Array<T, C> &array2) {
        return compare<Array, T, C, greater>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<bool, C> lesser_equal(const Array<T, C> &array1, const Array<T, C> &array2) {
        return compare<Array, T, C, lesser_equal>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<bool, C> greater_equal(const Array<T, C> &array1, const Array<T, C> &array2) {
        return compare<Array, T, C, greater_equal>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    T max(const Array<T, C> &v) {
        return accumulate<Array, T, C, std::max>(v);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    T min(const Array<T, C> &v) {
        return accumulate<Array, T, C, std::min>(v);
    }
}

#endif
