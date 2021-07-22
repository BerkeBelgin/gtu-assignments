public class Main {

	public static void main(String[] args) {
		AgeSearchTree<AgeData> ageTree = new AgeSearchTree<AgeData>();
		ageTree.add(new AgeData(10));
		ageTree.add(new AgeData(20));
		ageTree.add(new AgeData(5));
		ageTree.add(new AgeData(15));
		ageTree.add(new AgeData(10));
		System.out.println("Created tree");
		System.out.println(ageTree.toString());
		
		System.out.println("The amount of people younger than 15");
		System.out.println(ageTree.youngerThan(15));
		System.out.println("Node with age 10");
		System.out.println(ageTree.find(new AgeData(10)).toString());
		
	}

}
