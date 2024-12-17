uniform sampler2D texture;
uniform vec2 resolution;

void main()
{
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    vec3 invertedColor = vec3(1.0) - color.rgb;

    gl_FragColor = vec4(invertedColor, color.a);
}
