struct PixelShaderInput{
    float4 pos:SV_POSITION;
    float2 uv:TEXCOORD;
};
sampler MySampler;
Texture2D MyTex;
float4 main(PixelShaderInput input):SV_Target {
    return MyTex.Sample(MySampler,input.uv);
}