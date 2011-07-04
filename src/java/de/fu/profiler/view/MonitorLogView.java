package de.fu.profiler.view;

import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ItemListener;

import javax.swing.BorderFactory;
import javax.swing.JCheckBox;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTree;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionListener;

import de.fu.profiler.controller.MonitorLogTableListener;
import de.fu.profiler.model.JVM;
import de.fu.profiler.model.ProfilerModel;
import de.fu.profiler.model.ThreadStatsTableModel;

/**
 * This panel shows information about the notify and wait methods used by the
 * profiled JVM.
 * 
 * @author Konrad Johannes Reiche
 * 
 */
public class MonitorLogView extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1308837298229481853L;

	JTree stackTraces;

	public MonitorLogView(ProfilerModel model, JVM jvm) {

		super(new GridLayout(2, 1));
		JTable monitorLogTable = new JTable(model.getMonitorLogTables()
				.get(jvm));

		JScrollPane tableScrollPane = new JScrollPane(monitorLogTable);
		JPanel optionPanel = new JPanel(new GridLayout(2, 1));

		JCheckBox cbContendedEnter = new JCheckBox("Enter Locked Monitor", true);
		JCheckBox cbContendedEntered = new JCheckBox("Entered Locked Monitor",
				true);
		JCheckBox cbWaiting = new JCheckBox("Waiting", true);
		JCheckBox cbSignaling = new JCheckBox("Signaling", true);

		JPanel showEvent = new JPanel(new GridLayout(4, 1));
		showEvent.setBorder(BorderFactory.createTitledBorder("Show Events"));
		showEvent.add(cbContendedEnter);
		showEvent.add(cbContendedEntered);
		showEvent.add(cbWaiting);
		showEvent.add(cbSignaling);

		
		JPanel showThread = new JPanel(new GridLayout());
		showThread.setBorder(BorderFactory.createTitledBorder("Show Threads"));

		optionPanel.add(showEvent);
		optionPanel.add(showThread);

		optionPanel.setPreferredSize(new Dimension(100, 300));
		tableScrollPane.setPreferredSize(new Dimension(1000, 300));

		JSplitPane monitorLogTablePanel = new JSplitPane(
				JSplitPane.HORIZONTAL_SPLIT, tableScrollPane, optionPanel);

		stackTraces = new JTree(model.getNotifyWaitStackTracesTrees().get(jvm)
				.getRoot());
		stackTraces.setExpandsSelectedPaths(true);

		ListSelectionListener listener = new MonitorLogTableListener(
				monitorLogTable, model, jvm, stackTraces, cbContendedEnter,
				cbContendedEntered, cbWaiting, cbSignaling);

		ItemListener itemListener = (ItemListener) listener;
		cbContendedEnter.addItemListener(itemListener);
		cbContendedEntered.addItemListener(itemListener);
		cbWaiting.addItemListener(itemListener);
		cbSignaling.addItemListener(itemListener);
		
		monitorLogTable.getSelectionModel().addListSelectionListener(listener);

		ThreadStatsTableModel tableModel = model.getThreadStatsTableModels()
				.get(jvm);
		JTable threadStatsTable = new JTable(tableModel);

		JTabbedPane tabbedNotifyWaitPane = new JTabbedPane();
		tabbedNotifyWaitPane.add("Stack Traces", new JScrollPane(stackTraces));
		tabbedNotifyWaitPane
				.add("Statistic", new JScrollPane(threadStatsTable));

		monitorLogTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		monitorLogTable.setRowSelectionAllowed(true);
		super.add(monitorLogTablePanel);
		super.add(tabbedNotifyWaitPane);

	}
}
