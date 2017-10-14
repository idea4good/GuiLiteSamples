FILE(GLOB MANAGER manager/*.cpp)
FILE(GLOB MODULES modules/*.cpp)
FILE(GLOB RESOURCE resource/font/*.cpp
	resource/bitmap/*.cpp)
FILE(GLOB START start/*.cpp)
FILE(GLOB DATA data/*.cpp data/*.c)
FILE(GLOB UI_CTRL_EX ui_ctrl_ex/*.cpp)
FILE(GLOB UI_TREE ui_tree/*.cpp

	ui_tree/Dialog/about/*.cpp
	ui_tree/Dialog/patient_setup/*.cpp

	ui_tree/View/*.cpp
	ui_tree/View/ecg_7wave/*.cpp
	ui_tree/View/ecg_value/*.cpp
	ui_tree/View/ecg_wave/*.cpp
	ui_tree/View/nibp_list/*.cpp
	ui_tree/View/nibp_value/*.cpp
	ui_tree/View/resp_value/*.cpp
	ui_tree/View/resp_wave/*.cpp
	ui_tree/View/spo2_value/*.cpp
	ui_tree/View/spo2_wave/*.cpp
	ui_tree/View/temp_value/*.cpp
	ui_tree/View/top_bar/*.cpp
	ui_tree/View/top_bar/patient/*.cpp
	ui_tree/View/trend/*.cpp

	ui_tree/ViewMini/trend/*.cpp
	ui_tree/ViewMini/wav/*.cpp
	ui_tree/ViewMini/value/*.cpp
)

ADD_LIBRARY(sample
				${MANAGER}
				${MODULES}
				${RESOURCE}
				${START}
				${DATA}
				${UI_CTRL_EX}
				${UI_TREE})
				
TARGET_LINK_LIBRARIES(sample core gui)