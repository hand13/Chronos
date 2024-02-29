struct VertexShaderInput{
    float3 pos:POSITION;
    float2 uv:TEXCOORD;
    float3 normal:NORMAL;
};
struct PixelShaderInput{
    float4 pos:SV_POSITION;
    float2 uv:TEXCOORD;
};

cbuffer transformMatrix : register(b0){
    column_major matrix viewMatrix;
    column_major matrix projectionMatrix;
}

cbuffer model:register(b1){
    column_major matrix modelMatrix;
}

PixelShaderInput main(VertexShaderInput input) {
    PixelShaderInput output;
    matrix tmp = mul(viewMatrix,modelMatrix);
    matrix trans = mul(projectionMatrix,tmp);
    output.pos = mul(trans,float4(input.pos,1.f));
    output.uv = input.uv;
    return output;
}