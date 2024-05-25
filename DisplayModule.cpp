#include <hardware/hardware.h>
#include <log/log.h>
#include <rockchip/hardware/outputmanager/1.0/IRkOutputManager.h>
#include "DisplayModule.h"
#include <xf86drmMode.h>
#include <tinyxml2.h>

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "vman_display"
#endif

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

static void get_service() {
	if (mComposer == nullptr) {
		mComposer = IRkOutputManager::getService();
	}
}

#define DRM_MODE_CONNECTOR_HDMIA 11

#define HDMI_A_1_STATUS		"sys/class/drm/card0-HDMI-A-1/status"
#define HDMI_A_2_STATUS		"sys/class/drm/card0-HDMI-A-2/status"
#define STATUS_ON		"on"
#define STATUS_OFF		"off"
#define STATUS_DETECT		"detect"

enum connector_state {
	CONN_ON = 0,
	CONN_OFF,
	CONN_DETECT,
};

enum hdmi_port {
	HDMI_PORT1 = 1,
	HDMI_PORT2,
};

static int filter_whitelist(const std::string& res, char* mode)
{
  tinyxml2::XMLDocument doc;

  doc.LoadFile("/system/usr/share/resolution_white.xml");

  tinyxml2::XMLElement* root=doc.RootElement();
  /* usr tingxml2 to parse resolution.xml */
  if (!root)
    return -1;

  tinyxml2::XMLElement* resolution =root->FirstChildElement("resolution");

  while (resolution) {
    drmModeModeInfo m;
    int info_hdisplay = 0, info_vdisplay = 0, info_vrefresh = 0;

    #define PARSE(x) \
      tinyxml2::XMLElement* _##x = resolution->FirstChildElement(#x); \
      if (!_##x) { \
        ALOGE("------> failed to parse %s\n", #x); \
        resolution = resolution->NextSiblingElement(); \
        continue; \
      } \
      m.x = atoi(_##x->GetText())

    #define PARSE_HEX(x) \
      tinyxml2::XMLElement* _##x = resolution->FirstChildElement(#x); \
      if (!_##x) { \
        ALOGE("------> failed to parse %s\n", #x); \
        resolution = resolution->NextSiblingElement(); \
        continue; \
      } \
      sscanf(_##x->GetText(), "%x", &m.x);

    PARSE(clock);
    PARSE(hdisplay);
    PARSE(hsync_start);
    PARSE(hsync_end);
    PARSE(hskew);
    PARSE(vdisplay);
    PARSE(vsync_start);
    PARSE(vsync_end);
    PARSE(vscan);
    PARSE(vrefresh);
    PARSE(htotal);
    PARSE(vtotal);
    PARSE_HEX(flags);

    sscanf(res.c_str(),"%dx%dp%d", &info_hdisplay, &info_vdisplay, &info_vrefresh);

    if ((info_hdisplay == m.hdisplay) && (info_vdisplay == m.vdisplay)
	&& (info_vrefresh == m.vrefresh)) {
	sprintf(mode,"%dx%d@%f-%d-%d-%d-%d-%d-%d-%x-%d",
		m.hdisplay, m.vdisplay,
		(float)m.vrefresh, m.hsync_start, m.hsync_end,
		m.htotal,m.vsync_start,
		m.vsync_end, m.vtotal,
		m.flags, m.clock);

	ALOGI("set resolution:%s\n", mode);
	return 0;
    }

    resolution = resolution->NextSiblingElement();
  }

  return -1;
}


static int get_hdmi_status(enum hdmi_port port)
{
	int ret, fd;
	char statebuf[20];
	char node[128];

	memset(node, 0, 128);
	if (port == HDMI_PORT1)
		strcpy(node, HDMI_A_1_STATUS);
	else
		strcpy(node, HDMI_A_2_STATUS);
	fd = open(node, O_RDONLY);
	if (fd < 0){
		ALOGD("%s:%d", __FUNCTION__, __LINE__);
		return 0;
	}
	ret = read(fd, statebuf, sizeof(statebuf));
	close(fd);
	if (ret < 0) {
		ALOGD("%s:%d", __FUNCTION__, __LINE__);
		return 0;
	}
	if (!strcmp(statebuf, "connected\n")) {
		ALOGD("%s:%d", __FUNCTION__, __LINE__);
		return 1;
	}
		ALOGD("%s:%d", __FUNCTION__, __LINE__);

	return 0;
}

static int set_hdmi_status(enum hdmi_port port, enum connector_state state)
{
	int ret, fd;
	char statebuf[20];
	char node[128];

	memset(node, 0, 128);
	memset(statebuf, 0, 20);
	if (port == HDMI_PORT1)
		strcpy(node, HDMI_A_1_STATUS);
	else
		strcpy(node, HDMI_A_2_STATUS);

	if (state == CONN_ON)
		strcpy(statebuf, STATUS_ON);
	else if (state == CONN_OFF)
		strcpy(statebuf, STATUS_OFF);
	else
		strcpy(statebuf, STATUS_DETECT);
	fd = open(node, O_WRONLY);
        if (fd < 0) {
		ALOGD("%s:%d", __FUNCTION__, __LINE__);
                return -1;
        }
	ret = write(fd, statebuf, strlen(statebuf));
	close(fd);
	if (ret < 0) {
		ALOGD("%s:%d", __FUNCTION__, __LINE__);
		return -1;
	}
		ALOGD("%s:%d", __FUNCTION__, __LINE__);

	return 0;
}

 /*
  * Get HDMI-TX status
  * @return HDMI-TX status, range[0-1]
  */
static int get_display_enable(struct display_hal_module *module)
{
	hidl_vec<RkConnectorInfo> minfo;
	int ret = 0, portid = 0;;

	get_service();
	if (mComposer == nullptr || module == nullptr)
		return -1;
	mComposer->getConnectorInfo([&](const auto& tmpResult, const auto& tmpInfo) {
		ALOGD("%s:%d", __FUNCTION__, __LINE__);
		if (tmpResult == Result::OK) {
			minfo = tmpInfo;
			ret = 0;
			ALOGD("%s:%d", __FUNCTION__, __LINE__);
		} else {
			ret = -1;
			ALOGD("%s:%d", __FUNCTION__, __LINE__);
		}
	});
	for (size_t c=0;c<minfo.size();c++) {
		RkConnectorInfo tmpConnectorInfo = minfo[c];
		if (tmpConnectorInfo.type == DRM_MODE_CONNECTOR_HDMIA) {
			portid++;
			if (c == module->dpy) {
				if (portid == 1) {
					ALOGD("%s:%d", __FUNCTION__, __LINE__);
					ret = get_hdmi_status(HDMI_PORT1);
				} else if (portid == 2) {
					ALOGD("%s:%d", __FUNCTION__, __LINE__);
					ret = get_hdmi_status(HDMI_PORT2);
				}
				break;
			}
		}
	}

	return ret;
}
static int set_display_enable(struct display_hal_module *module, int value)
{
	hidl_vec<RkConnectorInfo> minfo;
	int ret = 0, portid = 0;;

	get_service();
	if (mComposer == nullptr || module == nullptr)
		return -1;
	mComposer->getConnectorInfo([&](const auto& tmpResult, const auto& tmpInfo) {
		if (tmpResult == Result::OK) {
			minfo = tmpInfo;
			ret = 0;
			ALOGD("%s:%d", __FUNCTION__, __LINE__);
		} else {
			ret = -1;
			ALOGD("%s:%d", __FUNCTION__, __LINE__);
		}
	});
	for (size_t c=0;c<minfo.size();c++) {
		RkConnectorInfo tmpConnectorInfo = minfo[c];
		if (tmpConnectorInfo.type == DRM_MODE_CONNECTOR_HDMIA) {
			portid++;
			if (c == module->dpy) {
				if (portid == 1) {
					if (value == 1) {
						set_hdmi_status(HDMI_PORT1, CONN_ON);
						set_hdmi_status(HDMI_PORT1, CONN_DETECT);
						ALOGD("%s:%d", __FUNCTION__, __LINE__);
					} else {
						set_hdmi_status(HDMI_PORT1, CONN_OFF);
						ALOGD("%s:%d", __FUNCTION__, __LINE__);
					}
				} else if (portid == 2) {
					if (value == 1) {
						set_hdmi_status(HDMI_PORT2, CONN_ON);
						set_hdmi_status(HDMI_PORT2, CONN_DETECT);
						ALOGD("%s:%d", __FUNCTION__, __LINE__);
					} else {
						set_hdmi_status(HDMI_PORT2, CONN_OFF);
						ALOGD("%s:%d", __FUNCTION__, __LINE__);
					}
				}
				break;
			}
		}
	}

	return ret;
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
static int get_display_support_resolution_list(struct display_hal_module* module, std::vector<std::string>& resolutionList) {
	int ret = 0;
	std::string info;
	hidl_vec<RkDrmMode> mModes;
	std::string info_interlace = "p";
	get_service();
	if (mComposer == nullptr || module == nullptr) {
		return -1;
	}

	mComposer->getDisplayModes(module->dpy, [&](const auto& tmpResult, const auto& tmpModes) {
		if (tmpResult == Result::OK) {
			mModes = tmpModes;
			ret = 0;
		} else {
			ret = -1;
		}
	});

	for (size_t c = 0; c < mModes.size(); c++) {
		RkDrmMode tmpMode = mModes[c];
		if (tmpMode.interlaceFlag)
			info_interlace = "i";
		else
			info_interlace = "p";
		std::string resolution = std::to_string(tmpMode.width) + "x" + std::to_string(tmpMode.height) + info_interlace + std::to_string(tmpMode.refreshRate);
		resolutionList.push_back(resolution);
		std::cout << "Resolution: " << resolution << std::endl;
	}
	return ret;
}

/*
 * Get the current resolution of the HDMI-TX
 * @param resolution: resolution list, resolution is a string, format: "3840x2160p60"
 * @return result[0: successfully, <0: failure]
 */
std::string get_display_resolution(struct display_hal_module* module) {
	if (module == nullptr) {
		return "";
	}

	get_service();
	if (mComposer == nullptr) {
		return "";
	}

	std::string resolution;
	mComposer->getCurMode(module->dpy, [&](const auto& tmpResult, const auto& tmpMode) {
		if (tmpResult == Result::OK) {
			resolution = tmpMode;
		} else {
			resolution = "";
		}
	});

	return resolution;
}

/*
 * Set the current resolution of the HDMI-TX
 * @param resolution: resolution list, resolution is a string, format: "3840x2160p60"
 * @return result[0: successfully, <0: failure]
 */
static int set_display_resolution(struct display_hal_module* module, const std::string& resolution) {

	char mode[100];
	Result res = Result::UNKNOWN;

	memset(mode, 0, 100);
	if (module == nullptr) {
		return -1;
	}

	get_service();
	if (mComposer == nullptr) {
		return -1;
	}

	if (strncmp(resolution.c_str(), "Auto", 4) == 0) {
		ALOGI("set resolution: [Auto] \n");
		res = mComposer->setMode(module->dpy, resolution);
	} else if (filter_whitelist(resolution, mode) == 0) {
		res = mComposer->setMode(module->dpy, mode);
	} else {
		ALOGE("set resolutionp fail, [%s] is invalid resolution!\n", resolution.c_str());
	}

	return (res == Result::OK ? 0 : -1);
}

/*
 * Get HDMI-TX HDCP status
 * @return HDCP status, range[0-1]
 */
static int get_display_hdcp_status(struct display_hal_module *module)
{
	int ret = 0;
	get_service();
	if (mComposer != nullptr && module != nullptr) {
		 mComposer->getHdcpEnableStatus(module->dpy,
			 [&](const auto& tmpResult, const auto& tmpValue) {
				if (tmpResult == Result::OK) {
					ret = tmpValue;
				}
		});
	}
	return ret;
}

/*
 * Set HDMI-TX HDCP status
 * @param value：set HDMI-TX HDCP status, range[0-1]
 * @return result [0: successfully, <0: failure]
 */
static int set_display_hdcp_status(struct display_hal_module *module, int value)
{
	Result ret = Result::UNKNOWN;
	get_service();
	if (mComposer != nullptr && module != nullptr) {
		ret = mComposer->setHdcpEnable(module->dpy, value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
}

static int get_extend_display_en_dvi_status(struct display_hal_module *module) {
	int ret = 0;
	get_service();
	if (mComposer != nullptr && module != nullptr) {
		mComposer->getDviStatus(module->dpy,
			[&](const auto& tmpResult, const auto& tmpValue) {
				if (tmpResult == Result::OK) {
					ret = tmpValue;
				}
		});
	}
	return ret;
}

static int set_extend_display_en_dvi_status(struct display_hal_module *module, int value) {
	Result ret = Result::UNKNOWN;
	get_service();
	if (mComposer != nullptr && module != nullptr) {
	    ret = mComposer->setDviStatus(module->dpy, value);
	}
	if (ret == Result::OK) {
		return 0;
	} else {
		return -1;
	}
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
	.get_extend_display_en_dvi_status = get_extend_display_en_dvi_status,
	.set_extend_display_en_dvi_status = set_extend_display_en_dvi_status,
};
