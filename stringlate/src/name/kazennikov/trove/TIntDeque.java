/**
 * CalebSoft

 * @author Carlos E. A. Torres
 * @email catencio@episunsa.edu.pe

 * Copyright 2016.
 */
package name.kazennikov.trove;

import gnu.trove.list.TIntList;
import gnu.trove.list.array.TIntArrayList;

/**
 * @author carlos
 *
 */
public class TIntDeque {
	// private List<Integer> queue;
	private TIntList queue;

	/**
	 * @param i
	 */
	public TIntDeque() {
		// queue = new ArrayList<>();
		queue = new TIntArrayList();

	}

	/**
	 * @param i
	 */
	public TIntDeque(int sz) {
		// queue = new ArrayList<>(sz);
		queue = new TIntArrayList(sz);
	}

	/**
	 * @return
	 */
	public boolean isEmpty() {
		return queue.isEmpty();
	}

	/**
	 * @param ptr
	 */
	public void addLast(int ptr) {
		queue.add(ptr);
	}

	/**
	 * @return
	 */
	public int pollFirst() {
		return queue.get(0);
	}

	/**
	 * @return
	 */
	public int pop() {
		// return queue.remove(0);
		return queue.removeAt(0);
	}

	/**
	 * @param start
	 */
	public boolean add(int elem) {
		/*
		 * for (int x : queue) { if (x == elem) return false; }
		 */
		if (queue.indexOf(elem) != -1)
			return false;

		addLast(elem);
		return true;
	}

}
