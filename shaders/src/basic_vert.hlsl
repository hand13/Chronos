struct VertexShaderInput{
    float3 pos:POSITION;
    float2 uv:TEXCOORD;
};
struct PixelShaderInput{
    float4 pos:SV_POSITION;
    float2 uv:TEXCOORD;
};
PixelShaderInput main(VertexShaderInput input) {
    PixelShaderInput output;
    output.pos = float4(input.pos,1.f);
    output.uv = input.uv;
    return output;
}