#pragma once
#include <wrl/client.h>
#include <winerror.h>
#define CHRONOS_D3D11_SHADER_DIR "resources/shader/d3d11"
using Microsoft::WRL::ComPtr;
void ThrowIfFailed(HRESULT x);