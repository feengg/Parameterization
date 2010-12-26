#ifndef HYWEI_PARAMCHART_H_
#define HYWEI_PARAMCHART_H_

#include "Parameterization.h"

namespace PARAM
{
	class ParamChart
	{
	public:
        ParamChart(int patch_id=-1)
            :m_patch_id(patch_id), m_valid_range( std::make_pair(0.0, 1.0) ) {}
        
        ~ParamChart(){}

	public:
		bool InValidRangle(const ParamCoord& param_coord) const
		{
			return GreaterEqual(param_coord.s_coord, m_valid_range.first, LARGE_ZERO_EPSILON)
				&& LessEqual(param_coord.s_coord, m_valid_range.second, LARGE_ZERO_EPSILON)
				&& GreaterEqual(param_coord.t_coord, m_valid_range.first, LARGE_ZERO_EPSILON)
				&& LessEqual(param_coord.t_coord, m_valid_range.second, LARGE_ZERO_EPSILON);
		}

	public:
		int m_patch_id;
		std::vector<ParamCoord> m_conner_param_coord_array;		
		std::pair<double, double> m_valid_range;
	};

    typedef ParamChart QuadChart;
}

#endif
