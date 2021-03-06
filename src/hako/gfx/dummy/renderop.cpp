#include <hako/gfx/dummy/renderop.h>
#include <hako/bindings_def.h>
#include <hako/util/debug.h>


Hako::Dummy::Gfx::RenderOperation::RenderOperation()
{
#ifdef HAKO_BUILD_DEBUG
	this->initialized = false;
	this->generated   = false;
#endif
}


Hako::Dummy::Gfx::RenderOperation::~RenderOperation()
{
	HAKO_ASSERT(!this->generated, "possible resource leak; destroy() was not called");
}


void Hako::Dummy::Gfx::RenderOperation::init()
{
	HAKO_ASSERT(!this->initialized, "init() has already been called");

	this->camera       = nullptr;
	this->camera_mask  = -1;
	this->scene        = nullptr;
	this->depth_buffer = nullptr;
	for (int i = 0; i < COLOR_BUFFER_NUM; i++)
		this->color_buffers[i] = nullptr;

	this->should_clear_color = false;
	this->should_clear_depth = false;

#ifdef HAKO_BUILD_DEBUG
	this->initialized = true;
#endif
}


void Hako::Dummy::Gfx::RenderOperation::set_scene(Hako::Gfx::Camera* camera, Hako::Gfx::Scene* scene, unsigned int mask)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(!this->generated, "cannot change render operation after it has been generated");
	this->camera      = camera;
	this->camera_mask = mask;
	this->scene       = scene;
}


void Hako::Dummy::Gfx::RenderOperation::set_color_buffer(unsigned int index, Hako::Gfx::FrameBuffer* colorbuf)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(!this->generated, "cannot change render operation after it has been generated");
	HAKO_ASSERT(index < COLOR_BUFFER_NUM, "index out of bounds");
	this->color_buffers[index] = colorbuf;
	this->check_buffer_dimensions();
}


void Hako::Dummy::Gfx::RenderOperation::set_depth_buffer(Hako::Gfx::FrameBuffer* depthbuf)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(!this->generated, "cannot change render operation after it has been generated");
	this->depth_buffer = depthbuf;
	this->check_buffer_dimensions();
}


void Hako::Dummy::Gfx::RenderOperation::check_buffer_dimensions()
{
    bool found_any = false;
    unsigned int width = 0;
    unsigned int height = 0;
    Hako::Gfx::FrameBuffer* bufs[] =
    {
        this->color_buffers[0], this->color_buffers[1],
        this->color_buffers[2], this->color_buffers[3],
        this->depth_buffer
    };

    for (int i = 0; i < 5; i++)
    {
        if (bufs[i] == nullptr)
            continue;

        if (!found_any)
        {
            found_any = true;
            width = bufs[i]->get_width();
            height = bufs[i]->get_height();
        }
        else
        {
            HAKO_UNUSED(width);
            HAKO_UNUSED(height);
            HAKO_ASSERT(bufs[i]->get_width() == width && bufs[i]->get_height() == height, "mismatched buffer dimensions");
        }
    }
}


void Hako::Dummy::Gfx::RenderOperation::set_clear_color(Hako::Math::Color color)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(!this->generated, "cannot change render operation after it has been generated");
	this->should_clear_color = true;
	this->clear_color        = color;
}


void Hako::Dummy::Gfx::RenderOperation::set_clear_depth(float depth)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(!this->generated, "cannot change render operation after it has been generated");
	this->should_clear_depth = true;
	this->clear_depth        = depth;
}


void Hako::Dummy::Gfx::RenderOperation::advance_interpolation_frame()
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	if (this->scene != nullptr)
		this->scene->advance_interpolation_frame();
	if (this->camera != nullptr)
		this->camera->advance_interpolation_frame();
}


Hako::Error Hako::Dummy::Gfx::RenderOperation::apply()
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(!this->generated, "apply() has already been called");

	Hako::Error err = this->internal_apply();
#ifdef HAKO_BUILD_DEBUG
	if (err.is_ok())
		this->generated = true;
#endif

	return err;
}


void Hako::Dummy::Gfx::RenderOperation::destroy()
{
	HAKO_ASSERT(this->initialized, "init() has not been called");
	HAKO_ASSERT(this->generated, "apply() has not been called");
	this->internal_destroy();
#ifdef HAKO_BUILD_DEBUG
	this->generated = false;
#endif
}
