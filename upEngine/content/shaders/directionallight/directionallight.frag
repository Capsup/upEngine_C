#version 330 core

out vec4 FragColor;

uniform sampler2D g_PositionMap;
uniform sampler2D g_ColorMap;
uniform sampler2D g_NormalMap;

uniform vec2 g_ScreenSize;

uniform vec3 g_EyeWorldPos;

uniform float g_MatSpecularIntensity;

struct DirectionalLight
{
	float AmbientIntensity;
	float DiffuseIntensity;
	vec3 Color;
	vec3 Direction;
};

uniform DirectionalLight dirLight;

vec4 CalcDirectionalLight( vec3 WorldPos, vec3 Normal )
{
	vec4 AmbientColor = vec4( dirLight.Color, 1.0f ) * dirLight.AmbientIntensity;
	vec4 DiffuseColor = vec4( 0, 0, 0, 0 );
	vec4 SpecularColor = vec4( 0, 0, 0, 0 );
	
	float DiffuseFactor = dot( Normal, -dirLight.Direction );
	if( DiffuseFactor > 0 )
	{
		DiffuseColor = vec4( dirLight.Color, 1.0f ) * dirLight.DiffuseIntensity * DiffuseFactor;
	
		vec3 VertexToEye = normalize( g_EyeWorldPos - WorldPos );
		vec3 LightReflect = normalize( reflect( dirLight.Direction, Normal ) );
		
		float SpecularFactor = dot( VertexToEye, LightReflect );
		SpecularFactor = pow( SpecularFactor, 32f );
		if( SpecularFactor > 0 )
		{
			SpecularColor = vec4( dirLight.Color, 1.0f ) * g_MatSpecularIntensity * SpecularFactor;
		}
	}
	
	return( AmbientColor + DiffuseColor + SpecularColor );
}

void main() 
{
	vec2 TexCoord = gl_FragCoord.xy / g_ScreenSize;
	vec3 WorldPos = texture2D( g_PositionMap, TexCoord ).xyz;
	vec3 Color = texture2D( g_ColorMap, TexCoord ).xyz;
	vec3 Normal = texture2D( g_NormalMap, TexCoord ).xyz;
	Normal = normalize( Normal );
	
	FragColor = vec4( Color, 1.0 ) * CalcDirectionalLight( WorldPos, Normal );
}