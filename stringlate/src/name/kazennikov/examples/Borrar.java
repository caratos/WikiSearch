/**
 * CalebSoft

 * @author Carlos E. A. Torres
 * @email catencio@episunsa.edu.pe

 * Copyright 2016.
 */
package name.kazennikov.examples;

import java.util.Scanner;

/**
 * @author carlos
 *
 */
public class Borrar extends Thread {
	public static void main(String[] args) {
		Borrar borrar = new Borrar();
		borrar.start();

		Scanner sc = new Scanner(System.in);
		while (sc.hasNext()) {
			String next = sc.next();
			if (next.startsWith("q"))
				break;
		}
	}

	public void run() {
		try {
			sleep(1000);
			Borrar another = new Borrar();
			another.start();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("Hola hijo");
	}
}
