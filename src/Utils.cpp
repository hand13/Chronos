#include "Utils.h"
#include <winerror.h>

void ThrowIfFailed(HRESULT x) {
    if(FAILED(x)){
        _com_error err(x);
        LPCSTR error = err.ErrorMessage();
        throw std::exception(error);
    }
}