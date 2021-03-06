package de.fu.profiler.view;

import java.awt.Color;
import java.awt.GridLayout;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Observable;
import java.util.Observer;
import java.util.concurrent.ConcurrentSkipListMap;

import javax.swing.JFrame;
import javax.swing.JTabbedPane;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import de.fu.profiler.model.JVM;
import de.fu.profiler.model.ProfilerModel;

/**
 * The graphical user interface of the profiler. Further elements of the
 * graphical user interface are initialized during the constructor of this
 * {@link JFrame}.
 * 
 * @author Konrad Johannes Reiche
 * 
 */
public class ProfilerView extends JFrame implements Observer {

	/**
	 * generated serial version ID
	 */
	private static final long serialVersionUID = -6276797391162392835L;

	private static final int WIDTH = 1400;

	private static final int HEIGHT = 800;

	// BOGUS
	List<JVM> jvms = new ArrayList<JVM>();

	/**
	 * The profiler model
	 */
	ProfilerModel model;

	JTabbedPane mainSelection;

	final Map<JVM, MonitorLogView> monitorLogViews;
	final Map<JVM, ResourceAllocationGraphView> resourceAllocationGraphs;
	final Map<JVM, JTabbedPane> tabbedPanes;

	public ProfilerView(ProfilerModel model) {

		this.model = model;
		monitorLogViews = new ConcurrentSkipListMap<JVM, MonitorLogView>();
		resourceAllocationGraphs = new ConcurrentSkipListMap<JVM, ResourceAllocationGraphView>();
		tabbedPanes = new ConcurrentSkipListMap<JVM, JTabbedPane>();
		model.addObserver(this);
		setUpLookAndFeel();

		setTitle("Java Concurrency Profiler");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new GridLayout(1, 2));

		mainSelection = new JTabbedPane(JTabbedPane.LEFT);
		mainSelection.add("Welcome", new WelcomePanel());
		this.add(mainSelection);
		this.setSize(WIDTH, HEIGHT);
	}

	private void createView(JVM jvm) {
		GeneralView generalView = new GeneralView(model, jvm);
		MonitorLogView monitorLogPanel = new MonitorLogView(model, jvm);
		MonitorView locks = new MonitorView(model, jvm);
		ResourceAllocationGraphView resourceAllocationGraph = new ResourceAllocationGraphView(
				model, jvm);
		MethodProfilingView methodProfilingView = new MethodProfilingView(
				model, jvm);

		monitorLogViews.put(jvm, monitorLogPanel);
		resourceAllocationGraphs.put(jvm, resourceAllocationGraph);

		JTabbedPane tabbedPane = new JTabbedPane();
		tabbedPane.add("General", generalView);
		tabbedPane.add("Monitor Log", monitorLogPanel);
		tabbedPane.add("Monitor", locks);
		tabbedPane.add("Resource-Allocation Graph", resourceAllocationGraph);
		tabbedPane.add("Method Profiling", methodProfilingView);
		tabbedPanes.put(jvm, tabbedPane);

		mainSelection.add(jvm.getHost() + " (PID " + jvm.getPid() + ")",
				tabbedPane);
		mainSelection.setSelectedComponent(tabbedPane);

		jvm.addObserver(monitorLogPanel);
		jvm.addObserver(this);
	}

	private void setUpLookAndFeel() {
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (InstantiationException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (UnsupportedLookAndFeelException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void update(Observable o, Object arg) {

		// TODO: different Observable for adding jvm and chaning its state
		if (arg != null && o instanceof ProfilerModel && !jvms.contains(arg)) {
			JVM jvm = (JVM) arg;
			jvms.add(jvm);
			createView(jvm);
		} else if (arg instanceof JVM) {
			JVM jvm = (JVM) arg;
			JTabbedPane pane = tabbedPanes.get(jvm);
			if (jvm.isDeadlocked()) {
				pane.setForegroundAt(3, Color.RED);
				pane.setTitleAt(3, "Deadlocked");
			} else if (pane.getTitleAt(3).equals("Deadlocked")
					&& !jvm.isDeadlocked()) {
				pane.setForegroundAt(3, Color.BLACK);
				pane.setTitleAt(3, "Resource-Allocation Graph");
			}
		}
	}
}
