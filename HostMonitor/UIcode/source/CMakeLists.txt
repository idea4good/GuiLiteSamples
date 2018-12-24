FILE(GLOB MANAGER manager/*.cpp)
FILE(GLOB MODULES modules/*.cpp)
FILE(GLOB RESOURCE resource/font/*.cpp
	resource/bitmap/*.cpp
	resource/shape/*.cpp
	resource/*.cpp)
FILE(GLOB START start/*.cpp)
FILE(GLOB DATA data/*.cpp data/*.c)
FILE(GLOB UI_CTRL_EX ui_ctrl_ex/*.cpp)
FILE(GLOB UI_TREE ui_layout/*.cpp

	ui_layout/Dialog/about/*.cpp
	ui_layout/Dialog/patient_setup/*.cpp

	ui_layout/View/*.cpp
	ui_layout/View/ecg_7wave/*.cpp
	ui_layout/View/ecg_value/*.cpp
	ui_layout/View/ecg_wave/*.cpp
	ui_layout/View/nibp_list/*.cpp
	ui_layout/View/nibp_value/*.cpp
	ui_layout/View/resp_value/*.cpp
	ui_layout/View/resp_wave/*.cpp
	ui_layout/View/spo2_value/*.cpp
	ui_layout/View/spo2_wave/*.cpp
	ui_layout/View/temp_value/*.cpp
	ui_layout/View/top_bar/*.cpp
	ui_layout/View/top_bar/patient/*.cpp
	ui_layout/View/trend/*.cpp

	ui_layout/ViewMini/trend/*.cpp
	ui_layout/ViewMini/wav/*.cpp
	ui_layout/ViewMini/value/*.cpp
)

ADD_LIBRARY(UIcode
				${MANAGER}
				${MODULES}
				${RESOURCE}
				${START}
				${DATA}
				${UI_CTRL_EX}
				${UI_TREE})
