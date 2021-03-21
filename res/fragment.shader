#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


uniform Material material;
uniform Light light;
uniform bool enable_custom_spec;
uniform vec3 viewPos;

void main()
{
    // ambient
    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = vec3(texture(material.specular, TexCoords)) * spec * light.specular;
    
    if(enable_custom_spec)
    {
        float spec2 = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess*64);
        specular += (vec3(texture(material.specular, TexCoords)) * 2) * spec2 * light.specular; 

        float spec3 = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess*2048);
        specular += (vec3(texture(material.specular, TexCoords)) * 10) * spec3 * light.specular;
    }
    
    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

    vec3 result = (ambient + diffuse + specular);
    
    FragColor = vec4(result, 1.0);
}