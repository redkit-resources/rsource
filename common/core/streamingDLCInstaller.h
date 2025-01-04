/**
* Copyright © 2014 CD Projekt Red. All Rights Reserved.
*/
#pragma once

#include "contentListener.h"
#include "installer.h"

#ifdef RED_PLATFORM_CONSOLE

class CStreamingDLCInstaller : public IContentListener, public IContentInstaller
{
public:
	//!< IContentListener functions
	virtual const Char* GetName() const override;

	virtual void OnContentAvailable( const SContentInfo& contentInfo ) override;

public:
	//!< IContentInstaller functions
	virtual void Update( TDynArray< SContentPackageEvent >& outContentPackageEvents );
	virtual Bool Init() override;
	virtual Bool IsReady() const override;

private:
	TDynArray< SContentPackageEvent > m_pendingPackageEvents;
};

#endif