import { mat4, vec4 } from "gl-matrix";
import { SGNode } from "../szenegraph/sgnode";
import { WebGLStart } from "../triangle/webglstart";


export class Material extends SGNode {
    emission:vec4;
    ambient: vec4;
    diffuse: vec4;
    specular: vec4;
    shininess: number;

    materialEmission:WebGLUniformLocation;
    materialAmbient:WebGLUniformLocation;
    materialDiffuse:WebGLUniformLocation;
    materialSpecular:WebGLUniformLocation;
    materialShininess:WebGLUniformLocation;


    constructor(emission:vec4, ambient:vec4, diffuse:vec4, specular:vec4, shininess:number) {
        super();
        this.emission = emission;
        this.ambient = ambient;
        this.diffuse = diffuse;
        this.specular = specular;
        this.shininess = shininess;

        let startGL = WebGLStart.getInstance();

        this.materialEmission = startGL.gl.getUniformLocation(startGL.shaderProgram, "uMaterialEmission");
        this.materialAmbient = startGL.gl.getUniformLocation(startGL.shaderProgram, "uMaterialAmbient");
        this.materialDiffuse = startGL.gl.getUniformLocation(startGL.shaderProgram, "uMaterialDiffuse");
        this.materialSpecular = startGL.gl.getUniformLocation(startGL.shaderProgram, "uMaterialSpecular");
        this.materialShininess = startGL.gl.getUniformLocation(startGL.shaderProgram, "uMaterialShininess");
    }

    draw() {
        let startGL = WebGLStart.getInstance();

        startGL.gl.uniform4fv(this.materialEmission, this.emission);
        startGL.gl.uniform4fv(this.materialAmbient, this.ambient);
        startGL.gl.uniform4fv(this.materialDiffuse, this.diffuse);
        startGL.gl.uniform4fv(this.materialSpecular, this.specular);
        startGL.gl.uniform1f(this.materialShininess, this.shininess);
    }
}
