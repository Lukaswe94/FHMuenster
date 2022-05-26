module mxr.engine  {	
	exports de.lab4inf.mxr.engine;
	
	requires transitive mxr.core;

	uses de.lab4inf.mxr.core.MXR; 
	
	provides de.lab4inf.mxr.core.MXR 
		with de.lab4inf.mxr.engine.MXREngine; 		
}