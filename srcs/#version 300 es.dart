#version 300 es
precision highp float;
out vec4 outColor;

in vec2 tc;
in vec3 fn;
in vec3 vertPos;

uniform int mode;
uniform vec3 lightDirection;


const vec4 ambientColor = vec4(0.01, 0.0, 0.0, 1.0);
const vec4 diffuseColor = vec4(0.25, 0.0, 0.0, 1.0);
const vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0);
const float shininess = 40.0;
const vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
const float irradiPerp = 1.0;

vec3 blinnPhongBRDF(vec3 lightDir, vec3 viewDir, vec3 normal, vec3 phongDiffuseCol, vec3 phongSpecularCol, float phongShininess) {
  vec3 color = phongDiffuseCol;
  vec3 halfDir = normalize(viewDir + lightDir);
  float specDot = max(dot(halfDir, normal), 0.0);
  color += pow(specDot, phongShininess) * phongSpecularCol;
  return color;
}

void main() {
  vec3 lightDir = normalize(-lightDirection);
  vec3 viewDir = normalize(-vertPos);
  vec3 n = normalize(fn);

  vec3 radiance = ambientColor.rgb;
  
  float irradiance = max(dot(lightDir, n), 0.0) * irradiPerp;
  if(irradiance > 0.0) {
    vec3 brdf = blinnPhongBRDF(lightDir, viewDir, n, diffuseColor.rgb, specularColor.rgb, shininess);
    radiance += brdf * irradiance * lightColor.rgb;
  }
  
  radiance = pow(radiance, vec3(1.0 / 2.2) ); // gamma correction
  outColor.rgb = radiance;
  outColor.a = 1.0;
} 
    