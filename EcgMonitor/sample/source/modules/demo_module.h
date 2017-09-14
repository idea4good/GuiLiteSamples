#ifndef DEMO_MODULE_H_
#define DEMO_MODULE_H_

#define  DEMO_ECG_WAVE_SPEED	250	//250 wave data per second.
#define  DEMO_RESP_WAVE_SPEED  	125 //125 wave data per second.
#define  DEMO_SPO2_WAVE_SPEED   60  //60 wave data per second.

class c_demo_module
{
public:
	void unpackage();
	static c_demo_module* get_instance()
	{
		static c_demo_module s_the_instance;
		return &s_the_instance;
	}
private:
	void unpack_ecg();
	void unpack_spo2();
	void unpack_resp();
	unsigned char  m_ecg_write_len_array[64];
	unsigned char  m_spo2_write_len_array[64];
	unsigned char  m_resp_write_len_array[64];
	int m_ecg_sample_rate;
	int m_spo2_sample_rate;
	int m_resp_sample_rate;
	void make_write_len_array();
	c_demo_module();
	c_demo_module(const c_demo_module &module);
	c_demo_module& operator=(const c_demo_module &module);
};

#endif /* DEMO_MODULE_H_ */
