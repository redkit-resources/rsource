/**
* Copyright � 2007 CD Projekt Red. All Rights Reserved.
*/

#include "build.h"

#ifndef NO_RUNTIME_MATERIAL_COMPILATION

/// Converts value in gamma space into linear space
class CMaterialBlockConvertGammaToLinear : public CMaterialBlock
{
	DECLARE_ENGINE_MATERIAL_BLOCK( CMaterialBlockConvertGammaToLinear, CMaterialBlock, "Deprecated", "GammaToLinear" );

public:

#ifndef NO_EDITOR_GRAPH_SUPPORT

	virtual void OnRebuildSockets()
	{
		GraphConnectionRebuilder rebuilder( this );
		CreateSocket( MaterialInputSocketSpawnInfo( CNAME( X ) ) );
		CreateSocket( MaterialOutputSocketSpawnInfo( CNAME( Out ) ) );
	}

#endif

	virtual CodeChunk Compile( CMaterialBlockCompiler& compiler, EMaterialShaderTarget shaderTarget, CMaterialOutputSocket* socket = NULL ) const
	{
		CodeChunk x = CompileInput( compiler, CNAME( X ), shaderTarget, 0.0f );		
		return compiler.GetPS().ApplyGammaToLinearExponent( MDT_Float4, x, false, false );
	}
};

DEFINE_SIMPLE_RTTI_CLASS( CMaterialBlockConvertGammaToLinear , CMaterialBlock);

IMPLEMENT_ENGINE_CLASS( CMaterialBlockConvertGammaToLinear );

#endif