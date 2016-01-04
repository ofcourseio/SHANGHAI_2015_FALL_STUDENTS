#version 120

uniform float width;
uniform float height;
uniform float time;
uniform vec2 mouse;
uniform float alpha;


void main( void )
{
	//gl_FragCoord
    float x = gl_FragCoord.x;
    float y = gl_FragCoord.y;
    float u;
    float v;
    float red;
    float green;
    float blue;
    v = (x - width/2) * (y - height/2);
    u = v * 0.0005 * time;
    red = sin(u);
    green = sin (u * 2);
    blue = 1- green;
    
    
    gl_FragColor = vec4(red, green, blue, alpha);
}

//void main( void )
//{
//    //gl_FragCoord
//    float x = gl_FragCoord.x;
//    float y = gl_FragCoord.y;
//    
//    
//    
//    float red;
//    
//    if (x>mouse.x) {
//        red = tan(0.05*x * y);
//    }else{
//        red = cos(0.05*x * y)/sin(0.6 * x * y);
//    }
//    
//    
//    float green;
//    //    float green = y / height;
//    if ( sin(time*x)/(cos(time*y)) > 0 ) {
//        green = ((cos((10 * x * y) / (width * height) * 10.0 + 2.5*time)) + 1.0) / 2.0;
//        //        green = 0.5;
//    }
//    else {
//        green = 0.2;
//    }
//    //    float green = ((cos((10 * x * y) / (width * height) * 10.0 + 2.5*time)) + 1.0) / 2.0;
//    
//    float blue = ((sin((10 * x * y) / (width * height) * 10.0 + 2.5*time)) + 1.0) / 2.0;
//    //    float blue = 0.3;
//    red = abs(blue-2.0*sin(time));
//    gl_FragColor = vec4(red, green, blue, 0.7);
//}