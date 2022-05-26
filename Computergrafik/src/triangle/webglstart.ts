import { mat4, vec3 } from "gl-matrix";
import * as fragment from "./../shaders/phong_fragmentshader.glsl";
import * as vertex from "./../shaders/phong_vertexshader.glsl";


export class WebGLStart {
    canvas: HTMLCanvasElement;
    gl: WebGLRenderingContext;

    vertexColorBuffer: WebGLBuffer;
    vertexPositionBuffer: WebGLBuffer;
    shaderProgram: WebGLProgram;
    vertexPositionAttribute: number;
    normalPositionAttribute:number;
    texCoordAttribute: number;
    vertexColorAttribute: number;

    pMatrixUniform: WebGLUniformLocation;
    mMatrixUniform: WebGLUniformLocation;
    nMatrixUniform: WebGLUniformLocation;
    fragmentColorAttribute: WebGLUniformLocation;
    modelViewMatrix: mat4;
    projectionMatrix: mat4;

 

    private static instance: WebGLStart;


    private constructor(canvasID: string) {
        this.canvas = <HTMLCanvasElement>document.getElementById(canvasID);
        this.gl = this.canvas.getContext("webgl");
        this.modelViewMatrix = mat4.create();
        this.projectionMatrix = mat4.create();
        this.webGLStartExample();
    }

    public static getInstance(): WebGLStart {
        if (!WebGLStart.instance) {
            WebGLStart.instance = new WebGLStart("glCanvas");
        }
        
        return WebGLStart.instance;
    }
    createShaders(sourceShader: any, type: number) {
        var shader = this.gl.createShader(type);
        this.gl.shaderSource(shader, sourceShader);
        this.gl.compileShader(shader);
        return shader;
    }
    initShaders() {
    

        let vertexShader = this.createShaders(vertex, this.gl.VERTEX_SHADER);
        let fragmentShader = this.createShaders(fragment, this.gl.FRAGMENT_SHADER);
    

        this.shaderProgram = this.gl.createProgram();
        this.gl.attachShader(this.shaderProgram, vertexShader);
        this.gl.attachShader(this.shaderProgram, fragmentShader);
        this.gl.linkProgram(this.shaderProgram);

        if (!this.gl.getProgramParameter(this.shaderProgram, this.gl.LINK_STATUS)) {
            alert("Could not initialise shaders");
        }

        this.gl.useProgram(this.shaderProgram);
        
        this.vertexPositionAttribute = this.gl.getAttribLocation(this.shaderProgram, "aVertexPosition");
        this.gl.enableVertexAttribArray(this.vertexPositionAttribute);

        this.normalPositionAttribute = this.gl.getAttribLocation(this.shaderProgram, "aNormalPosition");
        this.gl.enableVertexAttribArray(this.normalPositionAttribute);

        this.texCoordAttribute = this.gl.getAttribLocation(this.shaderProgram, "aTexCoord");
        this.gl.enableVertexAttribArray(this.texCoordAttribute);

        
        this.pMatrixUniform = this.gl.getUniformLocation(this.shaderProgram, "uProjectionMatrix");
        this.mMatrixUniform = this.gl.getUniformLocation(this.shaderProgram, "uModelViewMatrix");
        this.nMatrixUniform = this.gl.getUniformLocation(this.shaderProgram, "uNormalMatrix");
        
        
    }



    webGLStartExample() {

        this.initShaders();

        this.gl.clearColor(0.0, 0.0, 0.0, 1.0);
        this.gl.enable(this.gl.DEPTH_TEST);
        this.gl.enable(this.gl.CULL_FACE);
        this.canvas.height = window.innerHeight;
        this.canvas.width = window.innerWidth;

        console.log(this.gl.getParameter(this.gl.VERSION));
        console.log(this.gl.getParameter(this.gl.SHADING_LANGUAGE_VERSION));

      
    }
}
