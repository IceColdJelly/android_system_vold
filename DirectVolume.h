/*
 * Copyright (C) 2008 The Android Open Source Project
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

#ifndef _DEVICEVOLUME_H
#define _DEVICEVOLUME_H

#include <utils/List.h>

#include "Volume.h"

typedef android::List<char *> PathCollection;

class DirectVolume : public Volume {
protected:
    PathCollection *mPaths;
    int            mPartIdx;
    int            mDiskMaj;
    int            mDiskNumParts;
    unsigned char  mPendingPartMap;

public:
    DirectVolume(const char *label, const char *mount_point, int partIdx);
    virtual ~DirectVolume();

    int addPath(const char *path);

    int handleBlockEvent(NetlinkEvent *evt);
protected:
    int prepareToMount(int *major, int *minor);

private:
    void handleDiskAdded(const char *devpath, NetlinkEvent *evt);
    void handleDiskRemoved(const char *devpath, NetlinkEvent *evt);
    void handlePartitionAdded(const char *devpath, NetlinkEvent *evt);
    void handlePartitionRemoved(const char *devpath, NetlinkEvent *evt);

};

typedef android::List<DirectVolume *> DirectVolumeCollection;

#endif