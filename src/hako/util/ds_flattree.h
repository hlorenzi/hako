#ifndef HAKO_UTIL_DS_FLATTREE_H
#define HAKO_UTIL_DS_FLATTREE_H


#include <hako/util/ds_refvector.h>


namespace Hako
{
	namespace DS
	{
		template <typename T>
		class FlatTree
		{
		public:
			class Node;


			typedef typename Hako::DS::RefVector<Node>::Reference Reference;


			class Node
			{
				friend class FlatTree<T>;


			protected:
				T            data;
				Reference    parent;
				unsigned int child_number;
			};


			FlatTree()
			{
			#ifdef HAKO_BUILD_DEBUG
				this->initialized = false;
			#endif
			}


			void init()
			{
				HAKO_ASSERT(!this->initialized, "init() has already been called");

				this->nodes.init();

			#ifdef HAKO_BUILD_DEBUG
				this->initialized = true;
			#endif
			}


			Reference add(T data)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");

				Node node;
				node.data         = data;
				node.parent       = Reference::make_null();
				node.child_number = 0;

				return this->nodes.add(node);
			}


			Reference add_child(Reference& parent, T data)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");

				Node node;
				node.data         = data;
				node.parent       = Reference::make_null();
				node.child_number = 0;

				this->nodes.refresh_reference(&parent);
				unsigned int item_position = this->find_next_sibling(parent.cached_index);

				this->nodes.get_by_index(parent.cached_index).child_number += 1;

				return this->nodes.insert(node, item_position);
			}


			unsigned int count()
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				return this->nodes.length();
			}


			T& operator [] (Reference& refer)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				return this->nodes[refer].data;
			}


			T& get_by_index(unsigned int index)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				HAKO_ASSERT(index < this->count(), "index out of bounds");
				return this->nodes.get_by_index(index).data;
			}


			unsigned int get_child_num_by_index(unsigned int index)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				HAKO_ASSERT(index < this->count(), "index out of bounds");
				return this->nodes.get_by_index(index).child_number;
			}


		protected:
			unsigned int find_next_sibling(unsigned int index)
			{
				HAKO_ASSERT(index < this->count(), "index out of bounds");
				unsigned int result = index + 1;
				unsigned int count  = 0;
				while (count < this->nodes.get_by_index(index).child_number)
				{
					result = this->find_next_sibling(result);
					count += 1;
				}
				return result;
			}


		#ifdef HAKO_BUILD_DEBUG
			bool initialized;
		#endif
			Hako::DS::RefVector<Node> nodes;
		};
	}
}


#endif
