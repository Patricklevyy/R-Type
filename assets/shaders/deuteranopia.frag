uniform sampler2D texture;
uniform vec2 resolution;

void main()
{
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    mat3 deuteranopia = mat3(
        0.625, 0.375, 0.0,
        0.7,   0.3,   0.0,
        0.0,   0.3,   0.7
    );

    vec3 correctedColor = color.rgb * deuteranopia;
    gl_FragColor = vec4(correctedColor, color.a);
}
