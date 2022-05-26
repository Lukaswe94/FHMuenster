package de.lab4inf.swt.WidthStrategy;


import java.util.List;

import org.eclipse.swt.graphics.Point;

import de.lab4inf.swt.plotter.PlotterFunction;
import de.lab4inf.swt.plotter.SWTCanvasPlotter;

public interface StepSizeStrategy {
	public default int[] parseList(SWTCanvasPlotter canvas, List<Point> list) {
		int max_y = canvas.getMaxV();
		int min_y = -max_y;
		
		list.removeIf(x -> x.y > max_y || x.y < min_y);
		
		int[] polygon = new int[list.size()*2];
		
		for (int i = 0, j = 0; i < list.size()*2; i+=2, j++) {
			polygon[i] = list.get(j).x;
			polygon[i+1] = list.get(j).y;
		}
		return polygon;
	}
	public int[] calculatePoints(SWTCanvasPlotter canvas, PlotterFunction fct);
}
