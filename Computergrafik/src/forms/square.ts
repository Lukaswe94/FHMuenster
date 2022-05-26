import { vec3, vec4 } from "gl-matrix";
import { Triangle } from "../triangle/triangle";
import { WebGLStart } from "../triangle/webglstart";

// export class Square{
//     triangle1: Triangle;
//     triangle2: Triangle;
//     constructor(v1: vec3, v2: vec3, v3: vec3, v4: vec3){
//         this.triangle1 = new Triangle(v1, v2, v3);
//         this.triangle2 = new Triangle(v1, v3, v4);
//     };
//     draw(){
//         this.triangle1.draw();
//         this.triangle2.draw();
//     }

// }
export class Square{

    textPositionData: Array<number> = [];
    texturePositionBuffer: WebGLBuffer;



    triangles: Triangle[] =[];
    constructor(v1: vec3, v2: vec3, v3: vec3, v4: vec3){
        this.triangles.push(new Triangle(v1, v2, v3));
        this.triangles.push(new Triangle(v3, v4, v1)); 
        
        this.initBuffer();

    }


    initBuffer(){
        let gl = WebGLStart.getInstance().gl;
        this.texturePositionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, this.texturePositionBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.textPositionData), gl.STATIC_DRAW);

    }

    bindBuffer(){
        let webgl = WebGLStart.getInstance();
        let gl = webgl.gl;

        gl.bindBuffer(gl.ARRAY_BUFFER, this.texturePositionBuffer);
        gl.vertexAttribPointer(webgl.texCoordAttribute, 2, gl.FLOAT, false, 0, 0);
    }





    draw(){
        /*
        this.triangles.forEach(t =>{
            t.draw(3);
        })
        */

        //Dreieck unten links
        this.textPositionData = [
        0,0, //oben links
        0,1, //unten links
        1,1 //unten rechts
        ];
        this.initBuffer();
        this.bindBuffer();
        this.triangles[0].draw(3);

        this.textPositionData = [
            1,1, // unten rechts
            1,0, //oben rechts
            0,0 //oben links
        ];
        this.initBuffer();
        this.bindBuffer();
        this.triangles[1].draw(3);
    }


}