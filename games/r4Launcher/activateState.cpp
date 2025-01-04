/**
* Copyright © 2014 CD Projekt Red. All Rights Reserved.
*/

#include "build.h"
#include "activateState.h"
#include "utility.h"
#include "externDefinitions.h"
#include "states.h"

#include "../../common/redIO/redIO.h"

#include "../../games/r4/gameEngine.h"
#include "../../common/platformCommon/platform.h"
#include "../../common/game/configParser.h"

#if defined( RED_PLATFORM_ORBIS )
	#include <system_service.h>
	#include "r4MemoryOrbis.h"
	#define COMMAND_LINE_FILEPATH TXT( "/app0/bin/commandline.txt" )
#elif defined( RED_PLATFORM_DURANGO )
	#include "r4MemoryDurango.h"
	#define COMMAND_LINE_FILEPATH TXT( "g:\\bin\\commandline.txt" )
#elif defined( RED_PLATFORM_WINPC )
	#include "r4MemoryWindows.h"
	#define COMMAND_LINE_FILEPATH TXT( "commandline.txt" )
#endif
#include "../../common/core/cpuRecognizer.h"

#if defined(RED_PLATFORM_WINPC)
	#include <winuser.h>
#endif

#if defined(RED_PLATFORM_WINPC)
namespace GpuApi
{
	Bool HasMinimumRequiredGPU();
}
#endif

CActivateState::CActivateState( const wchar_t* commandLine )
:	m_rawCommandLine( commandLine )
{
}

#if defined( RED_PLATFORM_DURANGO )
static Bool IsCensoredArabicVersion()
{
	const GEOID geoID = GetUserGeoID( GEOCLASS_NATION );
	if ( geoID == GEOID_NOT_AVAILABLE )
	{
		RED_LOG_ERROR( TXT("Censor"), TXT("GetUserGeoID failed. Unable to acquire GeoID") );
		return false;
	}
	RED_LOG( TXT("Censor"), TXT("GEOID = 0x%x"), geoID );

	// TBD: Probably no real point getting ISO2 and ISO3, but as fallback just in case something changes

	// UAE and Saudi Arabia
	const wchar_t* censoredIso2[] = { L"AE", L"SA" };
	const wchar_t* censoredIso3[] = { L"ARE", L"SAU" };

	wchar_t iso2[3] = L"";
	wchar_t iso3[4] = L"";
	const Bool hasIso2 = ::GetGeoInfoW( geoID, GEO_ISO2, iso2, ARRAY_COUNT_U32( iso2 ), 0 ) != 0;
	if ( hasIso2 )
	{
		RED_LOG( TXT("Censor"), TXT("ISO2=%ls"), iso2 );
	}
	else
	{
		RED_LOG_WARNING( TXT("Censor"), TXT("GetGeoInfoW failed to get GEO_ISO2: LastError=0x%08X"), ::GetLastError() );
	}

	const Int32 hasIso3 = ::GetGeoInfoW( geoID, GEO_ISO3, iso3, ARRAY_COUNT_U32( iso3 ), 0 ) != 0;
	if ( hasIso3 )
	{
		RED_LOG( TXT("Censor"), TXT("ISO3=%ls"), iso3 );
	}
	else
	{
		RED_LOG_WARNING( TXT("Censor"), TXT("GetGeoInfoW failed to get GEO_ISO3: LastError=0x%08X"), ::GetLastError() );
	}
	
	if ( !hasIso2 && !hasIso3 )
	{
		RED_LOG_ERROR( TXT("Censor"), TXT("Failed to get GEO_ISO2 or GEOISO3") );
		return false;
	}

	if ( hasIso2 )
	{
		for ( Uint32 i = 0; i < ARRAY_COUNT_U32( censoredIso2 ); ++i )
		{
			if ( Red::System::StringCompareNoCase( iso2, censoredIso2[i] ) == 0 )
			{
				RED_LOG( TXT("Censor"), TXT("Found censored ISO2: %ls"), censoredIso2[i] );
				return true;
			}
		}
	}

	if ( hasIso3 )
	{
		for ( Uint32 i = 0; i < ARRAY_COUNT_U32( censoredIso3 ); ++i )
		{
			if ( Red::System::StringCompareNoCase( iso3, censoredIso3[i] ) == 0 )
			{
				RED_LOG( TXT("Censor"), TXT("Found censored ISO3: %ls"), censoredIso3[i] );
				return true;
			}
		}
	}

	RED_LOG( TXT("Censor"), TXT("No censored ISO found") );

	return false;
}
#elif defined( RED_PLATFORM_ORBIS )
static Bool IsCensoredArabicVersion()
{
	// #tbd: if resuming from suspension, in this case the game would need to be restarted
	SceSystemParamLang systemLanguage;
	Int32 err = ::sceSystemServiceParamGetInt( SCE_SYSTEM_SERVICE_PARAM_ID_LANG, &systemLanguage );
	if ( err != SCE_OK )
	{
		RED_LOG_ERROR( TXT("Censor"), TXT("sceSystemServiceParamGetInt() returned error code 0x%08X"), err );
		return false;
	}

	RED_LOG( TXT("Censor"), TXT("sceSystemServiceParamGetInt( SCE_SYSTEM_SERVICE_PARAM_ID_LANG): systemLanguage=%d"), systemLanguage);
	if ( systemLanguage == SCE_SYSTEM_PARAM_LANG_ARABIC )
	{
		RED_LOG( TXT("Censor"), TXT("System language is Arabic.") );
		return true;
	}

	RED_LOG( TXT("Censor"), TXT("System language is NOT Arabic.") );
	return false;
}
#elif defined( RED_PLATFORM_WINPC )
static Bool IsCensoredArabicVersion()
{
	return false;
}
#else
#error Unknown platform!
#endif

Red::System::Bool CActivateState::OnTick( IGameApplication& application )
{
	// Set up debug malloc if we are on Windows build
#if defined(RED_PLATFORM_WINPC) && defined(_DEBUG)
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

#if defined(RED_PLATFORM_WINPC)
	HardwareInstrumentation::CCpuRecognizer cpuRecognizer;
	if( cpuRecognizer.IsFeatureSupported( HardwareInstrumentation::ECpuFeature::SSE3 ) == false )
	{
		ERR_ENGINE( TXT("No SSE3 support. CPU does not meet minimal requirements.") );
		MessageBox( NULL, TXT("CPU does not meet minimal requirements. Support for SSE3 instructions is required."), TXT("Error"), MB_ICONHAND | MB_OK | MB_TASKMODAL | MB_SETFOREGROUND );
		return false;
	}

	//const Bool dumpScripts = Red::System::StringSearch( m_commandLine.AsChar(), TXT("-dumpscripts") ) != nullptr;
	const Bool dumpScripts = Red::System::StringSearch(m_rawCommandLine, TXT("-dumpscripts")) != nullptr;
	//const Bool verifyScripts = Red::System::StringSearch( m_commandLine.AsChar(), TXT( "-verifyscriptsandexit" ) ) != nullptr;
	const Bool verifyScripts = Red::System::StringSearch(m_rawCommandLine, TXT("-verifyscripsandexit")) != nullptr;

	if( !dumpScripts && !verifyScripts && GpuApi::HasMinimumRequiredGPU() == false )
	{
		ERR_ENGINE( TXT("No DirectX 11 support. GPU does not meet minimal requirements.") );
		MessageBox( NULL, TXT("GPU does not meet minimal requirements. Support for DirectX 11 is required."), TXT("Error"), MB_ICONHAND | MB_OK | MB_TASKMODAL | MB_SETFOREGROUND );
		return false;
	}
#endif

	RED_MEMORY_INITIALIZE( R4MemoryParameters );

	m_commandLine = m_rawCommandLine;

	SNamesPool::GetInstance().ReservePages( 14 );

	const Bool ioInit = Red::IO::Initialize();
	if ( !ioInit )
	{
		RED_FATAL( "Failed to initialize redIO" );
	}

	GIsGame = true;

	if( !InitializeGameConfiguration() )
	{
		return false;
	}

	InitialiseExternalClasses();

	if ( m_commandLine.Empty() )
	{
		if ( !GFileManager->LoadFileToString( COMMAND_LINE_FILEPATH, m_commandLine, true ) )
		{
#ifdef RED_PLATFORM_CONSOLE
			RED_FATAL( "No commandline specified and no commandline.txt - something's broken" );
			return false;
#endif
		}
	}

	Core::CommandLineArguments coreArguments;
	coreArguments.Parse( m_commandLine.AsChar() );

	// Pass pool parameters to gpu memory system AFTER command line is parsed
	auto poolParameterFn = []( Red::MemoryFramework::PoolLabel l, const Red::MemoryFramework::IAllocatorCreationParameters* p ) 
	{ 
		GpuApi::SetPoolParameters( l, p ); 
	};
	R4GpuMemoryParameters gpuMemoryPoolParameters( coreArguments );
	gpuMemoryPoolParameters.ForEachPoolParameter( poolParameterFn );

	CommandLineArguments arguments;
	ExtractCommandLineArguments( m_commandLine, arguments );

	CPlatform::SetVersionControlInitialiser( nullptr );
	CPlatform::SetAssertHandler( AssertMessage );

	// FIXME: The localization manager uses commandline argument (please check localizationManager.cpp) to decide whether
	// to use the DB connection. For various reasons we don't want to (ever) use localization data from the sql db with r4Laucnher.
	// Please remove after implementing the edior 'connect to sql db' button (it should use cooked data by default).
	m_commandLine += TXT( " -useCookedLocale" );

	if ( IsCensoredArabicVersion() )
	{
		RED_LOG( TXT("Censor"), TXT("Is CENSORED Arabic version") );
		m_commandLine += TXT( "-arabic" );
	}
	else
	{
		RED_LOG( TXT("Censor"), TXT("Is NOT censored Arabic version") );
	}

	CPlatform::Initialize( m_commandLine, coreArguments );
	
#ifndef RED_FINAL_BUILD
	RED_MEMORY_DUMP_POOL_MEMORY_REPORT( "ActivateState" );
#endif

	arguments.engineParameters.m_renderViewport = CPlatform::CreateViewport( false );
	GEngine = new CR4GameEngine( arguments.engineParameters, coreArguments );
	GEngine->SetSilentCompilationFeedback( arguments.silentScripts );

	application.RequestState( GameInitialize );

	return true;
}
