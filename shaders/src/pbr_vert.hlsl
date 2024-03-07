struct VertexShaderInput{
    float3 pos:POSITION;
    float2 uv:TEXCOORD;
    float3 normal:NORMAL;
};
struct PixelShaderInput{
    float2 TexCoords:TEXCOORD;
    float4 FPosition:SV_Position;
    float4 WorldPosition:POSITION;
    float3 Normal:NORMAL;
};

cbuffer transformMatrix : register(b0){
    column_major matrix viewMatrix;
    column_major matrix projectionMatrix;
}

cbuffer model:register(b1){
    column_major matrix modelMatrix;
    column_major matrix normMatrix;
}

PixelShaderInput main(VertexShaderInput input) {
    PixelShaderInput output;
    matrix tmp = mul(viewMatrix,modelMatrix);
    matrix trans = mul(projectionMatrix,tmp);
    output.WorldPosition = mul(modelMatrix,float4(input.pos,1.f));
    output.FPosition = mul(trans,float4(input.pos,1.f));
    output.TexCoords = input.uv;
    float3x3 nm = float3x3(normMatrix[0].xzy,normMatrix[1].xyz,normMatrix[2].xyz);
    output.Normal = normalize(mul(nm,input.normal));
    return output;
}