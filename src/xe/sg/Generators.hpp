
#pragma once

#ifndef __xe_sg_generator__
#define __xe_sg_generator__

#include <vector>
#include <cmath>

#include "xe/Vector.hpp"
#include "xe/Quaternion.hpp"
#include "xe/sg/Plane.hpp"
#include "xe/gfx/Primitive.hpp"

namespace xe { namespace sg {

    template<typename Type>
    struct Shape {
        xe::gfx::Primitive primitive;
        std::vector<Vector<Type, 3>> coords;
    };

    /**
     * @brief Geometry generators
     */
    template<typename Type>
    Shape<Type> gencoords(const Plane &plane, const Vector<Type, 2> &size, const Vector<int, 2> &parts) {
        typedef Vector<Type, 3> VectorType;

        Shape<Type> shape;

        const VectorType top = {0.0, 1.0, 0.0};

        const auto q = Quaternion<Type>{top, plane.normal};

        const auto up = plane.normal;
        const auto forward = transform(q, {0.0, 0.0, 1.0});
        const auto right = transform(q, {1.0, 0.0, 0.0});

        const auto center = plane.point;

        // compute the geometry patch
        for (int i=0; i<parts.y; i++) {
            for (int j=0; j<parts.x; j++) {
                // i, j are the coordinates of the current grid element.
                // each grid element has 4 points, so we need to generate six points (three per triangle)
                VectorType points[4];

                points[0] = center + float(j + 0)*right + float(i + 0)*forward;
                points[1] = center + float(j + 1)*right + float(i + 0)*forward;
                points[2] = center + float(j + 0)*right + float(i + 1)*forward;
                points[3] = center + float(j + 1)*right + float(i + 1)*forward;

                shape.coords.push_back(points[0]);
                shape.coords.push_back(points[1]);
                shape.coords.push_back(points[2]);

                shape.coords.push_back(points[2]);
                shape.coords.push_back(points[1]);
                shape.coords.push_back(points[3]);
            }
        }

        shape.primitive = xe::gfx::Primitive::TriangleList;

        return shape;
    }

    template<typename Type>
    std::vector<Vector<Type, 3>> gennormals(const Shape<Type> &shape) {
        std::vector<Vector<Type, 3>> normals;

        normals.resize(shape.coords.size());

        return normals;
    }

    template<typename Type>
    std::vector<Vector<Type, 2>> gentexcoords(const Shape<Type> &shape) {
        std::vector<Vector<Type, 2>> texcoords;

        texcoords.resize(shape.coords.size());

        return texcoords;
    }
}}

#endif
