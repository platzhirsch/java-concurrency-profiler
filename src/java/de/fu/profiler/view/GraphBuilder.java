package de.fu.profiler.view;

import java.awt.Color;
import java.awt.Component;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.TreeMap;

import com.mxgraph.swing.mxGraphComponent;
import com.mxgraph.util.mxConstants;
import com.mxgraph.view.mxGraph;
import com.mxgraph.view.mxStylesheet;

import de.fu.profiler.model.JVM;
import de.fu.profiler.model.Monitor;
import de.fu.profiler.model.NotifyWaitLogEntry;
import de.fu.profiler.model.ThreadInfo;

/**
 * Manages the building of different graphs used in the profiler.
 * <p>
 * Currently builds graphs for the notify/wait view.
 * 
 * @author Konrad Johannes Reiche
 * 
 */
public class GraphBuilder {

	final static String COLOR_STATE_NEW = "#FF5555";
	final static String COLOR_STATE_TERMINATED = "#5555FF";
	final static String COLOR_STATE_RUNNABLE = "#55FF55";
	final static String COLOR_STATE_BLOCKED = "#FFFF55";
	final static String COLOR_STATE_WAITING = "#FF55FF";
	final static String COLOR_STATE_TIMED_WAITING = "#55FFFFF";

	final static int THREAD_VERTEX_WIDTH = 30;
	final static int THREAD_VERTEX_HEIGHT = 30;
	final static int STATE_VERTEX_WIDTH = 80;
	final static int STATE_VERTEX_HEIGHT = 30;

	mxGraph notifyWaitGraph;
	mxGraph waitForGraph;

	public GraphBuilder() {
		this.notifyWaitGraph = new mxGraph();
		this.waitForGraph = new mxGraph();
		initializeStylesheets();
	}

	public Component getNotifyWaitGraph() {
		mxGraphComponent component = new mxGraphComponent(notifyWaitGraph);
		component.getViewport().setOpaque(true);
		component.getViewport().setBackground(Color.WHITE);
		component.setEnabled(false);
		return component;
	}

	public Component getWaitForGraph() {
		mxGraphComponent component = new mxGraphComponent(waitForGraph);
		component.getViewport().setOpaque(true);
		component.getViewport().setBackground(Color.WHITE);
		component.setEnabled(false);
		return component;
	}

	public void createWaitForGraph(JVM jvm) {

		Object parent = waitForGraph.getDefaultParent();
		waitForGraph.removeCells(waitForGraph.getChildVertices(parent));
		waitForGraph.getModel().beginUpdate();

		Map<Integer, Object> threadNodes = new TreeMap<Integer, Object>();
		Map<Long, Object> monitorNodes = new TreeMap<Long, Object>();

		int counter = 0;
		for (ThreadInfo thread : jvm.getThreads()) {

			if (counter % 2 == 0) {
				Object threadNode = waitForGraph.insertVertex(parent, null, "T"
						+ thread.getId(), 30, 30 + (counter * 50),
						THREAD_VERTEX_WIDTH, THREAD_VERTEX_HEIGHT, "THREAD");
				threadNodes.put(thread.getId(), threadNode);
			} else {
				Object threadNode = waitForGraph.insertVertex(parent, null, "T"
						+ thread.getId(), 150, 30 + (counter * 50),
						THREAD_VERTEX_WIDTH, THREAD_VERTEX_HEIGHT, "THREAD");
				threadNodes.put(thread.getId(), threadNode);
			}
			++counter;
		}

		counter = 0;
		for (Entry<Long, Monitor> entry : jvm.getMonitors().entrySet()) {

			Object monitorNode = waitForGraph.insertVertex(parent, null, "R"
					+ entry.getKey(), 90, 50 + (counter * 50),
					THREAD_VERTEX_WIDTH, THREAD_VERTEX_HEIGHT, "MONITOR");
			monitorNodes.put(entry.getKey(), monitorNode);
			++counter;
		}

		for (ThreadInfo thread : jvm.getThreads()) {

			Monitor monitor = thread.getRequestedResource();
			if (monitor != null) {
				waitForGraph.insertEdge(parent, null, null,
						threadNodes.get(thread.getId()),
						monitorNodes.get(monitor.getId()));
			}
		}

		for (Entry<Long, Monitor> entry : jvm.getMonitors().entrySet()) {

			ThreadInfo threadInfo = entry.getValue().getAllocatedToThread();
			if (threadInfo != null) {
				waitForGraph.insertEdge(parent, null, null,
						monitorNodes.get(entry.getKey()),
						threadNodes.get(threadInfo.getId()));
			}
		}

		waitForGraph.getModel().endUpdate();
	}

	public void createNotifyWaitGraph(JVM jvm) {

		Object parent = notifyWaitGraph.getDefaultParent();
		notifyWaitGraph.removeCells(notifyWaitGraph.getChildVertices(parent));
		notifyWaitGraph.getModel().beginUpdate();

		try {
			int index = 0;
			List<ThreadInfo> threads = initializeThreadList(jvm.getThreads());
			Map<ThreadInfo, Object> threadToLastNode = new TreeMap<ThreadInfo, Object>();
			Object initialState = null;
			for (ThreadInfo threadInfo : threads) {

				index = threads.indexOf(threadInfo);
				Object root = notifyWaitGraph.insertVertex(parent, null,
						threadInfo.getName(), 30 + (150 * index), 20,
						THREAD_VERTEX_WIDTH, THREAD_VERTEX_HEIGHT,
						"THREAD_START_STATE");

				initialState = notifyWaitGraph.insertVertex(parent, null,
						"RUNNABLE", 20 + (150 * index), 150,
						STATE_VERTEX_WIDTH, STATE_VERTEX_HEIGHT,
						"RUNNABLE_STATE");

				threadToLastNode.put(threadInfo, initialState);

				notifyWaitGraph.insertEdge(parent, null, null, root,
						initialState);
			}

			int j = 1;
			for (NotifyWaitLogEntry entry : jvm.getNotifyWaitLog().values()) {

				Object previousState = threadToLastNode.get(entry
						.getThreadInfo());
				Object nextState = null;
				String edgeLabel = null;

				switch (entry.getType()) {
				case INVOKED_WAIT:
					edgeLabel = "wait()";
					break;
				case LEFT_WAIT:
					edgeLabel = "exit wait()";
					break;
				case INVOKED_NOTIFY_ALL:
					edgeLabel = "notifyAll()";
					break;
				case INVOKED_NOTIFY:
					edgeLabel = "notify()";
					break;
				}

				edgeLabel += "\n";
				edgeLabel += entry.getMonitorClass() + "."
						+ entry.getMethodContext();

				index = threads.indexOf(entry.getThreadInfo());

				nextState = notifyWaitGraph.insertVertex(parent, null,
						entry.getState(), 20 + (150 * index), 150 + (j * 100),
						STATE_VERTEX_WIDTH, STATE_VERTEX_HEIGHT,
						entry.getState() + "_STATE");

				notifyWaitGraph.insertEdge(parent, null, edgeLabel,
						previousState, nextState, "EDGE");

				threadToLastNode.put(entry.getThreadInfo(), nextState);
				++j;
			}
		} finally {
			notifyWaitGraph.getModel().endUpdate();
		}
	}

	public List<ThreadInfo> initializeThreadList(Set<ThreadInfo> threads) {

		ArrayList<ThreadInfo> result = new ArrayList<ThreadInfo>();
		for (ThreadInfo threadInfo : threads) {

			String threadName = threadInfo.getName();

			if (!(threadName.equals("Signal Dispatcher")
					|| threadName.equals("main")
					|| threadName.equals("Finalizer")
					|| threadName.equals("Reference Handler") || threadName
					.equals("DestroyJavaVM"))) {

				result.add(threadInfo);
			}
		}

		return result;
	}

	private void initializeStylesheets() {

		mxStylesheet stylesheetNotifyWait = notifyWaitGraph.getStylesheet();
		mxStylesheet stylesheetWaitFor = waitForGraph.getStylesheet();

		Hashtable<String, Object> style1 = new Hashtable<String, Object>();
		style1.put(mxConstants.STYLE_SHAPE, mxConstants.SHAPE_DOUBLE_ELLIPSE);
		style1.put(mxConstants.STYLE_FILLCOLOR, COLOR_STATE_RUNNABLE);
		style1.put(mxConstants.STYLE_STROKECOLOR, "#55AA55");
		style1.put(mxConstants.STYLE_FONTCOLOR, "#000000");
		stylesheetNotifyWait.putCellStyle("THREAD_START_STATE", style1);

		Hashtable<String, Object> style2 = new Hashtable<String, Object>();
		style2.put(mxConstants.STYLE_ROUNDED, true);
		style2.put(mxConstants.STYLE_FONTCOLOR, "#000000");
		style2.put(mxConstants.STYLE_FILLCOLOR, COLOR_STATE_RUNNABLE);
		style2.put(mxConstants.STYLE_STROKECOLOR, "#55AA55");
		stylesheetNotifyWait.putCellStyle("RUNNABLE_STATE", style2);

		Hashtable<String, Object> style3 = new Hashtable<String, Object>();
		style3.put(mxConstants.STYLE_ROUNDED, true);
		style3.put(mxConstants.STYLE_FONTCOLOR, "#000000");
		style3.put(mxConstants.STYLE_FILLCOLOR, COLOR_STATE_NEW);
		style3.put(mxConstants.STYLE_STROKECOLOR, "#AA5555");
		stylesheetNotifyWait.putCellStyle("NEW_STATE", style3);

		Hashtable<String, Object> style4 = new Hashtable<String, Object>();
		style4.put(mxConstants.STYLE_ROUNDED, true);
		style4.put(mxConstants.STYLE_FONTCOLOR, "#000000");
		style4.put(mxConstants.STYLE_FILLCOLOR, COLOR_STATE_BLOCKED);
		style4.put(mxConstants.STYLE_STROKECOLOR, "#AAAA55");
		stylesheetNotifyWait.putCellStyle("BLOCKED_STATE", style4);

		Hashtable<String, Object> style5 = new Hashtable<String, Object>();
		style5.put(mxConstants.STYLE_ROUNDED, true);
		style5.put(mxConstants.STYLE_FONTCOLOR, "#000000");
		style5.put(mxConstants.STYLE_FILLCOLOR, COLOR_STATE_WAITING);
		style5.put(mxConstants.STYLE_STROKECOLOR, "#AA55AA");
		stylesheetNotifyWait.putCellStyle("WAITING_STATE", style5);

		Hashtable<String, Object> style6 = new Hashtable<String, Object>();
		style6.put(mxConstants.STYLE_ROUNDED, true);
		style6.put(mxConstants.STYLE_FONTCOLOR, "#000000");
		style6.put(mxConstants.STYLE_FILLCOLOR, COLOR_STATE_TIMED_WAITING);
		style6.put(mxConstants.STYLE_STROKECOLOR, "#AAAA55");
		stylesheetNotifyWait.putCellStyle("BLOCKED_STATE", style6);

		Hashtable<String, Object> style7 = new Hashtable<String, Object>();
		style7.put(mxConstants.STYLE_ROUNDED, true);
		style7.put(mxConstants.STYLE_FONTCOLOR, "#000000");
		style7.put(mxConstants.STYLE_FILLCOLOR, COLOR_STATE_TERMINATED);
		style7.put(mxConstants.STYLE_STROKECOLOR, "#5555AA");
		stylesheetNotifyWait.putCellStyle("TERMINATED", style7);

		Hashtable<String, Object> style8 = new Hashtable<String, Object>();
		style8.put(mxConstants.STYLE_LABEL_BACKGROUNDCOLOR, "#FFFFFF");
		stylesheetNotifyWait.putCellStyle("EDGE", style8);

		Hashtable<String, Object> style9 = new Hashtable<String, Object>();
		style9.put(mxConstants.STYLE_SHAPE, mxConstants.SHAPE_ELLIPSE);
		style9.put(mxConstants.STYLE_FONTCOLOR, "#000000");
		style9.put(mxConstants.STYLE_FILLCOLOR, "#CCCCFF");
		style9.put(mxConstants.STYLE_STROKECOLOR, "#7F7FFF");
		stylesheetWaitFor.putCellStyle("THREAD", style9);

		Hashtable<String, Object> style10 = new Hashtable<String, Object>();
		style10.put(mxConstants.STYLE_FONTCOLOR, "#000000");
		style10.put(mxConstants.STYLE_FILLCOLOR, "#CDCDCD");
		style10.put(mxConstants.STYLE_STROKECOLOR, "#808180");
		stylesheetWaitFor.putCellStyle("MONITOR", style10);
	}

}
