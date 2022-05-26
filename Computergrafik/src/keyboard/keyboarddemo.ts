import { WebGLStart } from "../triangle/webglstart";

export class KeyBoardDemo {
    

    registerEvents() {
        document.addEventListener('keydown', function (event) { Key.keyControl(event); });

        let Key = {
            keyboardDemo: this,
            keyControl: function (event: KeyboardEvent) {
                this.keyboardDemo.rotate(event.key);
            }
        }

    }
    
/*
    rotate(code: String) {
        let webglstart = WebGLStart.getInstance();
        if (code == 'ArrowDown'){
            webglstart.rotateX(-0.1);
        }
        else if (code == 'ArrowRight'){
            webglstart.rotateY(0.1);
        }
        else if ( code == 'ArrowLeft'){
            webglstart.rotateY(-0.1);
        }
        else if(code == 'ArrowUp'){
            webglstart.rotateX(0.1);
        }
        else
            console.log('KeyCode: ' + code);
    }
*/
}