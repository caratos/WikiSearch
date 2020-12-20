/**
 * CalebSoft

 * @author Carlos E. A. Torres
 * @email catencio@episunsa.edu.pe

 * Copyright 2016.
 */
package name.kazennikov.examples;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Semaphore;

/**
 * @author carlos
 *
 */
public class WikiReaderThread extends Thread {
	private Map<String, List<String>> bunch;
	private List<File> files;
	private int counter;
	private Semaphore semaphore;
	private boolean continueReading;
	public static final int BUNCH_SIZE = 10000;

	public WikiReaderThread(Map<String, List<String>> bunch, List<File> files, int counter, Semaphore semaphore) {
		this.bunch = bunch;
		this.files = files;
		this.counter = counter;
		this.semaphore = semaphore;

		continueReading = true;
	}

	public void run() {
		if (counter < files.size()) {
			for (int i = 0; i < BUNCH_SIZE && counter < files.size(); i++) {
				try {
					BufferedReader buf = new BufferedReader(new FileReader(files.get(counter)));

					String line = null;
					List<String> lines = new ArrayList<>();
					while ((line = buf.readLine()) != null) {
						lines.add(line);
					}
					bunch.put(files.get(counter).getName(), lines);
				} catch (IOException e) {
					e.printStackTrace();
				}
				counter++;
			}
		} else {
			continueReading = false;
		}
		semaphore.release();
	}

	public boolean canContinueReading() {
		return continueReading;
	}
}
