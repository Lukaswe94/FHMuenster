import {SGNode} from "./sgnode"

export class Component extends SGNode{
    private name : string

    constructor(name:any){
        super();
        this.name = name;
    }

    draw(){
    	return this.name+",";
    }
}
