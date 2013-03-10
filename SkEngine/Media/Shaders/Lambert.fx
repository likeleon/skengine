/**** UNTWEAKABLES: Hidden & Automatically-Tracked Parameters **********/
// transform object vertices to world-space:
float4x4 gWorldXf : World;
// transform object normals, tangents, & binormals to world-space:
float4x4 gWorldITXf : WorldInverseTranspose;
// transform object vertices to view space and project them in perspective:
float4x4 gWvpXf : WorldViewProjection;

/************* TWEAKABLES *****************/
// Point Lamp 0
float3 gLamp0Pos : POSITION
= {0.f, 0.0f, -10.25f};
float3 gLamp0Color : SPECULAR
= {1.0f, 1.0f, 1.0f};

// Ambient Light
float3 gAmbiColor : AMBIENT
= {0.07f, 0.07f, 0.07f};

/************* COLOR & TEXTURE **************/
texture gTexture : DIFFUSE;

sampler2D ColorSampler = sampler_state
{
	Texture = <gTexture>;
	FILTER = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

/************* DATA STRUCTS **************/

/* data from application vertex buffer */
struct appdata
{
	float3 Position	: POSITION;
	float2 UV		: TEXCOORD0;
	float4 Normal	: NORMAL;
};

/* data passed from vertex shader to pixel shader */
struct vertexOutput
{
    float4 Position   : POSITION;   // vertex position
	float2 UV		  : TEXCOORD0;
	float3 LightVec	  : TEXCOORD1;
	float3 WorldNormal	: TEXCOORD2;
};

/*********** vertex shader ******/
vertexOutput lambVS(appdata IN,
					uniform float4x4 WorldITXf,
					uniform float4x4 WorldXf,
					uniform float4x4 WvpXf,
					uniform float3 LampPos)
{
	vertexOutput OUT = (vertexOutput)0;
	OUT.WorldNormal = mul(IN.Normal, WorldITXf).xyz;
	float4 Po = float4(IN.Position.xyz, 1);
	float3 Pw = mul(Po, WorldXf).xyz;
	OUT.LightVec = (LampPos - Pw);
	OUT.UV = IN.UV;
	OUT.Position = mul(Po, WvpXf);
	return OUT;	
}


/*********** vertex shader ******/
float4 lambPS(vertexOutput IN,
			  uniform float3 LampColor,
			  uniform float3 AmbiColor) : COLOR
{
	float3 Ln = normalize(IN.LightVec);
	float3 Nn = normalize(IN.WorldNormal);
	float ldn = dot(Ln, Nn);
	ldn = max(0, ldn);
	float3 diffuseColor = tex2D(ColorSampler, IN.UV).rgb;
	float3 result = diffuseColor * (ldn * LampColor + AmbiColor);
	return float4(result, 1);
}

///////////////////////////////////////
/// TECHNIQUES ////////////////////////
///////////////////////////////////////
technique RenderTechnique
{
	pass P0
	{
		VertexShader = compile vs_1_1 lambVS(gWorldITXf, gWorldXf, gWvpXf, gLamp0Pos);
		PixelShader	 = compile ps_1_1 lambPS(gLamp0Color, gAmbiColor);
	}
}