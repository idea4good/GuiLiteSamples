#ifndef _VALUE_VIEW_H_
#define _VALUE_VIEW_H_

#define PARAM_VIEW_NUM		120

class c_value_view : public c_wnd
{
public:
	static void refresh_group_value(void* ptmr, void* parg);
protected:
	static int register_value_view(c_value_view* p_pm_view);
	void refresh_value(bool flash_or_not, unsigned int flash_color);
private:
	static c_value_view* ms_param_view_group[PARAM_VIEW_NUM];
	static bool ms_is_has_timer;
};

#endif
