#ifndef __CFG_CTRLID_H__
#define __CFG_CTRLID_H__

typedef enum e_ctrlid
{
	ID_NULL,

	ID_ROOT,
	ID_TOP_BAR,
	ID_PAGE_GROUP,
	ID_PAGE_MAIN,
	ID_PAGE_ECG_7WAVE,
	ID_PAGE_TREND,
	ID_PAGE_CONFIG,

	/****************************************
	*			top info
	****************************************/
	ID_PATIENT_VIEW_ID,
	ID_TOP_BAR_TIME_ID,

	/****************************************
	*  			main slide - value
	****************************************/
	ID_ECG_VALUE_VIEW,
	ID_SPO2_VALUE_VIEW,
	ID_RESP_VALUE_VIEW,
	ID_NIBP_VALUE_VIEW,
	ID_NIBP_LIST_VALUE_VIEW,
	ID_TEMP_VALUE_VIEW,

	//ECG
	ID_ECG_VIEW_HR_VALUE,
	ID_ECG_VIEW_PVCs_VALUE,
	ID_ECG_VIEW_STII_VALUE,

	//SPO2
	ID_SPO2_VIEW_SPO2_VALUE,

	//PR
	ID_SPO2_VIEW_PR_VALUE,

	//RESP
	ID_RESP_VIEW_RR_VALUE,

	//TEMP
	ID_TEMP_VIEW_T1_VALUE,
	ID_TEMP_VIEW_T2_VALUE,
	ID_TEMP_VIEW_TD_VALUE,

	//NIBP
	ID_NIBP_VIEW,
	ID_NIBP_VIEW_SYS_VALUE,
	ID_NIBP_VIEW_DIA_VALUE,
	ID_NIBP_VIEW_MEAN_VALUE,
	ID_NIBP_LIST_VIEW_TABLE,
	/****************************************
	*  			main slide - wave
	****************************************/
	ID_MAIN_PAGE_ECG_WAVE,
	ID_MAIN_PAGE_SPO2_WAVE,
	ID_MAIN_PAGE_RESP_WAVE,

	ID_MAIN_SCREEN_ECG_WAVE_CTRL,
	ID_MAIN_SCREEN_SPO2_WAVE_CTRL,
	ID_MAIN_SCREEN_RESP_WAVE_CTRL,
	
	/****************************************
	*   		ecg 7 slide
	****************************************/
	ID_ECG_FULL_SCREEN_VIEW_ID,
	ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE1,
	ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE2,
	ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE3,
	ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE4,
	ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE5,
	ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE6,
	ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE7,
	
	/****************************************
	*  			trend slide
	****************************************/
	ID_TREND_SCREEN_TREND,
	ID_TREND_SCREEN_TABLE_CTRL,
	ID_TREND_SCREEN_VITAL_TREND_CTRL,
	ID_TREND_SCREEN_PRESSURE_CTRL,
	ID_TREND_SCREEN_TIME_SCALE_BAR_CTRL,

	/****************************************
	*   		Mini values
	****************************************/
	ID_MINI_VALUE_VIEW_ID,
	ID_MINI_VALUE_VIEW_HR_VALUE,
	ID_MINI_VALUE_VIEW_SPO2_VALUE,
	ID_MINI_VALUE_VIEW_RESP_VALUE,

	/****************************************
	*   		Mini waves
	****************************************/
	ID_MINI_WAV_VIEW_ID,
	ID_MINI_WAV_VIEW_ECG_WAVE,
	ID_MINI_WAV_VIEW_SPO2_WAVE,
	ID_MINI_WAV_VIEW_RESP_WAVE,

	/****************************************
	*   			dialog
	****************************************/
	//patient setup dialog
	IDD_SETUP_DLG,
	ID_SETUP_DLG_EDIT_FIRST_NAME,
	ID_SETUP_DLG_EDIT_SECOND_NAME,
	ID_SETUP_DLG_LB_PATIENT_TYPE,
	ID_SETUP_DLG_LB_SEX,
	ID_SETUP_DLG_EDIT_HEIGHT,
	ID_SETUP_DLG_EDIT_WEIGHT,
	ID_SETUP_DLG_SB_BIRTHDAY_YEAR,
	ID_SETUP_DLG_SB_BIRTHDAY_MONTH,
	ID_SETUP_DLG_SB_BIRTHDAY_DAY,
	ID_SETUP_DLG_SB_ADMISSION_YEAR,
	ID_SETUP_DLG_SB_ADMISSION_MONTH,
	ID_SETUP_DLG_SB_ADMISSION_DAY,
	ID_SETUP_DLG_LB_PACED,
	ID_SETUP_DLG_EDIT_CASE,
	ID_SETUP_DLG_LB_BLOOD_TYPE,
	ID_SETUP_DLG_SP_DEPARTMENT,
	ID_SETUP_DLG_SP_BED_NO,

	//about
	IDD_ABOUT_DLG
}E_CTRLID;

#endif
