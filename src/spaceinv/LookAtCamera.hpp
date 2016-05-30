
#ifndef __lookatcamera__
#define __lookatcamera__

#include "xe/Common.hpp"
#include "xe/Vector.hpp"
#include "xe/sg/Camera.hpp"

class LookAtCamera : public xe::sg::Camera {
public:
	virtual ~LookAtCamera() {}

	virtual xe::Matrix4f computeView() const override {
		return xe::lookat(position, lookat, up);
	}

	virtual xe::Matrix4f computeProj() const override {
		return xe::perspective(fov, aspect, znear, zfar);
	}

	virtual xe::Rectf getViewport() const override {
		return xe::Rectf();
	}

public:
	xe::Vector3f position = {0.0f, 0.0f, 0.0f};
	xe::Vector3f lookat = {0.0f, 0.0f, 0.0f};
	xe::Vector3f up = {0.0f, 0.0f, 0.0f};

	float fov = xe::rad(60.0f);
	float aspect = 4.0f/3.0f;
	float znear = 0.0001f;;
	float zfar = 1000.0f;
};

#endif 
