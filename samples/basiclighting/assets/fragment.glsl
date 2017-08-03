uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
varying vec3 outNormal;
varying vec3 fragPos;
void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(outNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;

	gl_FragColor = vec4(result, 1.0);
}