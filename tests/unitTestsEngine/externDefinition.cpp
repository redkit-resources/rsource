/**
 * Copyright � 2014 CD Projekt Red. All Rights Reserved.
 */

// ctremblay HACK this file is mostly an attempt at reducing dependency between engine lib and the rest of the world.


#include "build.h"

#include "../unitTestsFramework/environment.h"
#include "../unitTestsFramework/memoryInitializer.h"

#include "../../common/core/core.h"
#include "../../common/engine/engine.h"
#include "../../common/game/expOracle.h"
#include "../../common/gpuApiUtils/gpuApiInterface.h"
#include "../../common/engine/flashPlayerScaleform.h"
#include "../../common/core/scriptingSystem.h"

class ObjectInitializer : public testing::Environment
{
public:

	virtual void SetUp() override final
	{
		CObject::InitializeSystem();
		GScriptingSystem = new CScriptingSystem( L"" );
		extern void InitializeRTTI();
		InitializeRTTI();

	}
	virtual void TearDown() override final
	{}

};

namespace Red
{
namespace UnitTest
{
	void AddLocalTestEnvironment()
	{
		testing::AddGlobalTestEnvironment( new ObjectInitializer );
	}
}
}

void RegisterGameClasses()
{}

void RegisterGameNames()
{}

void RegisterCommonGameClasses()
{}

void RegisterCommonGameNames()
{}

void RegisterRendererNames()
{}

void RegisterCommonGameFunctions()
{}

void RegisterFlashFunctions()
{}

void CreateDebugPageCommunityLog()
{}

void RegisterGameDebugWindows()
{}

void ExportAnimationNatives()
{}

#ifndef RED_FINAL_BUILD
void ExportShowFlagsNatives()
{}
#endif

class CGame;
CGame * CreateGame(void)
{
	return nullptr;
}

namespace GpuApi
{
	TextureDataDesc::TextureDataDesc()
	{}

	Bool CompressImage( const TextureDataDesc& , TextureDataDesc&, EImageCompressionHint compressionHint, Float alphaThreshold /*= 0.5f*/ )
	{ 
		return false;	
	}

	Bool DecompressImage( const TextureDataDesc& , TextureDataDesc&  )
	{
		return false;
	}

	Int32 GetMonitorCount()
	{
		return 0;
	}

	Bool GetMonitorCoordinates( Int32 monitorIndex, Int32& top, Int32& left, Int32& bottom, Int32& right )
	{
		return false;
	}

	Bool EnumerateDisplayModes( Int32 monitorIndex, Uint32* outNum, DisplayModeDesc** outDescs /*= nullptr*/ )
	{
		return false;
	}

	void GetNativeResolution( Uint32 outputIndex, Int32& width, Int32& height )
	{
		width = 0;
		height = 0;
	}
}

class CEntity;
void EdExplorationDesc::GetDistAndAngleToTest( CEntity const * , Float& , Float& , Float& , Bool ignoreSpeed ) const
{}

class CNode;
EngineTransform CStoryScenePlayer_GetAbsoluteTransform( CNode*  )
{
	return EngineTransform();
}

RED_DEFINE_NAME( EExplorationType );
RED_DEFINE_NAME( ExpZComparision );
RED_DEFINE_NAME( ExpDoubleSided );

#ifdef RED_PLATFORM_DURANGO

struct SRawInputGamepadReading;
void DurangoHackGetGamepadReading(struct SRawInputGamepadReading &)
{}

struct SRawKeyboardEvent;
void DurangoHackGetKeyboardReading( SRawKeyboardEvent events[], Uint32* numEvents )
{}

struct SRawMouseReading
{
};

SRawMouseReading DurangoHackGetMouseReading()
{
	return SRawMouseReading();
}

#endif

#ifdef RED_PLATFORM_DURANGO
void DurangoHackForceCloseLog()
{

}
#endif