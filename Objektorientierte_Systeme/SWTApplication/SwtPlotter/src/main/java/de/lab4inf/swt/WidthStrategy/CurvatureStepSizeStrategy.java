package de.lab4inf.swt.WidthStrategy;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.function.Function;
import org.eclipse.swt.graphics.Point;

import de.lab4inf.swt.plotter.PlotterFunction;
import de.lab4inf.swt.plotter.SWTCanvasPlotter;
import de.lab4inf.swt.plotter.Trafo;

public class CurvatureStepSizeStrategy implements StepSizeStrategy {


    private static final double MIN_STEP_PX = .5;

	private static final int MAX_STEP_PX = 50;

	private static final double h = 5;

	@Override
	public int[] calculatePoints(SWTCanvasPlotter canvas, PlotterFunction fct) {
		Objects.requireNonNull(canvas);
		Objects.requireNonNull(fct);
		
		int sizeScreen = canvas.getMaxU();
		double sizeWorld = canvas.getIntervall()[1];
		Trafo transformer = new Trafo(canvas);

		double min_step = sizeWorld / sizeScreen * MIN_STEP_PX;
		double max_step = sizeWorld / sizeScreen * MAX_STEP_PX;

		Function<Double,Double> toCalc = fct.getFunction();
		
		List<Point> pointslist = new ArrayList<>();
		
		double current = canvas.getIntervall()[0];
		double step = min_step;
		
		int[] retVal = transformer.convertXY(current, toCalc.apply(current));
		Point point = new Point(retVal[0], retVal[1]);
		pointslist.add(point);
		while(current < sizeWorld) {
			while( step < max_step && Math.abs(fct.curvature(current, h) - fct.curvature(current + step, h * step)) < .05)
				step += min_step;

			current += step;
			step = min_step;
			double yValue = toCalc.apply(current);
			if(yValue > sizeWorld || yValue < -sizeWorld || Double.isNaN(yValue)) continue;
			retVal = transformer.convertXY(current, toCalc.apply(current));
			point = new Point(retVal[0], retVal[1]);
			pointslist.add(point);
		}
		int[] polygon = parseList(canvas, pointslist);
		return polygon;
	}
}
