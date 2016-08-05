/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_SCENEGRAPH_PLANE_HPP__
#define __EXENG_SCENEGRAPH_PLANE_HPP__

#include <xe/Vector.hpp>
#include <xe/sg/Ray.hpp>
#include <xe/sg/IntersectInfo.hpp>

namespace xe { namespace sg {
    
    struct Ray;
    struct IntersectInfo;

    /**
     * @brief Plane on 3-space.
     */
    struct Plane {
        /**
         * @brief Initialize a plane on the X-Z plane, pointing on the positive Y-Axis.
         */
        Plane() {}
    
        Plane(const xe::Vector3f& point_, const xe::Vector3f& normal_) : point(point_), normal(normal_) {}
        
        /**
         * @brief Initialize a plane from three coplanar points.
         */
        Plane(const xe::Vector3f& p1, const xe::Vector3f& p2, const xe::Vector3f& p3);
    
        /**
         * @brief Check if the current plane intersects with the 
         */
        bool intersect(const Ray& ray, IntersectInfo* intersectInfo=nullptr) const;
        
        xe::Vector3f point = {0.0f, 0.0f, 0.0f};
        xe::Vector3f normal = {0.0f, 1.0f, 0.0f};
    };

    inline Plane::Plane(const xe::Vector3f& p1, const xe::Vector3f& p2, const xe::Vector3f& p3) {   
        const float factor = 1.0f/3.0f;
        
        normal = cross(p2 - p1, p3 - p1);
        point = factor * (p1 + p2 + p3);
    }

    inline bool Plane::intersect(const Ray& ray, IntersectInfo* intersectInfo) const {
        auto p = this->point;
        auto n = this->normal;
    
        auto r = ray.point;
        auto d = ray.direction;
    
        auto t = dot(n, p - r) / dot(n, d);
        
        bool result = false;
    
        if (t > 0.0f) {
            result = true;
        }
    
        if (intersectInfo) {
            intersectInfo->intersect = result;
            intersectInfo->distance = t;
            intersectInfo->normal = this->normal;
            intersectInfo->point = ray.getPointAt(t);
        }
    
        return result;
    }
}}

std::ostream& operator<< (std::ostream& os, const xe::sg::Plane &plane);

inline std::ostream& operator<< (std::ostream& os, const xe::sg::Plane &plane) {
    return os << "Point : {" << plane.point << "}, Normal : {" << plane.normal << "}";
}

#endif    //__EXENG_SCENEGRAPH_PLANE_HPP__
