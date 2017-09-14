#ifndef _SERIAL_H_
#define _SERIAL_H_

class c_data_source : public c_cmd_target
{
public:
	void read_serial(void);
public:
	static c_data_source* get_instance()
	{
		static c_data_source s_the_serial_group;
		return &s_the_serial_group;
	}
private:
	c_data_source(){};
	c_data_source(const c_data_source&);
	~c_data_source(){};
};

#endif
