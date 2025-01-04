#include "build.h"

#include "filePath.h"
#include "streamingDLCInstaller.h"

#ifdef RED_PLATFORM_CONSOLE
const Char* CStreamingDLCInstaller::GetName() const
{
	return TXT("StreamingDLCInstaller");
}

// #tbd: notified of a tick after the content, but should be OK since switching worlds after the content
// and so should have a tick
void CStreamingDLCInstaller::OnContentAvailable( const SContentInfo& contentInfo )
{
#if defined( RED_PLATFORM_ORBIS )
	const String mountPathBase = TXT("\\app0\\dlc\\");
#elif defined( RED_PLATFORM_DURANGO )
	const String mountPathBase = TXT("g:\\dlc\\");
#else
#error Unsupported platform!
#endif

	for ( const SContentFile* file : contentInfo.m_contentFiles )
	{
		const StringAnsi& path = file->m_path;
		CFilePath fp( ANSI_TO_UNICODE( path.AsChar() ) );
		if ( fp.GetExtension() != TXT("reddlclink"))
		{
			continue;
		}
		const String dlcLink = fp.GetFileName();
		if ( dlcLink.Empty() )
		{
			ERR_CORE(TXT("CStreamingDLCInstaller failed to get DLC link name from path: %hs"), path.AsChar() );
			continue;
		}

		const RuntimePackageID packageID = Helper::AllocRuntimePackageID();
		const Uint32 flags = eContentPackageMountFlags_AutoAttachChunks | eContentPackageMountFlags_IsHidden | eContentPackageMountFlags_IsStreamingDLC;
		String mountPath = String::Printf(TXT("%ls%ls/content/"), mountPathBase.AsChar(), dlcLink.AsChar());
		mountPath.ReplaceAll( TXT('/'), TXT('\\') );
		LOG_CORE(TXT("CStreamingDLCInstaller: DLC %ls available"), mountPath.AsChar());
		m_pendingPackageEvents.PushBack( SContentPackageEvent( packageID, mountPath.AsChar(), flags ) );
	}
}

//!< IContentInstaller functions
void CStreamingDLCInstaller::Update( TDynArray< SContentPackageEvent >& outContentPackageEvents )
{
	outContentPackageEvents.PushBack( m_pendingPackageEvents );
	m_pendingPackageEvents.ClearFast();
}

Bool CStreamingDLCInstaller::Init()
{
	return true;
}

Bool CStreamingDLCInstaller::IsReady() const
{ 
	return true; 
}

#endif