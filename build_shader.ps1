rm resources/shader/d3d11/*.cso 
fxc resources\shader\d3d11\basic_vert.hlsl /T vs_5_0 -Fo resources\shader\d3d11\basic_vert.cso
fxc resources\shader\d3d11\basic_pixel.hlsl /T ps_5_0 -Fo resources\shader\d3d11\basic_pixel.cso