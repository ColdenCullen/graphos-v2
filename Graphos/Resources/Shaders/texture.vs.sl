#version 400

// Input variables
in vec3 inputPosition;
in vec2 inputTexCoord;

// Output variables
out vec2 texCoord;

// Uniforms
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Shader code
void main( void )
{
	gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4( inputPosition, 1.0f );

	// Store texture coordinates for pixel shader
	texCoord = inputTexCoord;
}