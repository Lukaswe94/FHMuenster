import { vec3, vec4 } from "gl-matrix";
import { WebGLStart } from "./webglstart";



export class Triangle {
    vertices: number[];
    normal: number[];
    
    vertexPositionBuffer: WebGLBuffer;
    normalPositionBuffer: WebGLBuffer;
    texCoordBuffer: WebGLBuffer;
    webglStart: WebGLStart;

    gl: WebGLRenderingContext;
    vertexPositionAttribute: number;
    normalPositionAttribute: number;


 
    // vec3 -> 3D floating point vector
    constructor(v1: vec3, v2: vec3, v3: vec3) {
        this.vertices = [
            v1[0], v1[1], v1[2],
            v2[0], v2[1], v2[2],
            v3[0], v3[1], v3[2]
        ];
        let diff1 = vec3.sub(vec3.create(), v2, v1);
        let diff2 = vec3.sub(vec3.create(), v3, v1);
        let faceNormal = vec3.cross(vec3.create(), diff1, diff2);
        
        this.normal = [
            faceNormal[0], faceNormal[1], faceNormal[2],
            faceNormal[0], faceNormal[1], faceNormal[2],
            faceNormal[0], faceNormal[1], faceNormal[2]
        ];
        this.setWebGLRenderContext();
        this.initBuffers();
    }
 
    
    setWebGLRenderContext() {
        this.webglStart = WebGLStart.getInstance();
        this.gl = this.webglStart.gl;
        this.vertexPositionAttribute = this.webglStart.vertexPositionAttribute;
        this.normalPositionAttribute = this.webglStart.normalPositionAttribute;

        
    }
    initBuffers() {

            this.vertexPositionBuffer = this.gl.createBuffer();
            this.normalPositionBuffer = this.gl.createBuffer();

            this.gl.bindBuffer(this.gl.ARRAY_BUFFER, this.vertexPositionBuffer);
            this.gl.bufferData(this.gl.ARRAY_BUFFER, new Float32Array(this.vertices), this.gl.STATIC_DRAW);

            this.gl.bindBuffer(this.gl.ARRAY_BUFFER, this.normalPositionBuffer);
            this.gl.bufferData(this.gl.ARRAY_BUFFER, new Float32Array(this.normal), this.gl.STATIC_DRAW);


    }

    draw(count : number) {
       
            //bindBuffer() immer vor vertexAttribPointer() ausführen,
            //damit der gebundene Buffer in die zugehörige Shader Variable geladen wird!
            this.gl.bindBuffer(this.gl.ARRAY_BUFFER, this.vertexPositionBuffer);
            this.gl.vertexAttribPointer(this.vertexPositionAttribute, 3, this.gl.FLOAT, false, 0, 0);

            this.gl.bindBuffer(this.gl.ARRAY_BUFFER, this.normalPositionBuffer);
            this.gl.vertexAttribPointer(this.normalPositionAttribute, 3, this.gl.FLOAT, false, 0, 0);
            //this.gl.uniform4f(this.webglStart.fragmentColorAttribute, this.color[0], this.color[1], this.color[2], this.color[3]);
            this.gl.drawArrays(this.gl.TRIANGLES, 0, count);
    }
}
