// Objekte erstellen
import { mat4, vec4 } from "gl-matrix";
import { Camera } from "./camera";
import { Orbit } from "./orbit";
import { Planet } from "./planet";
import {Scenegraph} from "./scenegraph"
import { WebGLStart } from "../triangle/webglstart";
import { Sphere } from "./sphereNode";
import { CubeNode } from "./cubeNode";
import { Light } from "../materiallights/light";
import { Material } from "../materiallights/material";
import { Timer } from "./timer";
import * as sunTex from "../texture/SonnensystemTexturen/Texturen/sun.jpg";
import * as earthTex from "../texture/SonnensystemTexturen/Texturen/earth.jpg";
import * as marsTex from "../texture/SonnensystemTexturen/Texturen/mars.jpg";
import * as jupiterTex from "../texture/SonnensystemTexturen/Texturen/jupiter.jpg";
import * as mercuryTex from "../texture/SonnensystemTexturen/Texturen/mercury.jpg";
import * as neptuneTex from "../texture/SonnensystemTexturen/Texturen/neptune.jpg";
import * as saturnTex from "../texture/SonnensystemTexturen/Texturen/saturn.jpg";
import * as uranusTex from "../texture/SonnensystemTexturen/Texturen/uranus.jpg";
import * as venusTex from "../texture/SonnensystemTexturen/Texturen/venus.jpg";

import * as borg from "../texture/SonnensystemTexturen/Texturen/borg-cube.jpg";

import { Texture } from "../texture/texture";

import { GameController } from "../keyboard/gamecontroller";


let timer = new Timer(3);

/**
 * testing
 */

let light = new Light(
    vec4.fromValues(0,0,0,1), 
    vec4.fromValues(1,1,1,1), 
    vec4.fromValues(1,1,1,1), 
    vec4.fromValues(1,1,1,1));
/**
 * http://learnwebgl.brown37.net/10_surface_properties/surface_properties_color.html
 * gold 0.24725 	0.1995 	    0.0745
 *  	0.75164     0.60648     0.22648     1.0
 * 	    0.628281 	0.555802 	0.366065
 *  	0.4
 */
let sunMaterial = new Material(
    vec4.fromValues(0.7, 0.7, 0, 1), 
    vec4.fromValues(0.24725, .2245, .0645, 1), 
    vec4.fromValues(0.75164, 0.60648, 0.22648, 1), 
    vec4.fromValues(0.628281, 0.555802, 0.366065, 1),
    83.2);

    /**
     * Copper 	
     * 0.19125      0.0735      0.0225      1.0 
     * 0.7038       0.27048     0.0828      1.0
     * 0.256777     0.137622    0.086014    1.0
     * 12.8
     */
let marsMaterial = new Material(
    vec4.fromValues(0,0,0,1), 
    vec4.fromValues(0.1745,0.01175,0.01175,1.0), 
    vec4.fromValues(0.61424,0.04136,0.04136,1.0), 
    vec4.fromValues(0.727811,0.626959,0.626959,1.0), 
    0.6);

    /**
     * Emerald 	
     * 0.0215   0.1745      0.0215  0.55
     * 0.07568  0.61424     0.07568 0.55
     * 0.633    0.727811    0.633   0.55
     * 76.8
     */
let earthMaterial = new Material(
    vec4.fromValues(0, 0, 0, 1), 
    vec4.fromValues(0.135,0.2225,0.1575,1.0), 
    vec4.fromValues(0.54,0.89,0.63,1.0), 
    vec4.fromValues(0.316228,0.316228,0.316228,1.0), 
    12.8);

    /**
     * Pewter 	
     * 0.105882     0.058824    0.113725    1.0
     * 0.427451     0.470588    0.541176    1.0
     * 0.333333     0.333333    0.521569    1.0
     * 9.84615
     */
let moonMaterial = new Material(
    vec4.fromValues(0, 0, 0, 1),
    vec4.fromValues(0.105882 , 0.058824, 0.113725, 1), 
    vec4.fromValues(0.427451, 0.470588, 0.541176, 1), 
    vec4.fromValues(0.333333, 0.333333, 0.521569, 1), 
    9.84615);

let silver = new Material(
    vec4.fromValues(0.3,0.3,0.3,1.0),
    vec4.fromValues(0.19225,0.19225,0.19225,1.0),
    vec4.fromValues(0.50754,0.50754,0.50754,1.0),
    vec4.fromValues(0.508273,0.508273,0.508273,1.0),
    0.4*128
)


/**
 * 
 */

//let sphere = new Sphere(50, moonColor);
let camera = new Camera();

let gc = new GameController(camera);

//let sun = new Planet(30, 7.25, sunColor);
let sun = new Planet(7.25, 25.38,sunMaterial, sunTex);
let sunBody = new Sphere(20);
let sunOrbit = new Orbit(0, 0, 0);
//let earth = new Planet(4, 23.45, earthColor);
let earth = new Planet(23.45, 1, earthMaterial, earthTex);
let earthBody = new Sphere(4);
let earthOrbit = new Orbit(80, 0, 365);
//let mars = new Planet(2, 25.19, marsColor);
let mars = new Planet(25.19, 1.03, moonMaterial, marsTex);
let marsBody = new Sphere(2);
let marsOrbit = new Orbit(105, 19, 678);
//let moon = new Planet (0.5, 1.54, moonColor);

let moon = new Planet (1.54, 27.32, moonMaterial, borg);

let moonBody = new CubeNode(1, 1, 1);
let moonOrbit = new Orbit(6, 5.145, 27.32);

let neptune = new Planet(29.58, 0.80, moonMaterial, neptuneTex);
let neptuneBody = new Sphere(10);
let neptuneOrbit = new Orbit(450, 1.77, 60152);

let uranus = new Planet(97.86, 0.75, moonMaterial,uranusTex);
let uranusBody = new Sphere(11);
let uranusOrbit = new Orbit(280, 0.77, 30664);

let saturn = new Planet(26.73, 0.43, moonMaterial, saturnTex);
let saturnBody = new Sphere(14);
let saturnOrbit = new Orbit(210, 2.48, 10753);

let jupiter = new Planet(3.12, 0.41, moonMaterial, jupiterTex);
let jupiterBody = new Sphere(15);
let jupiterOrbit = new Orbit(130, 1.04, 4329);

let venus = new Planet(177.36, 243,moonMaterial, venusTex);
let venusBody = new Sphere(4);
let venusOrbit = new Orbit(60, 3.40, 226);

let mercury = new Planet(0, 58.65, silver, mercuryTex);
let mercuryBody = new Sphere(2);
let mercuryOrbit = new Orbit(40, 7.00, 88);



sun.setMaterial(sunMaterial);
earth.setMaterial(earthMaterial);
mars.setMaterial(marsMaterial);
moon.setMaterial(moonMaterial);

camera.addChild(sunOrbit);
sunOrbit.addChild(sun);
sunOrbit.addChild(earthOrbit);
sunOrbit.addChild(marsOrbit);

sunOrbit.addChild(neptuneOrbit);
sunOrbit.addChild(uranusOrbit);
sunOrbit.addChild(venusOrbit);
sunOrbit.addChild(mercuryOrbit);
sunOrbit.addChild(saturnOrbit);
sunOrbit.addChild(jupiterOrbit);

neptuneOrbit.addChild(neptune);
neptune.addChild(neptuneBody);

uranusOrbit.addChild(uranus);
uranus.addChild(uranusBody);

venusOrbit.addChild(venus);
venus.addChild(venusBody);

mercuryOrbit.addChild(mercury);
mercury.addChild(mercuryBody);

saturnOrbit.addChild(saturn);
saturn.addChild(saturnBody);

jupiterOrbit.addChild(jupiter);
jupiter.addChild(jupiterBody);


sun.addChild(sunBody);
sunBody.addChild(light);

marsOrbit.addChild(mars);
earthOrbit.addChild(earth);
mars.addChild(marsBody);

earth.addChild(earthBody);

earthOrbit.addChild(moonOrbit);
moonOrbit.addChild(moon);
moon.addChild(moonBody);

// sunBody.addChild(sunMaterial);
// marsBody.addChild(marsMaterial);
// earthBody.addChild(earthMaterial);
// moonBody.addChild(moonMaterial);


// zeichne Szenegraph, gebe Wurzelobjekt als Start
let scene = new Scenegraph(camera);


function drawScene() {
    
    let time = timer.daysPassed();
    let webglStart = WebGLStart.getInstance();
    let gl = webglStart.gl;
    gl.viewport(0, 0, webglStart.canvas.width, webglStart.canvas.height);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    gc.updateStatus();
    scene.draw(time);
    window.requestAnimationFrame(drawScene);
}
window.requestAnimationFrame(drawScene);
