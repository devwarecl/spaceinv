
#pragma once

#ifndef __xe_array__
#define __xe_array__

#include <cassert>

namespace xe {

    //template<typename Type, size_t Count>
    //struct DefaultArrayStorage {
    //    Type values[Count];
    //};

    //template<typename Type, size_t Count, template<typename, size_t> class ArrayStorage=DefaultArrayStorage>
    //class Array {
    //public:
    //    typedef Type type;
    //    static const size_t count = Count;

    //public:
    //    Type& operator[](const size_t index) {
    //        assert(index < count);
    //        return values[index];
    //    }

    //    const Type& operator[](const size_t index) const {
    //        assert(index < count);
    //        return values[index];
    //    }

    //    constexpr size_t size() const {
    //        return count;
    //    }

    //private:
    //    Type values[Count];
    //};

    /**
     * @brief make a new array from another array and a value using the specified binary function
     */
    //template <template<typename, size_t> class array, typename T, size_t C, typename F>
    //array<T, C> operate(array<T, C> arr1, array<T, C> arr2, F func) {
    //    array<T, C> result;
    //
    //    for (size_t i=0; i<count; i++) {
    //        result[i] = func(arr1, arr2);
    //    }
    //
    //    return result;
    //}

    ///**
    // * @brief make a new array from another array and a value using the specified binary function
    // */
    //template <template<typename, size_t> class array, typename T, size_t C, typename F>
    //array<T, C> operate(array<T, C> arr1, T value, F func) {
    //    array<T, C> result;
    //
    //    for (size_t i=0; i<count; i++) {
    //        result[i] = func(arr1, value);
    //    }
    //
    //    return result;
    //}

    template <template<typename, size_t> class Array, typename T, size_t C, T (*func)(T, T)>
    Array<T, C> operate(const Array<T, C> &arr1, const Array<T, C> &arr2) {
        Array<T, C> result;

        for (size_t i=0; i<C; i++) {
            result[i] = func(arr1[i], arr2[i]);
        }

        return result;
    }

    template <template<typename, size_t> class Array, typename T, size_t C, bool (*func)(T, T)>
    Array<bool, C> compare(Vector<T, C> &v1, Vector<T, C> &v2) {
        Array<T, C> result;

        for (size_t i=0; i<C; i++) {
            result[i] = func(arr1[i], arr2[i]);
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
        return operate<T, C, sub>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<T, C> mul(const Array<T, C> &array1, const Array<T, C> &array2) {
        return operate<T, C, mul>(array1, array2);
    }
    
    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<T, C> div(const Array<T, C> &array1, const Array<T, C> &array2) {
        return operate<T, C, div>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<T, C> add(const Array<T, C> &array1, const T value) {
        return operate<T, C, add>(array1, value);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<T, C> sub(const Array<T, C> &array1, const T value) {
        return operate<T, C, sub>(array1, value);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<T, C> mul(const Array<T, C> &array1, const T value) {
        return operate<T, C, mul>(array1, value);
    }
    
    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<T, C> div(const Array<T, C> &array1, const T value) {
        return operate<T, C, div>(array1, value);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<bool, C> equal(const Array<T, C> &array1, const Array<T, C> &array2) {
        return compare<T, C, equal>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<bool, C> not_equal(const Array<T, C> &array1, const Array<T, C> &array2) {
        return compare<T, C, not_equal>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<bool, C> lesser(const Array<T, C> &array1, const Array<T, C> &array2) {
        return compare<T, C, lesser>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<bool, C> greater(const Array<T, C> &array1, const Array<T, C> &array2) {
        return compare<T, C, greater>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<bool, C> lesser_equal(const Array<T, C> &array1, const Array<T, C> &array2) {
        return compare<T, C, lesser_equal>(array1, array2);
    }

    template <template<typename, size_t> class Array, typename T, size_t C>
    Array<bool, C> greater_equal(const Array<T, C> &array1, const Array<T, C> &array2) {
        return compare<T, C, greater_equal>(array1, array2);
    }
}

#endif

#ifndef _xe_vector_dev_hpp__
#define _xe_vector_dev_hpp__

namespace xe { namespace experimental {
    template<typename T, size_t Count>
    struct VectorStorage {
        T values[Count];

        VectorStorage() {}
    };

    template<typename T>
    struct VectorStorage<T, 2> {
        union {
            T values[2];

            struct {T x, y;};
        };

        VectorStorage() {}

        VectorStorage(T x, T y) {
            this->x = x;
            this->y = y;
        }
    };

    template<typename T>
    struct VectorStorage<T, 3> {
        union {
            T values[3];

            struct {T x, y, z;};
        };

        VectorStorage() {}

        VectorStorage(T x, T y, T z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
    };

    template<typename T>
    struct VectorStorage<T, 4> {
        union {
            T values[4];

            struct {T x, y, z, w;};
        };

        VectorStorage() {}

        VectorStorage(T x, T y, T z, T w) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }
    };

    template<typename T, size_t C> 
    struct Vector : public VectorStorage<T, C> {
        using VectorStorage<T, C>::VectorStorage;

        Vector() {}

        explicit Vector(const T* values) {
            std::memcpy(this->values, values, sizeof(T) * C);
        }

        explicit Vector(const T value) {
            for (size_t i=0; i<C; i++) {
                values[i] = value;
            }
        }

        explicit operator const T*() const {
            return values;
        }

        // array-like interface
        T& operator[](const size_t index) {
            assert(index < C);
            return values[index];
        }

        const T& operator[](const size_t index) const {
            assert(index < C);
            return values[index];
        }

        constexpr size_t size() const {
            return count;
        }
    };

    template<typename T, size_t C> 
    Vector<T, C> operator+ (const Vector<T, C> &v1, const Vector<T, C> &v2) {
        return add(v1, v2);
    }

    template<typename T, size_t C> 
    Vector<T, C> operator- (const Vector<T, C> &v1, const Vector<T, C> &v2) {
        return sub(v1, v2);
    }

    template<typename T, size_t C> 
    Vector<T, C> operator* (const Vector<T, C> &v1, const Vector<T, C> &v2) {
        return mul(v1, v2);
    }

    template<typename T, size_t C> 
    Vector<T, C> operator/ (const Vector<T, C> &v1, const Vector<T, C> &v2) {
        return div(v1, v2);
    }
    
    template<typename T, size_t C> 
    Vector<T, C> operator* (const Vector<T, C> &v1, const T value) {
        return mul(v1, value);
    }

    template<typename T, size_t C> 
    Vector<T, C> operator/ (const Vector<T, C> &v1, const T value) {
        return div(v1, value);
    }

    template<typename T, size_t C> 
    Vector<T, C>& operator+= (Vector<T, C> &v1, const Vector<T, C> &v2) {
        return v1 = add(v1, v2);
    }

    template<typename T, size_t C> 
    Vector<T, C>& operator-= (Vector<T, C> &v1, const Vector<T, C> &v2) {
        return v1 = sub(v1, v2);
    }

    template<typename T, size_t C> 
    Vector<T, C>& operator*= (Vector<T, C> &v1, const Vector<T, C> &v2) {
        return v1 = mul(v1, v2);
    }

    template<typename T, size_t C> 
    Vector<T, C>& operator/= (Vector<T, C> &v1, const Vector<T, C> &v2) {
        return v1 = div(v1, v2);
    }

    template<typename T, size_t C> 
    Vector<T, C>& operator*= (Vector<T, C> &v1, const T value) {
        return v1 = mul(v1, value);
    }

    template<typename T, size_t C> 
    Vector<T, C>& operator/= (Vector<T, C> &v1, const T value) {
        return v1 = div(v1, value);
    }

    template<typename T, size_t C>
    Vector<T, C> dot(const Vector<T, C> &v1, const Vector<T, C> &v2) {
        T result = T(0);

        for (size_t i=0; i<C; i++) {
            result += v1[i]*v2[i];
        }

        return result;
    }

    template<typename T>
    Vector<T, 3> cross(const Vector<T, 3> &v1, const Vector<T, 3> &v2) {
        return {
            v1.y*v2.z - v1.z*v2.y, 
            v1.z*v2.x - v1.x*v2.z, 
            v1.x*v2.y - v1.y*v2.x
        };
    }

    template<typename T>
    T dot(const Vector<T, 3> &v1, const Vector<T, 3> &v2, const Vector<T, 3> &v3) {
        return dot(cross(v1, v2), v3);
    }

    template<typename T>
    Vector<T, 3> dot(const Vector<T, 3> &v1, const Vector<T, 3> &v2, const Vector<T, 3> &v3) {
        return cross(cross(v1, v2), v3);
    }

    template<typename T, size_t C>
    T norm_pow2(const Vector<T, C> &v) {
        return dot(v, v);
    }

    template<typename T, size_t C>
    T norm(const Vector<T, C> &v) {
        return std::sqrt(norm_pow2(v));
    }

    template<typename T, size_t C>
    Vector<T, C> normalize(const Vector<T, C> &v) {
        return v / norm(v);
    }

    template<typename T, size_t C>
    Vector<T, C> proj(const Vector<T, C> &v1, const Vector<T, C> &v2) {
        return v1 * ((dot(v1, v2) / norm_pow2(v1, v1)));
    }

    template<typename T, int C>
    Vector<T, C> lerp(const Vector<T, C>& v1, const Vector<T, C>& v2, T t) {
        return t*v2 + v1*(T(1) - t);
    }

    template<typename T, typename S>
    T lerp(const T &v1, const T &v2, S t) {
        return t*v2 + v1*(S(1) - t);
    }

    template<typename T, int C>
    Vector<T, C> hermite (const Vector<T, C>& V1, const Vector<T, C>& T1, const Vector<T, C>& V2, const Vector<T, C>& T2, T t) {
        T ss = t*t;
        T sss = ss*t;

        T _2sss = sss+sss;
        T _3ss = ss+ss+ss;
    
        return  V1*(_2sss - _3ss + T(t))    + 
                V2*(_3ss - _2sss) + 
                T1*(sss - (ss+ss) + t) + 
                T2*(sss - ss);
    }
}}

#endif
