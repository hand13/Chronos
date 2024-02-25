project(Chronos)
cmake_minimum_required(VERSION 3.22)

find_package(fmt CONFIG REQUIRED)
find_package(Poco CONFIG REQUIRED Foundation)
find_package(Eigen3 CONFIG REQUIRED NO_MODULE)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall)
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/third_party)
# set(GLAD_DIR ${THIRD_PARTY_DIR}/glad)
# set(GLFW_DIR ${THIRD_PARTY_DIR}/glfw)
# set(STB_DIR ${THIRD_PARTY_DIR}/stb)
# set(GLM_DIR ${THIRD_PARTY_DIR}/glm)
set(IMGUI_DIR ${THIRD_PARTY_DIR}/imgui)
# set(ASSIMP_DIR ${THIRD_PARTY_DIR}/assimp)

add_subdirectory(${IMGUI_DIR})
include_directories(${IMGUI_DIR})
# add_subdirectory(third_party/glad)
# add_subdirectory(third_party/glm)

# include_directories(${GLAD_DIR}/include)
# include_directories(${STB_DIR})
# include_directories(${GLM_DIR})
# include_directories(${ASSIMP_DIR}/include)

# include_directories(${GLFW_DIR}/include)

# link_directories(${GLFW_DIR}/lib)
# link_directories(${ASSIMP_DIR}/debug/lib)

aux_source_directory(src SRC)

aux_source_directory("src/platform/windows" PLATFORM_WIN_SRC)

aux_source_directory("src/render" RENDER_SRC)

aux_source_directory("src/render/d3d11" D3D11_RENDER_SRC)

aux_source_directory("src/imgui_control" IMGUI_CONTROL_SRC)


# add_library(render STATIC ${RENDER_SRC})

# add_library(d3d11render STATIC ${D3D11_RENDER_SRC})

add_executable(Chronos ${SRC} ${PLATFORM_WIN_SRC} ${D3D11_RENDER_SRC} ${RENDER_SRC} ${IMGUI_CONTROL_SRC})

add_executable(test test/test.cpp src/Param.cpp src/Utils.cpp src/Log.cpp)

target_link_libraries(test PRIVATE Poco::Foundation)

target_link_libraries(Chronos PRIVATE dxgi d3d11 d3d12 imgui_dx12 Eigen3::Eigen  Poco::Foundation fmt::fmt)

# target_link_libraries(glworld glfw3 glad imgui_dx12 d3d12 dxgi assimp-vc142-mtd)

# file(COPY_FILE ${GLFW_DIR}/lib/glfw3.dll ${CMAKE_BINARY_DIR}/glfw3.dll)
# file(COPY_FILE ${ASSIMP_DIR}/debug/bin/assimp-vc142-mtd.dll ${CMAKE_BINARY_DIR}/assimp-vc142-mtd.dll)

# add_custom_command(TARGET glworld PRE_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy_directory
#  	${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:glworld>/shaders)

add_custom_command(TARGET Chronos PRE_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy_directory
 	${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Chronos>/resources)