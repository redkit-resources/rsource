/**
* Copyright � 2015 CD Projekt Red. All Rights Reserved.

* Modified from Scaleform sources to reduce video microstuttering. Temporarily here
* to avoid having to rebuild the video library while tweaking.
*/

/**************************************************************************

Filename    :   Video_VideoSoundSystemPS4.h
Content     :   Video sound system implementation based on PS4 AudioOut library
Created     :   May 2014
Authors     :   Vladislav Merker

Copyright   :   Copyright 2014 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifdef USE_SCALEFORM
#ifdef RED_PLATFORM_ORBIS

#ifndef INC_GFX_VIDEO_SYSTEMSOUND_PS4_H
#define INC_GFX_VIDEO_SYSTEMSOUND_PS4_H

#include "GFxConfig.h"
#ifdef GFX_ENABLE_VIDEO

#include "Video/Video_Video.h"
#include "Kernel/SF_MemoryHeap.h"

namespace Scaleform { namespace GFx { namespace Video {

//////////////////////////////////////////////////////////////////////////
//

// VideoSoundSystemPS4 is a sample video sound system implementation based on AudioOut
// library used on the PS4 platform. An instance of this class is usually created and
// passed to the Video::SetSoundSystem method as a part of GFx video initialization.

class VideoSoundSystemPS4Tmp : public VideoSoundSystem
{
public:
	VideoSoundSystemPS4Tmp(MemoryHeap *pheap = Memory::GetGlobalHeap()) :
		VideoSoundSystem(pheap), pHeap(pheap) {}
	~VideoSoundSystemPS4Tmp() {}

	virtual VideoSound *Create();

private:
	MemoryHeap *pHeap;
}; 

}}} // Scaleform::GFx::Video

#endif // GFX_ENABLE_VIDEO

#endif // INC_GFX_VIDEO_SYSTEMSOUND_PS4_H

#endif // RED_PLATFORM_ORBIS
#endif // USE_SCALEFORM