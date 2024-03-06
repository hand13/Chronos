#pragma once
#include <string>
#include <vector>
#include <stack>
#include <clang-c/Index.h>
#include "Klass.h"
struct ParseContext {
    std::string file_name;
    std::vector<Klass> klasses;
    std::stack<void*> stack;
    std::stack<CXCursor> cursorStack;
    ParseContext(){}
};
class KlassParser {
    private:
    CXIndex index;
    public:
    KlassParser();
    void parseFileIntoParseContext(const std::string& file_path,ParseContext& pc);
    ~KlassParser();
};