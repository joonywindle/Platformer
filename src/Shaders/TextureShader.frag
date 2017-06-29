#version 130

in vec4 fragmentColor;
in vec2 fragUV;

out vec4 color;

uniform sampler2D aSampler;

void main()
{
	vec4 texColor = texture(aSampler,fragUV);

	color = texColor;
}
