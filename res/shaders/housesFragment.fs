#version 450 core
layout (location = 0) in vec2 TexCoord;
layout (location = 1) in vec4 textureColor;
layout (location = 3) in vec3 normal;
layout (location = 4) in vec3 fragPos;
layout (location = 5) in mat3 normalMatrix;
out vec4 color;

layout(binding = 3) uniform sampler2D currentTexture;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec4 lightColor_;

struct Material 
{
   sampler2D ambient;
   sampler2D diffuse;
   vec3 specular;
   float shininess;
};

struct DirLight 
{
   vec3 direction;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
}; 

struct PointLight 
{    
   vec3 position;

   float constant;
   float linear;
   float quadratic;  

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};  

struct SpotLight 
{
   vec3 position;
   vec3 direction;
   float cutOff;
   float outerCutOff;
  
   float constant;
   float linear;
   float quadratic;
  
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;       
};

#define NR_SPOT_LIGHTS 2
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

uniform DirLight dirLight;
uniform PointLight pointLight;
uniform Material material;

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
   vec3 lightDir = normalize(-light.direction);
   // światło rozproszone
   float diff = max(dot(normal, lightDir), 0.0);
   // światło lustrzane
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   // połącz wyniki
   vec3 ambient  = light.ambient  * vec3(texture(currentTexture, TexCoord));
   vec3 diffuse  = light.diffuse  * diff * vec3(texture(currentTexture, TexCoord));
   vec3 specular = light.specular * spec * material.specular;
   return vec4((ambient + diffuse + specular), 1.0);
}; 

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
   vec3 lightDir = normalize(light.position - fragPos);
   // światło rozproszone
   float diff = max(dot(normal, lightDir), 0.0);
   // światło lustrzane
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   // tłumienie
   float distance    = length(light.position - fragPos);
   float attenuation = 1.0 / (light.constant + light.linear * distance + 
   		            light.quadratic * (distance * distance));    
   // połącz wyniki
   vec3 ambient  = light.ambient  * vec3(texture(currentTexture, TexCoord));
   vec3 diffuse  = light.diffuse  * diff * vec3(texture(currentTexture, TexCoord));
   vec3 specular = light.specular * spec * material.specular;
   ambient  *= attenuation;
   diffuse  *= attenuation;
   specular *= attenuation;
   return vec4((ambient + diffuse + specular), 1.0);
};

vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(currentTexture, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(currentTexture, TexCoord));
    vec3 specular = light.specular * spec * material.specular;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return vec4((ambient + diffuse + specular), 1.0);
};

void main()
{
   vec3 norm = normalize(normalMatrix * normal);
   vec3 viewDir = normalize(viewPos - fragPos);
   vec4 result = vec4(0.0);
   result = CalcDirLight(dirLight, norm, viewDir);

   for(int i = 0; i < NR_SPOT_LIGHTS; i++)
   {
      result += CalcSpotLight(spotLights[i], norm, fragPos, viewDir); 
   }

   // result += CalcPointLight(pointLight, norm, fragPos, viewDir); 


   color = result;
}