#version 130

in vec4 fragmentColor;
in vec2 fragUV;

out vec4 color;

uniform float time;
uniform sampler2D aSampler;

void main()
{
	vec4 texColor = texture(aSampler,fragUV);

	vec4 anotherColor = fragmentColor + vec4(1.0f * (cos(time)+1.0)*0.5,1.0f * (cos(time+2)+.0)*0.5,1.0f * (sin(time)+1.0)*0.5,1.0f);
	color = texColor * anotherColor;
}
