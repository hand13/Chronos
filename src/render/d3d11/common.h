#pragma once
#include <wrl/client.h>
#include <winerror.h>
using Microsoft::WRL::ComPtr;
void ThrowIfFailed(HRESULT x);