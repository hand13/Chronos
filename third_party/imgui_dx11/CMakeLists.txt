project(Imgui)
set(IMGUI_SRC imgui_demo.cpp imgui_draw.cpp 
	imgui_impl_dx11.cpp imgui_impl_win32.cpp imgui_tables.cpp imgui_widgets.cpp imgui.cpp)
add_library(imgui_dx11 STATIC ${IMGUI_SRC})
# add_executable(master main.cpp)
# target_link_libraries(master imgui_dx12 d3d12 dxgi)