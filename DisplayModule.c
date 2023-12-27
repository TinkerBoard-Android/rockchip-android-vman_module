#include <hardware/hardware.h>
#include <log/log.h>
#include "DisplayModule.h"

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "vman_display"
#endif

/*
 * Get HDMI-TX status
 * @return HDMI-TX status, range[0-1]
 */
static int get_display_enable(struct display_hal_module *module)
{
	return 0;
}

/*
 * Set HDMI-TX status
 * @param value: status, range[0-1]
 * @return result [00: successfully, <0: failure]
 */
static int set_display_enable(struct display_hal_module *module, int value)
{
	return 0;
}

/*
 * Get HDMI-TX status in HDMI channel（HDMI-TX sometimes does not allow output in HDMI channel）
 * @return status, range[0-1]
 */
static int get_display_hdmi_enable(struct display_hal_module *module)
{
	return 0;
}

/*
 * Set HDMI-TX status in HDMI channel（HDMI-TX sometimes does not allow output in HDMI channel）
 * @param value: set 的 value, range[0-1]
 * @return result [0: successfully, <0: failure]
 */
static int set_display_hdmi_enable(struct display_hal_module *module, int value)
{
	return 0;
}

/*
 * Get list of resolution support for HDMI-TX
 * @param resolutionList: resolution list, resolution is a string, format: "3840x2160p60"
 * @return result[0: successfully, <0: failure]
 */
static int get_display_support_resolution_list(struct display_hal_module *module, char resolutionList[][20])
{
	return 0;
}

/*
 * Get the current resolution of the HDMI-TX
 * @param resolution: resolution list, resolution is a string, format: "3840x2160p60"
 * @return result[0: successfully, <0: failure]
 */
static int get_display_resolution(struct display_hal_module *module, char* resolution)
{
	return 0;
}

/*
 * Set the current resolution of the HDMI-TX
 * @param resolution: resolution list, resolution is a string, format: "3840x2160p60"
 * @return result[0: successfully, <0: failure]
 */
static int set_display_resolution(struct display_hal_module *module, char* resolution)
{
	return 0;
}

/*
 * Get HDMI-TX HDCP status
 * @return HDCP status, range[0-1]
 */
static int get_display_hdcp_status(struct display_hal_module *module)
{
	return 0;
}

/*
 * Set HDMI-TX HDCP status
 * @param value：set HDMI-TX HDCP status, range[0-1]
 * @return result [0: successfully, <0: failure]
 */
static int set_display_hdcp_status(struct display_hal_module *module, int value)
{
	return 0;
}

static struct hw_module_methods_t display_hal_module_methods =
{
	.open = NULL,
};

struct display_hal_module HAL_MODULE_INFO_SYM =
{
	.common = {
		.tag = HARDWARE_MODULE_TAG,
		.module_api_version = DISPLAY_HAL_MODULE_API_VERSION,
		.hal_api_version = HARDWARE_HAL_API_VERSION,
		.id = DISPLAY_HAL_HARDWARE_MODULE_ID,
		.name ="Default DISPLAY HAL",
		.author = "The DISPLAY Project",
		.methods = &display_hal_module_methods,
	},

	.get_display_enable = get_display_enable,
	.set_display_enable = set_display_enable,
	.get_display_hdmi_enable = get_display_hdmi_enable,
	.set_display_hdmi_enable = set_display_hdmi_enable,
	.get_display_support_resolution_list = get_display_support_resolution_list,
	.get_display_resolution = get_display_resolution,
	.set_display_resolution = set_display_resolution,
	.get_display_hdcp_status = get_display_hdcp_status,
	.set_display_hdcp_status = set_display_hdcp_status,
};
