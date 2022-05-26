import { mat4 } from "gl-matrix";

export class MatrixStack {
    private matrixStack:  Array<mat4> = []

    constructor() {
    }

    push(mat: mat4){
        this.matrixStack.push(mat4.clone(mat))
    }

    pop() {
        
        return mat4.clone(this.matrixStack.pop());
    }
}

