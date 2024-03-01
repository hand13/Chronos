struct PixelShaderInput{
    float4 pos:SV_POSITION;
    float2 uv:TEXCOORD;
};

float4 mix(float4 a,float4 b,float value){
    return a*value + b*(1-value);
}
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

    float4 edge_color = float4(0.f,0.9f,0.f,1.f);
    float min_distance_from_edge = min(min(uv.x,abs(1.f -uv.x)),min(uv.y,abs(1.f-uv.y)));
    float p= smoothstep(0.02f,0.01f,min_distance_from_edge);
    // if((x+y)&0x01 == 1){
    //     color = float4(0.2f,0.2,0.2f,1.f);
    // }
    // Output to screen
    return mix(edge_color,cs[(x+y) & 0x01],p);
}