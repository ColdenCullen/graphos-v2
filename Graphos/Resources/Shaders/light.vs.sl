#version 400

// Input variables
in vec3 inputPosition;
in vec2 inputTexCoord;
in vec3 inputNormal;

// Output variables
out vec2 texCoord;
out vec3 normal;

// Uniforms
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Shader code
void main( void )
{
	gl_Position = worldMatrix * vec4( inputPosition, 1.0f );
	gl_Position = viewMatrix * gl_Position;
	gl_Position = projectionMatrix * gl_Position;

	// Store texture coordinates for pixel shader
	texCoord = inputTexCoord;

	// Calculate the normal vector against world matrix
	normal = mat3( worldMatrix ) * inputNormal;

	// Normalize
	normal = normalize( normal );
}