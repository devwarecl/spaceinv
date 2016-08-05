
/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SCENEGRAPH_RAY_HPP__
#define __EXENG_SCENEGRAPH_RAY_HPP__

#include <iosfwd>
#include <cassert>

#include "xe/Vector.hpp"

namespace xe { namespace sg { 
    
    /**
     * @brief Ray abstraction.
     */
    struct Ray {
        /**
         * @brief Initializes the ray, positioned around the origin, and pointing in the positive Z-axis.
         */
        Ray() {}
    
        /**
         * @brief Initialize the ray, orientated around a arbitrary origin and direction.
         */
        Ray(const xe::Vector3f& point_, const xe::Vector3f& direction_) : point(point_), direction(direction_) {}

        /**
         * @brief Computes the point of the ray at 't' distance from the starting point, to the 
         * direction of the ray.
         */
        xe::Vector3f getPointAt(float t) const {
            const auto p = this->point;
            const auto d = this->direction;
    
            return p + t*d;
        }
        
        xe::Vector3f point = {0.0f, 0.0f, 0.0f};
        xe::Vector3f direction = {0.0f, 0.0f, 0.0f};
    };
}}

std::ostream& operator<< (std::ostream& os, const xe::sg::Ray& ray) {
    return os << "Point : {" << ray.point << "}, Direction : {" << ray.direction << "}";
}

#endif 
