//@	{
//@	 "targets":[{"name":"city.test","type":"application","autorun":1}]
//@	}

#undef NDEBUG

#include "city.hpp"

#include <cassert>

namespace
	{
	class DummyRng
		{
		public:
			using result_type = int;

			explicit DummyRng(bool val):m_val{val}{}

			int operator()() const
				{return static_cast<int>(m_val);}

			static constexpr int min()
				{return 0;}

			static constexpr int max()
				{return 1;}

			DummyRng& value(bool val)
				{
				m_val = val;
				return *this;
				}

		private:
			bool m_val;
		};
	}

namespace Test
	{
	void cityplanGetSplitDirectionWide()
		{
		Cityplan::Block a{Cityplan::Position{}.x(0).y(0), Cityplan::Dimension{}.width(2).height(1)};
		DummyRng rng{false};
		auto dir = getSplitDirection(a, rng);
		assert(dir == Cityplan::SplitDirection::Vertical);
		}

	void cityplanGetSplitDirectionTall()
		{
		Cityplan::Block a{Cityplan::Position{}.x(0).y(0), Cityplan::Dimension{}.width(1).height(2)};
		DummyRng rng{false};
		auto dir = getSplitDirection(a, rng);
		assert(dir == Cityplan::SplitDirection::Horizontal);
		}

	void cityplanGetSplitDirectionTie()
		{
		Cityplan::Block a{Cityplan::Position{}.x(0).y(0), Cityplan::Dimension{}.width(1).height(1)};

		DummyRng rng{false};
		auto dir_a = getSplitDirection(a, rng);

		rng.value(true);
		auto dir_b = getSplitDirection(a, rng);
		assert(dir_a != dir_b);
		}

	void cityplanMakeNewBlockAccept()
		{
		Cityplan::City c;
		c.append(Cityplan::Block
			{
			 Cityplan::Position{}.x(0).y(0)
			,Cityplan::Dimension{}.width(2).height(1)
			});

		assert(c.blockCount() == 1);
		DummyRng rng{false};
		auto res = makeNewBlock(c, rng, [](auto const&)
			{return true;});
		assert(res == true);
		assert(c.blockCount() == 2);
		}

	void cityplanMakeNewBlockReject()
		{
		Cityplan::City c;
		c.append(Cityplan::Block
			{
			 Cityplan::Position{}.x(0).y(0)
			,Cityplan::Dimension{}.width(1).height(1)
			});

		assert(c.blockCount() == 1);
		DummyRng rng{false};
		auto res = makeNewBlock(c, rng, [](auto const){return false;});
		assert(res == true);
		assert(c.blockCount() == 1);
		}
	}

int main()
	{
	Test::cityplanGetSplitDirectionWide();
	Test::cityplanGetSplitDirectionTall();
	Test::cityplanGetSplitDirectionTie();
	Test::cityplanMakeNewBlockAccept();
	}