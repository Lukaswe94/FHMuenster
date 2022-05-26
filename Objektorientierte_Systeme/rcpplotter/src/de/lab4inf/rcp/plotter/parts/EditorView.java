package de.lab4inf.rcp.plotter.parts;



import javax.annotation.PostConstruct;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Group;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Text;
import org.eclipse.ui.part.ViewPart;

public class EditorView extends ViewPart {
	private Group parentGroup;
	private Text functionText;
	private Button addButton;
	private Button removeButton;
	private Button clearButton;
	private ModelProvider provider;
	@PostConstruct
	@Override
	public void createPartControl(Composite parent) {
		provider = ModelProvider.getInstance();
		Group editMySet = new Group(parent, SWT.BORDER);
		editMySet.setLayout(new GridLayout(1, false));
		GridData gd = new GridData(SWT.FILL, SWT.FILL, false, true);
		editMySet.setLayoutData(gd);

		Group coorSystem = new Group(editMySet, SWT.BORDER);
		coorSystem.setLayout(new GridLayout(4, false));
		gd = new GridData(SWT.FILL, SWT.FILL, true, false);
		coorSystem.setLayoutData(gd);

		Label xMinLabel = new Label(coorSystem, SWT.NONE);
		xMinLabel.setText("Xmin ");
		gd = new GridData(SWT.LEFT, SWT.CENTER, false, false);
		xMinLabel.setLayoutData(gd);

		Text myXminText = new Text(coorSystem, SWT.BORDER);
		gd = new GridData(SWT.FILL, SWT.FILL, true, false);
		//myXminText.setText(String.valueOf(canvas.getIntervall()[0]));
		myXminText.setLayoutData(gd);

		Label xMaxLabel = new Label(coorSystem, SWT.NONE);
		xMaxLabel.setText("Xmax ");
		gd = new GridData(SWT.LEFT, SWT.CENTER, false, false);
		xMaxLabel.setLayoutData(gd);

		Text myXmaxText = new Text(coorSystem, SWT.BORDER);
		gd = new GridData(SWT.FILL, SWT.FILL, true, false);
		//myXmaxText.setText(String.valueOf(canvas.getIntervall()[1]));
		myXmaxText.setLayoutData(gd);

		Label yMinLabel = new Label(coorSystem, SWT.NONE);
		yMinLabel.setText("Ymin ");
		gd = new GridData(SWT.LEFT, SWT.CENTER, false, false);
		yMinLabel.setLayoutData(gd);

		Text myYminText = new Text(coorSystem, SWT.BORDER);
		gd = new GridData(SWT.FILL, SWT.FILL, true, false);
		myYminText.setLayoutData(gd);

		Label yMaxLabel = new Label(coorSystem, SWT.NONE);
		yMaxLabel.setText("Ymax ");
		gd = new GridData(SWT.LEFT, SWT.CENTER, false, false);
		yMaxLabel.setLayoutData(gd);

		Text myYmaxText = new Text(coorSystem, SWT.BORDER);
		gd = new GridData(SWT.FILL, SWT.FILL, true, false);
		myYmaxText.setLayoutData(gd);

		Button updateButton = new Button(coorSystem, SWT.PUSH);
		gd = new GridData(SWT.FILL, SWT.FILL, true, false);
		gd.horizontalSpan = 6;
		updateButton.setLayoutData(gd);
		updateButton.setText("Update");
		Group addRemoveClean = new Group(editMySet, SWT.BEGINNING);
		addRemoveClean.setLayout(new GridLayout(6, true));
		gd = new GridData(SWT.FILL, SWT.FILL, true, false);
		addRemoveClean.setLayoutData(gd);

		functionText = new Text(addRemoveClean, SWT.BORDER);
		gd = new GridData(SWT.FILL, SWT.FILL, true, false);
		gd.horizontalSpan = 6;
		functionText.setLayoutData(gd);

		gd = new GridData(SWT.FILL, SWT.FILL, true, false);
		gd.horizontalSpan = 2;

		addButton = new Button(addRemoveClean, SWT.PUSH);
		addButton.setLayoutData(gd);
		addButton.setText("Add");
		
		removeButton = new Button(addRemoveClean, SWT.PUSH);
		removeButton.setLayoutData(gd);
		removeButton.setText("Remove");

		clearButton = new Button(addRemoveClean, SWT.PUSH);
		clearButton.setLayoutData(gd);
		clearButton.setText("Clear");
		
		parentGroup = editMySet;
	}
	public void addListeners() {
		addButton.addListener(SWT.Selection, new Listener() {
			@Override
			public void handleEvent(Event event) {
				if (event.type == SWT.Selection) {
					
				}
			}
		});

		
	}
	@Override
	public void setFocus() {
		parentGroup.setFocus();

	}

}
