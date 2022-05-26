import { mat3, mat4, vec3 } from "gl-matrix";
import { MatrixStack } from "../matrixstack/matrixstack";
import {SGNode} from "./sgnode"
import { WebGLStart } from "../triangle/webglstart";
import { Light } from "../materiallights/light";


export class Scenegraph {
    private root: SGNode
	private trafoStack: MatrixStack;
	private days: number;

    constructor(rootNode: SGNode){
        this.root = rootNode;
        this.trafoStack = new MatrixStack();
		this.trafoStack.push(rootNode.getTrafo());
    }

    drawTraversal(node: SGNode){
		//Hole webgl instance für Transformationsmatrizen
		let webglStart = WebGLStart.getInstance();
		let gl = webglStart.gl;
		//hole obersten trafoStack trafo und multipliziere
		
		let trafo = this.trafoStack.pop();
		//mat4.mul(trafo,trafo,trafoParent);
		this.trafoStack.push(trafo);
        mat4.mul(trafo,trafo,node.getTrafo());
		
        this.trafoStack.push(trafo);
		
		let normal = mat3.normalFromMat4(mat3.create(), trafo);
		
		// Gebe infos von trafo berechnung an Shader 
		gl.uniformMatrix4fv(webglStart.mMatrixUniform, false, trafo);
		gl.uniformMatrix3fv(webglStart.nMatrixUniform, false, normal);
		if(node instanceof Light){
			node.updatePosition(trafo);
		}
		node.draw(this.days);
		//wiederhole für alle Children
		
		for (let child of node.getChildren()) {
			this.drawTraversal(child);
		}
		
		this.trafoStack.pop();

    }

    draw (days: number){
		this.days = days;
		this.drawTraversal(this.root);
    	}
	}