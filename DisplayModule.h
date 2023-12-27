#ifndef ANDROID_INCLUDE_HARDWARE_DISPLAY_HAL_H
#define ANDROID_INCLUDE_HARDWARE_DISPLAY_HAL_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <hardware/hardware.h>

__BEGIN_DECLS

#define DISPLAY_HAL_MODULE_API_VERSION  HARDWARE_MODULE_API_VERSION(0, 1)

/*
*  The id of this module
*/
#define DISPLAY_HAL_HARDWARE_MODULE_ID      "vman_display_hal"

typedef struct display_hal_module {
	struct hw_module_t common;
	int (*get_display_enable)(struct display_hal_module *module);
	int (*set_display_enable)(struct display_hal_module *module, int value);
	int (*get_display_hdmi_enable)(struct display_hal_module *module);
	int (*set_display_hdmi_enable)(struct display_hal_module *module, int value);
	int (*get_display_support_resolution_list)(struct display_hal_module *module, char resolutionList[][20]);
	int (*get_display_resolution)(struct display_hal_module *module, char* resolution);
	int (*set_display_resolution)(struct display_hal_module *module, char* resolution);
	int (*get_display_hdcp_status)(struct display_hal_module *module);
	int (*set_display_hdcp_status)(struct display_hal_module *module, int value);
} display_hal_module_t;

__END_DECLS

#endif /* ANDROID_INCLUDE_HARDWARE_DISPLAY_HAL_H */
