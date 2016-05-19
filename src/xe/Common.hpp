
#pragma once

#ifndef __xe_common__
#define __xe_common__

#include <cmath>

namespace xe { 
    //http://irshu.blogspot.com/2005/08/check-if-number-is-power-of-2-easier.html
    inline bool isPowerOf2(unsigned int x) {
        return ((x != 0) && !(x & (x - 1)));
    }

    template<typename Type>
    struct Pi {
        static const Type value;
    };

    template<typename Type>
    const Type Pi<Type>::value = Type(3.14159265358979);

    template<typename Type>
    Type deg(Type radians) {
        return radians * Type(180.0) / Pi<Type>::value;
    }

    template<typename Type>
    Type rad(Type degrees) {
        return degrees * Pi<Type>::value / Type(180.0);
    }

    /*
    template<typename Type>
    bool compare(Type v1, Type v2) {
        return v1 == v2;
    }

    template<typename Type>
    bool compare(Type v1, Type v2, Type epsilon = Type(0.00001)) {
        return std::abs(v1 - v2) < epsilon;
    }

    template<typename Type, typename Scalar>
    Type hermite(const Type& V1, const Type& T1, const Type& V2, const Type& T2, Scalar s) {
        auto ss = s*s;
        auto sss = ss*s;

        auto _2sss = sss+sss;
        auto _3ss = ss+ss+ss;
    
        auto t1 = V1*(_2sss - _3ss + Scalar(s));
        auto t2 = V2*(_3ss - _2sss);
        auto t3 = T1*(sss - (ss+ss) + s);
        auto t4 = T2*(sss - ss);

        return t1 + t2 + t3 + t4;
    }

    template<typename Type, typename Scalar>
    Type lerp(const Type& V1, const Type& V2, Scalar S) {
        return S*V2 + V1*(Scalar(1.0) - S);
    }

    template<typename Type, typename Scalar>
    Scalar proj_abs(const Type &a, const Type &b) {
        return dot(a, b) / dot(a, a);
    }
	
    template<typename Type>
    Type proj(const Type &a, const Type &b) {
        return proj_abs(a, b) * a;
    }

    template<typename Type>
    Type triple(const Type &a, const Type &b, const Type &c) {
        return dot(cross(a, b), c);
    }
    */
}

#endif 
