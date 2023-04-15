#version 450 core
in float lifetime;
out vec4 fragColor;

void main()
{
    float alpha = lifetime / 1300.0;

    if (alpha > 1.0)
    {
        alpha = 1.0;
    }

    vec4 color = vec4(0.5, 0.5, 0.5, alpha);
    fragColor = color;
}