#version 330
in vec3 TexCoord0;

uniform sampler2D gSampler;

void main()
{
    float w;
    float x = TexCoord0.x;
    float y = TexCoord0.y;
    float z = TexCoord0.z;

    if (x >= 0 && z >= 0)
    {
        w = (2 * 3.14 - atan(abs(x / z))) / (2 * 3.14);
    }
    else if (x > 0 && z < 0) 
    {
        w = (3.14 + atan(abs(x / z))) / (2 * 3.14);
    }
    else if (x <= 0 && z <=0)
    {
        w = (3.14 - atan(abs(x / z))) / (2 * 3.14);
    }
    else
    {
        w = atan(abs(x / z)) / (2 * 3.14);
    }

    gl_FragColor = texture2D(gSampler, vec2(w, -1 * (asin(y)*2/3.14 + 1)/2));
}
