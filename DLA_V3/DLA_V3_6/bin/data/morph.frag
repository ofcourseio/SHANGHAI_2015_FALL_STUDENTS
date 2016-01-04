#version 120

uniform sampler2DRect tex0;
varying vec2 texCoordVarying;
uniform float time;
attribute vec4 gl_Color;
//varying vec4 gl_Color;
varying vec4 gl_FrontColor;

void main( void ){
//    gl_FrontColor = gl_Color;
    float r = texture2DRect( tex0, texCoordVarying ).r;
    float g = texture2DRect( tex0, texCoordVarying ).g;
    float b = texture2DRect( tex0, texCoordVarying ).b;
    vec4 col0 = texture2DRect( tex0, texCoordVarying );
//    gl_FragColor = vec4(0.0, 0.0, 0.0, 0.1);
//    gl_FragColor = gl_Color;
//    gl_FragColor = vec4(r, g, b, 1.0);
//    gl_FragColor = gl_Color;
//    gl_FragColor = gl_FrontColor;
}
