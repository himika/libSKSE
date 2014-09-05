#pragma once

#if _DEBUG
#pragma comment(lib, "skse_common_d.lib")
#pragma comment(lib, "skse_d.lib")
#else
#pragma comment(lib, "skse_common.lib")
#pragma comment(lib, "skse.lib")
#endif

#include "skse/common/IPrefix.h"
#include "skse/skse_version.h"

#define SKSE_SUPPORTING_RUNTIME_VERSION  RUNTIME_VERSION_1_9_32_0

