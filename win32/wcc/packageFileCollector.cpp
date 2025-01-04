/**
 * Copyright © 2014 CD Projekt Red. All Rights Reserved.
 */

#include "build.h"

#include "../../common/redSystem/crt.h"
#include "../../common/core/contentManifest.h"
#include "../../common/core/contentManifestParser.h"
#include "../../common/core/stringConversion.h"

#include "packageFileCollector.h"
#include "packageConstants.h"
#include "packageFiles.h"

static const Char FORBIDDEN_CHARS[] = { TXT('*'), TXT(':'), TXT(';'), TXT('?'), TXT('\"'), TXT('<'), TXT('>'), TXT('|'), TXT('/'), TXT('\\'), };

Bool CPackageFileCollector::GenerateOnDiscDLCContentManifest( const String& projectAbsolutePath, const SPackageFiles& packageFiles ) const
{
	if ( !m_isGOTY )
	{
		ERR_WCC(TXT("GenerateOnDiscDLCContentManifest requires GOTY flag!"));
		return false;
	}
	// #fixme: PS4 if ever want to add more DLC to the base game during a patch
	// Need to allow for Patches on XBox, or else the packaging tool will think we deleted a file
	if ( m_packageType == ePackageType_Dlc )
	{
		// #tbd: not supporting ADDING or REMOVING files from on disc DLC, so shouldn't replace the DLC manifest file,
		// the contents of which would need merging with the base
		ERR_WCC(TXT("GenerateOnDiscDLCContentManifest doesn't support content manifest merging!"));
		return false;
	}

	// at this point, any unwanted files should have been filtered out and removed, including DLC directories that shouldn't be included
	String normalizedProjectAbsolutePath = projectAbsolutePath.ToLower();
	normalizedProjectAbsolutePath.ReplaceAll(TXT('/'), TXT('\\'));
	if ( !normalizedProjectAbsolutePath.EndsWith(TXT("\\")) )
	{
		normalizedProjectAbsolutePath += TXT('\\');
	}

	const String dlcRootDir = normalizedProjectAbsolutePath + TXT("dlc\\");
	TDynArray< String > dlcDirs;
	GFileManager->FindDirectories( dlcRootDir, dlcDirs );
	for ( const String& dlcDir : dlcDirs )
	{
		const String dlcAbsolutePath = dlcRootDir + dlcDir + TXT("\\");
		const String dlcManifest = dlcAbsolutePath + TXT("content\\content.xml");
		if ( !GFileManager->FileExist( dlcManifest ) )
		{
			ERR_WCC(TXT("Can't find DLC stub manifest %ls"), dlcManifest.AsChar());
			return false;
		}

		// Perform a non-recursive directory scan to find cache files
		// Should only add files that were gathered!
		TDynArray< String > absolutePaths;

 		GFileManager->FindFiles( dlcAbsolutePath, TXT("*.*"), absolutePaths, true );
 		for ( String& path : absolutePaths )
 		{
 			path.ReplaceAll( TXT("/"), TXT("\\") );
 		}

		// Brute force check, but not that many files
		struct DlcFinder
		{
			static Bool FindInContent( const String localPath, const SPackageFiles& packageFiles )
			{
				Bool fileFound = false;
				for ( const auto& it : packageFiles.m_gameContentFilesMap )
				{
					const auto& onDiscDLC = it.m_second.m_onDiscDLCFiles;
					for ( const String& localPathFile : onDiscDLC )
					{
						if ( localPathFile == localPath )
						{
							fileFound = true;
							break;
						}
					}
				}
				return fileFound;
			}

			static Bool FindInEP1( const String localPath, const SPackageFiles& packageFiles )
			{
				Bool fileFound = false;
				for ( const String& localPathFile : packageFiles.m_ep1Files )
				{
					if ( localPathFile == localPath )
					{
						fileFound = true;
						break;
					}
				}

				return fileFound;
			}

			static Bool FindInEP2( const String localPath, const SPackageFiles& packageFiles )
			{
				Bool fileFound = false;
				for ( const String& localPathFile : packageFiles.m_ep2Files )
				{
					if ( localPathFile == localPath )
					{
						fileFound = true;
						break;
					}
				}

				return fileFound;
			}
		};

		for ( Int32 j = absolutePaths.SizeInt() - 1; j >= 0; --j )
		{
			String localPath;
			const String& file = absolutePaths[j];
			if ( !ConvertToLocalProjectPath( projectAbsolutePath, file, localPath ) )
			{
				ERR_WCC(TXT("Failed to convert to local path %ls"), file.AsChar());
				return false;
			}
			
			String tempBuf;
			localPath = CFilePath::ConformPath( localPath, tempBuf );

			// Remove content.xml from indexing itself
			if ( localPath.EndsWith( TXT("\\content\\content.xml")) )
			{
				LOG_WCC(TXT("DLC content.xml skipping (self) content.xml %ls"), file.AsChar());
				absolutePaths.RemoveAt( j );
				continue;
			}

			Bool fileFound = false;
			if ( dlcDir.EqualsNC( TXT("bob") ) )
				fileFound = DlcFinder::FindInEP2(localPath, packageFiles);
			else if ( dlcDir.EqualsNC( TXT("ep1") ) )
				fileFound = DlcFinder::FindInEP1(localPath, packageFiles);
			else if ( dlcDir.ToLower().BeginsWith( TXT("dlc") ) )
				fileFound = DlcFinder::FindInContent(localPath, packageFiles);
			else
			{
				ERR_WCC(TXT("Unrecognized DLC %ls"), dlcDir.AsChar() );
				return false;
			}

			if ( !fileFound )
			{
				if ( !file.EndsWith( TXT(".w3speech")) && !file.EndsWith( TXT(".w3strings") ) )
				{
					ERR_WCC(TXT("Internal error? Can't find file in local DLC group: %ls"), file.AsChar());
					return false;
				}
				LOG_WCC(TXT("DLC content.xml skipping file %ls"), file.AsChar());
				absolutePaths.RemoveAt( j );
			}
		}

		const String rootDir = dlcAbsolutePath + TXT("content\\");
		SContentChunk newContentChunk;
		Red::System::DateTime timestamp;

		// #tbd: how much it really matters anymore, or just dlc0? Look at speech/text merging
		const CName chunkName = CName( TXT("dlc0") );
		if ( !Helper::CreateContentChunk( newContentChunk, timestamp, chunkName, absolutePaths, rootDir, true, true /*skip creating CRC, never used*/ ) )
		{
			return false;
		}

		SContentManifest contentManifest;
		contentManifest.m_contentPack.m_id = CName(dlcDir.ToLower());
		contentManifest.m_contentPack.m_contentChunks.PushBack( Move( newContentChunk ) );

		CContentManifestWriter manifestWriter( contentManifest );
		String manifestXml;
		if ( !manifestWriter.ParseManifest( manifestXml ) )
		{
			ERR_WCC(TXT("Failed to parse manifest XML!"));
			return false;
		}

		if ( ! GFileManager->SaveStringToFile( dlcManifest, manifestXml ) )
		{
			ERR_WCC(TXT("Failed to save content manifest for file '%ls'"), dlcManifest.AsChar() );
			return false;
		}
	}

	return true;
}

CPackageFileCollector::CPackageFileCollector( EPackageType packageType, Bool isGOTY )
	: m_packageType( packageType )
	, m_isGOTY( isGOTY )
{
	const Char* const EXTENSIONS_TO_IGNORE[] = { 
		RED_DLCLINK_EXT,
		TXT("fx"), TXT("pdb"), TXT("a"), TXT("lib"), TXT("pri"), TXT("lnk"), TXT("db"), TXT("gp4"), TXT("iso"), TXT("ws"), TXT("manifest"), TXT("log"), TXT("bat")
	};
	TDynArray< String > extensionsToIngore;
	for ( Uint32 i = 0; i < ARRAY_COUNT_U32(EXTENSIONS_TO_IGNORE); ++i )
	{
		m_extensionsToIgnore.PushBack( EXTENSIONS_TO_IGNORE[i] );
	}
}

void CPackageFileCollector::AddExtensionsToIgnore( const TDynArray< String >& extensions )
{
	m_extensionsToIgnore.PushBack( extensions );
}

Bool CPackageFileCollector::CollectPackageFiles( const String& projectAbsolutePath, SPackageFiles& outPackageFiles ) const
{
	String normalizedProjectAbsolutePath = projectAbsolutePath.ToLower();
	normalizedProjectAbsolutePath.ReplaceAll(TXT('/'), TXT('\\'));
	if ( !normalizedProjectAbsolutePath.EndsWith(TXT("\\")) )
	{
		normalizedProjectAbsolutePath += TXT('\\');
	}

	// TODO: Should validate contents aren't missing or extra unallowed stuff (not .prx in sce_module)
	// Or prx in bin and already in sce_sys. Shouldn't have DLLs or PRX files in game content dirs
	SPackageFiles newPackageFiles;
	TDynArray< String > dirs;
	GFileManager->FindDirectories( normalizedProjectAbsolutePath, dirs );

	for ( String& dir : dirs )
	{
		dir += TXT("\\");

		if ( ! ProcessDirectory( normalizedProjectAbsolutePath, dir, newPackageFiles ) )
		{
			return false;
		}
	}

	outPackageFiles = Move( newPackageFiles );

	return true;	
}

static Bool ParsePatchNumber( const Char* patchName, Uint32& outPatchNumber )
{
	const Char* patchPostfix = patchName + Red::System::StringLength(PATCH_NAME_PREFIX);
	if ( !GParseInteger( patchPostfix, outPatchNumber ) )
	{
		ERR_WCC(TXT("Patch dir '%ls' must end with a content number"), patchName);
		return false;
	}

	return true;
}

static Bool ParseContentNumber( const Char* contentName, Uint32& outContentNumber )
{
	const Char* contentPostfix = contentName + Red::System::StringLength(CONTENT_NAME_PREFIX);
	if ( !GParseInteger( contentPostfix, outContentNumber ) )
	{
		ERR_WCC(TXT("Content dir '%ls' must end with a content number"), contentName);
		return false;
	}

	return true;
}

Bool CPackageFileCollector::ProcessDirectory( const String& normalizedProjectAbsolutePath, const String& dirPath, SPackageFiles& outPackageFile ) const
{
	if ( dirPath.BeginsWith(GAME_BIN_DIR) )
	{
		if ( ! AddGameBinaryDirectory( normalizedProjectAbsolutePath, dirPath, outPackageFile ) )
		{
			return false;
		}
	}
	else if ( dirPath.BeginsWith(CONTENT_DIR) )
	{
		TDynArray< String > contentDirs;
		const String& contentAbsolutePath = normalizedProjectAbsolutePath + dirPath;

		// Kind of a hack
		const Char* storeFiles[] = { TXT("metadata.store"), TXT("metadata.censored.store") };
		for ( Uint32 i = 0; i < ARRAY_COUNT_U32( storeFiles ); ++i )
		{
			String metadataStoreFilePath = contentAbsolutePath + storeFiles[i];
			if ( GFileManager->FileExist( metadataStoreFilePath ) )
			{
				String localPath;
				if ( ConvertToLocalProjectPath( normalizedProjectAbsolutePath, metadataStoreFilePath, localPath ) )
				{
					String tempPath;
					metadataStoreFilePath = Move( CFilePath::ConformPath( localPath, tempPath ) );
					outPackageFile.m_gameBinFiles.PushBack( Move( metadataStoreFilePath ) );
				}
			}
		}
		
		// Allow patch directories to replace content files, for those ones that are unaware of the patch mechanism. E.g., static shader cache, scripts, etc
		if ( m_packageType == ePackageType_App || m_packageType == ePackageType_Patch )
		{
			GFileManager->FindDirectories( contentAbsolutePath, contentDirs );
			for ( const String& contentDir : contentDirs )
			{
				const String& contentName = contentDir;
				const String contentDepotPath = dirPath + contentDir + TXT("\\");
				if ( contentName.BeginsWith( CONTENT_NAME_PREFIX ) )
				{
					Uint32 contentNumber = 0;
					if ( !ParseContentNumber(contentName.AsChar(), contentNumber) )
					{
						return false;
					}
					if ( ! AddGameContentDirectory( contentNumber, normalizedProjectAbsolutePath, contentDepotPath, outPackageFile ) )
					{
						return false;
					}
				}
				else if ( m_packageType == ePackageType_Patch && contentName.BeginsWith( PATCH_NAME_PREFIX ) )
				{
					Uint32 patchNumber = 0;
					if ( !ParsePatchNumber(contentName.AsChar(), patchNumber) )
					{
						return false;
					}
					if ( ! AddGamePatchDirectory( patchNumber, normalizedProjectAbsolutePath, contentDepotPath, outPackageFile ) )
					{
						return false;
					}
				}
				else
				{
					ERR_WCC(TXT("Content dir '%ls' {%ls} must start with prefix '%ls'"), contentDir.AsChar(), (normalizedProjectAbsolutePath+contentDir).AsChar(), CONTENT_NAME_PREFIX);
					return false;
				}
			}
		}
		else if ( m_packageType == ePackageType_Dlc )
		{
			// Almost like an app layout, only there's no content0, content1 etc, all data starts in content
			// E.g.,
			/*
			    [addcont0] <- mount point
				\sce_sys\*
				\content
				\content\metadata.store
				\content\bundles\*.bundle
				\content\*.cache
				\content\*.w3speech
				etc...
			*/
			Uint32 contentNumber = 0;
			const String contentDepotPath = dirPath;
			if ( ! AddGameContentDirectory( contentNumber, normalizedProjectAbsolutePath, contentDepotPath, outPackageFile ) )
			{
				return false;
			}
		}
		else
		{
			ERR_WCC(TXT("Unhandled package type %u"), m_packageType );
			return false;
		}
	}
	else if ( dirPath.BeginsWith(DLC_DIR) )
	{
		if ( !m_isGOTY )
		{
			ERR_WCC(TXT("Top level DLC dir only allowed if GOTY!"));
			return false;
		}

		// On disc DLC only
		if ( m_packageType == ePackageType_Dlc )
		{
			ERR_WCC(TXT("Actual downloadable DLC shouldn't have a top level DLC dir!"));
			return false;
		}

		TDynArray< String > dlcDirs;
		const String& dlcAbsolutePath = normalizedProjectAbsolutePath + dirPath;

		// Allow patch directories to replace content files, for those ones that are unaware of the patch mechanism. E.g., static shader cache, scripts, etc
		
		// #fixme: hardcoded hackery
		GFileManager->FindDirectories( dlcAbsolutePath, dlcDirs );
		for ( const String& dlcDir : dlcDirs )
		{
			// Need to touch the file so included in the list of files, but don't know the contents until language files have been filtered out later
			{
				const String dlcContentManifestPathStub = dlcAbsolutePath + dlcDir + TXT("\\content\\content.xml");
				Red::TScopedPtr< IFile > writer( GFileManager->CreateFileWriter( dlcContentManifestPathStub, FOF_AbsolutePath ) );
				if ( !writer )
				{
					ERR_WCC(TXT("Failed to create DLC content manifest stub: %ls"), dlcContentManifestPathStub.AsChar());
					return false;
				}
			}
			
			// #tbd: cleanup should delete reddlclink files
			struct DLCLinkCreator : Red::System::NonCopyable
			{
				explicit DLCLinkCreator( const String& normalizedProjectAbsolutePath )
					: m_normalizedProjectAbsolutePath( normalizedProjectAbsolutePath )
				{}

				Bool CreateLink( Uint32 contentNumber, const String& dlcName, String& outLinkName ) const
				{
					const String linkPath = String::Printf( TXT("%lscontent\\content%d\\%ls.reddlclink"), m_normalizedProjectAbsolutePath.AsChar(), contentNumber, dlcName.ToLower().AsChar() );
					Red::TScopedPtr< IFile > writer( GFileManager->CreateFileWriter( linkPath, FOF_AbsolutePath ) );
					if ( !writer )
					{
						ERR_WCC(TXT("Failed to create DLC link: %ls"), linkPath.AsChar());
						return false;
					}

					// Make it non-zero size in case any checks or packaging tools later complain
					Uint8 buf = 0;
					writer->Serialize( &buf, sizeof(buf) );

					String localPath;
					if ( ! ConvertToLocalProjectPath( m_normalizedProjectAbsolutePath, linkPath, localPath ) )
					{
						return false;
					}

					String tempBuf;
					outLinkName = CFilePath::ConformPath( localPath, tempBuf );

					return true;
				}

			private:
				const String& m_normalizedProjectAbsolutePath;
			};

			const String& dlcName = dlcDir;
			const String dlcDepotPath = dirPath + dlcDir + TXT("\\");
			if ( dlcName.EqualsNC(TXT("bob")) ) // bob == EP2
			{
				const Uint32 contentNumber = HACK_NOVIGRAD_CONTENT_NUMBER;
				DLCLinkCreator linker( normalizedProjectAbsolutePath );
				String linkConformedPath;
				if ( !linker.CreateLink( contentNumber, dlcName, linkConformedPath ) )
				{
					return false;
				}
				outPackageFile.m_ep2Files.PushBack( linkConformedPath );	
				if ( !AddEP2DLCDirectory( normalizedProjectAbsolutePath, dlcDepotPath, outPackageFile ) )
				{
					return false;
				}
			}
			else if ( dlcName.EqualsNC(TXT("ep1")) )
			{
				const Uint32 contentNumber = HACK_NOVIGRAD_CONTENT_NUMBER;
				DLCLinkCreator linker( normalizedProjectAbsolutePath );
				String linkConformedPath;
				if ( !linker.CreateLink( contentNumber, dlcName, linkConformedPath ) )
				{
					return false;
				}
				outPackageFile.m_ep1Files.PushBack( linkConformedPath );	
				if ( !AddEP1DLCDirectory( normalizedProjectAbsolutePath, dlcDepotPath, outPackageFile ) )
				{
					return false;
				}
			}
			else if ( dlcName.ToLower().BeginsWith(TXT("dlc")) )
			{
				const Uint32 contentNumber = HACK_DLC_CONTENT_NUMBER;
				DLCLinkCreator linker( normalizedProjectAbsolutePath );
				String linkConformedPath;
				if ( !linker.CreateLink( contentNumber, dlcName, linkConformedPath ) )
				{
					return false;
				}
				outPackageFile.m_gameContentFilesMap.GetRef(contentNumber).m_onDiscDLCFiles.PushBack( linkConformedPath );
				if ( !AddOnDiscDLCDirectory( contentNumber, normalizedProjectAbsolutePath, dlcDepotPath, outPackageFile ) )
				{
					return false;
				}
			}
			else
			{
				// #tbd: VO DLCs if accidentally includeds
				ERR_WCC(TXT("Unrecognized DLC package %ls"), dlcName.AsChar());
				return false;
			}
		}
	}
	else if ( !dirPath.BeginsWith(TXT("sce_") ) )
	{
		WARN_WCC(TXT("Adding unknown dir '%ls' {%ls} to default content%u"), dirPath.AsChar(), (normalizedProjectAbsolutePath + dirPath).AsChar(), DEFAULT_CONTENT_NAME_NUMBER );
		if ( ! AddGameContentDirectory( DEFAULT_CONTENT_NAME_NUMBER, normalizedProjectAbsolutePath, dirPath, outPackageFile ) )
		{
			return false;
		}
		return true;
	}
	else
	{
		ERR_WCC(TXT("Unhandled directory '%ls'"), dirPath.AsChar() );
		return false;
	}

	return true;
}

Bool CPackageFileCollector::AddGamePatchDirectory( Uint32 patchNumber, const String& projectAbsolutePath, const String& depotPath, SPackageFiles& outPackageFiles ) const
{
	if ( depotPath.BeginsWith(TXT("sce_")) || depotPath.BeginsWith(TXT("eboot")) || depotPath.BeginsWith(TXT("standby_screen")) )
	{
		ERR_WCC(TXT("Cannot add reserved SCE directory as patch: patch%u: '%ls'"), patchNumber, depotPath.AsChar());
		return false;
	}

	TDynArray< String > newFiles;
	if ( ! PopulateFilesFromDirectory( projectAbsolutePath, depotPath, newFiles ) )
	{
		return false;
	}

	for ( Int32 j = newFiles.SizeInt()-1; j >= 0; --j )
	{
		const String& file = newFiles[ j ];
		if ( file.EndsWith( SYS_PRX_EXT ) )
		{
			ERR_WCC(TXT("PRX '%ls' can't go in game patch patch%u"), file.AsChar(), patchNumber );
			return false;
		}
		else if ( file.EndsWith( SYS_ELF_EXT ) )
		{
			ERR_WCC(TXT("ELF '%ls' can't go in game patch patch%u"), file.AsChar(), patchNumber );
			return false;
		}
	}

	TDynArray<String>& patchFiles = outPackageFiles.m_gamePatchFilesMap.GetRef( patchNumber );
	patchFiles.PushBack( newFiles );

	return true;
}

Bool CPackageFileCollector::AddGameContentDirectory( Uint32 contentNumber, const String& projectAbsolutePath, const String& depotPath, SPackageFiles& outPackageFiles ) const
{
	if ( depotPath.BeginsWith(TXT("sce_")) || depotPath.BeginsWith(TXT("eboot")) || depotPath.BeginsWith(TXT("standby_screen")) )
	{
		ERR_WCC(TXT("Cannot add reserved SCE directory as content: content%u: '%ls'"), contentNumber, depotPath.AsChar());
		return false;
	}

	TDynArray< String > newFiles;
	if ( ! PopulateFilesFromDirectory( projectAbsolutePath, depotPath, newFiles ) )
	{
		return false;
	}

	for ( Int32 j = newFiles.SizeInt()-1; j >= 0; --j )
	{
		const String& file = newFiles[ j ];
		if ( file.EndsWith( SYS_PRX_EXT ) )
		{
			ERR_WCC(TXT("PRX '%ls' can't go in game content content%u"), file.AsChar(), contentNumber );
			return false;
		}
		else if ( file.EndsWith( SYS_ELF_EXT ) )
		{
			ERR_WCC(TXT("ELF '%ls' can't go in game content content%u"), file.AsChar(), contentNumber );
			return false;
		}
	}

	SPackageGameFiles& gameFiles = outPackageFiles.m_gameContentFilesMap.GetRef( contentNumber );
	MoveGameFilesByExtension( newFiles, gameFiles );

	return true;
}

Bool CPackageFileCollector::AddOnDiscDLCDirectory( Uint32 contentNumber, const String& projectAbsolutePath, const String& depotPath, SPackageFiles& outPackageFiles ) const
{
	if ( depotPath.BeginsWith(TXT("sce_")) || depotPath.BeginsWith(TXT("eboot")) || depotPath.BeginsWith(TXT("standby_screen")) )
	{
		ERR_WCC(TXT("Cannot add reserved SCE directory as content: content%u: '%ls'"), contentNumber, depotPath.AsChar());
		return false;
	}

	TDynArray< String > newFiles;
	if ( ! PopulateFilesFromDirectory( projectAbsolutePath, depotPath, newFiles ) )
	{
		return false;
	}

	for ( Int32 j = newFiles.SizeInt()-1; j >= 0; --j )
	{
		const String& file = newFiles[ j ];
		if ( file.EndsWith( SYS_PRX_EXT ) )
		{
			ERR_WCC(TXT("PRX '%ls' can't go in game content content%u"), file.AsChar(), contentNumber );
			return false;
		}
		else if ( file.EndsWith( SYS_ELF_EXT ) )
		{
			ERR_WCC(TXT("ELF '%ls' can't go in game content content%u"), file.AsChar(), contentNumber );
			return false;
		}
	}

	SPackageGameFiles& gameFiles = outPackageFiles.m_gameContentFilesMap.GetRef( contentNumber );
	
	// Can't move them, since appending from other DLCs too
	gameFiles.m_onDiscDLCFiles.PushBack( newFiles );

	return true;
}

Bool CPackageFileCollector::AddEP1DLCDirectory( const String& projectAbsolutePath, const String& depotPath, SPackageFiles& outPackageFiles ) const
{
	if ( depotPath.BeginsWith(TXT("sce_")) || depotPath.BeginsWith(TXT("eboot")) || depotPath.BeginsWith(TXT("standby_screen")) )
	{
		ERR_WCC(TXT("Cannot add reserved SCE directory as EP1 content: '%ls'"), depotPath.AsChar());
		return false;
	}

	TDynArray< String > newFiles;
	if ( ! PopulateFilesFromDirectory( projectAbsolutePath, depotPath, newFiles ) )
	{
		return false;
	}

	for ( Int32 j = newFiles.SizeInt()-1; j >= 0; --j )
	{
		const String& file = newFiles[ j ];
		if ( file.EndsWith( SYS_PRX_EXT ) )
		{
			ERR_WCC(TXT("PRX '%ls' can't go in EP1"), file.AsChar() );
			return false;
		}
		else if ( file.EndsWith( SYS_ELF_EXT ) )
		{
			ERR_WCC(TXT("ELF '%ls' can't go in EP1"), file.AsChar() );
			return false;
		}
	}

	TDynArray<String>& ep1Files = outPackageFiles.m_ep1Files;

	// Can't move them, since appending from other DLCs too
	ep1Files.PushBack( newFiles );

	return true;
}

Bool CPackageFileCollector::AddEP2DLCDirectory( const String& projectAbsolutePath, const String& depotPath, SPackageFiles& outPackageFiles ) const
{
	if ( depotPath.BeginsWith(TXT("sce_")) || depotPath.BeginsWith(TXT("eboot")) || depotPath.BeginsWith(TXT("standby_screen")) )
	{
		ERR_WCC(TXT("Cannot add reserved SCE directory as EP2 content: '%ls'"), depotPath.AsChar());
		return false;
	}

	TDynArray< String > newFiles;
	if ( ! PopulateFilesFromDirectory( projectAbsolutePath, depotPath, newFiles ) )
	{
		return false;
	}

	for ( Int32 j = newFiles.SizeInt()-1; j >= 0; --j )
	{
		const String& file = newFiles[ j ];
		if ( file.EndsWith( SYS_PRX_EXT ) )
		{
			ERR_WCC(TXT("PRX '%ls' can't go in EP2"), file.AsChar() );
			return false;
		}
		else if ( file.EndsWith( SYS_ELF_EXT ) )
		{
			ERR_WCC(TXT("ELF '%ls' can't go in EP2"), file.AsChar() );
			return false;
		}
	}

	TDynArray<String>& ep2Files = outPackageFiles.m_ep2Files;

	// Can't move them, since appending from other DLCs too
	ep2Files.PushBack( newFiles );

	return true;
}

Bool CPackageFileCollector::AddGameBinaryDirectory( const String& projectAbsolutePath, const String& depotPath, SPackageFiles& outPackageFiles ) const
{
// 	if ( depotPath.BeginsWith(TXT("sce_")) || depotPath.BeginsWith(TXT("eboot")) || depotPath.BeginsWith(TXT("standby_screen")) )
// 	{
// 		ERR_WCC(TXT("Cannot add reserved SCE directory as bin: '%ls'"), depotPath.AsChar());
// 		return false;
// 	}

	TDynArray< String > newFiles;
	if ( ! PopulateFilesFromDirectory( projectAbsolutePath, depotPath, newFiles ) )
	{
		return false;
	}

	for ( Int32 j = newFiles.SizeInt()-1; j >= 0; --j )
	{
		const String& file = newFiles[ j ];
		if ( file.EndsWith( SYS_PRX_EXT ) || file.EndsWith( SYS_DLL_EXT ) )
		{
			outPackageFiles.m_dynLibFiles.PushBack( Move( file ) );
			newFiles.RemoveAt( j );
		}
		else if ( file.EndsWith( SYS_ELF_EXT ) || file.EndsWith( SYS_EXE_EXT ) )
		{
			outPackageFiles.m_exeFiles.PushBack( Move( file ) );
			newFiles.RemoveAt( j );
		}
	}

	outPackageFiles.m_gameBinFiles.PushBack( Move( newFiles ) );

	return true;
}

Bool CPackageFileCollector::AddSystemDirectory( const String& projectAbsolutePath, const String& depotPath, SPackageFiles& outPackageFiles ) const
{
	TDynArray< String > newFiles;
	if ( ! PopulateFilesFromDirectory( projectAbsolutePath, depotPath, newFiles ) )
	{
		return false;
	}

	for ( Uint32 i = 0 ; i < newFiles.Size(); ++i )
	{
		const String& file = newFiles[ i ];
		if ( file.EndsWith( SYS_PRX_EXT ) )
		{
			ERR_WCC(TXT("PRX '%ls' can't go in system directory"), file.AsChar() );
			return false;
		}
		else if ( file.EndsWith( SYS_ELF_EXT ) )
		{
			ERR_WCC(TXT("ELF '%ls' can't go in system directory"), file.AsChar() );
			return false;
		}
	}

	outPackageFiles.m_sysFiles.PushBack( Move( newFiles ) );

	return true;
}

Bool CPackageFileCollector::PopulateFilesFromDirectory( const String& projectAbsolutePath, const String& depotPath, TDynArray< String >& outFiles ) const
{
	const String absolutePath = projectAbsolutePath + depotPath;
	TDynArray< String > files;
	GFileManager->FindFiles( absolutePath, TXT("*.*"), files, true );
	for ( Int32 j = files.SizeInt()-1; j >= 0; --j )
	{
		String& file = files[j];
		String localPath;
		if ( ! ConvertToLocalProjectPath( projectAbsolutePath, file, localPath ) )
		{
			return false;
		}

		String tempPath;
		file = Move( CFilePath::ConformPath( localPath, tempPath ) );

		// Remove before validation
		const String ext = CFilePath( file ).GetExtension();
		if ( m_extensionsToIgnore.Exist( ext ) )
		{
			files.RemoveAt( j );
			continue;
		}
		
		if ( !ValidateLocalAppPath(file) )
		{
			return false;
		}
	}
	outFiles.PushBack( Move(files) );

	return true;
}

Bool CPackageFileCollector::ConvertToLocalProjectPath( const String& projectAbsolutePath, const String& absolutePath, String& localPath )
{
	// Strip absolute path of this directory
	StringBuffer<512> absolutePathBuf( absolutePath );

	StringBuffer<512> directoryAbsolutePathBuf( projectAbsolutePath.AsChar() );

	absolutePathBuf.ToLower();
	directoryAbsolutePathBuf.ToLower();
	absolutePathBuf[ directoryAbsolutePathBuf.Size() ] = 0;

	// find if it begins with 
	if ( absolutePathBuf == directoryAbsolutePathBuf )
	{
		localPath = absolutePath.ToLower().StringAfter( projectAbsolutePath.ToLower() );
		return true;
	}

	// Not a local path
	ERR_WCC(TXT("Failed to convert path '%ls' to local app path"), absolutePath.AsChar() );
	return false;
}

Bool CPackageFileCollector::ValidateLocalAppPath( const String& path ) const
{
	if ( path.GetLength() > MAX_PATH_LENGTH )
	{
		ERR_WCC(TXT("Entire path '%ls' is too long for the PS4 (length %u, max %u)'"), path.AsChar(), path.GetLength(), MAX_PATH_LENGTH );
		return false;
	}

	if ( path.Empty() )
	{
		ERR_WCC(TXT("Entire path is empty"));
		return false;
	}

	CFilePath filePath( path );
	// Not sure why this doesn't return a const ref
	TDynArray< String > dirs = filePath.GetDirectories();
	const Uint32 dirDepth = dirs.Size() + (filePath.HasFilename() ? 1 : 0);
	if ( dirDepth > MAX_DIR_DEPTH )
	{
		ERR_WCC(TXT("Path '%ls' with depth %u exceeds the %u level directory depth"), path.AsChar(), dirDepth, MAX_DIR_DEPTH );
		return false;
	}

	if ( filePath.HasFilename() )
	{
		if ( ! ValidatePathComponent( filePath.GetFileNameWithExt() ) )
		{
			return false;
		}
	}

	for ( const String& dir : dirs )
	{
		if ( dir.GetLength() > MAX_ENTRY_LENGTH )
		{
			ERR_WCC(TXT("Dir '%ls' is too long for the PS4 (length %u, max %u) in path '%ls'"), dir.AsChar(), dir.GetLength(), MAX_ENTRY_LENGTH );
			return false;
		}
		if ( ! ValidatePathComponent( dir ) )
		{
			return false;
		}
	}

	const String fileNameWithExt = filePath.GetFileNameWithExt();
	if ( fileNameWithExt.GetLength() > MAX_ENTRY_LENGTH )
	{
		ERR_WCC(TXT("File '%ls' is too long for the PS4 (length %u, max %u) in path '%ls'"), fileNameWithExt.AsChar(), fileNameWithExt.GetLength(), MAX_ENTRY_LENGTH );
		return false;
	}

	return true;
}

Bool CPackageFileCollector::ValidatePathComponent( const String& pathComponent ) const
{
	for ( const Char* pch = pathComponent.AsChar(); *pch; ++pch )
	{
		const Char ch = *pch;
		if ( (Uint32)ch >= 0x7F || ((Uint32)ch >= 0x0 && (Uint32)ch <= 0x1F) )
		{
			ERR_WCC(TXT("Path component '%ls' contains illegal character '%lc'"), pathComponent.AsChar(), ch );
			return false;
		}
		for ( Uint32 j = 0; j < ARRAY_COUNT_U32(FORBIDDEN_CHARS); ++j )
		{
			if ( ch == FORBIDDEN_CHARS[j] )
			{
				ERR_WCC(TXT("Path component contains illegal character '%lc'"), pathComponent.AsChar(), ch );
				return false;
			}
		}
	}

	return true;
}

void CPackageFileCollector::MoveGameFilesByExtension( TDynArray< String >& inFiles, SPackageGameFiles& outGameFiles ) const
{
	for ( Int32 j = inFiles.SizeInt()-1; j >= 0; --j )
	{
		const String& file = inFiles[ j ];

		// FIXME: inconsistent but in non-split cook .store goes into game content directory vs bin
		if ( file.EndsWith(TXT(".bundle")) || file.EndsWith(TXT(".store")) )
		{
			outGameFiles.m_bundleFiles.PushBack( Move( file ) );
		}
		else if ( file.EndsWith(TXT(".redscripts")) )
		{
			outGameFiles.m_scriptFiles.PushBack( Move( file ) );
		}
		else if ( m_isGOTY && file.EndsWith( TXT("streaming.cache")) )
		{
			outGameFiles.m_streamingCacheFiles.PushBack( Move(file) );
		}
		else if ( file.EndsWith(TXT(".cache")) )
		{
			outGameFiles.m_cacheFiles.PushBack( Move( file ) );
		}
		else if ( file.EndsWith(TXT(".w3speech")) )
		{
			outGameFiles.m_speechFiles.PushBack( Move( file ) );
		}
		else if ( file.EndsWith(TXT(".w3strings")) )
		{
			outGameFiles.m_stringsFiles.PushBack( Move( file ) );
		}
		else
		{
			outGameFiles.m_miscFiles.PushBack( Move( file ) );
		}
		inFiles.RemoveAt( j );
	}

	RED_FATAL_ASSERT( inFiles.Empty(), "Missed processing some files!" );
}
