#include "core_include/api.h"
#include "core_include/cmd_target.h"
#include "../source/manager/wave_manager.h"
#include "../modules/demo_module.h"
#include "data_source.h"

void c_data_source::read_serial(void)
{
	c_demo_module::get_instance()->unpackage();
}
