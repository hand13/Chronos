struct VertexShaderInput{
    float3 pos:POSITION;
    float2 uv:TEXCOORD;
};
struct PixelShaderInput{
    float4 pos:SV_POSITION;
    float2 uv:TEXCOORD;
};

cbuffer transformMatrix : register(b0){
    column_major matrix viewMatrix;
    column_major matrix projectionMatrix;
}

PixelShaderInput main(VertexShaderInput input) {
    PixelShaderInput output;
    matrix tmp = mul(projectionMatrix,viewMatrix);
    output.pos = mul(tmp,float4(input.pos,1.f));
    output.uv = input.uv;
    return output;
}