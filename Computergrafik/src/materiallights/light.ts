import { mat4, vec4 } from "gl-matrix";
import { SGNode } from "../szenegraph/sgnode";
import { WebGLStart } from "../triangle/webglstart";

export class Light extends SGNode{
    position: vec4;
    worldposition: vec4;
    ambient: vec4;
    diffuse: vec4;
    specular: vec4;
    isDirectionalLight: Boolean;
    lightPosition:WebGLUniformLocation;
    lightAmbient:WebGLUniformLocation;
    lightDiffuse:WebGLUniformLocation;
    lightSpecular:WebGLUniformLocation;


    constructor(position:vec4, ambient:vec4, diffuse:vec4, specular:vec4) {
        super();
        this.position = vec4.set(vec4.create(), position[0], position[1], position[2], position[3]);
        this.worldposition = vec4.clone(this.position);
        this.ambient = ambient;
        this.diffuse = diffuse;
        this.specular = specular;
        this.isDirectionalLight = this.position[3] == 0;
        
        if (this.isDirectionalLight) {
            this.position[3] = 1;
        }

        let startGL = WebGLStart.getInstance()


        this.lightPosition = startGL.gl.getUniformLocation(startGL.shaderProgram, "uLightPosition");
        this.lightAmbient = startGL.gl.getUniformLocation(startGL.shaderProgram, "uLightAmbient");
        this.lightDiffuse = startGL.gl.getUniformLocation(startGL.shaderProgram, "uLightDiffuse");
        this.lightSpecular = startGL.gl.getUniformLocation(startGL.shaderProgram, "uLightSpecular");
    }

    updatePosition(mvMatrix: mat4) {

        mat4.mul(this.worldposition as mat4, mvMatrix, this.position as mat4);

        if (this.isDirectionalLight) {
            this.worldposition[3] = 0;
        }
    }

    draw() {
        let startGL = WebGLStart.getInstance()

        startGL.gl.uniform4fv(this.lightPosition, this.worldposition);
        startGL.gl.uniform4fv(this.lightAmbient, this.ambient);
        startGL.gl.uniform4fv(this.lightDiffuse, this.diffuse);
        startGL.gl.uniform4fv(this.lightSpecular, this.specular);
    }
}
