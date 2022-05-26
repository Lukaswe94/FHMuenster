// Dummy vertex shader

attribute vec3 aVertexPosition;
attribute vec4 aVertexColor;

uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;


varying vec4 vColor;

void main(void) {
  gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aVertexPosition, 1.0);
  vColor = aVertexColor;
  
  //vColor = (vec4(aVertexPosition, 1.0)/0.5+0.49)/2.0;
  //vColor.w = 1.0;
}