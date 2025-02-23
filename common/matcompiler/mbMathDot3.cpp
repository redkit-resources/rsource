/**
* Copyright � 2007 CD Projekt Red. All Rights Reserved.
*/

#include "build.h"
#include "../engine/materialBlock.h"
#include "../engine/graphBlock.h"

#ifndef NO_RUNTIME_MATERIAL_COMPILATION

/// Add two values
class CMaterialBlockMathDot3 : public CMaterialBlock
{
	DECLARE_ENGINE_MATERIAL_BLOCK( CMaterialBlockMathDot3, CMaterialBlock, "Math", "Dot3" );

public:
	Bool m_dot4;


#ifndef NO_EDITOR_GRAPH_SUPPORT

	virtual void OnRebuildSockets()
	{
		GraphConnectionRebuilder rebuilder( this );
		CreateSocket( MaterialInputSocketSpawnInfo( CNAME( A ) ) );
		CreateSocket( MaterialInputSocketSpawnInfo( CNAME( B ) ) );
		CreateSocket( MaterialOutputSocketSpawnInfo( CNAME( Out ) ) );
	}

#endif

	virtual CodeChunk Compile( CMaterialBlockCompiler& compiler, EMaterialShaderTarget shaderTarget, CMaterialOutputSocket* socket = NULL ) const
	{
		CodeChunk a = CompileInput( compiler, CNAME( A ), shaderTarget, Vector( 1.0f, 1.0f, 1.0f, 1.0f ) );
		CodeChunk b = CompileInput( compiler, CNAME( B ), shaderTarget, Vector( 1.0f, 1.0f, 1.0f, 1.0f ) );
		return m_dot4 ? CodeChunkOperators::Dot4( a, b ).xxxx() : CodeChunkOperators::Dot3( a, b ).xxxx();
	}
};


BEGIN_CLASS_RTTI(CMaterialBlockMathDot3)
	PARENT_CLASS(CMaterialBlock);
	PROPERTY_EDIT( m_dot4, TXT("Dot4?") );
END_CLASS_RTTI();
IMPLEMENT_ENGINE_CLASS( CMaterialBlockMathDot3 );

#endif