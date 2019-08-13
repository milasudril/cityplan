//@	{
//@	 "targets":[{"name":"load_rects.o","type":"object"}]
//@	}

#include "load_rects.hpp"

#include <string>

using namespace Cityplan;

std::vector<Rectangle> Cityplan::loadRects(FILE* src)
	{
	std::vector<Rectangle> ret;
	std::string buffer;
	Position pos;
	Dimension dim;
	size_t k = 0;
	enum class State : int {Normal, Whitespace};
	auto state_current = State::Normal;
	while(true)
		{
		auto ch_in = getc(src);
		switch(state_current)
			{
			case State::Normal:
				if((ch_in>=0 && ch_in<=' ') || ch_in == EOF)
					{
					switch(k % 4)
						{
						case 0:
							pos.x(stof(buffer));
							break;
						case 1:
							pos.y(stof(buffer));
							break;
						case 2:
							dim.width(stof(buffer));
							break;
						case 3:
							dim.height(stof(buffer));
							ret.push_back(Rectangle{pos, dim});
							break;
						}
					if(ch_in == EOF)
						{return ret;}
					buffer.clear();

					state_current = State::Whitespace;
					++k;
					}
				else
					{buffer+=ch_in;}
				break;
			case State::Whitespace:
				if(ch_in == EOF)
					{return ret;}

				if(!(ch_in>= 0 && ch_in<=' '))
					{
					state_current = State::Normal;
					buffer+=ch_in;
					}

				break;
			}
		}
	}