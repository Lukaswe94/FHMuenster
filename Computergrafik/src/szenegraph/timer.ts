
export class Timer{
	private days_per_sec: number;
	private lastDate: number;
	constructor(days_per_sec: number){
		this.days_per_sec = days_per_sec;
		this.lastDate = Date.now();
		
	}
	daysPassed(){
		if(this.lastDate == 0){
			this.lastDate = Date.now();
			return 0;
		}
		let diff = this.days_per_sec*((Date.now()-this.lastDate)/1000);
		this.lastDate = Date.now();
		return diff;
	}
}



