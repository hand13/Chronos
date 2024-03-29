#pragma once
#include <clang-c/Index.h>

#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "KlassInfo.h"

struct ParseContext {
    std::string file_name;
    std::vector<std::shared_ptr<KlassInfo>> klasses;
    std::stack<Info*> stack;
    std::stack<CXCursor> cursorStack;
    ParseContext() {}
};
class KlassParser {
   private:
    CXIndex index;

   public:
    KlassParser();
    void parseFileIntoParseContext(
        const std::string& file_path, ParseContext& pc,
        const std::vector<std::string>& include_dirs);
    ~KlassParser();
};