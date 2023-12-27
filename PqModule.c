/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * VMAN -- PQ module
 *
 * Copyright (C) 2023 Rockchip Electronics Co., Ltd.
 *
 */

#include <hardware/hardware.h>
#include <log/log.h>
#include "PqModule.h"

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "vman_pq"
#endif

/*
 * get brightness
 * @return brightness value, range[0-100]
 */
static int get_brightness(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set brightness
 * @param value: set brightness value, range[0-100]
 * @return result [0: successfully, <0: failure]
 */
static int set_brightness(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get contrast
 * @return contrast value, range[0-100]
*/
static int get_contrast(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set contrast
 * @param value: set contrast，range[0-100]
 * @return result [0: successfully, <0: failure]
*/
static int set_contrast(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get saturation
 * @return saturation value, range[0-100]
 */
static int get_saturation(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set saturation
 * @param value: set saturation value, range[0-100]
 * @return result [0: successfully, <0: failure]
 */
static int set_saturation(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get sharpness
 * @return sharpness value, range[0-100]
 */
static int get_sharpness(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set sharpness
 * @param value: set sharpness value, range[0-100]
 * @return result [0: successfully, <0: failure]
 */
static int set_sharpness(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get hue
 * @return hue value，range[0-100]
 */
static int get_hue(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set hue
 * @param value: set hue value, range[0-100]
 * @return result [0: successfully, <0: failure]
 */
static int set_hue(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get color temperature mode
 * @return color temperature mode, range[ui_color_temp_t]
 */
static ui_color_temp_t get_color_temp_mode(struct pq_hal_module *module)
{
	return 0;
}

/*
 * reset color temperature mode
 * @return result [0: successfully, <0: failure]
 */
static int reset_color_temp(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set color temperature mode
 * @param value: set color temperature mode, range[ui_color_temp_t]
 * @return result [0: successfully, <0: failure]
 */
static int set_color_temp_mode(struct pq_hal_module *module, ui_color_temp_t value)
{
	return 0;
}

/*
 * get white balance R gain value
 * @return white balance R gain value, range[0-255]
 */
static int get_wb_r_gain(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set white balance R gain value
 * @param value: set white balance R gain value, range[0-255]
 * @return result [0: successfully, <0: failure]
 */
static int set_wb_r_gain(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get white balance G gain value
 * @return white balance G gain value, range[0-255]
 */
static int get_wb_g_gain(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set white balance G gain value
 * @param value: set white balance G gain value, range[0-255]
 * @return result [0: successfully, <0: failure]
 */
static int set_wb_g_gain(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get white balance B gain value
 * @return white balance B gain value, range[0-255]
 */
static int get_wb_b_gain(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set white balance B gain value
 * @param value: set white balance B gain value, range[0-255]
 * @return result [0: successfully, <0: failure]
 */
static int set_wb_b_gain(struct pq_hal_module *module, int value)
{
	return 0;
}


/*
 * get white balance R offset value
 * @return white balance R offset value, range[0-1024]
 */
static int get_wb_r_offset(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set white balance R offset value
 * @param value: set white balance R offset value, range[0-1024]
 * @return result [0: successfully, <0: failure]
 */
static int set_wb_r_offset(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get white balance G offset value
 * @return white balance G offset value, range[0-1024]
 */
static int get_wb_g_offset(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set white balance G offset value
 * @param value: set white balance G offset value, range[0-1024]
 * @return result [0: successfully, <0: failure]
 */
static int set_wb_g_offset(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get white balance B offset value
 * @return white balance B offset value, range[0-1024]
 */
static int get_wb_b_offset(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set white balance B offset value
 * @param value: set white balance B offset value, range[0-1024]
 * @return result [0: successfully, <0: failure]
 */
static int set_wb_b_offset(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * set DCI status
 * @param value: status, range[0-1]
 * @return result [0: successfully, <0: failure]
 */
static int set_dci_enable(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get DCI status
 * @return status, range[0-1]
 */
static int get_dci_enable(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set Acm status
 * @param value: status, range[0-1]
 * @return result [0: successfully, <0: failure]
 */
static int set_acm_enable(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get Acm status
 * @return status, range[0-1]
 */
static int get_acm_enable(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set PQ status
 * @param value: status, range[0-1]
 * @return result [0: successfully, <0: failure]
 */
static int set_pq_enable(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get PQ status
 * @return status, range[0-1]
 */
static int get_pq_enable(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set picture mode
 * @param value: picture mode, range[ui_picture_mode_t]
 * @return result [0: successfully, <0: failure]
 */
static int set_picture_mode(struct pq_hal_module *module, ui_picture_mode_t value)
{
	return 0;
}

/*
 * get picture mode
 * @return picture mode, range[ui_picture_mode_t]
 */
static ui_picture_mode_t get_picture_mode(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set gamma index
 * @param value: gamma index, range[0-15]
 * @return result [0: successfully, <0: failure]
 */
static int set_gamma_mode(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get gamma index
 * @return gamma index, range[0-15]
 */
static int get_gamma_mode(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set 3dlut index
 * @param value: 3dlut index, range[0-10]
 * @return result [0: successfully, <0: failure]
 */
static int set_3dlut_mode(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get 3dlut index
 * @return 3dlut index, range[0-10]
 */
static int get_3dlut_mode(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set 3dlut data
 * @param value: 3dlut data, char array
 * @return result [0: successfully, <0: failure]
 */
static int set_3dlut_data_buff(struct pq_hal_module *module, char* data)
{
	return 0;
}

/*
 * get 3dlut data
 * @return 3dlut data, char array
 */
static int get_3dlut_data_buff(struct pq_hal_module *module, char* data)
{
	return 0;
}

/*
 *  reset 3dlut data
 * @return result [0: successfully, <0: failure]
 */
static int reset_3dlut_data(struct pq_hal_module *module)
{
	return 0;
}

/*
 * get aspect mode
 * @return aspect mode, range[ui_aspect_mode_t]
 */
static ui_aspect_mode_t get_aspect_mode(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set aspect mode
 * @param value: aspect mode, range[ui_aspect_mode_t]
 * @return result [0: successfully, <0: failure]
 */
static int set_aspect_mode(struct pq_hal_module *module, ui_aspect_mode_t value)
{
	return 0;
}

/*
 * get Color Range
 * @return Color Range, range[ui_color_range_t]
*/
static ui_color_range_t get_color_range(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set Color Range
 * @param value: Color Range, range[ui_color_range_t]
 * @return result [0: successfully, <0: failure]
 */
static int set_color_range(struct pq_hal_module *module, ui_color_range_t value)
{
	return 0;
}

/*
 * get backlight value
 * @return backlight value, range[0-100]
 */
static int get_backlight(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set backlight value
 * @param value: backlight value, range[0-100]
 * @return result [0: successfully, <0: failure]
 */
static int set_backlight(struct pq_hal_module *module, int value)
{
	return 0;
}

/*
 * get MAX backlight value
 * @return MAX backlightm, range[0-100]
 */
static int get_max_backlight(struct pq_hal_module *module)
{
	return 0;
}

/*
 * set MAX backlight value
 * @param value: MAX backlight, range[0-100]
 * @return result [0: successfully, <0: failure]
 */
static int set_max_backlight(struct pq_hal_module *module, int value)
{
	return 0;
}

static struct hw_module_methods_t pq_hal_module_methods =
{
	.open = NULL,
};

struct pq_hal_module HAL_MODULE_INFO_SYM =
{
	.common = {
		.tag = HARDWARE_MODULE_TAG,
		.module_api_version = PQ_HAL_MODULE_API_VERSION,
		.hal_api_version = HARDWARE_HAL_API_VERSION,
		.id = PQ_HAL_HARDWARE_MODULE_ID,
		.name ="Default PQ HAL",
		.author = "The PQ Project",
		.methods = &pq_hal_module_methods,
	},

	.get_brightness = get_brightness,
	.set_brightness = set_brightness,
	.get_contrast = get_contrast,
	.set_contrast = set_contrast,
	.get_saturation = get_saturation,
	.set_saturation = set_saturation,
	.set_sharpness = set_sharpness,
	.get_sharpness = get_sharpness,
	.get_hue = get_hue,
	.set_hue = set_hue,
	.set_color_temp_mode = set_color_temp_mode,
	.get_color_temp_mode = get_color_temp_mode,
	.reset_color_temp = reset_color_temp,

	.get_wb_r_gain = get_wb_r_gain,
	.set_wb_r_gain = set_wb_r_gain,
	.get_wb_g_gain = get_wb_g_gain,
	.set_wb_g_gain = set_wb_g_gain,
	.get_wb_b_gain = get_wb_b_gain,
	.set_wb_b_gain = set_wb_b_gain,

	.get_wb_r_offset = get_wb_r_offset,
	.set_wb_r_offset = set_wb_r_offset,
	.get_wb_g_offset = get_wb_g_offset,
	.set_wb_g_offset = set_wb_g_offset,
	.get_wb_b_offset = get_wb_b_offset,
	.set_wb_b_offset = set_wb_b_offset,

	.set_dci_enable = set_dci_enable,
	.get_dci_enable = get_dci_enable,
	.set_acm_enable = set_acm_enable,
	.get_acm_enable = get_acm_enable,
	.set_pq_enable = set_pq_enable,
	.get_pq_enable = get_pq_enable,

	.set_picture_mode = set_picture_mode,
	.get_picture_mode = get_picture_mode,

	.set_gamma_mode = set_gamma_mode,
	.get_gamma_mode = get_gamma_mode,

	.set_3dlut_mode = set_3dlut_mode,
	.get_3dlut_mode = get_3dlut_mode,
	.set_3dlut_data_buff = set_3dlut_data_buff,
	.get_3dlut_data_buff = get_3dlut_data_buff,
	.reset_3dlut_data = reset_3dlut_data,

	.get_aspect_mode = get_aspect_mode,
	.set_aspect_mode = set_aspect_mode,

	.get_color_range = get_color_range,
	.set_color_range = set_color_range,

	.get_backlight = get_backlight,
	.set_backlight = set_backlight,
	.get_max_backlight = get_max_backlight,
	.set_max_backlight = set_max_backlight,
};
