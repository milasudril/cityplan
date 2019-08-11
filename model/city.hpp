//@	{
//@	 "targets":[{"name":"city.hpp","type":"include"}]
//@	}

#ifndef CITYPLAN_CITY_HPP
#define CITYPLAN_CITY_HPP

#include "geom/rectangle.hpp"

#include <vector>
#include <random>

#include <cassert>

namespace Cityplan
	{
	using Block = Rectangle;  // For now, should be a distinct type

	class City
		{
		public:
			City& append(Block const& block) &
				{
				m_blocks.push_back(block);
				return *this;
				}

			City&& append(Block const& block) &&
				{
				m_blocks.push_back(block);
				return std::move(*this);
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

	 // TODO: Should be moved to "Block" class
	template<class Rng>
	auto getSplitDirection(Block const& block, Rng& rng)
		{
		if(width(block) < height(block))
			{return SplitDirection::Horizontal;}
		if(width(block) > height(block))
			{return SplitDirection::Vertical;}
		std::uniform_int_distribution<int> dirSelector{0, 1};
		return dirSelector(rng) == 0? SplitDirection::Horizontal : SplitDirection::Vertical;
		}

	template<class Rng, class AcceptFun>
	bool makeNewBlock(City& city, Rng& rng, AcceptFun&& blockAccepted)
		{
		assert(city.blockCount() != 0);
		std::uniform_int_distribution<size_t> blockSelector{0, city.blockCount() - 1};
		auto block_index = blockSelector(rng);
		auto& block = city.getBlock(block_index);
		auto result = split(block, getSplitDirection(block, rng));
		if(blockAccepted(result))
			{
			city.update(block_index, result.first).append(result.second);
			return true;
			}
		return false;
		}
	}

#endif
