// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330

// Tex coord input from vertex shader
in vec2 fragTexCoord;
in vec3 fragVertColor;

// This corresponds to the output color to the color buffer
out vec4 outColor;

// This is used for the texture sampling
uniform sampler2D uTexture;

void main()
{
	// Sample color from texture
	outColor = texture(uTexture, fragTexCoord);
	outColor.x = (outColor.x + fragVertColor.x) / 2.0f;
	outColor.y = (outColor.y + fragVertColor.y) / 2.0f;
	outColor.z = (outColor.z + fragVertColor.z) / 2.0f;
}
