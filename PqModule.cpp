/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * VMAN -- PQ module
 *
 * Copyright (C) 2023 Rockchip Electronics Co., Ltd.
 *
 */
#include <errno.h>
#include <fcntl.h>
#include <hardware/hardware.h>
#include <log/log.h>
#include <rockchip/hardware/outputmanager/1.0/IRkOutputManager.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "PqModule.h"

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "vman_pq"
#endif

#define DEFAULT_BRIGHTNESS  50
#define DEFAULT_CONTRAST  50
#define DEFAULT_SATURATION  50
#define DEFAULT_HUE  50
#define DEFAULT_SHARPNESS  0
#define DEFAULT_RGAIN  256
#define DEFAULT_GGAIN  256
#define DEFAULT_BGAIN  256
#define SIZE_3D_LUT_DATA 17 * 17 * 17
#define CONFIG_3D_LUT_DEFAULT_DATA_PATH "/vendor/etc/3D_lut_0.csv"
#define BACKLIGHT_PATH "/sys/class/backlight/backlight/brightness"

using namespace rockchip::hardware::outputmanager::V1_0;

using ::rockchip::hardware::outputmanager::V1_0::IRkOutputManager;
using ::rockchip::hardware::outputmanager::V1_0::Result;
using android::hardware::hidl_handle;
using android::hardware::hidl_string;
using android::hardware::hidl_vec;
using android::hardware::Return;
using android::hardware::Void;
using ::android::sp;

sp<IRkOutputManager> mComposer = nullptr;

static void init(struct pq_hal_module *module) {
	if (mComposer == nullptr) {
		mComposer = IRkOutputManager::getService();
	}
}

/*
 * get brightness
 * @return brightness value, range[0-100]
 */
static int get_brightness(struct pq_hal_module *module)
{
	int ret = DEFAULT_BRIGHTNESS;
	if (mComposer != nullptr && module != nullptr) {
		hidl_vec<uint32_t> hidlBcsh;
		if (mComposer != nullptr && module != nullptr) {
			mComposer->getBcsh(module->dpy, [&](const auto& tmpResult, const auto& tmpBcshs) {
				if (tmpResult == Result::OK) {
					hidlBcsh = tmpBcshs;
				}
			});
		}
		if (hidlBcsh.size() == 4) {
			ret = hidlBcsh[0];
		}
	}
	return ret;
}

/*
 * set brightness
 * @param value: set brightness value, range[0-100]
 * @return result [0: successfully, <0: failure]
 */
static int set_brightness(struct pq_hal_module *module, int value)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->setBrightness(module->dpy, value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * get contrast
 * @return contrast value, range[0-100]
*/
static int get_contrast(struct pq_hal_module *module)
{
	int ret = DEFAULT_CONTRAST;
	if (mComposer != nullptr && module != nullptr) {
		hidl_vec<uint32_t> hidlBcsh;
		if (mComposer != nullptr && module != nullptr) {
			mComposer->getBcsh(module->dpy, [&](const auto& tmpResult, const auto& tmpBcshs) {
				if (tmpResult == Result::OK) {
					hidlBcsh = tmpBcshs;
				}
			});
		}
		if (hidlBcsh.size() == 4) {
			ret = hidlBcsh[1];
		}
	}
	return ret;

}

/*
 * set contrast
 * @param value: set contrast，range[0-100]
 * @return result [0: successfully, <0: failure]
*/
static int set_contrast(struct pq_hal_module *module, int value)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->setContrast(module->dpy, value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * get saturation
 * @return saturation value, range[0-100]
 */
static int get_saturation(struct pq_hal_module *module)
{
	int ret = DEFAULT_SATURATION;
	if (mComposer != nullptr && module != nullptr) {
		hidl_vec<uint32_t> hidlBcsh;
		if (mComposer != nullptr && module != nullptr) {
			mComposer->getBcsh(module->dpy, [&](const auto& tmpResult, const auto& tmpBcshs) {
				if (tmpResult == Result::OK) {
					hidlBcsh = tmpBcshs;
				}
			});
		}
		if (hidlBcsh.size() == 4) {
			ret = hidlBcsh[2];
		}
	}
	return ret;
}

/*
 * set saturation
 * @param value: set saturation value, range[0-100]
 * @return result [0: successfully, <0: failure]
 */
static int set_saturation(struct pq_hal_module *module, int value)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->setSaturation(module->dpy, value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * get sharpness
 * @return sharpness value, range[0-100]
 */
static int get_sharpness(struct pq_hal_module *module)
{
	int ret = DEFAULT_SHARPNESS;
	if (mComposer != nullptr && module != nullptr) {
		 mComposer->getSharpPeakingGain(module->dpy,
			 [&](const auto& tmpResult, const auto& tmpValue) {
				if (tmpResult == Result::OK) {
					ret = tmpValue;
				}
		});
	}
	return ret;
}

/*
 * set sharpness
 * @param value: set sharpness value, range[0-100]
 * @return result [0: successfully, <0: failure]
 */
static int set_sharpness(struct pq_hal_module *module, int value)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->setSharpPeakingGain(module->dpy, value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * get hue
 * @return hue value，range[0-100]
 */
static int get_hue(struct pq_hal_module *module)
{
	int ret = DEFAULT_HUE;
	if (mComposer != nullptr && module != nullptr) {
		hidl_vec<uint32_t> hidlBcsh;
		if (mComposer != nullptr && module != nullptr) {
			mComposer->getBcsh(module->dpy, [&](const auto& tmpResult, const auto& tmpBcshs) {
				if (tmpResult == Result::OK) {
					hidlBcsh = tmpBcshs;
				}
			});
		}
		if (hidlBcsh.size() == 4) {
			ret = hidlBcsh[3];
		}
	}
	return ret;
}

/*
 * set hue
 * @param value: set hue value, range[0-100]
 * @return result [0: successfully, <0: failure]
 */
static int set_hue(struct pq_hal_module *module, int value)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->setHue(module->dpy, value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * get color temperature mode
 * @return color temperature mode, range[ui_color_temp_t]
 */
static ui_color_temp_t get_color_temp_mode(struct pq_hal_module *module)
{
	int ret = COLOR_TEMP_STANDARD;
	if (mComposer != nullptr && module != nullptr) {
		mComposer->getWhiteBalanceMode(module->dpy,
			[&](const auto& tmpResult, const auto& tmpIndex) {
			if (tmpResult == Result::OK) {
				ret = tmpIndex;
			}
		});
	}
	return (ui_color_temp_t)ret;
}

/*
 * reset color temperature mode
 * @return result [0: successfully, <0: failure]
 */
static int reset_color_temp(struct pq_hal_module *module)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr)
		ret = mComposer->setWhiteBalanceMode(module->dpy, COLOR_TEMP_STANDARD);
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * set color temperature mode
 * @param value: set color temperature mode, range[ui_color_temp_t]
 * @return result [0: successfully, <0: failure]
 */
static int set_color_temp_mode(struct pq_hal_module *module, ui_color_temp_t value)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr)
		ret = mComposer->setWhiteBalanceMode(module->dpy, value);
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * get white balance R gain value
 * @return white balance R gain value, range[0-255]
 */
static int get_wb_r_gain(struct pq_hal_module *module)
{
	int ret = DEFAULT_RGAIN;
	if (mComposer != nullptr && module != nullptr) {
		 mComposer->getRGain(module->dpy,
			 [&](const auto& tmpResult, const auto& tmpValue) {
				if (tmpResult == Result::OK) {
					ret = tmpValue;
				}
		});
	}
	return ret;
}

/*
 * set white balance R gain value
 * @param value: set white balance R gain value, range[0-255]
 * @return result [0: successfully, <0: failure]
 */
static int set_wb_r_gain(struct pq_hal_module *module, int value)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->setRGain(module->dpy, value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * get white balance G gain value
 * @return white balance G gain value, range[0-255]
 */
static int get_wb_g_gain(struct pq_hal_module *module)
{
	int ret = DEFAULT_GGAIN;
	if (mComposer != nullptr && module != nullptr) {
		 mComposer->getGGain(module->dpy,
			 [&](const auto& tmpResult, const auto& tmpValue) {
				if (tmpResult == Result::OK) {
					ret = tmpValue;
				}
		});
	}
	return ret;
}

/*
 * set white balance G gain value
 * @param value: set white balance G gain value, range[0-255]
 * @return result [0: successfully, <0: failure]
 */
static int set_wb_g_gain(struct pq_hal_module *module, int value)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->setGGain(module->dpy, value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * get white balance B gain value
 * @return white balance B gain value, range[0-255]
 */
static int get_wb_b_gain(struct pq_hal_module *module)
{
	int ret = DEFAULT_BGAIN;
	if (mComposer != nullptr && module != nullptr) {
		 mComposer->getBGain(module->dpy,
			 [&](const auto& tmpResult, const auto& tmpValue) {
				if (tmpResult == Result::OK) {
					ret = tmpValue;
				}
		});
	}
	return ret;
}

/*
 * set white balance B gain value
 * @param value: set white balance B gain value, range[0-255]
 * @return result [0: successfully, <0: failure]
 */
static int set_wb_b_gain(struct pq_hal_module *module, int value)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->setBGain(module->dpy, value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
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
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->setDciEnable(value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * get DCI status
 * @return status, range[0-1]
 */
static int get_dci_enable(struct pq_hal_module *module)
{
	int ret = 0;
	if (mComposer != nullptr && module != nullptr) {
		 mComposer->getDciEnable(
			 [&](const auto& tmpResult, const auto& tmpValue) {
				if (tmpResult == Result::OK) {
					ret = tmpValue;
				}
		});
	}
	return ret;
}

/*
 * set Acm status
 * @param value: status, range[0-1]
 * @return result [0: successfully, <0: failure]
 */
static int set_acm_enable(struct pq_hal_module *module, int value)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->setAcmEnable(value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * get Acm status
 * @return status, range[0-1]
 */
static int get_acm_enable(struct pq_hal_module *module)
{
	int ret = 0;
	if (mComposer != nullptr && module != nullptr) {
		 mComposer->getAcmEnable(
			 [&](const auto& tmpResult, const auto& tmpValue) {
				if (tmpResult == Result::OK) {
					ret = tmpValue;
				}
		});
	}
	return ret;
}

/*
 * set PQ status
 * @param value: status, range[0-1]
 * @return result [0: successfully, <0: failure]
 */
static int set_pq_enable(struct pq_hal_module *module, int value)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->setPqEnable(value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * get PQ status
 * @return status, range[0-1]
 */
static int get_pq_enable(struct pq_hal_module *module)
{
	int ret = 0;
	if (mComposer != nullptr && module != nullptr) {
		 mComposer->getPqEnable(
			 [&](const auto& tmpResult, const auto& tmpValue) {
				if (tmpResult == Result::OK) {
					ret = tmpValue;
				}
		});
	}
	return ret;
}

/*
 * set picture mode
 * @param value: picture mode, range[ui_picture_mode_t]
 * @return result [0: successfully, <0: failure]
 */
static int set_picture_mode(struct pq_hal_module *module, ui_picture_mode_t value)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->setBCSHMode(module->dpy, value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * get picture mode
 * @return picture mode, range[ui_picture_mode_t]
 */
static ui_picture_mode_t get_picture_mode(struct pq_hal_module *module)
{
	int ret = PICTURE_MODE_STANDARD;
	if (mComposer != nullptr && module != nullptr) {
		 mComposer->getBCSHMode(module->dpy,
			 [&](const auto& tmpResult, const auto& tmpValue) {
				if (tmpResult == Result::OK) {
					ret = tmpValue;
				}
		});
	}
	return (ui_picture_mode_t)ret;
}

/*
 * set gamma index
 * @param value: gamma index, range[0-15]
 * @return result [0: successfully, <0: failure]
 */
static int set_gamma_mode(struct pq_hal_module *module, int value)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->setGammaMode(module->dpy, value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * get gamma index
 * @return gamma index, range[0-15]
 */
static int get_gamma_mode(struct pq_hal_module *module)
{
	int ret = 0;
	if (mComposer != nullptr && module != nullptr) {
		 mComposer->getGammaMode(module->dpy,
			 [&](const auto& tmpResult, const auto& tmpValue) {
				if (tmpResult == Result::OK) {
					ret = tmpValue;
				}
		});
	}
	return ret;
}

/*
 * set 3dlut index
 * @param value: 3dlut index, range[0-10]
 * @return result [0: successfully, <0: failure]
 */
static int set_3dlut_mode(struct pq_hal_module *module, int value)
{
	Result ret = Result::UNKNOWN;
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->set3DLutMode(module->dpy, value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

/*
 * get 3dlut index
 * @return 3dlut index, range[0-10]
 */
static int get_3dlut_mode(struct pq_hal_module *module)
{
	int ret = 0;
	if (mComposer != nullptr && module != nullptr) {
		 mComposer->get3DLutMode(module->dpy,
			 [&](const auto& tmpResult, const auto& tmpValue) {
				if (tmpResult == Result::OK) {
					ret = tmpValue;
				}
		});
	}
	return ret;
}

static uint16_t format_3d_lut_data(uint16_t in) {
	return in * 4 > 4096 ? 4095 : in * 4;
}

/*
 * set 3dlut data
 * @param value: 3dlut data, char array
 * @return result [0: successfully, <0: failure]
 */
static int set_3dlut_data_buff(struct pq_hal_module *module, int index, char* data)
{
	Result ret = Result::UNKNOWN;
	int dataIndex = 0;
	int b, g, r;
	unsigned long int i = 0;
	std::vector<uint16_t> hidlRed, hidlGreen, hidlBlue;
	char buf[30] = {0};
	const char* dest_data = data;
	int size_line = 0;

	if (module == nullptr || data == NULL) {
		return -1;
	}
	ALOGD("strlen of data:%zu", strlen(data));
	while ((*data != '\0') && dataIndex < SIZE_3D_LUT_DATA) {
		while (data[i] != '\n') {
			i++;
			size_line++;
		}
		if (data[i] == '\n' && (*dest_data != '\0')) {
			memset(buf, 0, sizeof(buf));
			strncpy(buf, dest_data, size_line);
			dest_data = dest_data + size_line + 1;
			sscanf(buf, "%d,%d,%d", &b, &g, &r);
			hidlRed.push_back(format_3d_lut_data(r));
			hidlGreen.push_back(format_3d_lut_data(g));
			hidlBlue.push_back(format_3d_lut_data(b));
			dataIndex++;
			size_line = 0;
		}
		i++;
		if (SIZE_3D_LUT_DATA == dataIndex) {
			if (mComposer != nullptr && module != nullptr) {
				ret = mComposer->setPreset3DLut(module->dpy, 0,
					index, SIZE_3D_LUT_DATA, hidlRed, hidlGreen, hidlBlue);
			}
			if (ret == Result::OK) {
				return 0;
			} else {
				return -1;
			}
		}
	}

	return -1;
}

/*
 * get 3dlut data
 * @return 3dlut data, char array
 */
static int get_3dlut_data_buff(struct pq_hal_module *module, int index, char* data)
{
	hidl_vec<uint16_t> hidl3dlut;
	int array[SIZE_3D_LUT_DATA * 3] = {0};
	if (mComposer != nullptr && module != nullptr) {
		mComposer->getPreset3DLut(module->dpy, 0, index,
			[&](const auto& tmpResult, const auto& temp3DLut) {
			if (tmpResult == Result::OK) {
				hidl3dlut = temp3DLut;
			}
		});
	}
	for (int i = 0; i < SIZE_3D_LUT_DATA * 3; i++) {
		array[i] = hidl3dlut[i];
	}
	data = (char *)array;
	return 0;
}

/*
 *  reset 3dlut data
 * @return result [0: successfully, <0: failure]
 */
static int reset_3dlut_data(struct pq_hal_module *module)
{
	int ret = -1;
	std::vector<uint16_t> hidlRed, hidlGreen, hidlBlue;
	int b, g, r;
	int index = 0;
	char buf[30];
	char path[64] = CONFIG_3D_LUT_DEFAULT_DATA_PATH;
	FILE* fp = fopen(path, "r");
	if (fp == NULL) {
		ALOGD("reset_3dlut_data open path fail \n");
		return -1;
	}
	while (!feof(fp) && index < SIZE_3D_LUT_DATA) {
		char* p = fgets(buf, sizeof(buf),fp);
		if(p != NULL){
			sscanf(buf, "%d,%d,%d", &b, &g, &r);
			hidlRed.push_back(format_3d_lut_data(r));
			hidlGreen.push_back(format_3d_lut_data(g));
			hidlBlue.push_back(format_3d_lut_data(b));
			index++;
		}
	}
	if (SIZE_3D_LUT_DATA == index) {
		if (mComposer != nullptr && module != nullptr) {
			Result result = mComposer->set3DLut(module->dpy,
				SIZE_3D_LUT_DATA, hidlRed, hidlGreen, hidlBlue);
			if (result == Result::OK) {
				ret = 0;
			} else {
				ret = -1;
			}
		}
	}
	if (fp != NULL) {
		fclose(fp);
	}
	return ret;
}

/*
 * get aspect mode
 * @return aspect mode, range[ui_aspect_mode_t]
 */
static ui_aspect_mode_t get_aspect_mode(struct pq_hal_module *module)
{
	return ASPECT_16X9;
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
	return COLOR_RANGE_AUTO;
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
int get_backlight(struct pq_hal_module *module)
{
	int ret = 0;
	char buf[8];
	int len;
	int fd = open(BACKLIGHT_PATH, O_RDONLY);
	if (fd < 0) {
		ALOGE("Error opening %s: %s\n", BACKLIGHT_PATH, buf);
		return -1;
	}
	len = read(fd, buf, 8);
	if (len < 0) {
		ALOGE("Error read %s: len %d\n", BACKLIGHT_PATH, len);
		ret = -1;
	} else {
		ret = atoi(buf) * 100 / 255;
	}
	close(fd);
	return ret;
}

/*
 * set backlight value
 * @param value: backlight value, range[0-100]
 * @return result [0: successfully, <0: failure]
 */
int set_backlight(struct pq_hal_module *module, int value)
{
	int ret = 0;
	char buf[8];
	int len;
	int fd = open(BACKLIGHT_PATH, O_WRONLY);
	if (fd < 0) {
		ALOGE("Error opening %s: %s\n", BACKLIGHT_PATH, buf);
		return -1;
	}
	sprintf(buf, "%d", value * 255 / 100 + 1);
	len = write(fd, buf, strlen(buf));
	if (len < 0) {
		ALOGE("Error writing to %s: %s\n", BACKLIGHT_PATH, buf);
		ret = -1;
	} else {
		ret = 0;
	}
    close(fd);
	return ret;
}

/*
 * get MAX backlight value
 * @return MAX backlightm, range[0-100]
 */
static int get_max_backlight(struct pq_hal_module *module)
{
	return 100;
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

	.init = init,
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
