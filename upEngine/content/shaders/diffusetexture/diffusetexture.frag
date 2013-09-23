#version 330 core

in vec2 TexCoord0;
in vec3 Normal0;

out vec4 FragColor;

struct DirectionalLight
{
	vec3 v3Color;
	float fAmbientIntensity;
	float fDiffuseIntensity;
	vec3 v3Direction;
};

uniform sampler2D g_Sampler;
uniform DirectionalLight g_DirectionalLight;

void main() 
{
	//vec4 ambColor = vec4( 154.f/255.f, 210.f/255.f, 255.f/255.f, 1.f ) * texture( g_Tex, TexCoord0 );
	//float ambIntens = 0.1f;
	//vec4 sunColor = vec4( 255.f/255.f, 255.f/255.f, 204.f/255.f, 1.f ) * texture( g_Tex, TexCoord0 );
	//float sunIntens = 0.6f;
	//outColor = ( ambColor * ambIntens ) + ( ( sunColor * outDot ) * sunIntens );
	//outColor = vec4( Normal, 1.0 );
	//outColor = vec4( 1.0, 1.0, 1.0, 1.0 ) * texture2D( tex, Texcoords );
	//outColor = vec4( Texcoords.x, Texcoords.y, 1.0, 1.0 );
	
	vec3 v3AmbientColor = vec3( 154.f/255.f, 210.f/255.f, 255.f/255.f ) * g_DirectionalLight.fAmbientIntensity;
	vec4 v4AmbientColor = vec4( v3AmbientColor, 1.0f );
	vec3 v3Normal = normalize( Normal0 );
	float fDiffuseFactor = dot( v3Normal, -g_DirectionalLight.v3Direction );
	vec4 v4DiffuseColor;
	vec4 v4SpecularColor;
	
	if( fDiffuseFactor > 0 )
	{
		v4DiffuseColor = vec4( g_DirectionalLight.v3Color, 1.0f ) * g_DirectionalLight.fDiffuseIntensity * fDiffuseFactor;
	}
	else
	{
		v4DiffuseColor = vec4( 0, 0, 0, 0 );
	}
	
	FragColor = texture2D( g_Sampler, TexCoord0.xy ) * ( v4AmbientColor + v4DiffuseColor );
}