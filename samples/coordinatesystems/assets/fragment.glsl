varying vec2 otexcoord;
uniform sampler2D Texture0;
uniform sampler2D Texture1;
void main()
{
	gl_FragColor = mix(texture2D( Texture0, otexcoord ) , texture2D(Texture1, otexcoord), 0.2);
}