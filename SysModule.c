#include <hardware/hardware.h>
#include <log/log.h>
#include "SysModule.h"

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "vman_ays"
#endif

/*
 * Get input timing information
 * @param data: ui_stream_config_t
 * @return Getresult [0: successfully, <0: failure]
 */
static int get_input_stream_config(struct sys_hal_module *module, ui_stream_config_t* data)
{
	return 0;
}

/*
 * Get input Interlaced status
 * @return int 1:Normal, 0: No Signal
 */
static int get_cur_signal_status(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Get input Interlaced status
 * @return int 1:I-Signal, 0:P-Signal
 */
static int get_cur_Source_Interlaced(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Get input signal type, DVI or HDMI
 * @return int 1:DVI, 0:HDMI
 */
static int get_cur_source_dvi_mode(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Get the hdcp encryption status of the input signal
 * @return int 1:encrypte, 0:no encrypte
 */
static int get_cur_source_hdcp_encrypted(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Get CEC status
 * @return CEC status, 0:OFF, 1:ON
 */
static int get_cec_enable(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set CEC status
 * @param value: 0:OFF, 1:ON
 * @return result [0: successfully, <0: failure]
 */
static int set_cec_enable(struct sys_hal_module *module, int value)
{
	return 0;
}

/*
 * Get ARC status
 * @return ARC status, 0:OFF, 1:ON
 */
static int get_arc_enable(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set ARC status
 * @param value: 0:OFF, 1:ON
 * @return result [0: successfully, <0: failure]
 */
static int set_arc_enable(struct sys_hal_module *module, int value)
{
	return 0;
}


/*
 * Get overscan value
 * @param data：overscan value
 * @return Getresult [0: successfully, <0: failure]
 */
static int get_overscan(struct sys_hal_module *module, ui_overscan_data_t *data)
{
	return 0;
}

/*
 * Set overscan value
 * @param data：overscan value
 * @return Getresult [0: successfully, <0: failure]
 */
static int set_overscan(struct sys_hal_module *module, ui_overscan_data_t data)
{
	return 0;
}

 /*
 * Set pattern
 * @param int red, int green, int blue: RGB, range[0-255]
 * @return result [0: successfully, <0: failure]
 */
static int set_screen_pattern(struct sys_hal_module *module, int red, int green, int blue)
{
	return 0;
}


 /*
 * Set half screen mode
 * @param value: 0:OFF, 1:ON
 * @return result [0: successfully, <0: failure]
 */
static int set_half_screen_mode(struct sys_hal_module *module, int value)
{
	return 0;
}

 /*
 * Get half screen mode
 * @param value: 0:OFF, 1:ON
 * @return result [0: successfully, <0: failure]
 */
static int get_half_screen_mode(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Get DCR status
 * @return status, range[0-1]
 */
int get_dcr_enable(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set DCR status
 * @param value: 0:OFF, 1:ON
 * @return result [0: successfully, <0: failure]
 */
int set_dcr_enable(struct sys_hal_module *module, int value)
{
	return 0;
}

/*
 * Get DBC MAX backlight
 * @return MAX backlight, range[0-100]
 */
int get_dbc_max_backlight(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set DBC MAX backlight
 * @param value: range[0-100]
 * @return result [0: successfully, <0: failure]
 */
int set_dbc_max_backlight(struct sys_hal_module *module, int value)
{
	return 0;
}

/*
 * Get DBC MIN backlight
 * @return MIN backlight, range[0-100]
 */
int get_dbc_min_backlight(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set DBC MIN backlight
 * @param value: range[0-100]
 * @return result [0: successfully, <0: failure]
 */
int set_dbc_min_backlight(struct sys_hal_module *module, int value)
{
	return 0;
}

/*
 * Get DBC backlight step time(ms)
 * @return setp time, range[0-1000]
 */
int get_dbc_step_time(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set DBC backlight step time(ms)
 * @param value: range[0-1000]
 * @return result [0: successfully, <0: failure]
 */
int set_dbc_step_time(struct sys_hal_module *module, int value)
{
	return 0;
}

/*
 * Get DBC backlight step value
 * @return backlight step value, range[0-100]
 */
int get_dbc_step_value(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set DBC backlight step value
 * @param value: range[0-100]
 * @return result [0: successfully, <0: failure]
 */
int set_dbc_step_value(struct sys_hal_module *module, int value)
{
	return 0;
}

/*
 * Get DBC status
 * @return status, range[0-1]
 */
int get_dbc_enable(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set DBC status
 * @param value: 0:OFF, 1:ON
 * @return result [0: successfully, <0: failure]
 */
int set_dbc_enable(struct sys_hal_module *module, int value)
{
	return 0;
}

/*
 * Get panel partition(V-by-One)
 * @return panel partition, range[ui_panel_division_t]
 */
ui_panel_division_t get_panel_division(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set panel partition(V-by-One)
 * @param value: range[ui_panel_division_t]
 * @return result [0: successfully, <0: failure]
 */
int set_panel_division(struct sys_hal_module *module, ui_panel_division_t value)
{
	return 0;
}






/*
* Get VBO swing
* @return  VBO swing, range[0-255]
 */
int get_panel_swing(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set  VBO swing
 * @param value: range[0-255]
 * @return result [0: successfully, <0: failure]
 */
int set_panel_swing(struct sys_hal_module *module, int value)
{
	return 0;
}

/*
 * Get VBO preemphasis
 * @return  VBO preemphasis, range[0-255]
 */
int get_panel_preemphasis(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set  VBO preemphasis
 * @param value: range[0-255]
 * @return result [0: successfully, <0: failure]
 */
int set_panel_preemphasis(struct sys_hal_module *module, int value)
{
	return 0;
}

/*
 * Get freerun status
 * @return  freerun status, range[0-1]
 */
int get_panel_freerun(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set  freerun preemphasis
 * @param value: range[0-1]
 * @return result [0: successfully, <0: failure]
 */
int set_panel_freerun(struct sys_hal_module *module, int value)
{
	return 0;
}

/*
 * Get shake screen status
 * @return status, range[0-1]
 */
int get_shake_screen_mode(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set shake screen status
 * @param value: range[0-1]
 * @return result [0: successfully, <0: failure]
 */
int set_shake_screen_mode(struct sys_hal_module *module, int value)
{
	return 0;
}

/*
 * Get average brightness
 * @return average brightness, range[0-255]
 */
int get_average_brightness(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Get HDMI EDID
 * @return EDID, range[ui_edid_mode_t]
 */
ui_edid_mode_t get_hdmi_edid_mode(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set HDMI EDID
 * @param value: range[ui_edid_mode_t]
 * @return result [0: successfully, <0: failure]
 */
int set_hdmi_edid_mode(struct sys_hal_module *module, ui_edid_mode_t value)
{
	return 0;
}

/*
 * Get PC EDID
 * @return PC EDID, range[ui_edid_mode_t]
 */
ui_edid_mode_t get_pc_edid_mode(struct sys_hal_module *module)
{
	return 0;
}

/*
 * Set PC EDID
 * @param value: range[ui_edid_mode_t]
 * @return result [0: successfully, <0: failure]
 */
int set_pc_edid_mode(struct sys_hal_module *module, ui_edid_mode_t value)
{
	return 0;
}

static struct hw_module_methods_t sys_hal_module_methods =
{
	.open = NULL,
};

struct sys_hal_module HAL_MODULE_INFO_SYM =
{
    .common ={
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = SYS_HAL_MODULE_API_VERSION,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = SYS_HAL_HARDWARE_MODULE_ID,
        .name ="Default SYS HAL",
        .author = "The SYS Project",
        .methods = &sys_hal_module_methods,
   },
    .get_input_stream_config = get_input_stream_config,
    .get_cur_signal_status = get_cur_signal_status,
    .get_cur_Source_Interlaced = get_cur_Source_Interlaced,
    .get_cur_source_dvi_mode = get_cur_source_dvi_mode,
    .get_cur_source_hdcp_encrypted = get_cur_source_hdcp_encrypted,
    .get_overscan = get_overscan,
    .set_overscan = set_overscan,
    .get_cec_enable = get_cec_enable,
    .set_cec_enable = set_cec_enable,
    .get_arc_enable = get_arc_enable,
    .set_arc_enable = set_arc_enable,
    .set_screen_pattern = set_screen_pattern,
    .set_half_screen_mode = set_half_screen_mode,
    .get_half_screen_mode = get_half_screen_mode,
    .get_average_brightness = get_average_brightness,
    .get_dcr_enable = get_dcr_enable,
    .set_dcr_enable = set_dcr_enable,
    .get_dbc_max_backlight = get_dbc_max_backlight,
    .set_dbc_max_backlight = set_dbc_max_backlight,
    .get_dbc_min_backlight = get_dbc_min_backlight,
    .set_dbc_min_backlight = set_dbc_min_backlight,
    .get_dbc_step_time = get_dbc_step_time,
    .set_dbc_step_time = set_dbc_step_time,
    .get_dbc_step_value = get_dbc_step_value,
    .set_dbc_step_value = set_dbc_step_value,
    .get_dbc_enable = get_dbc_enable,
    .set_dbc_enable = set_dbc_enable,
    .get_panel_division = get_panel_division,
    .set_panel_division = set_panel_division,
    .get_panel_swing = get_panel_swing,
    .set_panel_swing = set_panel_swing,
    .get_panel_preemphasis = get_panel_preemphasis,
    .set_panel_preemphasis = set_panel_preemphasis,
    .get_panel_freerun = get_panel_freerun,
    .set_panel_freerun = set_panel_freerun,
    .get_shake_screen_mode = get_shake_screen_mode,
    .set_shake_screen_mode = set_shake_screen_mode,
    .get_hdmi_edid_mode = get_hdmi_edid_mode,
    .set_hdmi_edid_mode = set_hdmi_edid_mode,
    .get_pc_edid_mode = get_pc_edid_mode,
    .set_pc_edid_mode = set_pc_edid_mode,
};
