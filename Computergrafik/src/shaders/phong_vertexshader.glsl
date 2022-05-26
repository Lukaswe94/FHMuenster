attribute vec3 aVertexPosition;
attribute vec3 aNormalPosition;
attribute vec2 aTexCoord;

uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;
uniform mat3 uNormalMatrix;

varying vec3 vVertexPos;
varying vec3 vNormalPos;

varying vec2 vTexCoord;


void main(void) {
    gl_Position = uProjectionMatrix * uModelViewMatrix *vec4(aVertexPosition, 1);
    vec4 pos = uModelViewMatrix * vec4(aVertexPosition, 1);
    vVertexPos = pos.xyz / pos.w;
    vNormalPos = normalize(uNormalMatrix * aNormalPosition);
    vTexCoord = aTexCoord;
}
