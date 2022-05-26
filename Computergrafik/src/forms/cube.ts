import { vec3, vec4 } from "gl-matrix";

import { Square } from "./square";

export class Cube extends Square{
    constructor(heigth: number, width: number, depth: number){
        let v1=vec3.create();
        let v2=vec3.create();
        let v3=vec3.create();
        let v4=vec3.create();
        let v5=vec3.create();
        let v6=vec3.create();
        let v7=vec3.create();
        let v8=vec3.create();
        vec3.set(v1, heigth/2, width/2, -depth/2);
        vec3.set(v2, heigth/2, -width/2, -depth/2);
        vec3.set(v3, -heigth/2, -width/2, -depth/2);
        vec3.set(v4, -heigth/2, width/2, -depth/2);
        vec3.set(v5, heigth/2, width/2, depth/2);
        vec3.set(v6, heigth/2, -width/2, depth/2);
        vec3.set(v7, -heigth/2, -width/2, depth/2)
        vec3.set(v8, -heigth/2, width/2, depth/2);
        super(v1, v2, v3, v4);
        let background = new Square(v6, v5, v8, v7);
        let top = new Square(v5, v6, v2, v1);
        let right = new Square(v5, v1, v4, v8);
        let left = new Square(v2, v6, v7, v3);
        let bottom = new Square(v4, v3, v7, v8);
        
        //this.vertices = this.vertices.concat(background.vertices, top.vertices, right.vertices, left.vertices, bottom.vertices);
       
        //this.initBuffers();
    }

    /**  old  constructor(v1: vec3, v2: vec3, v3: vec3, v4: vec3){
        super(v1, v2, v3, v4);
        let v5 = vec3.create();
        let v6 = vec3.create();
        let v7 = vec3.create();
        let v8 = vec3.create();
        vec3.set(v5, v1[0], v1[1], -0.5);
        vec3.set(v6, v2[0], v2[1], -0.5);
        vec3.set(v7, v3[0], v3[1], -0.5);
        vec3.set(v8, v4[0], v4[1], -0.5);
        let background = new Square(v5, v8, v7, v6);
        let top = new Square(v1, v5, v6, v2);
        let right = new Square(v1, v4, v8, v5);
        let left = new Square(v2, v6, v7, v3);
        let bottom = new Square(v7, v8, v4, v3);
        this.vertices = this.vertices.concat(background.vertices, top.vertices, right.vertices, left.vertices, bottom.vertices);
        this.color = [  
            0.0,  0.0,  0.0,  1.0, 
            1.0,  0.0,  0.0,  1.0,
            0.0,  0.0,  0.0,  1.0, 
            0.0,  0.0,  0.0,  1.0,
            0.0,  0.0,  0.0,  1.0,
            0.0,  1.0,  0.0,  1.0,
            0.0,  0.0,  0.0,  1.0, 
            1.0,  0.0,  0.0,  1.0,
            0.0,  0.0,  0.0,  1.0, 
            0.0,  0.0,  0.0,  1.0,
            0.0,  0.0,  0.0,  1.0,
            0.0,  1.0,  0.0,  1.0, 
            0.0,  0.0,  0.0,  1.0, 
            1.0,  0.0,  0.0,  1.0,
            0.0,  0.0,  0.0,  1.0, 
            0.0,  0.0,  0.0,  1.0,
            0.0,  0.0,  0.0,  1.0,
            0.0,  1.0,  0.0,  1.0, 
            0.0,  0.0,  0.0,  1.0, 
            1.0,  0.0,  0.0,  1.0,
            0.0,  0.0,  0.0,  1.0, 
            0.0,  0.0,  0.0,  1.0,
            0.0,  0.0,  0.0,  1.0,
            0.0,  1.0,  0.0,  1.0, 
            0.0,  0.0,  0.0,  1.0, 
            1.0,  0.0,  0.0,  1.0,
            0.0,  0.0,  0.0,  1.0, 
            0.0,  0.0,  0.0,  1.0,
            0.0,  0.0,  0.0,  1.0,
            0.0,  1.0,  0.0,  1.0, 
            0.0,  0.0,  0.0,  1.0, 
            1.0,  0.0,  0.0,  1.0,
            0.0,  0.0,  0.0,  1.0, 
            0.0,  0.0,  0.0,  1.0,
            0.0,  0.0,  0.0,  1.0,
            0.0,  1.0,  0.0,  1.0 
            ];
        this.initBuffers();
    } */
    

}