/**
 * CalebSoft

 * @author Carlos E. A. Torres
 * @email catencio@episunsa.edu.pe

 * Copyright 2016.
 */
package name.kazennikov.examples;

import java.io.IOException;

import gnu.trove.list.array.TIntArrayList;
import name.kazennikov.dafsa.IntDAFSAInt;
import name.kazennikov.dafsa.TroveUtils;

/**
 * @author carlos
 *
 */
public class ExampleMinimization {

	public static void main(String[] args) throws IOException {
		IntDAFSAInt fsa = new IntDAFSAInt();
		fsa.setFinalValue(1);

		// String words[] = new String[] { "casa", "cama", "cerrojo", "diurno", "bola",
		// "maria", "carlos" };
		String words[] = new String[] { "casa/001.txt", "casa/002.txt", "orbe/003.txt" };

		TIntArrayList a = new TIntArrayList();

		for (String word : words) {
			TroveUtils.expand(a, word);
			fsa.addMinWord(a);
		}

		fsa.toDot("mini.dot");
	}
}
