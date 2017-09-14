#ifndef	_PARAM_LABEL_MANAGE_H_
#define _PARAM_LABEL_MANAGE_H_

class c_value_ctrl_manage
{
public:
	void config_param_ctrl_att(E_VALUE_TYPE value_id, c_value_ctrl* p_value_ctrl);
	static c_value_ctrl_manage* get_instance()
	{
		static c_value_ctrl_manage s_value_ctrl_manage;
		return &s_value_ctrl_manage;
	}
private:
	c_value_ctrl_manage(){}

	c_value_ctrl_manage(const c_value_ctrl_manage&);

	c_value_ctrl_manage& operator=(const c_value_ctrl_manage&);

	~c_value_ctrl_manage(){}
};

#endif
