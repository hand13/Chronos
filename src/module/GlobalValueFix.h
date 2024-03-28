#pragma once
#include <cstddef>
#ifdef WIN32
#include <Windows.h>
#endif
#include <exception>
/**
 * @brief 修复 moudle动态库 中引用主moudle中的全局变量
 *
 * @param needFixValue
 * @param target_name
 */
template <typename T>
void fixGlobalValue(T* needFixValue, const char* target_name) {
    if (needFixValue) {
#ifdef WIN32
        HMODULE hm = GetModuleHandle(NULL);
        if (hm) {
            T* v = reinterpret_cast<T*>(GetProcAddress(hm, target_name));
            if (v) {
                *needFixValue = *v;
            }
        }
#endif
#ifndef WIN32
        throw std::exception("not implements");
#endif
    }
}