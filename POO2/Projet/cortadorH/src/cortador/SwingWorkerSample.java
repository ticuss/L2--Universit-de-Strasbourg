package cortador;

//Java program to illustrate  
//working of SwingWorker 
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.List;
import java.util.concurrent.ExecutionException;

import javax.swing.*;

public class SwingWorkerSample implements PropertyChangeListener {

	private static JLabel statusLabel;
	private static JFrame mainFrame;
	static SwingWorker<String, Integer> sw1;

	public void swingWorkerSample() {
		mainFrame = new JFrame("Swing Worker");
		mainFrame.setSize(400, 400);
		mainFrame.setLayout(new GridLayout(2, 1));

		mainFrame.addWindowListener(new WindowAdapter() {

			@Override
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}

		});

		statusLabel = new JLabel("Not Completed", JLabel.CENTER);
		mainFrame.add(statusLabel);

		JButton btn = new JButton("Start counter");
		btn.setPreferredSize(new Dimension(5, 5));

		btn.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				System.out.println("Button clicked, thread started");
				startThread();
			}

		});

		mainFrame.add(btn);
		// mainFrame.pack();
		mainFrame.setVisible(true);
	}

	private void startThread() {

		sw1 = new SwingWorker<String, Integer>() {

			@Override
			protected String doInBackground() throws Exception {
				// define what thread will do here
				for (int i = 10; i >= 0; i--) {
					Thread.sleep(100);
					System.out.println("Value in thread : " + i);
					publish(i);
					// publish("Hola: "+i);
				}

				String res = "Finished Execution";
				return res;
			}

			@Override
			protected void process(List chunks) {
				// define what the event dispatch thread
				// will do with the intermediate results received
				// while the thread is executing
				int val = (int) chunks.get(chunks.size() - 1);

				statusLabel.setText(String.valueOf(val));
			}

			@Override
			protected void done() {
				// this method is called when the background
				// thread finishes execution
				try {
					String statusMsg = (String) get();
					System.out.println("Inside done function");
					statusLabel.setText(statusMsg);

				} catch (InterruptedException e) {
					e.printStackTrace();
				} catch (ExecutionException e) {
					e.printStackTrace();
				}
			}
		};

		// executes the swingworker on worker thread
		sw1.addPropertyChangeListener(this);
		sw1.execute();
	}

	public static void main(String[] args) {
		SwingWorkerSample mySwingWorkerSample = new SwingWorkerSample();
		SwingUtilities.invokeLater(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				mySwingWorkerSample.swingWorkerSample();
			}

		});
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		// TODO Auto-generated method stub
		if (evt.getSource() == sw1) {
			System.out.println("Message arrived");
			System.out.println(sw1.getState());

		}
	}

	}
