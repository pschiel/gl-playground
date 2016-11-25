#version 330 core

in vec2 uv;
out vec3 color;
uniform sampler2D tex;
uniform int test;

void main()
{

	if (test == 1) {
		color = vec3(255, 255, 255);
	}
	else if (test == 2) {
		color = vec3(0, 255, 0);
	}
	else if (test == 3) {
		color = vec3(255, 255, 0);
	}
	else if (test == 4) {
		color = vec3(255, 0, 0);
	}
	else {
		color = texture2D(tex, uv).rgb;
	}

}
