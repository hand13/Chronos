struct VertexShaderInput{
    float3 pos:POSITION;
    float2 uv:TEXCOORD;
    float3 normal:NORMAL;
};
struct PixelShaderInput{
    float2 TexCoords:TEXCOORD;
    float4 WorldPos:SV_Position;
    float3 Normal:NORMAL;
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
    output.WorldPos = mul(trans,float4(input.pos,1.f));
    output.TexCoords = input.uv;
    output.Normal = input.normal;
    return output;
}