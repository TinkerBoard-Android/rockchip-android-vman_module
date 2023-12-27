#include <hardware/hardware.h>
#include <log/log.h>
#include "PowerModule.h"

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "vman_power"
#endif

/*
 * Get power-on mode
 * @return mode, range[ui_power_mode_t]
 */
static ui_power_mode_t get_power_mode(struct power_hal_module *module)
{
	return 0;
}

/*
 * Set power-on mode
 * @param value: mode, range[ui_power_mode_t]
 * @return result [0: successfully, 1: failure]
 * @note default: POWER_MODE_OFF, power-off will save
 */
static int set_power_mode(struct power_hal_module *module, ui_power_mode_t value)
{
	return 0;
}

static struct hw_module_methods_t power_hal_module_methods =
{
	.open = NULL,
};

struct power_hal_module HAL_MODULE_INFO_SYM =
{
	.common = {
		.tag = HARDWARE_MODULE_TAG,
		.module_api_version = POWER_HAL_MODULE_API_VERSION,
		.hal_api_version = HARDWARE_HAL_API_VERSION,
		.id = POWER_HAL_HARDWARE_MODULE_ID,
		.name ="Default Power HAL",
		.author = "The Power Project",
		.methods = &power_hal_module_methods,
	},
	.get_power_mode = get_power_mode,
	.set_power_mode = set_power_mode,
};
