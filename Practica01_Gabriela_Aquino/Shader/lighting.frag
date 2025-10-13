#version 330 core

// Estructuras (sin cambios)
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Entradas (sin cambios)
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

// Salida (sin cambios)
out vec4 color;

// Uniforms
uniform vec3 viewPos;
uniform Material material;
uniform sampler2D texture_diffuse; // Renombrado para evitar confusión

// Tenemos dos luces
uniform Light light;
uniform Light light2;

// Esta función calcula la iluminación para una sola fuente de luz.
vec3 CalcularLuz(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // Ambiente
    vec3 ambient = light.ambient * material.diffuse;
    
    // Difusa
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // Especular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);
    
    return (ambient + diffuse + specular);
}


void main()
{
    // Propiedades comunes para ambos cálculos de luz
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // Calcular la contribución de la primera luz
    vec3 result1 = CalcularLuz(light, norm, FragPos, viewDir);
    
    // Calcular la contribución de la segunda luz
    vec3 result2 = CalcularLuz(light2, norm, FragPos, viewDir);
    
    // El resultado final es la suma de ambas luces
    vec3 result = result1 + result2;
    
    // Aplicar la textura al resultado combinado
    color = vec4(result, 1.0f) * texture(texture_diffuse, TexCoords);
}