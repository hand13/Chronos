project(Chs_Reflect)
find_package(fmt CONFIG REQUIRED)
include_directories(".")
add_definitions("-D_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING")
add_definitions("-D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS")

find_package(nlohmann_json CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

aux_source_directory("." REFLECT_SRC)
list(REMOVE_ITEM REFLECT_SRC "./reflect_test.cpp")

message(${REFLECT_SRC})

aux_source_directory("reflect_api" REFLECT_API_SRC)


add_executable(reflect ${REFLECT_SRC} ${REFLECT_API_SRC})
target_compile_features(reflect PRIVATE cxx_std_17)
target_include_directories(reflect PRIVATE "D:/usr/local/LLVM/include")

target_link_directories(reflect PRIVATE "D:/usr/local/LLVM/lib")
target_link_libraries(reflect PRIVATE libclang fmt::fmt)
target_link_libraries(reflect PRIVATE nlohmann_json::nlohmann_json)
  target_link_libraries(reflect PRIVATE cxxopts::cxxopts)




aux_source_directory("generated" GENERATED_SRC)
add_library(load_fn STATIC ${GENERATED_SRC})

aux_source_directory("." TEST_SRC)
list(REMOVE_ITEM TEST_SRC "./reflect.cpp")

add_executable(reflect_test ${TEST_SRC} ${REFLECT_API_SRC})
target_compile_features(reflect_test PRIVATE cxx_std_17)
target_include_directories(reflect_test PRIVATE "D:/usr/local/LLVM/include")

target_link_directories(reflect_test PRIVATE "D:/usr/local/LLVM/lib")
target_link_libraries(reflect_test PRIVATE libclang fmt::fmt)
target_link_libraries(reflect_test PRIVATE load_fn)