import { mat4, vec3 } from "gl-matrix";
import { Framerate } from "./framerate";
import { SGNode } from "./sgnode";

export class Orbit extends SGNode{
	private radius: number;
	private tiltRad: number;
	private circulation: number;
	constructor(radius: number, tilt: number, circulationPeriod: number){
		super();
		this.radius = radius;
		this.tiltRad = tilt * (Math.PI/180);
		this.circulation = circulationPeriod;

		mat4.rotateZ(this.trafo, mat4.create(), this.tiltRad);
		mat4.translate(this.trafo, this.trafo, vec3.fromValues(this.radius, 0, 0));

	}
	getTrafo(){



		return this.trafo;
	}
	draw(days: number){
		let rotation;

		if(this.circulation==0){
			return;            
		}
		/*timer v1

		rotation =50* Framerate.ftime/(this.circulation);

		 */
		// timer = dauer eines "Tages" in tag*sec, komplette circulation entspricht 360grad = 2pirad
		// anteil = timer/circulation => (timer/circ)*pi/180 ?? anteil =anteil* 2pirad/360
		// timer v2
		
		let part = days/this.circulation;
		rotation = part*2*Math.PI;
		mat4.translate(this.trafo, this.trafo, vec3.fromValues(-this.radius, 0, 0))
		mat4.rotateY(this.trafo, this.trafo, rotation);
		mat4.translate(this.trafo, this.trafo, vec3.fromValues(this.radius, 0, 0));
	}
}
