struct PixelShaderInput{
    float4 pos:SV_POSITION;
    float2 uv:TEXCOORD;
};
// sampler MySampler;
// Texture2D MyTex;
float4 main(PixelShaderInput input):SV_Target {
    // return float4(1.f,1.f,1.f,1.f);
    float2 uv = input.uv;

    float dis = distance(uv,float2(uv.x,sin(uv.x*10.0)/10.0 + 0.5));
    float3 color = float3(0.0353, 0.3373, 0.9451);
    float k = smoothstep(0.005f,0.0f,dis);
    float3 target = k * color;

    float d = distance(uv,float2(uv.x,2.0f * sin((uv.x+0.75f)*10.0)/10.0 + 0.8));
    float3 col = float3(0.9765, 0.502, 0.0275);
    float w = smoothstep(0.005f,0.0f,d);
    float3 targe = w * col;
    // Output to screen
    return float4(target + targe,1.0);
}