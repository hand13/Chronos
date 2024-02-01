#pragma once
#include <exception>
#include <winerror.h>
#include <comdef.h>
#include <winnt.h>
inline void Panic(const char* msg){
    throw std::exception(msg);
};

void ThrowIfFailed(HRESULT x);