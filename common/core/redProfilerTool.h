/**
* Copyright � 2014 CD Projekt Red. All Rights Reserved.
*/

#pragma once

#include "profiler.h"

#ifdef USE_RED_PROFILER

#include "profiler/newRedProfiler.h"

class CRedProfiler : public IProfilerTool
{
public:
	static const Char* st_name;

	static IProfilerTool* Create();

	CRedProfiler();

	virtual SProfilerFuncPackage GetFuncPackage();
	virtual const Char* GetName();

	virtual void RefreshCustomHandleData(CProfilerHandle* handleTable[PROFILER_MAX_SCOPES], Uint32 activeHandleCount);
	virtual void InitializeCustomHandleData(CProfilerHandle* handle);

	virtual void Tick();

private:
	void BeginEvent( CProfilerBlock* block );
	void EndEvent( CProfilerBlock* block );
	void Message( CProfilerBlock* block, const Char* msg );

};

#endif
