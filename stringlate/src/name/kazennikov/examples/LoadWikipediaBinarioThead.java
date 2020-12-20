/**
 * CalebSoft

 * @author Carlos E. A. Torres
 * @email catencio@episunsa.edu.pe

 * Copyright 2016.
 */
package name.kazennikov.examples;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.Timestamp;
import java.time.Duration;
import java.time.Instant;
import java.util.List;
import java.util.Map;

import gnu.trove.list.array.TIntArrayList;
import name.kazennikov.dafsa.IntDAFSAInt;
import name.kazennikov.dafsa.TroveUtils;

/**
 * @author carlos
 *
 */
public class LoadWikipediaBinarioThead {
	public static String humanReadableFormat(Duration duration) {
		return duration.toString().substring(2).replaceAll("(\\d[HMS])(?!$)", "$1 ").toLowerCase();
	}

	public static void memoryStamp(FileWriter logFile) throws IOException {

		String command = "free";
		String arg = " ";
		ProcessBuilder builder = new ProcessBuilder(command);
		Process process = builder.start();

		BufferedReader br = new BufferedReader(new InputStreamReader(process.getInputStream()));
		String line;
		System.out.printf("Memory is:");
		logFile.write("Memory is:\n");

		while ((line = br.readLine()) != null) {
			System.out.println(line);
			logFile.write(line + "\n");
		}
		System.out.println("Fin");

	}

	public static void main(String[] args) throws IOException {
		Instant start = Instant.now();
		Timestamp timestamp = null;

		IntDAFSAInt fsa = new IntDAFSAInt();
		fsa.setFinalValue(1);

		TIntArrayList a = new TIntArrayList();

		String wikipediaPath = null;
		if (args.length > 0)
			wikipediaPath = args[0];
		else {
			wikipediaPath = "/home/carlos/Documentos/Cursos/DOCTORADO/EstructuraDatos/TrabajoFinal/Ascii";
			// wikipediaPath = "/disksdd/Doctorado/Wikipedia/Ascii";
		}

		File fromPath = new File(wikipediaPath);
		File logPath = new File("LoadWikipedia.log");
		File errorPath = new File("LoadWikipedia.error.log");

		FileWriter logFile = new FileWriter(logPath);

		timestamp = new Timestamp(System.currentTimeMillis());
		System.out.println("Starting: " + timestamp);
		logFile.write(timestamp.toString() + "\n");

		int count = 0;
		WikipediaReader reader = new WikipediaReader(fromPath);
		Map<String, List<String>> mapita;
		try {
			while ((mapita = reader.getNextBunch()) != null) {

				for (Map.Entry<String, List<String>> entry : mapita.entrySet()) {
					count++;
					if (count % 10000 == 0) {
						System.out.println("Procesando: " + count + " files");
						timestamp = new Timestamp(System.currentTimeMillis());
						System.out.println(timestamp);
						logFile.write(timestamp.toString() + "\n");
					}
					// if (count == 500000) // -> 500000 FILES
					// break;

					for (String line : entry.getValue()) {
						char[] lineChar = line.toCharArray();
						for (int i = 0; i < line.length(); i++) {
							if (Character.isLetter(lineChar[i])) {
								if (Character.isUpperCase(lineChar[i])) {
									lineChar[i] = Character.toLowerCase(lineChar[i]);
								}
							} else {
								lineChar[i] = ' ';
							}
						}
						line = new String(lineChar);
						String words[] = line.split("\\s+");
						for (int i = 1; i < words.length; i++) {
							String word = words[i - 1] + ' ' + words[i];

							// So it is going to store just the first appearance
							TroveUtils.expand(a, word + "/" + entry.getKey());
							fsa.addMinWord(a);
						}
					}
				}
			}
		} catch (OutOfMemoryError mem) {
			FileWriter errorFile = new FileWriter(errorPath);

			errorFile.write("ERROR OUT OF MEMORY\n");
			System.err.println("ERROR OUT OF MEMORY");
			errorFile.write("It processed: " + count + " files");

			memoryStamp(errorFile);
			errorFile.close();
		} catch (InterruptedException ioex) {
			System.err.println("INTERRUPTED EXCEPTION");
			ioex.printStackTrace();
		}

		try {
			fsa.toDot("wikipedia-binario.dot");
		} catch (IOException e) {
			System.err.println("ERROR WRITING wikipedia.dot");
			e.printStackTrace();
		} catch (OutOfMemoryError mem) {
			System.err.println("ERROR OUT OF MEMORY AT THE MOMENT OF GENERATING .dot");
		}
		System.out.println("DONE");
		Instant end = Instant.now();
		Duration timeElapsed = Duration.between(start, end);
		System.out.println("TOTAL TIME:" +

				humanReadableFormat(timeElapsed) + "\n");
		logFile.write("TOTAL TIME:" + humanReadableFormat(timeElapsed) + "\n");

		memoryStamp(logFile);
		logFile.flush();
		logFile.close();
	}
}
