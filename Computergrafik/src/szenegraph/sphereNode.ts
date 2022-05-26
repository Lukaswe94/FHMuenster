import { mat4, vec3 } from "gl-matrix";
import { WebGLStart } from "../triangle/webglstart";
import { SGNode } from "./sgnode";

/*
 * by Kathrin Ungru, kathrin.ungru@fh-muenster.de
 * University of Applied Sciences Münster
 */
export class Sphere extends SGNode {
    /* 
    * Zeichne Kugel mit TRIANGLE_STRIPs
    *
    *  ... * - * - * ...
    *      |  /|  /|
    *      | / | / |
    *  ... * - * - * ...
    *      .
    *      .
    *      0   2   4
    *  ... * - * - * ...
    *      |  /|  /|
    *      | / | / |
    *  ... * - * - * ...
    *      1   3   5
    *      .
    *      .
    *  ... * - * - * ...
    *      |  /|  /|
    *      | / | / |
    *  ... * - * - * ...
    */
    height: number;
    vertexPositionData: Array<number> = [];
    normalPositionData: Array<number> = [];
    indexData: Array<number> = [];
    texData: Array<number> = [];
    vertexPositionBuffer: WebGLBuffer;
    normalPositionBuffer: WebGLBuffer;
    indexBuffer: WebGLBuffer;
    texCoordBuffer: WebGLBuffer;


    constructor(radius: number) {
        super();
        this.height = 2 * radius;
        const latitudeBands = 100;
        const longitudeBands = 100;

        
        // Erzeuge Punkte, af den Breiten- (latitudeBands) und Längengraden (longitudeBands) einer Kugel
        for (let i = 0; i <= latitudeBands; i++) {
            let theta = i * Math.PI / latitudeBands;
            let sinTheta = Math.sin(theta);
            let cosTheta = Math.cos(theta);
            for (let j = 0; j <= longitudeBands; j++) {
                let phi = j * 2 * Math.PI / longitudeBands;
                let x = sinTheta * Math.sin(phi);
                let y = cosTheta;
                let z = sinTheta * Math.cos(phi);
                this.vertexPositionData.push(radius * x);
                this.vertexPositionData.push(radius * y);
                this.vertexPositionData.push(radius * z);
                this.normalPositionData.push(x, y, z);
                
                this.texData.push(j/longitudeBands);
                this.texData.push(i/latitudeBands);
                
                
            }
        }


        //console.log(this.vertexPositionData);
        // Erzeuge Reihenfolge, in der die Punkte gezeichnet werden sollen
        for (let i = 0; i < latitudeBands; i++) {
            for (let j = 0; j < longitudeBands; j++) {
                let idx0 = (i * (longitudeBands + 1)) + j;
                let idx1 = idx0 + longitudeBands + 1;
                let idx2 = idx0 + 1;
                let idx3 = idx1 + 1;;
                this.indexData.push(idx0);
                this.indexData.push(idx1);
                this.indexData.push(idx2);
                this.indexData.push(idx3);
            }
        }
        this.initBuffers();
    }

    getHeight() {
        return this.height;
    }

    initBuffers() {
        let gl = WebGLStart.getInstance().gl;
        this.vertexPositionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, this.vertexPositionBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.vertexPositionData), gl.STATIC_DRAW);
        
        this.indexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.indexBuffer);
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(this.indexData), gl.STATIC_DRAW);

        this.normalPositionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, this.normalPositionBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.normalPositionData), gl.STATIC_DRAW);

        this.texCoordBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, this.texCoordBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.texData), gl.STATIC_DRAW);
        
    }

    bindBuffers() {
        let webgl = WebGLStart.getInstance();
        let gl = webgl.gl;

        // Binden des Buffers immer vor vertexAttribPointer() durchführen!
        gl.bindBuffer(gl.ARRAY_BUFFER, this.vertexPositionBuffer);
        gl.vertexAttribPointer(webgl.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);
        
        

        gl.bindBuffer(gl.ARRAY_BUFFER, this.normalPositionBuffer);
        gl.vertexAttribPointer(webgl.normalPositionAttribute, 3, gl.FLOAT, false, 0, 0);

        gl.bindBuffer(gl.ARRAY_BUFFER, this.texCoordBuffer);
        gl.vertexAttribPointer(webgl.texCoordAttribute, 2, gl.FLOAT, false, 0, 0);
        
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.indexBuffer);
    }

    draw(days: number) {
        let webglStart = WebGLStart.getInstance();
        let gl = webglStart.gl;
        this.bindBuffers();
        
        //Zeichnet Elemente im Array-Buffer gemäß Element-Indices im Index-Buffer
        gl.drawElements(gl.TRIANGLE_STRIP, this.indexData.length, gl.UNSIGNED_SHORT, 0);
    }
}
