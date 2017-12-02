#include "core_include/api.h"
#include "core_include/msg.h"
#include "core_include/audio.h"
#include "../include/msg_id.h"
#include "core_include/cmd_target.h"
#include "../source/manager/wave_manager.h"
#include "../source/manager/value_manager.h"
#include <string.h>
#include <stdlib.h>
#include "demo_module.h"

//DEMO wave
static const unsigned char	s_ecg_i_data[] =
{
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7E, 0x7F, 0x81, 0x83, 0x83, 0x84, 0x85, 0x86,
	0x87, 0x87, 0x87, 0x87, 0x86, 0x85, 0x84, 0x83,

	0x82, 0x80, 0x7F, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7C, 0x7B, 0x7A, 0x78, 0x76, 0x79, 0x85,
	0x90, 0x9B, 0xA5, 0xB0, 0xB4, 0xAA, 0x9F, 0x94,
	0x89, 0x7E, 0x76, 0x77, 0x79, 0x7A, 0x7C, 0x7C,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7E, 0x80, 0x80, 0x82, 0x83, 0x84, 0x86, 0x87,
	0x88, 0x89, 0x8A, 0x8B, 0x8B, 0x8C, 0x8D, 0x8E,
	0x8F, 0x8F, 0x8F, 0x90, 0x90, 0x91, 0x90, 0x90,
	0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x89, 0x89, 0x88,
	0x86, 0x85, 0x83, 0x82, 0x80, 0x7F, 0x7E, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D
};

static const unsigned char	s_ecg_ii_data[] =
{
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7E, 0x7E, 0x7F, 0x81, 0x81, 0x82, 0x82, 0x83,
	0x84, 0x84, 0x84, 0x84, 0x83, 0x82, 0x82, 0x81,

	0x81, 0x7F, 0x7F, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7C, 0x7B, 0x7A, 0x79, 0x7A, 0x82,
	0x89, 0x91, 0x98, 0x9F, 0xA2, 0x9B, 0x94, 0x8C,
	0x85, 0x7E, 0x78, 0x79, 0x7A, 0x7B, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7E, 0x7F, 0x7F, 0x81, 0x81, 0x82, 0x83, 0x84,
	0x84, 0x85, 0x86, 0x87, 0x87, 0x87, 0x88, 0x88,
	0x89, 0x89, 0x89, 0x8A, 0x8A, 0x8A, 0x8A, 0x89,
	0x89, 0x88, 0x88, 0x87, 0x87, 0x85, 0x85, 0x85,
	0x83, 0x82, 0x81, 0x81, 0x7F, 0x7E, 0x7E, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D
};

static const unsigned char	s_ecg_v_data[] =
{
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x82, 0x82, 0x82, 0x82, 0x83, 0x83,
	0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x81, 0x81,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x83, 0x83,
	0x88, 0x88, 0x87, 0x87, 0x7d, 0x7d, 0x6c, 0x6c,
	0x65, 0x65, 0x6d, 0x6d, 0x7d, 0x7d, 0x81, 0x81,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x81,
	0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
	0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x82, 0x82,
	0x81, 0x81, 0x82, 0x82, 0x82, 0x82, 0x83, 0x83,
	0x83, 0x83, 0x83, 0x83, 0x82, 0x82, 0x82, 0x82,
	0x82, 0x82, 0x81, 0x81, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x7f, 0x7f, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80
};

const char s_spo2_data[] =
{
	0x21, 0x22, 0x23, 0x22, 0x21, 0x20, 0x1E, 0x1C,
	0x1B, 0x19, 0x18, 0x16, 0x14, 0x12, 0x11, 0x10,
	0x0F, 0x0D, 0x0C, 0x0A, 0x09, 0x07, 0x06, 0x05,
	0x04, 0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x06, 0x0E, 0x18, 0x23, 0x2D, 0x37, 0x40,
	0x49, 0x51, 0x57, 0x5A, 0x5A, 0x59, 0x55, 0x50,
	0x49, 0x42, 0x3B, 0x34, 0x2F, 0x29, 0x24, 0x20,
	0x1F, 0x1e, 0x1d, 0x1f
};

unsigned char s_resp_data[] =
{
	0x53, 0x53, 0x53, 0x52, 0x53, 0x53, 0x52, 0x52,
	0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52,
	0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53,
	0x53, 0x54, 0x54, 0x54, 0x54, 0x55, 0x55, 0x55,
	0x55, 0x56, 0x57, 0x57, 0x58, 0x59, 0x5A, 0x5B,
	0x5C, 0x5D, 0x5F, 0x60, 0x62, 0x64, 0x66, 0x68,
	0x6A, 0x6C, 0x6E, 0x70, 0x72, 0x75, 0x77, 0x79,
	0x7B, 0x7D, 0x80, 0x82, 0x84, 0x87, 0x89, 0x8B,
	0x8D, 0x8F, 0x91, 0x93, 0x94, 0x96, 0x97, 0x98,
	0x9A, 0x9B, 0x9C, 0x9C, 0x9D, 0x9E, 0x9E, 0x9E,
	0x9E, 0x9F, 0x9F, 0x9F, 0x9F, 0x9F, 0x9F, 0x9F,
	0x9F, 0x9E, 0x9F, 0x9E, 0x9E, 0x9E, 0x9E, 0x9E,
	0x9E, 0x9E, 0x9D, 0x9D, 0x9D, 0x9D, 0x9C, 0x9C,
	0x9C, 0x9C, 0x9B, 0x9B, 0x9A, 0x9A, 0x9A, 0x99,
	0x99, 0x98, 0x98, 0x98, 0x97, 0x97, 0x96, 0x96,
	0x96, 0x95, 0x95, 0x94, 0x94, 0x93, 0x93, 0x92,

	0x92, 0x91, 0x91, 0x90, 0x90, 0x8F, 0x8F, 0x8E,
	0x8E, 0x8D, 0x8D, 0x8C, 0x8B, 0x8B, 0x8A, 0x8A,
	0x89, 0x89, 0x88, 0x88, 0x87, 0x87, 0x86, 0x85,
	0x85, 0x85, 0x84, 0x83, 0x83, 0x82, 0x82, 0x81,
	0x81, 0x80, 0x7F, 0x7F, 0x7E, 0x7D, 0x7D, 0x7C,
	0x7B, 0x7B, 0x7A, 0x7A, 0x79, 0x78, 0x77, 0x77,
	0x76, 0x75, 0x74, 0x74, 0x73, 0x72, 0x71, 0x71,
	0x70, 0x6F, 0x6F, 0x6E, 0x6D, 0x6D, 0x6C, 0x6B,
	0x6A, 0x6A, 0x69, 0x69, 0x68, 0x67, 0x66, 0x66,
	0x65, 0x65, 0x64, 0x64, 0x63, 0x63, 0x62, 0x62,
	0x61, 0x61, 0x61, 0x60, 0x60, 0x5F, 0x5F, 0x5F,
	0x5E, 0x5E, 0x5D, 0x5D, 0x5D, 0x5C, 0x5C, 0x5C,
	0x5B, 0x5B, 0x5B, 0x5B, 0x5B, 0x5A, 0x5A, 0x5A,
	0x59, 0x59, 0x59, 0x58, 0x58, 0x57, 0x57, 0x57,
	0x56, 0x56, 0x55, 0x55, 0x55, 0x55, 0x54, 0x54,
	0x54, 0x54, 0x54, 0x54, 0x53, 0x54, 0x53, 0x53,
};

c_demo_module::c_demo_module()
{
	//init_trend_data();
	m_ecg_sample_rate = DEMO_ECG_WAVE_SPEED;
	m_spo2_sample_rate = DEMO_SPO2_WAVE_SPEED;
	m_resp_sample_rate = DEMO_RESP_WAVE_SPEED;
	make_write_len_array();
}

void c_demo_module::make_write_len_array()
{
	int unpack_times_per_second = 1000 / REAL_TIME_TASK_CYCLE_MS;

	memset(m_ecg_write_len_array, 0, sizeof(m_ecg_write_len_array));
	memset(m_spo2_write_len_array, 0, sizeof(m_spo2_write_len_array));
	memset(m_resp_write_len_array, 0, sizeof(m_resp_write_len_array));

	for (unsigned int i = 1; i < sizeof(m_ecg_write_len_array) + 1; i++)
	{
		m_ecg_write_len_array[i-1] = m_ecg_sample_rate * i / unpack_times_per_second - m_ecg_sample_rate * (i-1) / unpack_times_per_second;
	}

	for (unsigned int i = 1; i < sizeof(m_spo2_write_len_array) + 1; i++)
	{
		m_spo2_write_len_array[i-1] = m_spo2_sample_rate * i / unpack_times_per_second - m_spo2_sample_rate * (i-1) / unpack_times_per_second;
	}

	for (unsigned int i = 1; i < sizeof(m_resp_write_len_array) + 1; i++)
	{
		m_resp_write_len_array[i-1] = m_resp_sample_rate * i / unpack_times_per_second - m_resp_sample_rate * (i-1) / unpack_times_per_second;
	}
}

void c_demo_module::unpackage()
{
	unpack_ecg();
	unpack_spo2();
	unpack_resp();

	int delta = (rand() % 5);
	c_value_manager::get_instance()->save_value(VALUE_TEMP_T1, 368 + delta);
	c_value_manager::get_instance()->save_value(VALUE_TEMP_T2, 365 + delta);
	c_value_manager::get_instance()->save_value(VALUE_TEMP_TD, 3);

	delta = (rand() % 20);
	c_value_manager::get_instance()->save_value(VALUE_NIBP_SYS,  120 + delta);
	c_value_manager::get_instance()->save_value(VALUE_NIBP_MEAN, 90 + delta);
	c_value_manager::get_instance()->save_value(VALUE_NIBP_DIA,  80 + delta);
}

void c_demo_module::unpack_ecg()
{
	static int step_index;
	static int sample_index;

	c_value_manager::get_instance()->save_value(VALUE_HR, 60 + (rand() % 50));
	c_value_manager::get_instance()->save_value(VALUE_PVCs, 0);
	c_value_manager::get_instance()->save_value(VALUE_ST_II, 0);
	c_value_manager::get_instance()->save_value(VALUE_ST_I, 0);
	c_value_manager::get_instance()->save_value(VALUE_ST_III, 0);
	c_value_manager::get_instance()->save_value(VALUE_ST_AVF, 0);
	c_value_manager::get_instance()->save_value(VALUE_ST_AVR, 0);
	c_value_manager::get_instance()->save_value(VALUE_ST_AVL, 0);
	c_value_manager::get_instance()->save_value(VALUE_ST_V1, 0);

	short temp1,temp2;
	short demo_iii,demo_avr,demo_avl,demo_avf;

	int cnt_per_step = m_ecg_write_len_array[step_index++];
	step_index %= sizeof(m_ecg_write_len_array);

	for (int i = 0; i < cnt_per_step; i++)
	{
		temp2 = s_ecg_i_data[sample_index] - 0x80;
		temp1 = s_ecg_ii_data[sample_index] - 0x80;
		demo_iii = (temp2-temp1) + 0x80;
		demo_avr = (temp2+temp1) / 2 + 0x80;
		demo_avl = temp1 - temp2 / 2 + 0x80;
		demo_avf = temp2 - temp1 / 2 + 0x80;

		if(demo_avr < 0x80)
		{
			demo_avr = (0x80 - demo_avr) + 0x80;
		}
		else if(demo_avr > 0x80)
		{
			demo_avr = 0x80 - (demo_avr - 0x80);
		}

		c_wave_manage::get_instance()->save_curve_data(WAVE_ECG1, s_ecg_ii_data[sample_index]); //I
		c_wave_manage::get_instance()->save_curve_data(WAVE_ECG2, s_ecg_i_data[sample_index]);  //II
		c_wave_manage::get_instance()->save_curve_data(WAVE_ECG3, demo_iii);					//III
		c_wave_manage::get_instance()->save_curve_data(WAVE_ECG4, demo_avr);					//AVR
		c_wave_manage::get_instance()->save_curve_data(WAVE_ECG5, demo_avl);					//AVL
		c_wave_manage::get_instance()->save_curve_data(WAVE_ECG6, demo_avf);					//AVR
		c_wave_manage::get_instance()->save_curve_data(WAVE_ECG7, s_ecg_v_data[sample_index]);  //V
		
		if (s_ecg_ii_data[sample_index] == 0xA2)
		{
			c_audio::play(AUDIO_HEART_BEAT);
		}

		sample_index++;
		if (sample_index == sizeof(s_ecg_ii_data))
		{
			sample_index = 0;
		}
	}
}

void c_demo_module::unpack_spo2()
{
	static int step_index;
	static unsigned int sample_index;

	c_value_manager::get_instance()->save_value(VALUE_PR, 60);
	c_value_manager::get_instance()->save_value(VALUE_SPO2, 98 + (rand() % 2));

	int cnt_per_step = m_spo2_write_len_array[step_index++];
	step_index %= sizeof(m_spo2_write_len_array);
	for (int i = 0; i < cnt_per_step; i++ )
	{
		c_wave_manage::get_instance()->save_curve_data(WAVE_SPO2, s_spo2_data[sample_index]);
		sample_index++;
		if (sample_index >= sizeof(s_spo2_data))
		{
			sample_index = 0;
		}
	}
}

void c_demo_module::unpack_resp()
{
	c_value_manager::get_instance()->save_value(VALUE_RESP, 30 + (rand() % 20));

	static int step_index;
	static unsigned int sample_index;

	int cnt_per_step = m_resp_write_len_array[step_index++];
	step_index %= sizeof(m_resp_write_len_array);

	for (int i = 0; i < cnt_per_step; i++ )
	{
		c_wave_manage::get_instance()->save_curve_data(WAVE_RESP,s_resp_data[sample_index]);
		sample_index++;
		if (sample_index >= sizeof(s_resp_data))
		{
			sample_index = 0;
		}
	}
}
