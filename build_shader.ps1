rm resources/shader/d3d11/*.cso 
fxc resources\shader\d3d11\basic_vert.hlsl /Zi /T vs_5_0 -Fo resources\shader\d3d11\basic_vert.cso
fxc resources\shader\d3d11\basic_pixel.hlsl /Zi /T ps_5_0 -Fo resources\shader\d3d11\basic_pixel.cso

fxc resources\shader\d3d11\test_vert.hlsl /Zi /T vs_5_0 -Fo resources\shader\d3d11\test_vert.cso
fxc resources\shader\d3d11\test_pixel.hlsl /Zi /T ps_5_0 -Fo resources\shader\d3d11\test_pixel.cso