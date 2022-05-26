import { mat4, vec3 } from "gl-matrix";
import { WebGLStart } from "../triangle/webglstart";
import { SGNode } from "./sgnode";

export class Camera extends SGNode{


    private fovRadian : number;
    private projectionMatrix: mat4;
    private cameraPosition: vec3;
    private cameraMatrix: mat4;

    private x: number;
    private y: number;
    private z: number;
    private px: number;
    private pz: number;


    constructor(){
        super();
        this.fovRadian = Math.PI/2;
        this.cameraPosition = vec3.fromValues(0, 0, 100);
        this.cameraMatrix = mat4.create();
        this.initListeners();
        mat4.translate(this.cameraMatrix, this.cameraMatrix, this.cameraPosition);
        this.y = 
        this.x =
        this.z = 
        this.px =
        this.pz = 0;
        
    }
    getTrafo(){

        return this.trafo;
    }
    getCameraMatrix(){return this.cameraMatrix}
    setCameraMatrix(matrix: mat4){this.cameraMatrix = matrix}
    draw(){
        
        this.projectionMatrix = mat4.create();
        let webglStart= WebGLStart.getInstance();
        mat4.perspective(this.projectionMatrix, this.fovRadian%Math.PI, webglStart.canvas.width / webglStart.canvas.height, 1, 1000);

        let translation = vec3.fromValues(this.px, 0, this.pz);
        mat4.translate(this.cameraMatrix, this.cameraMatrix, translation);
        mat4.rotateX(this.cameraMatrix, this.cameraMatrix, this.x);
        mat4.rotateY(this.cameraMatrix, this.cameraMatrix, this.y);
        mat4.rotateZ(this.cameraMatrix, this.cameraMatrix, this.z);
        let viewMatrix = mat4.invert(mat4.create(), this.cameraMatrix);
        mat4.mul(this.projectionMatrix, this.projectionMatrix, viewMatrix);

        /* Funktioniert aber warum
        let start = mat4.copy(mat4.create(), this.trafo);
        let inverse = mat4.invert(mat4.create(), this.trafo);
        let inv_cam = vec3.negate(vec3.create(), this.cameraPosition);
        mat4.mul(this.trafo, this.trafo, inverse);
        // Warum Ursprung vor Camera und nicht direkt camera ?? 
        mat4.translate(this.trafo, this.trafo, inv_cam);
        mat4.translate(this.trafo, this.trafo, translation);
        mat4.rotateY(this.trafo, this.trafo, this.px);
        mat4.translate(this.trafo, this.trafo, this.cameraPosition);
        mat4.mul(this.trafo, this.trafo, start);
        */


        webglStart.gl.uniformMatrix4fv(webglStart.pMatrixUniform, false, this.projectionMatrix);
        
    }
    initListeners(){
        document.addEventListener('keydown', event => this.rotate(event.key,1) );
        document.addEventListener('keyup', event => this.rotate(event.key,0) );
    }
    
    rotate(code: String, status: number) {
        if(status == 1){
            if (code == 'ArrowDown'){
                this.pz = 10;
            }
            else if(code == 'ArrowUp'){
                this.pz = -10;
            }
            else if(code == 'ArrowLeft'){
                this.px = -10;
            }
            else if(code == 'ArrowRight'){
                this.px = 10;
            }
            if(code == 'w'){
                this.x = -0.05;
            }
            else if(code == 'a'){
                this.y = 0.05;
            }
            else if(code == 's'){
                this.x = 0.05;
            }
            else if(code == 'd'){
                this.y = -0.05;   
            }
            else if(code == 'q'){
                this.z = 0.05;
            }
            else if(code == 'e'){
                this.z = -0.05;
            }
    }
        else{
            this.px =
            this.pz = 
            this.y = 
            this.x =
            this.z = 0;
        }
    }
}