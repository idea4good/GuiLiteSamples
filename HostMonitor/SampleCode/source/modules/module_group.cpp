#include "../core_include/cmd_target.h"
#include "../core_include/resource.h"
#include "../source/manager/wave_manager.h"
#include "../source/manager/value_manager.h"
#include "../modules/demo_module.h"
#include "module_group.h"

static void parse_your_data(void* data, int length);
static bool is_demo_mode = true;

//Non-reentrant function, should be protected by metux
void on_receive_data(void* data, int length)
{
	if (length > 0)
	{//Turn demo off while data detected. restart demo by reboot APP.
		is_demo_mode = false;
	}

	if (is_demo_mode)
	{
		return c_demo_module::get_instance()->unpackage();
	}
	
	if (data == 0 || length <= 0)
	{
		return;
	}
	parse_your_data(data, length);
}

static void parse_your_data(void* data, int length)
{
	unsigned char* tmp_data = (unsigned char*)data;
	c_wave_manage* wave_manager = c_wave_manage::get_instance();
	for (int i = 0; i < length; i++)
	{
		wave_manager->save_wave_data(WAVE_ECG1, *tmp_data);	//I
		wave_manager->save_wave_data(WAVE_ECG2, *tmp_data);	//II
		wave_manager->save_wave_data(WAVE_ECG3, *tmp_data);	//III
		wave_manager->save_wave_data(WAVE_ECG4, *tmp_data);	//AVR
		wave_manager->save_wave_data(WAVE_ECG5, *tmp_data);	//AVL
		wave_manager->save_wave_data(WAVE_ECG6, *tmp_data);	//AVR
		wave_manager->save_wave_data(WAVE_ECG7, *tmp_data);	//V

		wave_manager->save_wave_data(WAVE_SPO2, *tmp_data);	//SPO2
		wave_manager->save_wave_data(WAVE_RESP, *tmp_data);	//RESP

		tmp_data++;
	}
}