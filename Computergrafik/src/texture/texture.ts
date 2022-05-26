import { SGNode } from "../szenegraph/sgnode";
import {WebGLStart} from "../triangle/webglstart"

//Beispiel Laden von jpg
import * as myImage1 from './earth.jpg'

export class Texture extends SGNode {
	public texture: WebGLTexture;
	public image: any;

    constructor(src:any) {
       super();
        let webgl = WebGLStart.getInstance();
        this.texture = webgl.gl.createTexture();
        this.image = new Image();
        this.image.src = src;
        this.image.texture = this.texture;
        this.image.onload =  () => {
            Texture.loadTexture(this.image, this.texture);
            console.log("Texture " + src + " loaded.");
        };
        this.image.onerror =  () => {
            console.warn("Could not load texture: " + src);
        };

    }

    static loadTexture(image:TexImageSource, texture:WebGLTexture) {
  
        let webgl = WebGLStart.getInstance();
        let gl = webgl.gl;
     
        gl.bindTexture(gl.TEXTURE_2D, texture);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);

        //Erlaube alle Größen von Texturen
        //(idealerweise haben Texturen die Seitengröße x^2)
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);

        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image);
        gl.bindTexture(gl.TEXTURE_2D, null);
    }

    draw() {
        let webgl = WebGLStart.getInstance();
        let gl = webgl.gl;
        gl.activeTexture(gl.TEXTURE0);
        gl.bindTexture(gl.TEXTURE_2D, this.texture);
        gl.uniform1i(gl.getUniformLocation(webgl.shaderProgram, "uSampler"), 0);
    }
}
//Beispiel Laden von jpg
//let texture = new Texture(myImage1)
