
varying vec3 norm;
varying vec3 viewVec;


void main()
{
	vec4 v = vec4(gl_Vertex);
	gl_Position = gl_ModelViewProjectionMatrix * v;
    vec3 ecPosition = vec3(gl_ModelViewMatrix * gl_Vertex);
    norm      = normalize(gl_NormalMatrix * gl_Normal);
    viewVec    = normalize(-ecPosition);
}

//varying vec3 Normal;
//varying vec3 EyeDir;
//uniform samplerCube cube_texture;

//void main()
//{
//        gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
//        Normal = gl_NormalMatrix * gl_Normal;
//        EyeDir = vec3(gl_ModelViewMatrix * gl_Vertex);
//}