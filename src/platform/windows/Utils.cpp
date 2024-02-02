#include <comdef.h>
#include "../../Utils.h"
void ThrowIfFailed(HRESULT x) {
    if(FAILED(x)){
        _com_error err(x);
        LPCWSTR error = err.ErrorMessage();
        Panic(error);
    }
}