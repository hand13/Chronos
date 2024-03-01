project(ChronosProject)
cmake_minimum_required(VERSION 3.22)

set(CMAKE_BUILD_TYPE Debug)

add_definitions(-DNOMINMAX)
add_definitions(-D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)

find_package(fmt CONFIG REQUIRED)
find_package(Poco CONFIG REQUIRED Foundation)
find_package(Eigen3 CONFIG REQUIRED NO_MODULE)

set(CMAKE_CXX_STANDARD 20)
# add_compile_options(-Wall)
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/third_party)
# set(GLAD_DIR ${THIRD_PARTY_DIR}/glad)
# set(GLFW_DIR ${THIRD_PARTY_DIR}/glfw)
# set(STB_DIR ${THIRD_PARTY_DIR}/stb)
# set(GLM_DIR ${THIRD_PARTY_DIR}/glm)
set(IMGUI_DIR ${THIRD_PARTY_DIR}/imgui)
set(ASSIMP_DIR ${THIRD_PARTY_DIR}/assimp)

set(PHYSX_DIR "G:/PhysX-105.1-physx-5.3.1/physx")

add_subdirectory(${IMGUI_DIR})
include_directories(${IMGUI_DIR})

include_directories(${PHYSX_DIR}/include)
# add_subdirectory(third_party/glad)
# add_subdirectory(third_party/glm)

# include_directories(${GLAD_DIR}/include)
# include_directories(${STB_DIR})
# include_directories(${GLM_DIR})
include_directories(${ASSIMP_DIR}/include)

# include_directories(${GLFW_DIR}/include)

# link_directories(${GLFW_DIR}/lib)
link_directories(${ASSIMP_DIR}/debug/lib)

aux_source_directory(src SRC)

aux_source_directory("src/platform/windows" PLATFORM_WIN_SRC)
aux_source_directory("src/render" RENDER_SRC)
aux_source_directory("src/render/d3d11" D3D11_RENDER_SRC)
aux_source_directory("src/imgui_control" IMGUI_CONTROL_SRC)
aux_source_directory("src/component" COMPONENT_SRC)
aux_source_directory("src/game_object" GAME_OBJECT_SRC)
aux_source_directory("src/model" MODEL_SRC)


# add_library(render STATIC ${RENDER_SRC})

# add_library(d3d11render STATIC ${D3D11_RENDER_SRC})

add_executable(Chronos ${SRC} ${PLATFORM_WIN_SRC} ${D3D11_RENDER_SRC} ${RENDER_SRC} ${IMGUI_CONTROL_SRC} ${COMPONENT_SRC} ${GAME_OBJECT_SRC} ${MODEL_SRC})

add_executable(test test/test.cpp src/Param.cpp src/Utils.cpp src/Log.cpp src/ParamList.cpp)

target_link_libraries(test PRIVATE Poco::Foundation)

target_link_libraries(Chronos PRIVATE dxgi d3d11 d3d12 imgui_dx12 Eigen3::Eigen  assimp-vc142-mtd Poco::Foundation fmt::fmt)

# target_link_libraries(glworld glfw3 glad imgui_dx12 d3d12 dxgi assimp-vc142-mtd)

# file(COPY_FILE ${GLFW_DIR}/lib/glfw3.dll ${CMAKE_BINARY_DIR}/glfw3.dll)
# file(COPY_FILE ${ASSIMP_DIR}/debug/bin/assimp-vc142-mtd.dll ${CMAKE_BINARY_DIR}/assimp-vc142-mtd.dll)

# add_custom_command(TARGET glworld PRE_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy_directory
#  	${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:glworld>/shaders)

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
                     COMMAND fxc.exe /nologo /Emain /T ${shadertype}_${shadermodel} $<IF:$<CONFIG:DEBUG>,/Od,/O1> /Zi /Fo $<TARGET_FILE_DIR:Chronos>/resources/shader/d3d11/${FILE_WE}.cso /Fd $<TARGET_FILE_DIR:Chronos>/resources/shader/d3d11/${FILE_WE}.pdb ${FILE}
                     MAIN_DEPENDENCY ${FILE}
                     COMMENT "HLSL ${FILE}"
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                     VERBATIM)
endforeach(FILE)


# add_dependencies(Chronos shaders) 循环依赖了

add_custom_command(TARGET Chronos PRE_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy_directory
 	${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Chronos>/resources)

add_custom_command(TARGET Chronos PRE_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy
 	${ASSIMP_DIR}/debug/bin/assimp-vc142-mtd.dll $<TARGET_FILE_DIR:Chronos>/assimp-vc142-mtd.dll)

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
    ${PHYSX_DIR}/bin/win.x86_64.vc143.md/debug/${FILE} $<TARGET_FILE_DIR:Chronos>/${FILE})
endforeach(FILE)