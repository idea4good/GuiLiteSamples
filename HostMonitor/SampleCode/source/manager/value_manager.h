#ifndef _VALUE_H_
#define _VALUE_H_

typedef enum e_digit
{
	DIGIT_0,
	DIGIT_1,
	DIGIT_2,
	DIGIT_3,
	DIGIT_4
}E_DIGIT;

typedef enum
{
	VALUE_START,

	VALUE_HR = VALUE_START,
	VALUE_PVCs,
	VALUE_ST_II,
	
	VALUE_SPO2,
	VALUE_PR,

	VALUE_RESP,

	VALUE_TEMP_T1,
	VALUE_TEMP_T2,
	VALUE_TEMP_TD,
		
	VALUE_NIBP_SYS,
	VALUE_NIBP_MEAN,
	VALUE_NIBP_DIA,

	VALUE_MAX
}E_VALUE_TYPE;

typedef struct struct_data_info
{
	E_VALUE_TYPE id;
	short value;
	short digit;
}VALUE_INFO;

class c_value_manager
{
public:
	int save_value(unsigned int id, short value);
	void get_value(unsigned int id, short &value);
	short get_value(unsigned int id);
	short get_real_data_digit(unsigned int id){return ms_value_info[id].digit;}
	static c_value_manager* get_instance()
	{
		static c_value_manager s_the_value_manager;
		return &s_the_value_manager;
	}
private:
	static VALUE_INFO ms_value_info[VALUE_MAX];
	c_value_manager(){};
	c_value_manager(const c_value_manager&);
	~c_value_manager(){}
};

#endif
