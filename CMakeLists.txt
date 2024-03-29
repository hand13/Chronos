project(ChronosProject)
cmake_minimum_required(VERSION 3.22)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DNOMINMAX)
add_definitions(-D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)

# add_subdirectory(reflect)

find_package(fmt CONFIG REQUIRED)
find_package(Poco CONFIG REQUIRED Foundation)
find_package(Eigen3 CONFIG REQUIRED NO_MODULE)
find_package(directxtk CONFIG REQUIRED)
find_package(ICU REQUIRED uc)

include_directories(${EIGEN3_INCLUDE_DIR})
# message(${POCO_INCLUDE_DIRS})
# include_directories(${POCO_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/third_party)
set(IMGUI_DIR ${THIRD_PARTY_DIR}/imgui_dx11)
set(ASSIMP_DIR ${THIRD_PARTY_DIR}/assimp)

set(PHYSX_DIR "G:/PhysX-105.1-physx-5.3.1/physx")

add_subdirectory(${IMGUI_DIR})
include_directories(${IMGUI_DIR})

include_directories(${PHYSX_DIR}/include)
include_directories(${ASSIMP_DIR}/include)
link_directories(${ASSIMP_DIR}/debug/lib)

include_directories(src)

include_directories(reflect)
include_directories(generated)

aux_source_directory("src/platform/windows" PLATFORM_WIN_SRC)
aux_source_directory("src/platform/windows/window/d3d11" PLATFORM_WINDOW_D3D11_SRC)
aux_source_directory("src/platform/windows/render/d3d11" PLATFORM_RENDER_D3D11_SRC)

add_library(platform_window STATIC ${PLATFORM_WIN_SRC})
add_library(d3d11_window STATIC ${PLATFORM_WINDOW_D3D11_SRC})
add_library(d3d11_renderer SHARED ${PLATFORM_RENDER_D3D11_SRC})

aux_source_directory("src/render" RENDER_SRC)
aux_source_directory("src/editor" EDITOR_SRC)
aux_source_directory("src/component" COMPONENT_SRC)
aux_source_directory("src/game_object" GAME_OBJECT_SRC)
aux_source_directory("src/model" MODEL_SRC)
aux_source_directory("src/module" MODULE_SRC)
aux_source_directory("src/engine" ENGINE_SRC)
aux_source_directory("src/base" BASE_SRC)

aux_source_directory("generated" GENERATED_SRC)
aux_source_directory("reflect/reflect_api" REFLECT_API_SRC)

add_library(renderer STATIC ${RENDER_SRC})
add_library(editor STATIC ${EDITOR_SRC})
add_library(component STATIC ${COMPONENT_SRC})
add_library(game_object STATIC ${GAME_OBJECT_SRC})
add_library(model STATIC ${MODEL_SRC})
add_library(module STATIC ${MODULE_SRC})
add_library(base STATIC ${BASE_SRC})
add_library(engine STATIC ${ENGINE_SRC})

add_library(generated STATIC ${GENERATED_SRC})
add_library(reflect_api STATIC ${REFLECT_API_SRC})

target_link_libraries(base ICU::uc Poco::Foundation)

target_link_libraries(component base)
target_link_libraries(editor base)
target_link_libraries(game_object base)
target_link_libraries(engine base)
target_link_libraries(d3d11_window base)
target_link_libraries(d3d11_renderer PRIVATE base platform_window renderer Microsoft::DirectXTK d3d11 dxgi)

aux_source_directory(src GAME_SRC)
list(REMOVE_ITEM GAME_SRC "src/editor_main.cpp" "src/ChronosEditorStarter.cpp")
add_executable(ChronosGame ${GAME_SRC})
target_link_libraries(ChronosGame PRIVATE base engine renderer module component game_object model d3d11_window platform_window)
target_link_libraries(ChronosGame PRIVATE ICU::uc dxgi d3d11 imgui_dx11 Eigen3::Eigen  assimp-vc142-mtd Poco::Foundation fmt::fmt)

aux_source_directory(src EDITOR_SRC)
list(REMOVE_ITEM EDITOR_SRC "src/game_main.cpp" "src/ChronosGameStarter.cpp")
add_executable(ChronosEditor ${EDITOR_SRC})
target_link_libraries(ChronosEditor PRIVATE base reflect_api generated engine renderer module editor component game_object model d3d11_window platform_window)
target_link_libraries(ChronosEditor PRIVATE ICU::uc dxgi d3d11 imgui_dx11 Eigen3::Eigen  assimp-vc142-mtd Poco::Foundation fmt::fmt)

add_executable(test test/test.cpp)
target_link_libraries(test PRIVATE  base Poco::Foundation ICU::uc)

set(shader_src_dir "shaders/src")
add_custom_target(shaders)
file(GLOB vertex_shader_sources ${shader_src_dir}/*_vert.hlsl)
file(GLOB pixel_shader_sources ${shader_src_dir}/*_pixel.hlsl)

file(GLOB shader_sources ${shader_src_dir}/*.hlsl)

set_source_files_properties(${vertex_shader_sources} PROPERTIES ShaderType "vs")
set_source_files_properties(${pixel_shader_sources} PROPERTIES ShaderType "ps")

set_source_files_properties(${vertex_shader_sources} PROPERTIES ShaderModel "5_0")
set_source_files_properties(${pixel_shader_sources} PROPERTIES ShaderModel "5_0")

foreach(FILE ${shader_sources})
  get_filename_component(FILE_WE ${FILE} NAME_WE)
  get_source_file_property(shadertype ${FILE} ShaderType)
  get_source_file_property(shadermodel ${FILE} ShaderModel)
  add_custom_command(TARGET shaders
                     COMMAND fxc.exe  /Emain /T ${shadertype}_${shadermodel} $<IF:$<CONFIG:DEBUG>,/Od,/O1> /Zi /Fo $<TARGET_FILE_DIR:ChronosGame>/resources/shader/d3d11/${FILE_WE}.cso /Fd $<TARGET_FILE_DIR:ChronosGame>/resources/shader/d3d11/${FILE_WE}.pdb ${FILE}
                     MAIN_DEPENDENCY ${FILE}
                     COMMENT "HLSL ${FILE}"
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                     VERBATIM)
endforeach(FILE)


# add_dependencies(Chronos shaders) 循环依赖了

add_custom_command(TARGET ChronosGame PRE_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy_directory
 	${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:ChronosGame>/resources)

add_custom_command(TARGET ChronosGame PRE_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy
 	${ASSIMP_DIR}/debug/bin/assimp-vc142-mtd.dll $<TARGET_FILE_DIR:ChronosGame>/assimp-vc142-mtd.dll)

option(PHYSX_BUILD_TYPE "The build type of PhysX, i.e., one of {debug, checked, profile, release}" "checked")


# include_directories(${PHYSX_DIR}/include)

if(CMAKE_BUILD_TYPE AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Building in debug configuration")
    add_compile_definitions(_DEBUG)
    link_directories(${PHYSX_DIR}/bin/win.x86_64.vc143.md/debug) # This is the path where PhysX libraries are installed
else()
    message("Building in release configuration with PhysX ${PHYSX_BUILD_TYPE} configuration")
    add_compile_definitions(NDEBUG)
    link_directories(${PHYSX_DIR}/bin/win.x86_64.vc143.mt/${PHYSX_BUILD_TYPE}) # This is the path where PhysX libraries are installed
endif()

add_executable(PX_Test
test/px_test.cpp
)

target_link_libraries(PX_Test
    PhysX_64
    PhysXExtensions_static_64
    PhysXPvdSDK_static_64
    PhysXCommon_64
    PhysXFoundation_64

    # pthread
    # dl
)

set(PhysX_dll PhysXCommon_64.dll PhysX_64.dll PhysXFoundation_64.dll)

foreach(FILE ${PhysX_dll})
  # get_filename_component(FILE_WE ${FILE} NAME_WE)
  add_custom_command(TARGET PX_Test PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
    ${PHYSX_DIR}/bin/win.x86_64.vc143.md/debug/${FILE} $<TARGET_FILE_DIR:ChronosGame>/${FILE})
endforeach(FILE)