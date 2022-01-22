#pragma once

#include "../engine_dll/ConVar.h"

namespace vgui
{
	typedef unsigned long HCursor;
}

enum ClientFrameStage_t
{
    FRAME_START = 0x0,
    FRAME_NET_UPDATE_START = 0x1,
    FRAME_NET_UPDATE_POSTDATAUPDATE_START = 0x2,
    FRAME_NET_UPDATE_POSTDATAUPDATE_END = 0x3,
    FRAME_NET_UPDATE_END = 0x4,
    FRAME_RENDER_START = 0x5,
    FRAME_RENDER_END = 0x6,
    FRAME_NET_FULL_FRAME_UPDATE_ON_REMOVE = 0x7,
    FRAME_UNDEFINED = 0xFFFFFFFF,
};

ConVar viewmodel_fov = ConVar("viewmodel_fov", "54", 0x80, "");
ConVar viewmodel_offset_randomize = ConVar(
    "viewmodel_offset_randomize",
    "0",
    0x4000,
    "randomly change viewmodel offsets to visualize range");

class ClientModeShared
{
public:
	float GetViewModelFOV();
};