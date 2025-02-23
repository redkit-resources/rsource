/**
 * Copyright � 2014 CD Projekt Red. All Rights Reserved.
 */

#pragma once
#include "packageConstants.h"

struct SPackageFiles;
struct SPackageGameFiles;

class CPackageFileCollector
{
	DECLARE_CLASS_MEMORY_ALLOCATOR( MC_Engine );

public:
	// #fixme: here so in one place
	Bool GenerateOnDiscDLCContentManifest( const String& projectAbsolutePath, const SPackageFiles& packageFiles ) const;

public:
	CPackageFileCollector( EPackageType packageType, Bool isGOTY );

public:
	Bool CollectPackageFiles( const String& projectAbsolutePath, SPackageFiles& outPackageFiles ) const;

protected:
	virtual Bool ProcessDirectory( const String& normalizedProjectAbsolutePath, const String& dirPath, SPackageFiles& outPackageFile ) const;

protected:
	void AddExtensionsToIgnore( const TDynArray< String >& extensions );

protected:
	Bool AddSystemDirectory( const String& projectAbsolutePath, const String& depotPath, SPackageFiles& outPackageFiles ) const;
	
	// FIXME: should separate so doesn't add ELFs, since ExeDeps also does this
	Bool AddGameBinaryDirectory( const String& projectAbsolutePath, const String& depotPath, SPackageFiles& outPackageFiles ) const;
	
	Bool AddGameContentDirectory( Uint32 contentNumber, const String& projectAbsolutePath, const String& depotPath, SPackageFiles& outPackageFiles ) const;

	Bool AddGamePatchDirectory( Uint32 patchNumber, const String& projectAbsolutePath, const String& depotPath, SPackageFiles& outPackageFiles ) const;

	Bool AddOnDiscDLCDirectory( Uint32 contentNumber, const String& projectAbsolutePath, const String& depotPath, SPackageFiles& outPackageFiles ) const;
	Bool AddEP1DLCDirectory( const String& projectAbsolutePath, const String& depotPath, SPackageFiles& outPackageFiles ) const;
	Bool AddEP2DLCDirectory( const String& projectAbsolutePath, const String& depotPath, SPackageFiles& outPackageFiles ) const;

private:
	Bool PopulateFilesFromDirectory( const String& projectAbsolutePath, const String& depotPath, TDynArray< String >& outFiles ) const;
	void MoveGameFilesByExtension( TDynArray< String >& inFiles, SPackageGameFiles& outGameFiles ) const;
	static Bool ConvertToLocalProjectPath( const String& projectAbsolutePath, const String& absolutePath, String& localPath );
	Bool ValidateLocalAppPath( const String& path ) const;
	Bool ValidateEntryName( const String& entry ) const;

private:
	Bool ValidatePathComponent( const String& pathComponent) const;

private:
	TDynArray< String > m_extensionsToIgnore;
	EPackageType		m_packageType;
	Bool				m_isGOTY;
};