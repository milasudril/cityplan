//@	{
//@	 "targets":[{"name":"city.hpp","type":"include"}]
//@	}

#ifndef CITYPLAN_CITY_HPP
#define CITYPLAN_CITY_HPP

#include "geom/rectangle.hpp"

#include <vector>


namespace Cityplan
	{
	using Block = Rectangle;  // For now, should be a distinct type

	class City
		{
		public:
			City& append(Block const& block)
				{
				m_blocks.push_back(block);
				return *this;
				}

			City& update(size_t block_index, Block const& new_block)
				{
				m_blocks[block_index] = new_block;
				return *this;
				}

			Block const& getBlock(size_t block_index) const
				{return m_blocks[block_index];}

			Block const* begin() const
				{return m_blocks.data();}

			Block const* end() const
				{return begin() + blockCount();}

			size_t blockCount() const
				{return m_blocks.size();}

		private:
			std::vector<Block> m_blocks;
		};
	}

#endif
