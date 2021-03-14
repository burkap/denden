#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 ourColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    // specular
    float specularStrength = 1;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
    vec3 specular = specularStrength * 1 * spec * lightColor;


    float spec2 = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular2 = specularStrength * 2 * spec2 * lightColor; 

    float spec3 = pow(max(dot(viewDir, reflectDir), 0.0), 2048);
    vec3 specular3 = specularStrength * 10 * spec3 * lightColor;
    
    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse + specular + specular2 + specular3) * ourColor;
    FragColor = vec4(result, 1.0);
}