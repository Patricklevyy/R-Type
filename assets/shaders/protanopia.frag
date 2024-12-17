uniform sampler2D texture;
uniform vec2 resolution;

void main()
{
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    mat3 protanopia = mat3(
        0.56667, 0.43333, 0.0,
        0.55833, 0.44167, 0.0,
        0.0,     0.24167, 0.75833
    );

    vec3 correctedColor = color.rgb * protanopia;
    gl_FragColor = vec4(correctedColor, color.a);
}
