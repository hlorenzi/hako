#include <hako/gfx/dummy/mesh.h>
#include <hako/util/debug.h>


Hako::Dummy::Gfx::Mesh::Mesh()
{
#ifdef HAKO_BUILD_DEBUG
	this->initialized = false;
#endif
}


Hako::Dummy::Gfx::Mesh::~Mesh()
{

}


void Hako::Dummy::Gfx::Mesh::init(unsigned int vertex_num, unsigned int index_num, int data_bitfield)
{
	HAKO_ASSERT(!this->initialized, "init() has already been called");

	this->vertex_num    = vertex_num;
	this->index_num     = index_num;
	this->data_bitfield = data_bitfield;

	this->internal_init();

#ifdef HAKO_BUILD_DEBUG
	this->initialized = true;
#endif
}


void Hako::Dummy::Gfx::Mesh::set_data(int data_bit, unsigned int start, unsigned int count, float* data)
{
	HAKO_ASSERT(this->initialized, "init() must be called first");
	HAKO_ASSERT(start + count <= this->vertex_num, "range out of bounds");
	HAKO_ASSERT((this->data_bitfield & data_bit) != 0, "mesh does not hold this kind of data");
	this->internal_set_data(data_bit, start, count, data);
}


void Hako::Dummy::Gfx::Mesh::set_indices(unsigned int start, unsigned int count, int* indices)
{
	HAKO_ASSERT(this->initialized, "init() must be called first");
	HAKO_ASSERT(start + count <= this->index_num, "range out of bounds");
	this->internal_set_indices(start, count, indices);
}