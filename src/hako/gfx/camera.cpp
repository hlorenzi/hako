#include <hako/gfx/camera.h>


Hako::Gfx::Camera::Camera()
{

}


Hako::Gfx::Camera::~Camera()
{

}


void Hako::Gfx::Camera::init()
{

}


void Hako::Gfx::Camera::set_projection_ortho(float left, float right, float top, float bottom, float znear, float zfar)
{
	this->projection_kind = ProjectionKind::Orthographic;
	this->projection_data.orthographic.left   = this->projection_data.orthographic.left_last   = left;
	this->projection_data.orthographic.right  = this->projection_data.orthographic.right_last  = right;
	this->projection_data.orthographic.top    = this->projection_data.orthographic.top_last    = top;
	this->projection_data.orthographic.bottom = this->projection_data.orthographic.bottom_last = bottom;
	this->projection_data.orthographic.znear  = this->projection_data.orthographic.znear_last  = znear;
	this->projection_data.orthographic.zfar   = this->projection_data.orthographic.zfar_last   = zfar;
}


void Hako::Gfx::Camera::lerp_projection_ortho(float left, float right, float top, float bottom, float znear, float zfar)
{
	this->projection_data.orthographic.left   = left;
	this->projection_data.orthographic.right  = right;
	this->projection_data.orthographic.top    = top;
	this->projection_data.orthographic.bottom = bottom;
	this->projection_data.orthographic.znear  = znear;
	this->projection_data.orthographic.zfar   = zfar;
}


void Hako::Gfx::Camera::set_projection_perspective(float fovy, float aspect_w_by_h, float znear, float zfar)
{
	this->projection_kind = ProjectionKind::Perspective;
	this->projection_data.perspective.fovy   = this->projection_data.perspective.fovy_last   = fovy;
	this->projection_data.perspective.aspect = this->projection_data.perspective.aspect_last = aspect_w_by_h;
	this->projection_data.perspective.znear  = this->projection_data.perspective.znear_last  = znear;
	this->projection_data.perspective.zfar   = this->projection_data.perspective.zfar_last   = zfar;
}


void Hako::Gfx::Camera::lerp_projection_perspective(float fovy, float aspect_w_by_h, float znear, float zfar)
{
	this->projection_data.perspective.fovy   = fovy;
	this->projection_data.perspective.aspect = aspect_w_by_h;
	this->projection_data.perspective.znear  = znear;
	this->projection_data.perspective.zfar   = zfar;
}


void Hako::Gfx::Camera::set_projection_frustum(float left, float right, float top, float bottom, float znear, float zfar)
{
	this->projection_kind = ProjectionKind::Frustum;
	this->projection_data.frustum.left   = this->projection_data.frustum.left_last   = left;
	this->projection_data.frustum.right  = this->projection_data.frustum.right_last  = right;
	this->projection_data.frustum.top    = this->projection_data.frustum.top_last    = top;
	this->projection_data.frustum.bottom = this->projection_data.frustum.bottom_last = bottom;
	this->projection_data.frustum.znear  = this->projection_data.frustum.znear_last  = znear;
	this->projection_data.frustum.zfar   = this->projection_data.frustum.zfar_last   = zfar;
}


void Hako::Gfx::Camera::lerp_projection_frustum(float left, float right, float top, float bottom, float znear, float zfar)
{
	this->projection_data.frustum.left   = left;
	this->projection_data.frustum.right  = right;
	this->projection_data.frustum.top    = top;
	this->projection_data.frustum.bottom = bottom;
	this->projection_data.frustum.znear  = znear;
	this->projection_data.frustum.zfar   = zfar;
}


void Hako::Gfx::Camera::set_projection_custom(Hako::Math::Matrix4 matrix)
{
	this->projection_kind = ProjectionKind::Custom;
	this->projection_data.custom.matrix = matrix;
}