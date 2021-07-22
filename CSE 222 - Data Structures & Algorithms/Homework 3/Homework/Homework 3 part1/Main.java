import java.util.ListIterator;

public class Main {
	public static void main(String[] args) {
		LinkedArrayList<Integer> test = new LinkedArrayList<Integer>();
		
		System.out.println("TASK:  Initializing the list");
		test.add(1);
		test.add(2);
		test.add(3);
		test.add(4);
		test.add(5);
		test.add(6);
		test.add(7);
		test.add(8);
		test.printDebugState();
		test.printNormalState();
		System.out.println();
		
		System.out.println("TASK:  Inserting an element to make first node exceed its capacity");
		test.add(9);
		test.printDebugState();
		test.printNormalState();
		System.out.println();
		
		System.out.println("TASK:  Inserting an element into given index (0)");
		test.add(0, 10);
		test.printDebugState();
		test.printNormalState();
		System.out.println();
		
		System.out.println("TASK:  Setting the value of the element in given index (0)");
		test.set(0, 0);
		test.printDebugState();
		test.printNormalState();
		System.out.println();
		
		System.out.println("TASK:  Removing the element in given index (0)");
		test.remove(0);
		test.printDebugState();
		test.printNormalState();
		System.out.println();
		
		System.out.println("TASK:  Inserting elements into given index (0)");
		test.add(0, 0);
		test.add(0, -1);
		test.add(0, -2);
		test.add(0, -3);
		test.add(0, -4);
		test.printDebugState();
		test.printNormalState();
		System.out.println();
		
		System.out.println("TASK:  Removing the element (" + test.get(5) + ") in given index (5)");
		test.remove(5);
		System.out.println("TASK:  Removing the element (" + test.get(5) + ") in given index (5)");
		test.remove(5);
		System.out.println("TASK:  Removing the element (" + test.get(5) + ") in given index (5)");
		test.remove(5);
		System.out.println("TASK:  Removing the element (" + test.get(5) + ") in given index (5)");
		test.remove(5);
		test.printDebugState();
		test.printNormalState();
		System.out.println();
		
		System.out.println("TASK:  Clearing the list");
		test.clear();
		test.printDebugState();
		test.printNormalState();
		System.out.println();
		
		System.out.println("TASK:  Initializing the list");
		test.add(0, 0);
		test.add(0, -1);
		test.add(0, -2);
		test.add(0, -3);
		test.add(0, -4);
		test.printDebugState();
		test.printNormalState();
		System.out.println();
		
		System.out.println("TASK:  Printing the list with an iterator");
		System.out.print("ITER:  [");
		ListIterator<Integer> iter = test.listIterator();
		while(iter.hasNext()) {
			System.out.print(iter.next());
			if(iter.hasNext())System.out.print(", ");
		}
		System.out.println("]");
		
		System.out.println("TASK:  Printing the list with a for loop");
		System.out.print("INDEX: [");
		for(int i = 0; i < test.size(); i++) {
			System.out.print(test.get(i));
			if(i + 1 < test.size())System.out.print(", ");
		}
		System.out.println("]");
		System.out.println();
	}

}
