import javax.swing.*;
import java.awt.*;

public class sample extends JFrame implements sampleFieldEdit {
	private JTextField name;
	private JTextField asshole;
	private JTextField potato;
	private JTextArea statusArea;

	public sample () {
		super("SomeDamnExample");
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setLayout(new BorderLayout());
		setSize(350,600);
		init();
		pack();
		}

	private void init() {
		JPanel topPanel = new JPanel(new BorderLayout());
		
		JPanel fieldPanel = new JPanel();
		GroupLayout fieldLayout = new GroupLayout(fieldPanel);
		fieldPanel.setLayout(fieldLayout);
		fieldLayout.setAutoCreateGaps(true);
		fieldLayout.setAutoCreateContainerGaps(true);

		name= new JTextField(15);
		JLabel labelname = new JLabel("name");
		asshole= new JTextField(15);
		JLabel labelasshole = new JLabel("asshole");
		potato= new JTextField(15);
		JLabel labelpotato = new JLabel("potato");

		fieldLayout.setHorizontalGroup(
			fieldLayout.createSequentialGroup()
			.addGroup(fieldLayout.createParallelGroup()
				.addComponent(labelname)
				.addComponent(labelasshole)
				.addComponent(labelpotato)
			)
			.addGroup(fieldLayout.createParallelGroup()
				.addComponent(name)
				.addComponent(asshole)
				.addComponent(potato)
			)
		);
		fieldLayout.setVerticalGroup(
			fieldLayout.createSequentialGroup()
			.addGroup(fieldLayout.createParallelGroup()
				.addComponent(labelname)
				.addComponent(name))
			.addGroup(fieldLayout.createParallelGroup()
				.addComponent(labelasshole)
				.addComponent(asshole))
			.addGroup(fieldLayout.createParallelGroup()
				.addComponent(labelpotato)
				.addComponent(potato))
		);

		topPanel.add(fieldPanel, BorderLayout.CENTER);
		JPanel buttonPanel = new JPanel(new FlowLayout());

		JButton buttonclicky = new JButton("clicky");
		buttonclicky.addActionListener(new null(this) );
		buttonPanel.add(buttonclicky);
		JButton buttonflicky = new JButton("flicky");
		buttonflicky.addActionListener(new null(this) );
		buttonPanel.add(buttonflicky);

		topPanel.add(buttonPanel, BorderLayout.SOUTH);
		this.add(topPanel, BorderLayout.NORTH);

		JPanel botPanel = new JPanel(new BorderLayout());
		JPanel statusPanel = new JPanel();
		JLabel statusLabel = new JLabel("STATUS");
		statusPanel.add(statusLabel);
		botPanel.add(statusPanel, BorderLayout.NORTH);

		JPanel boxPanel = new JPanel(new GridLayout(1,1));
		statusArea = new JTextArea();
		statusArea.setRows(12);
		JScrollPane scroll = new JScrollPane(statusArea);
		scroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		scroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		boxPanel.add(scroll);
		botPanel.add(boxPanel, BorderLayout.CENTER);

		this.add(botPanel,BorderLayout.CENTER);

	}

		public void appendToStatusArea(String str) {
		statusArea.append(str);
	}

	public String getDCname() {
		return name.getText();
	}

	public void setDCname(String str) {
		name.setText(str);
	}

	public String getDCasshole() {
		return asshole.getText();
	}

	public void setDCasshole(String str) {
		asshole.setText(str);
	}

	public String getDCpotato() {
		return potato.getText();
	}

	public void setDCpotato(String str) {
		potato.setText(str);
	}

	public static void main(String args[]) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				sample myGui = new sample();
				myGui.setVisible(true);
			}
		});
	}
}


