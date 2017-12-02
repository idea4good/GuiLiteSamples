#include "core_include/api.h"
#include <string.h>
#include "value_manager.h"

VALUE_INFO c_value_manager::ms_value_info[VALUE_MAX] = 
{
	{VALUE_HR,		XXX},
	{VALUE_PVCs,	XXX},
	{VALUE_ST_II,	XXX,	DIGIT_2},
	{VALUE_ST_I,	XXX,	DIGIT_2},
	{VALUE_ST_III,	XXX,	DIGIT_2},
	{VALUE_ST_AVR,	XXX,	DIGIT_2},
	{VALUE_ST_AVL,	XXX,	DIGIT_2},
	{VALUE_ST_AVF,	XXX,	DIGIT_2},
	{VALUE_ST_V1,	XXX,	DIGIT_2},

	{VALUE_SPO2,	XXX},
	{VALUE_PR,		XXX},

	{VALUE_RESP,	XXX},

	{VALUE_TEMP_T1, XXX,	DIGIT_1	},
	{VALUE_TEMP_T2, XXX,	DIGIT_1	},
	{VALUE_TEMP_TD, XXX,	DIGIT_1	},

	{VALUE_NIBP_SYS,    XXX},
	{VALUE_NIBP_MEAN,   XXX},
	{VALUE_NIBP_DIA,    XXX}
};

int c_value_manager::save_value(unsigned int id, short value)
{
	if (ms_value_info[id].id != id)
	{
		ASSERT(FALSE);
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