import { mat4, vec3 } from "gl-matrix";
import { connected } from "process";
import { Camera } from "../szenegraph/camera";
import { SGNode } from "../szenegraph/sgnode";

// https://developer.mozilla.org/en-US/docs/Web/Guide/API/Gamepad
export class GameController{
    node: Camera
    connected: Boolean;
    gp: { controller:Gamepad,
          connected:Boolean,
         connecthandler:(gamepad: Gamepad) => void,
         disconnecthandler:(gamepad: Gamepad) => void;
    }
    constructor(node: Camera){
        // Knoten der durch den Controller gesteuert werden soll (z.B. die Kamera)
        this.node = node;

        this.registerEvents();
    }

    registerEvents(){

        window.addEventListener("gamepadconnected", function(e:GamepadEvent) { gp.connecthandler(e.gamepad);});
        window.addEventListener("gamepaddisconnected", function(e:GamepadEvent) { gp.disconnecthandler(e.gamepad);});
        var gp = {
            connected: this.connected,
            controller: navigator.getGamepads()[0],
            connecthandler: function(gamepad:Gamepad) {
                console.log("Gamepad connected at index %d: %s. %d buttons, %d axes.",
                  gamepad.index, gamepad.id, gamepad.buttons.length, gamepad.axes.length);
                  gp.controller = navigator.getGamepads()[gamepad.index];
                  gp.connected  = true;
            },
            disconnecthandler: function(gamepad:Gamepad) {
                if(this.controller.index == gamepad.index){
                  console.log("Gamepad disconnected from index %d: %s", gamepad.index, gamepad.id);
                  gp.connected = false;
                  delete this.controller;
                }
            }
        };
        this.gp = gp;


    }

    isConnected() {
        return this.gp.connected;
    }

    buttonAction(buttonidx:number){
        // Beispielcode
        let camera = this.node.getCameraMatrix();

        if(buttonidx == 5){
            mat4.rotateZ(camera, camera, -0.1);
        }
        if(buttonidx == 4){
            mat4.rotateZ(camera, camera, 0.1);
        }
        /**
         Hier Code einfügen
        **/
    }

    axesAction(axes:ReadonlyArray<number>) {
        // Beispielcode zum auslesen der Werte von Stick 3
        let camera = this.node.getCameraMatrix();

        //axes.forEach(number =>{console.log(number)});
        mat4.translate(camera, camera, vec3.fromValues(Number(axes[0]*10), 0, Number(axes[1]*10)))          
        mat4.rotateY(camera, camera, Number(-axes[3]/10));
        mat4.rotateX(camera, camera, Number(-axes[4]/10));
        this.node.setCameraMatrix(camera);
    }

    // updateStatus() wird vor jedem Zeichnen der Szene aufgerufen
    updateStatus() {

        if(!this.isConnected())
            return;

        let controller = this.gp.controller;
        controller.buttons.forEach((button,index) => {
            let val = button;
            let pressed = false;
            let value = 0;
            if (typeof(val) == "object"){
                pressed = val.pressed;
                value = val.value;
            }

            if (pressed){
                this.buttonAction(index);
            }
        })


        for (let i = 0; i < controller.buttons.length; i++){
           
        }

        this.axesAction(controller.axes);
    }
}
