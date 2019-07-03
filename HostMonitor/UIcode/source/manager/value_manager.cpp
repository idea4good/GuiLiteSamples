#include "../core_include/api.h"
#include <string.h>
#include "value_manager.h"

VALUE_INFO c_value_manager::ms_value_info[VALUE_MAX] = 
{
	{VALUE_HR,		0},
	{VALUE_PVCs,	0},
	{VALUE_ST_II,	0,	DIGIT_2},

	{VALUE_SPO2,	0},
	{VALUE_PR,		0},

	{VALUE_RESP,	0},

	{VALUE_TEMP_T1, 0,	DIGIT_1	},
	{VALUE_TEMP_T2, 0,	DIGIT_1	},
	{VALUE_TEMP_TD, 0,	DIGIT_1	},

	{VALUE_NIBP_SYS,    0},
	{VALUE_NIBP_MEAN,   0},
	{VALUE_NIBP_DIA,    0}
};

int c_value_manager::save_value(unsigned int id, short value)
{
	if (ms_value_info[id].id != id)
	{
		ASSERT(false);
		return -1;
	}

	if (id >= VALUE_MAX)
	{
		return -1;
	}
	ms_value_info[id].value = value;
	return 1;
}

void c_value_manager::get_value(unsigned int id, short &value)
{
	value = ms_value_info[id].value;
}

short c_value_manager::get_value(unsigned int id)
{
	return ms_value_info[id].value;
}