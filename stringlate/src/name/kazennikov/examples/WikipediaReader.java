/**
 * CalebSoft

 * @author Carlos E. A. Torres
 * @email catencio@episunsa.edu.pe

 * Copyright 2016.
 */
package name.kazennikov.examples;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Semaphore;

/**
 * This class is going to read wikipedia by bunch using multithreading
 * 
 * @author carlos
 *
 */
public class WikipediaReader {
	private Semaphore semaphore;
	private WikiReaderThread thread;
	private Map<String, List<String>> bunch;
	private List<File> files;
	private int counter;

	public WikipediaReader(File directory) {
		semaphore = new Semaphore(0);

		bunch = new HashMap<>();

		files = new ArrayList<>();
		for (File entry : directory.listFiles()) {
			if (!entry.isDirectory()) {
				files.add(entry);
			}
		}

		counter = 0;

		// Initial launch
		thread = new WikiReaderThread(bunch, files, counter, semaphore);
		thread.start();

	}

	public Map<String, List<String>> getNextBunch() throws InterruptedException {
		semaphore.acquire();
		if (!thread.canContinueReading()) {
			return null;
		}

		Map<String, List<String>> previous = bunch; // saving reference
		counter += WikiReaderThread.BUNCH_SIZE;

		bunch = new HashMap<>(); // new reference

		thread = new WikiReaderThread(bunch, files, counter, semaphore);
		thread.start();

		return previous;
	}
}
