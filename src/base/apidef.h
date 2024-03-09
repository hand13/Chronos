#pragma once
#ifdef WIN32
#include <Windows.h>
#define CHRONOS_API extern "C" __declspec(dllexport)
#endif
#ifndef WIN32
#define CHRONOS_API extern "C"
#endif