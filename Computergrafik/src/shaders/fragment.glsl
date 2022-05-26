// Dummy fragment shader
#ifdef GL_ES
precision mediump float;
varying vec4 vColor;
#endif
uniform vec4 color;

void main(void) {
    gl_FragColor = color;
}
