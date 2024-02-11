struct VertexShaderInput{
    float3 pos:POSITION;
    float2 uv:TEXCOORD;
};
struct PixelShaderInput{
    float4 pos:SV_POSITION;
    float2 uv:TEXCOORD;
};

cbuffer transformMatrix : register(b0){
    row_major matrix viewMatrix;
    row_major matrix projectionMatrix;
}

PixelShaderInput main(VertexShaderInput input) {
    PixelShaderInput output;
    row_major matrix tmp = mul(viewMatrix ,projectionMatrix);
    output.pos = mul(float4(input.pos,1.f),tmp);
    output.uv = input.uv;
    return output;
}