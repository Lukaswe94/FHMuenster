import { mat4, vec3 } from "gl-matrix";
import { Triangle } from "./triangle";
import { WebGLStart } from "./webglstart";
import { Square } from "../forms/square";
import { Cube } from "../forms/cube";

/**
 * fragmentshader farbberechnung mit aVertexPosition 
 * cube mit höhe,breite,tiefe berechnen
 * rotation modelviewmatrix oder math.pi
 *  */ 
/*let form = "";
document.getElementById("triangleButton").onclick = function() {
    form = "triangle"
}
document.getElementById("squareButton").onclick = function() {
    form = "square"
}
document.getElementById("cubeButton").onclick = function() {
    form = "cube"
}

let v1 = vec3.create();
vec3.set(v1, 0.5, 0.5, 0.5);

let v2 = vec3.create();
vec3.set(v2, -0.5, 0.5, 0.5);

let v3 = vec3.create();
vec3.set(v3, -0.5, -0.5, 0.5);

let v4 = vec3.create();
vec3.set(v4, 0.5, -0.5, 0.5);

let triangle = new Triangle(v2, v3, v4);

let square = new Square(v1, v2, v3, v4);
let cube = new Cube(1, 1, 1);


function drawScene() {
    let webglStart = WebGLStart.getInstance();
    let gl = webglStart.gl;
    gl.viewport(0, 0, webglStart.canvas.width, webglStart.canvas.height);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    mat4.identity(webglStart.projectionMatrix);
    mat4.identity(webglStart.modelViewMatrix);

    gl.uniformMatrix4fv(webglStart.pMatrixUniform, false, webglStart.projectionMatrix);
    gl.uniformMatrix4fv(webglStart.mMatrixUniform, false, webglStart.modelViewMatrix);
    
    if(form == "triangle") triangle.draw(3);
    else if(form == "square")square.draw(6);
    else cube.draw(36);
    window.requestAnimationFrame(drawScene);
}
window.requestAnimationFrame(drawScene);

import { KeyBoardDemo } from "../keyboard/keyboarddemo";




let keyboardDemo = new KeyBoardDemo();

keyboardDemo.registerEvents();
*/