#version 120

uniform sampler2DRect tex0;
uniform float scale;
uniform float time;
uniform float width;
uniform float height;
varying vec2 texCoordVarying;

void main(void)
{
    // get the texture coordinates
    texCoordVarying = gl_MultiTexCoord0.xy;
    
    
    // get the position of the vertex relative to the modelViewProjectionMatrix
    vec4 position = gl_Vertex;
    vec3 normal = gl_Normal;
    
    float u = position.x / width  * 1 * 3.1415926;
    float v = position.y / height * 2 * 3.1415926;
    
  
    
    
    vec4 positionA = position;
    vec4 positionB = position;
    
    
    positionA.x = cos(3*u)/3.0;
    positionA.y = sin(u+v);
    positionA.z = sin(v);
    
    
    positionB.x = sin(v)*cos(u);
    positionB.y = sin(v)*sin(u);
    positionB.z = cos(v);

    
//    position.x = sin(sin(v) * 3.0) * cos(u);
//    position.y = sin(u) * sin(u);
//    position.z = sin(v);
//    
//    position *= width;
//
    positionA.x *= width;
    positionA.y *= width;
    positionA.z *= width;
//
    positionB.x *= width;
    positionB.y *= width;
    positionB.z *= width;
//
    float morph = sin(time* 0.1) * 0.5 + 0.5;
    
    vec4 finalPosition = positionA * morph + positionB * (1.0 - morph);


	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * finalPosition;

}
