uniform sampler2D texture;
uniform vec2 resolution;

void main()
{
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    mat3 tritanopia = mat3(
        0.95,  0.05,  0.0,
        0.0,   0.43333, 0.56667,
        0.0,   0.475,  0.525
    );

    vec3 correctedColor = color.rgb * tritanopia;
    gl_FragColor = vec4(correctedColor, color.a);
}
