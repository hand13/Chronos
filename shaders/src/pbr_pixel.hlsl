struct PixelShaderInput{
    float2 TexCoords:TEXCOORD;
    float4 Pos:SV_POSITION;
    float4 WorldPos:POSITION;
    float3 Normal:NORMAL;
};
cbuffer PBRParam: register(b0){
    float3 ialbedo;
    float imetallic;
    float iroughness;
    float ao;
}
cbuffer LightParam:register(b1){
    float3 lightPostion[1];
    float3 lightColor[1];
}
cbuffer Camera:register(b2){
    float3 camPos;
};

SamplerState ssp: register(s0);

Texture2D albedoTex : register(t0);
Texture2D metallicTex :register(t1);
Texture2D roughnessTex : register(t2);

static const float PI = 3.14159265359;

float DIstributionGGX(float3 N,float3 H,float roughtness);
float GeometrySchlickGGX(float NdotV,float roughtness);
float GeometrySmith(float3 N,float3 V,float3 L,float roughness);
float3 fresnelSchlick(float cosTheta,float3 F0);

float3 mix(float3 a,float3 b,float value){
    return a * value + b * (1-value);
}

float4 main(PixelShaderInput input) :SV_TARGET{

    float3 albedo = pow((float3)albedoTex.Sample(ssp,input.TexCoords),float3(2.2,2.2,2.2)) + ialbedo;
    // float3 albedo = (float3)albedoTex.Sample(ssp,input.TexCoords) + ialbedo;
    float metallic = metallicTex.Sample(ssp,input.TexCoords).r + imetallic;
    float roughness = roughnessTex.Sample(ssp,input.TexCoords).r + iroughness;


    float3 N = normalize(input.Normal);
    float3 WorldPos = (float3)input.WorldPos;
    float3 V = normalize(camPos - WorldPos);
    float3 F0 = float3(0.04,0.04,0.04);
    F0 = mix(F0,albedo,metallic);
    float3 Lo = float3(0.0,0.0,0.0);
    for(int i = 0;i<1;++i){
        float3 L = normalize(lightPostion[i] - WorldPos);
        float3 H = normalize(V+L);
        float dis = length(lightPostion[i] - WorldPos);
        float attenuation = 1.0/(dis * dis);
        float3 radiance = lightColor[i] * attenuation;

        float NDF = DIstributionGGX(N,H,roughness);
        float G = GeometrySmith(N,V,L,roughness);
        float3 F = fresnelSchlick(max(dot(H,V),0.0),F0);
        float3 kS = F;
        float3 kD = float3(1.0,1.0,1.0) - kS;
        kD *= 1.0 - metallic;
        float3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N,V),0.0) * max(dot(N,L),0.0) + 0.0001;
        float3 specular = numerator / denominator;
        float3 NdotL = max(dot(N,L),0.0);
        Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    }
    float3 ambient = float3(0.03,0.03,0.03) * albedo * ao;
    float3 color = ambient + Lo;
    color = color / (color + float3(1.0,1.0,1.0));
    float gamma = 1.0/2.2;
    color = pow(abs(color),float3(gamma,gamma,gamma));
    return float4(color,1.f);
}
float DIstributionGGX(float3 N,float3 H,float roughness){
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N,H),0.0);
    float NdotH2 = NdotH * NdotH;
    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI *denom * denom;
    return num/denom;
}
float GeometrySchlickGGX(float NdotV,float roughness){
    float r = (roughness + 1.0);
    float k = (r*r)/8.0;
    float num = NdotV;
    float denom = NdotV * (1.0-k) + k;
    return num/denom;
}
float GeometrySmith(float3 N,float3 V,float3 L,float roughness){
    float NdotV = max(dot(N,V),0.0);
    float NdotL = max(dot(N,L),0.0);
    float ggx2 = GeometrySchlickGGX(NdotV,roughness);
    float ggx1 = GeometrySchlickGGX(NdotL,roughness);
    return ggx1 * ggx2;
}
float3 fresnelSchlick(float cosTheta,float3 F0){
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta,0.0,1.0),5.0);
}