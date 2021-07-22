public class Main {

	public static void main(String[] args) {
		System.out.println("Reverse String:");
		System.out.println("    Hello World : " + Recursions.reverseString("Hello World"));
		System.out.println("    Finally finished homework! : " + Recursions.reverseString("Finally finished homework!"));
		
		
		System.out.println("\nElfish checker:");
		System.out.println("    Aragorn: " + Recursions.elfishChecker("Aragorn"));
		System.out.println("    Legolas: " + Recursions.elfishChecker("Legolas"));
		System.out.println("    Elrond: " + Recursions.elfishChecker("Elrond"));
		
		
		System.out.println("\nSelection Sort:");
		int[] arr = Recursions.selectionSort(new int[] {6, 4, 1, 9, 5, 2, 3, 7, 8});
		System.out.print("    [6, 4, 1, 9, 5, 2, 3, 7, 8] : [");
		for(int i = 0; i < arr.length; i++) System.out.print(arr[i] + (i != arr.length - 1 ? ", " : "]\n"));
		
		int[] arr2 = Recursions.selectionSort(new int[] {1, 9, 2, 8, 3, 7, 4, 6, 5});
		System.out.print("    [1, 9, 2, 8, 3, 7, 4, 6, 5] : [");
		for(int i = 0; i < arr2.length; i++) System.out.print(arr2[i] + (i != arr2.length - 1 ? ", " : "]\n"));
		
		int[] arr3 = Recursions.selectionSort(new int[] {4, 1, 3, 2, 4, 1, 3, 2, 0});
		System.out.print("    [4, 1, 3, 2, 4, 1, 3, 2, 0] : [");
		for(int i = 0; i < arr3.length; i++) System.out.print(arr3[i] + (i != arr3.length - 1 ? ", " : "]\n"));
		
		System.out.println("\nCalculate Postfix:");
		System.out.println("    [1 2 / 10 *]: " + Recursions.calculatePostfix("1 2 / 10 *"));
		System.out.println("    [1 2 - 12 2 / * 3 *]: " + Recursions.calculatePostfix("1 2 - 12 2 / * 3 *"));
		System.out.println("    [12 8 4 / - 15 4 / 2 - *]: " + Recursions.calculatePostfix("12 8 4 / - 15 4 / 2 - *"));
		
		
		System.out.println("\nCalculate Prefix:");
		System.out.println("    [* / 1 2 10]: " + Recursions.calculatePrefix("* / 1 2 10"));
		System.out.println("    [* * - 1 2 / 12 2 3]: " + Recursions.calculatePrefix("* * - 1 2 / 12 2 3"));
		System.out.println("    [* - 12 / 8 4 - / 15 4 2]: " + Recursions.calculatePrefix("* - 12 / 8 4 - / 15 4 2"));
		
		
		System.out.println("\nTravel in 2D Array:");
		System.out.print("    [1 , 2 , 3 ]\n    [4 , 5 , 6 ]\n    [7 , 8 , 9 ]\n");
		System.out.print("        [");
		Recursions.recursiveTravel(new int[][] {{1,  2,  3}, {4, 5, 6}, {7, 8, 9}}, 0, 0);
		System.out.println("]\n");
		
		System.out.print("    [1 , 2 , 3 , 4 , 5 ]\n    [14, 15, 16, 17, 6 ]\n    [13, 20, 19, 18, 7 ]\n    [12, 11, 10, 9 , 8 ]\n");
		System.out.print("        [");
		Recursions.recursiveTravel(new int[][] {{1,  2,  3,  4,  5}, {14, 15, 16, 17, 6}, {13, 20, 19, 18, 7}, {12, 11, 10, 9,  8}}, 0, 0);
		System.out.println("]\n");
		
		System.out.print("    [1 , 2 , 3 , 4 ]\n    [5 , 6 , 7 , 8 ]\n    [9 , 10, 11, 12]\n    [13, 14, 15, 16]\n    [17, 18, 19, 20]\n");
		System.out.print("        [");
		Recursions.recursiveTravel(new int[][] {{1,  2,  3,  4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}, {17, 18, 19, 20}}, 0, 0);
		System.out.println("]\n");
	}

}
