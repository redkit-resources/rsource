/**
* Copyright � 2007 CD Projekt Red. All Rights Reserved.
*/

#pragma once

#include "materialParameter.h"


/// A block that defines scalar parameter
class CMaterialParameterScalar : public CMaterialParameter
{
	DECLARE_ENGINE_MATERIAL_PARAMETER( CMaterialParameterScalar, CMaterialParameter, "Parameters", "Scalar" );

public:
	Float	m_scalar;				//!< Value

public:
	CMaterialParameterScalar();
	virtual IProperty* GetParameterProperty() const;
#ifndef NO_EDITOR_GRAPH_SUPPORT
	virtual void OnRebuildSockets();
#endif
#ifndef NO_RUNTIME_MATERIAL_COMPILATION
	virtual CodeChunk Compile( CMaterialBlockCompiler& compiler, EMaterialShaderTarget shaderTarget, CMaterialOutputSocket* socket = NULL ) const;
#endif
};

BEGIN_CLASS_RTTI( CMaterialParameterScalar );
PARENT_CLASS( CMaterialParameter );
PROPERTY_EDIT( m_scalar, TXT("Scalar value") );
END_CLASS_RTTI();
