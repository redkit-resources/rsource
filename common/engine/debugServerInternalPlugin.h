/**
* Copyright � 2014 CD Projekt Red. All Rights Reserved.
* DrUiD
*/

#pragma once


//////////////////////////////////////////////////////////////////////////
// forwards
class CDebugServerPlugin;


//////////////////////////////////////////////////////////////////////////
// declarations
class CDebugServerInternalPlugin : public CDebugServerPlugin
{
	// common
	virtual Bool Init() final;
	virtual Bool ShutDown() final;

	// life-time
	virtual void GameStarted() final;
	virtual void GameStopped() final;
	virtual void AttachToWorld() final;
	virtual void DetachFromWorld() final;
	virtual void Tick() final;
};


//////////////////////////////////////////////////////////////////////////
// EOF
