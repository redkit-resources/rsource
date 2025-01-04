//--------------------------------------------------------------------------------------
// Based on the XDK sample loader
//
// http://go.microsoft.com/fwlink/?LinkId=248926
// http://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------

#pragma once

#include "../gpuApiUtils/gpuApiUtils.h"
#include "gpuApiBase.h"

namespace GpuApi
{
	enum DDS_ALPHA_MODE
	{
		DDS_ALPHA_MODE_UNKNOWN       = 0,
		DDS_ALPHA_MODE_STRAIGHT      = 1,
		DDS_ALPHA_MODE_PREMULTIPLIED = 2,
		DDS_ALPHA_MODE_OPAQUE        = 3,
		DDS_ALPHA_MODE_CUSTOM        = 4,
	};

	HRESULT CreateDDSTextureFromMemory( _In_ ID3D11Device* d3dDevice,
		_In_reads_bytes_(ddsDataSize) const uint8_t* ddsData,
		_In_ size_t ddsDataSize,
		_Outptr_opt_ ID3D11Resource** texture,
		_Outptr_opt_ ID3D11ShaderResourceView** textureView,
		_In_ size_t maxsize = 0,
		_Out_opt_ DDS_ALPHA_MODE* alphaMode = nullptr
		);

	HRESULT CreateDDSTextureFromFile( _In_ ID3D11Device* d3dDevice,
		_In_z_ const wchar_t* szFileName,
		_Outptr_opt_ ID3D11Resource** texture,
		_Outptr_opt_ ID3D11ShaderResourceView** textureView,
		_In_ size_t maxsize = 0,
		_Out_opt_ DDS_ALPHA_MODE* alphaMode = nullptr
		);

	HRESULT CreateDDSTextureFromMemoryEx( _In_ ID3D11Device* d3dDevice,
		_In_reads_bytes_(ddsDataSize) const uint8_t* ddsData,
		_In_ size_t ddsDataSize,
		_In_ size_t maxsize,
		_In_ D3D11_USAGE usage,
		_In_ unsigned int bindFlags,
		_In_ unsigned int cpuAccessFlags,
		_In_ unsigned int miscFlags,
		_In_ bool forceSRGB,
		_Outptr_opt_ ID3D11Resource** texture,
		_Outptr_opt_ ID3D11ShaderResourceView** textureView,
		_Out_opt_ DDS_ALPHA_MODE* alphaMode = nullptr
		);

	HRESULT CreateDDSTextureFromFileEx( _In_ ID3D11Device* d3dDevice,
		_In_z_ const wchar_t* szFileName,
		_In_ size_t maxsize,
		_In_ D3D11_USAGE usage,
		_In_ unsigned int bindFlags,
		_In_ unsigned int cpuAccessFlags,
		_In_ unsigned int miscFlags,
		_In_ bool forceSRGB,
		_Outptr_opt_ ID3D11Resource** texture,
		_Outptr_opt_ ID3D11ShaderResourceView** textureView,
		_Out_opt_ DDS_ALPHA_MODE* alphaMode = nullptr
		);
}