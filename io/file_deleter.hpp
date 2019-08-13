//@	{
//@	 "targets":[{"name":"file_deleter.hpp","type":"include"}]
//@ }

#ifndef CITYPLAN_FILEDELETER_HPP
#define CITYPLAN_FILEDELETER_HPP

#include <cstdio>

namespace Cityplan
	{
	struct FileDeleter
		{
		void operator()(FILE* f)
			{fclose(f);}
		};
	}

#endif