struct PixelShaderInput{
    float4 pos:SV_POSITION;
    float2 uv:TEXCOORD;
};
// sampler MySampler;
// Texture2D MyTex;
float4 main(PixelShaderInput input):SV_Target {
    // return float4(1.f,1.f,1.f,1.f);
    float2 uv = input.uv;
    float divide = 10.f;
    int x = (int)(uv.x * divide);
    int y = (int)(uv.y * divide);
    float4 cs[2] = {
        float4(.9f,0.9f,0.9f,1.f),
        float4(0.2f,0.2,0.2f,1.f)
    };
    // if((x+y)&0x01 == 1){
    //     color = float4(0.2f,0.2,0.2f,1.f);
    // }
    // Output to screen
    return cs[(x+y) & 0x01];
}