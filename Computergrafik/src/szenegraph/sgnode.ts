import { mat4 } from "gl-matrix";


export class SGNode{
	private children: Array<SGNode> = [];
	protected trafo: mat4;
	constructor(){
		this.trafo = mat4.create();

	}

	getChildren(){
		return this.children;
	}

	addChild(node: SGNode){
		this.children.push(node);
	}
	getTrafo(){
		return this.trafo;
	}

	draw(days: number){}
}
