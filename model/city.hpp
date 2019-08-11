//@	{
//@	 "targets":[{"name":"city.hpp","type":"include"}]
//@	}

#ifndef CITYPLAN_CITY_HPP
#define CITYPLAN_CITY_HPP

#include "geom/rectangle.hpp"

#include <vector>
#include <random>

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

	template<class Rng>
	auto getSplitDirection(Block const& block, Rng& rng)
		{
		if(width(block) < height(block))
			{return SplitMode::Horizontal;}
		if(width(block) > height(block)
			{return SplitMode::Vertical;}
		std::uniform_int_distribution<int> dirSelector{0, 1};
		return dirSelector(rng) == 0? SplitMode::Horizontal : SplitMode::Vertical;
		}

	template<class Rng>
	void makeNewBlock(City& city Rng& rng)
		{
		std::uniform_int_distribution<size_t> blockSelector{0, city.size() - 1};
		auto block_index = blockSelector(rng);
		auto& block = city.getBlock(block_index);
		auto result = split(block, getSplitDirection(block, rng));
		city.update(block_index, result.first).append(result.second);
		}
	}

#endif
