struct VS_INPUT {
    float3 pos:Position;
    float2 uv:TEXCOORD;
};
struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : Texcoord;
};

VS_OUT main(VS_INPUT input)
{
    VS_OUT vso;
    vso.pos = float4(input.pos,1.f);
    vso.uv = input.uv;
    return vso;
}