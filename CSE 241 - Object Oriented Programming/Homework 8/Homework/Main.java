public class Main {
	private static<T> void print(GTUContainer<T> container) {
		GTUIterator<T> iter = container.iterator();
		System.out.print("[ ");
		while(iter.hasNext()) {
			try {
				System.out.print(iter.next());
			} catch (Exception e) {
				System.exit(0);
			}
			if(iter.hasNext())System.out.print(", ");
		}
		System.out.println(" ]");
		System.out.println("Size: " + container.size());
		System.out.println("Max Size: " + container.max_size());
		if(container.empty()) System.out.println("Set is empty");
		else System.out.println("Set is not empty");
		System.out.println("");
	}
	
	
	
	public static void main(String[] args) {
		GTUSet<Integer> set = new GTUSet<Integer>(12);
		GTUIterator<Integer> setIter;
		System.out.println("-----Set-----");
		print(set);
		
		set.insert(2);
		set.insert(5);
		set.insert(3);
		set.insert(8);
		set.insert(1);
		set.insert(7);
		System.out.println("Inserted 6 elements");
		print(set);
		
		if(set.contains(3)) System.out.println("Set contains 3");
		else System.out.println("Set doesn't contain 3");
		if(set.contains("Hello")) System.out.println("Set contains \"Hello\"");
		else System.out.println("Set doesn't contain \"Hello\"");
		System.out.println("");
		
		setIter = set.iterator();
		for(int i = 0; setIter.hasNext(); i++) {
			try {
				setIter.next();
			} catch (Exception e) {
				System.exit(0);
			}
			if(i % 2 == 0) {
				set.erase(setIter);
			}
		}
		System.out.println("Erased every one of two elements");
		print(set);
		
		System.out.println("Cleared set");
		set.clear();
		print(set);
		
		
		
		GTUVector<String> vector = new GTUVector<String>(8);
		GTUIterator<String> vectorIter;
		System.out.println("-----Vector-----");
		print(vector);
		
		vector.insert("Hello");
		vector.insert("World");
		vector.insert("I");
		vector.insert("am");
		vector.insert("a");
		vector.insert("GTU");
		vector.insert("vector");
		System.out.println("Inserted 7 elements");
		print(vector);
		
		if(vector.contains(3)) System.out.println("Vector contains 3");
		else System.out.println("Vector doesn't contain 3");
		if(vector.contains("Hello")) System.out.println("Vector contains \"Hello\"");
		else System.out.println("Vector doesn't contain \"Hello\"");
		System.out.println("");
		
		vectorIter = vector.iterator();
		for(int i = 0; vectorIter.hasNext(); i++) {
			try {
				vectorIter.next();
			} catch (Exception e) {
				System.exit(0);
			}
			if(i % 2 == 0) {
				vector.erase(vectorIter);
			}
		}
		System.out.println("Erased every one of two elements");
		print(vector);
		
		System.out.println("Cleared set");
		vector.clear();
		print(vector);
	}
}
