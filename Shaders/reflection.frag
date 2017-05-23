
varying vec3 norm;
varying vec3 viewVec;
uniform samplerCube cube_texture;

//uniform samplerCube cube_texture;

void main()
{
	vec3 ref = reflect(viewVec, norm);

	//float fog = (gl_Fog.end - gl_FogFragCoord) * gl_Fog.scale;
	vec4 colorFog = texture(cube_texture, ref);
	gl_FragColor = 	colorFog;
}

//varying vec3 Normal;
//varying vec3 EyeDir;

//uniform samplerCube cube_texture;

// void main(void)
// {
//    vec3 reflectedDirection = normalize(reflect(EyeDir, normalize(Normal)));
//    reflectedDirection.y = -reflectedDirection.y;
//    vec4 fragColor = textureCube(cube_texture, reflectedDirection);
//    gl_FragColor = fragColor;
//} 