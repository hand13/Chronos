project(Chs_Reflect)
find_package(fmt CONFIG REQUIRED)
aux_source_directory("./" REFLECT_SRC)
add_executable(reflect ${REFLECT_SRC})
target_include_directories(reflect PRIVATE "D:/usr/local/LLVM/include")
target_link_directories(reflect PRIVATE "D:/usr/local/LLVM/lib")
target_link_libraries(reflect PRIVATE libclang fmt::fmt)
add_custom_command(TARGET reflect PRE_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy
 	${PROJECT_SOURCE_DIR}/head_for_reflect.h $<TARGET_FILE_DIR:reflect>/head_for_reflect.h)

add_custom_command(TARGET reflect PRE_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy
 	${PROJECT_SOURCE_DIR}/MetaPrefix.h $<TARGET_FILE_DIR:reflect>/MetaPrefix.h)