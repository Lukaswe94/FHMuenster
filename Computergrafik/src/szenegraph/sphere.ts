import { WebGLStart } from "../triangle/webglstart";
import { SGNode } from "./sgnode";

export class Sphere extends SGNode{
    private vertices : number[];
    private radius: number;
    private x: number[];
    private y: number[];

    vertexPositionBuffer: WebGLBuffer;
    vertexColorBuffer: WebGLBuffer;
    
    webglStart: WebGLStart;

    gl: WebGLRenderingContext;
    vertexPositionAttribute: number;
    vertexColorAttribute: number;
    color : number[];    
    constructor(diameter: number, color: number[]){
        super();
        this.radius = diameter/2;
        this.color = color;
        this.vertices = [0];
        this.calcVertices();
        this.setWebGLRenderContext();
        this.initBuffers();
    }
    calcVertices(){
        for(let i = 0; i <= 360; i+=3){
            let angle = i*(Math.PI/180);
            this.vertices[i] = this.radius*Math.sin(angle);
            this.vertices[i+1] = this.radius*Math.cos(angle);
            this.vertices[i+2] = 0;
        }
    }

        
    setWebGLRenderContext() {
        this.webglStart = WebGLStart.getInstance();
        this.gl = this.webglStart.gl;
        this.vertexPositionAttribute = this.webglStart.vertexPositionAttribute;


        
    }
    initBuffers() {

            this.vertexPositionBuffer = this.gl.createBuffer();

            this.gl.bindBuffer(this.gl.ARRAY_BUFFER, this.vertexPositionBuffer);
            this.gl.bufferData(this.gl.ARRAY_BUFFER, new Float32Array(this.vertices), this.gl.STATIC_DRAW);




    }

    draw() {
       
            //bindBuffer() immer vor vertexAttribPointer() ausführen,
            //damit der gebundene Buffer in die zugehörige Shader Variable geladen wird!
            this.gl.bindBuffer(this.gl.ARRAY_BUFFER, this.vertexPositionBuffer);
            this.gl.vertexAttribPointer(this.vertexPositionAttribute, 3, this.gl.FLOAT, false, 0, 0);
            this.gl.uniform4f(this.webglStart.fragmentColorAttribute, this.color[0], this.color[1], this.color[2], this.color[3]);
            this.gl.drawArrays(this.gl.TRIANGLES, 0, 120);
    }
}