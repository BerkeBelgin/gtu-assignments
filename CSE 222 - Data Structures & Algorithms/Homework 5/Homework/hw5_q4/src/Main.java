
public class Main {

	public static void main(String[] args) {
		MaxHeap<AgeData> heap = new MaxHeap<AgeData>();
		heap.add(new AgeData(10));
		heap.add(new AgeData(5));
		heap.add(new AgeData(70));
		heap.add(new AgeData(10));
		heap.add(new AgeData(50));
		heap.add(new AgeData(5));
		heap.add(new AgeData(15));
		heap.add(new AgeData(21));
		System.out.println("21 inserted");
		System.out.println(heap.toString());
		heap.add(new AgeData(21));
		heap.add(new AgeData(21));
		System.out.println("21 became root");
		System.out.println(heap.toString());
		heap.add(new AgeData(21));
		heap.add(new AgeData(21));
		heap.add(new AgeData(21));
		System.out.println("21 became even more root");
		System.out.println(heap.toString());
		heap.remove(new AgeData(21));
		heap.remove(new AgeData(21));
		heap.remove(new AgeData(21));
		heap.remove(new AgeData(21));
		System.out.println("21 is no more root");
		System.out.println(heap.toString());
		heap.remove(new AgeData(21));
		heap.remove(new AgeData(21));
		System.out.println("rest in peace 21");
		System.out.println(heap.toString());
		System.out.println("The amount of people older than 10");
		System.out.println(heap.youngerThan(10));
		System.out.println("Node with age 10");
		System.out.println(heap.find(new AgeData(10)).toString());
		
		
		
	}

}
