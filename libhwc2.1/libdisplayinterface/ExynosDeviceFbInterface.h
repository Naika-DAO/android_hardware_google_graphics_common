/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _EXYNOSDEVICEFBINTERFACE_H
#define _EXYNOSDEVICEFBINTERFACE_H

#include <sys/types.h>
#include <thread>
#include <poll.h>
#include "ExynosDeviceInterface.h"

/* for restriction query */
typedef struct dpu_dpp_info {
    struct dpp_restrictions_info dpuInfo;
    bool overlap[16] = {false};
} dpu_dpp_info_t;

class ExynosDevice;
class ExynosDeviceFbInterface : public ExynosDeviceInterface {
    public:
        ExynosDeviceFbInterface(ExynosDevice *exynosDevice);
        virtual ~ExynosDeviceFbInterface();
        virtual void init(ExynosDevice *exynosDevice) override;
        virtual void updateRestrictions() override;
        std::atomic<bool> mEventHandlerRunning = true;
    protected:
        int32_t makeDPURestrictions();
        int32_t updateFeatureTable();
    protected:
        /**
         * Kernel event handling thread (e.g.) Vsync, hotplug, TUI enable events.
         */
        std::thread mEventHandlerThread;
        // Gathered DPU resctrictions
        dpu_dpp_info_t mDPUInfo;
        /* framebuffer fd for main display */
        int mDisplayFd;
};

#endif //_EXYNOSDEVICEFBINTERFACE_H
