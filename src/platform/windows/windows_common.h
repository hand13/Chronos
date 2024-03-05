#pragma once
#include <winerror.h>
#include <wrl/client.h>
#define CHRONOS_D3D11_SHADER_DIR "resources/shader/d3d11"
using Microsoft::WRL::ComPtr;
void ThrowIfFailed(HRESULT x);