
export class Framerate{
    
    static ftime: number;
    static last_frame_time: number;
    private static instance: Framerate;
    private constructor(){
        Framerate.last_frame_time = 0;
        Framerate.start(0);
    }
    public static getInstance(){
        if(!Framerate.instance){
            Framerate.instance = new Framerate();
        }
        return Framerate.instance;
    }
    private static start(time: number){
        Framerate.ftime = (time - Framerate.last_frame_time)/1000;
        Framerate.last_frame_time = time;
        window.requestAnimationFrame(Framerate.start);
    }
}