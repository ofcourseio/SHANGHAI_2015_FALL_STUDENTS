#version 120

uniform sampler2DRect tex0;
uniform float scale;
uniform float time;
uniform float width;
uniform float height;
varying vec2 texCoordVarying;
//varying vec4 gl_Color;
varying vec4 gl_FrontColor;

void main(void)
{
    // get the texture coordinates
    texCoordVarying = gl_MultiTexCoord0.xy;

    // get the position of the vertex relative to the modelViewProjectionMatrix
    vec4 position = gl_Vertex;
    vec3 normal = gl_Normal;
    float u = position.x ;
    float v = position.y ;

//    float u = position.x ;
//    float v = position.y ;

    
    vec4 positionA = position;
    vec4 positionB = position;
    float dist = sqrt( (u-width/2) * (u-width/2) +  (v-height/2)*(v-height/2));
    float theta;
    theta = (u-width/2)/dist;
//    theta = asin(theta);
//    positionB.x += sin(2.*theta);
//    positionB.y += cos(2.*theta);
//    positionB.z = dist;
//    positionB.z = 0.35 * dist * ( sin( 7  * theta ))+dist;
    positionB.z = 0.00025 * sin(1.2*time)* dist*( dist + cos(0.5*time)) * (sin(0.09 * sqrt(dist)))* ( sin( 16 *sin(0.3*time) * theta + theta * tan(0.05 * time ) ))+0.5*dist;
//        positionB.z = 0.00025 * sin(1.2*time)* dist*( dist + cos(0.5*time)) * (sin(0.009 * sqrt(dist)))* ( sin( 18 *sin(0.3*time) * theta + theta * tan(0.005*time) ))+0.5*dist;
//    positionB.z = 0.35 * sin(time)* dist * ( sin( 7  * theta ))+dist;
//    positionB.z = dist*( sin( 7 * sin(time) * theta));

    


    float morph = sin(time * 1.) * 0.5 + 0.5;
    morph = 0;
    vec4 finalPosition = positionA * morph + positionB * (1.0 - morph);
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * finalPosition;
//    gl_Position = finalPosition * gl_ModelViewMatrix;
//    gl_Position = finalPosition * gl_ModelViewProjectionMatrix;
    gl_FrontColor = gl_Color;
}
