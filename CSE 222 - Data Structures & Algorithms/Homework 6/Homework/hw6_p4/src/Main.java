import java.util.Random;

public class Main {
	public static void test() {
		HashTableOpen <Integer, Integer> hashTableOpen = new HashTableOpen<Integer, Integer>();
		HashTableChain<Integer, Integer> hashTableChain = new HashTableChain<Integer, Integer>();
		HashTableOpen <Integer, Integer> hashTableOpenDH = new HashTableOpen<Integer, Integer>();
		HashTableChain<Integer, Integer> hashTableChainBT = new HashTableChain<Integer, Integer>();
		
		int n = 100000;
		int getSize = 1000;
		
		System.out.print("Put Hash Table Open: ");
		Integer[] keys1 = new Integer[getSize];
		long startTime = System.nanoTime();
		Random rand1 = new Random();
		for(int i = 0; i < n; i++) {
			int key = rand1.nextInt(1000);
			hashTableOpen.put(key, rand1.nextInt(1000));
			if(i % (n/getSize) == 0)keys1[i / (n/getSize)] = key;
		}
		long endTime = System.nanoTime();
		long time = endTime - startTime;
		System.out.println(time);
		
		System.out.print("Put Hash Table Chain: ");
		Integer[] keys2 = new Integer[getSize];
		startTime = System.nanoTime();
		Random rand2 = new Random();
		for(int i = 0; i < n; i++) {
			int key = rand2.nextInt(1000);
			hashTableChain.put(key, rand2.nextInt(1000));
			if(i % (n/getSize) == 0)keys2[i / (n/getSize)] = key;
		}
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println(time);
		
		System.out.print("Put Hash Table Open Double Hashing: ");
		Integer[] keys3 = new Integer[getSize];
		startTime = System.nanoTime();
		Random rand3 = new Random();
		for(int i = 0; i < n; i++) {
			int key = rand3.nextInt(1000);
			hashTableOpenDH.put(key, rand3.nextInt(1000));
			if(i % (n/getSize) == 0)keys3[i / (n/getSize)] = key;
		}
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println(time);
		
		System.out.print("Put Hash Table Chain Binary Tree: ");
		Integer[] keys4 = new Integer[getSize];
		startTime = System.nanoTime();
		Random rand4 = new Random();
		for(int i = 0; i < n; i++) {
			int key = rand4.nextInt(1000);
			hashTableChainBT.put(key, rand4.nextInt(1000));
			if(i % (n/getSize) == 0)keys4[i / (n/getSize)] = key;
		}
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println(time);
		System.out.println();
		
		
		
		System.out.print("Get Hash Table Open: ");
		startTime = System.nanoTime();
		for(int i = 0; i < keys1.length; i++) {
			hashTableOpen.get(keys1[i]);
		}
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println(time);
		
		System.out.print("Get Hash Table Chain: ");
		startTime = System.nanoTime();
		for(int i = 0; i < keys2.length; i++) {
			hashTableChain.get(keys2[i]);
		}
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println(time);
		
		System.out.print("Get Hash Table Open Double Hashing: ");
		startTime = System.nanoTime();
		for(int i = 0; i < keys3.length; i++) {
			hashTableOpenDH.get(keys3[i]);
		}
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println(time);
		
		System.out.print("Get Hash Table Chain Binary Tree: ");
		startTime = System.nanoTime();
		for(int i = 0; i < keys4.length; i++) {
			hashTableChainBT.get(keys4[i]);
		}
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println(time);
		System.out.println();
		
		
		
		System.out.print("Remove Hash Table Open: ");
		startTime = System.nanoTime();
		for(int i = 0; i < keys1.length; i++) {
			hashTableOpen.remove(keys1[i]);
		}
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println(time);
		
		System.out.print("Remove Hash Table Chain: ");
		startTime = System.nanoTime();
		for(int i = 0; i < keys2.length; i++) {
			hashTableChain.remove(keys2[i]);
		}
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println(time);
		
		System.out.print("Remove Hash Table Open Double Hashing: ");
		startTime = System.nanoTime();
		for(int i = 0; i < keys3.length; i++) {
			hashTableOpenDH.remove(keys3[i]);
		}
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println(time);
		
		System.out.print("Remove Hash Table Chain Binary Tree: ");
		startTime = System.nanoTime();
		for(int i = 0; i < keys4.length; i++) {
			hashTableChainBT.remove(keys4[i]);
		}
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println(time);
		System.out.println();

		System.out.println(hashTableOpen.size());
		System.out.println(hashTableChain.size());
		System.out.println(hashTableOpenDH.size());
		System.out.println(hashTableChainBT.size());
	}
	
	public static void main(String[] args) {
		for(int i = 0; i < 4; i++)test();
	}
}
