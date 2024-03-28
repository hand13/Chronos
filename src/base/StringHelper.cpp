#include "StringHelper.h"

#include <unicode/ucnv.h>
#include <unicode/umachine.h>
#include <unicode/urename.h>

#include "Utils.h"


std::string WideToUTF8(const std::wstring& str) {
    UErrorCode code;
    UConverter* convert = ucnv_open("utf_8", &code);
    if (U_FAILURE(code)) {
        Panic("should not happended");
    }
    size_t buffer_size = ucnv_getMaxCharSize(convert) * str.size() + 1;
    char* tmp = new char[buffer_size];
    memset(tmp, 0, sizeof(char) * buffer_size);
    UChar* t = (UChar*)str.c_str();

    ucnv_fromUChars(convert, tmp,
                    static_cast<unsigned int>(sizeof(char) * buffer_size), t,
                    static_cast<unsigned int>(str.size()), &code);
    if (U_FAILURE(code)) {
        Panic("should not happended");
    }

    std::string result;
    result.append(tmp);
    ucnv_close(convert);
    delete[] tmp;

    return result;
}

std::wstring UTF8toWide(const std::string& str) {
    UErrorCode code;
    UConverter* convert = ucnv_open("utf_8", &code);

    if (U_FAILURE(code)) {
        Panic("should not happended");
    }
    size_t buffer_size = str.size() + 1;
    UChar* tmp = new UChar[buffer_size];
    memset(tmp, 0, sizeof(UChar) * buffer_size);

    ucnv_toUChars(convert, tmp,
                  static_cast<unsigned int>(sizeof(UChar) * buffer_size),
                  str.c_str(), static_cast<unsigned int>(str.size()), &code);
    if (U_FAILURE(code)) {
        Panic("should not happended");
    }
    std::wstring wc = (wchar_t*)tmp;
    ucnv_close(convert);
    delete[] tmp;
    return wc;
}
