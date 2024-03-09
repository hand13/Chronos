#include <comdef.h>
#include "windows_common.h"
#include <base/Utils.h>
void ThrowIfFailed(HRESULT x) {
    if(FAILED(x)){
        _com_error err(x);
        const TCHAR* error = err.ErrorMessage();
        Panic(error);
    }
}