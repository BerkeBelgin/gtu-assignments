import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * A class to hold some recursive methods that requested in the homework
 * 
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-04-13
 */
public class Recursions {
	
	/**
	 * Method that reverses given String recursively.
	 * @param str String to be reversed
	 * @return the reversed String
	 * @throws IllegalArgumentException if given String is null
	 */
	public static String reverseString(String str) throws IllegalArgumentException {
		if(str != null) {
			List<String> splitStr = new ArrayList<String>(Arrays.asList(str.split(" ")));
			if(!splitStr.get(0).equals("")) {
				return splitStr.get(splitStr.size() - 1) + " " + reverseString(String.join(" ", splitStr.subList(0, splitStr.size() - 1)));
			}
			else return "";
		} else throw new IllegalArgumentException();
	}
	
	/**
	 * Method that checkes if a string is elfish by checking every character
	 * of it if they contain either of "e", "l" or "f" characters recursively.
	 * @param str String to be reversed
	 * @return {@code true} if given String is elfish
	 * @throws IllegalArgumentException if given String is null
	 */
	public static boolean elfishChecker(String str) throws IllegalArgumentException {
		if(str != null) {
			if(str.length() == 0)return false;
			else if(str.charAt(0) == 'e' || str.charAt(0) == 'l' || str.charAt(0) == 'f' || str.charAt(0) == 'E' || str.charAt(0) == 'L' || str.charAt(0) == 'F') return true;
			else return elfishChecker(str.substring(1, str.length()));
		} else throw new IllegalArgumentException();
	}

	private static int minIndex(int arr[], int fromIndex) 
    { 
        if(fromIndex < arr.length - 1) {
        	int prevIndex = minIndex(arr, fromIndex + 1);
        	
        	if(arr[prevIndex] < arr[fromIndex])return prevIndex;
        	else return fromIndex;
        } else {
        	return fromIndex;
        }
    } 
	
	private static void copyArrayReverseOrder(int[] from, int[] to, int fromIndex) {
		int toIndex = to.length - (from.length - fromIndex);
		if(from.length > fromIndex && fromIndex >= 0 && to.length > toIndex && toIndex >= 0) {
			to[toIndex] = from[fromIndex];
			copyArrayReverseOrder(from, to, fromIndex - 1);
		}
	}
	
	/**
	 * Method that sorts given array recursively using Selection Sort Algorithm
	 * @param arr array to be sorted
	 * @return sorted array
	 * @throws IllegalArgumentException if given array is null
	 */
	public static int[] selectionSort(int[] arr) throws IllegalArgumentException{	
		if(arr != null) {
			if(arr.length > 1) {
				int minIndex = minIndex(arr, 0);
				
				int temp = arr[0];
				arr[0] = arr[minIndex];
				arr[minIndex] = temp;
				
				int[] arr2 = new int[arr.length - 1];
				copyArrayReverseOrder(arr, arr2, arr.length - 1);
				arr2 = selectionSort(arr2);
				copyArrayReverseOrder(arr2, arr, arr2.length - 1);
				return arr;
			} else return arr;
		} else throw new IllegalArgumentException();
	}
	
	private static boolean isOperator(String str) {
		switch(str) {
		case "+":
		case "-":
		case "*":	
		case "/":
			return true;
		default: 
			return false;
		}
	}
	private static boolean isOperand(String str) {
		try {
			Float.parseFloat(str);
			return true;
		} catch(NumberFormatException e){
			return false;
		}
	}
	private static float calculate(String opr, float num1, float num2) throws IllegalArgumentException {
		switch(opr) {
		case "+":
			return num1 + num2;
		case "-":
			return num1 - num2;
		case "*":
			return num1 * num2;
		case "/":
			return num1 / num2;
		default: 
			throw new IllegalArgumentException();
		}
	}
	
	private static int getOperatorIndexPrefix(List<String> splitStr, int n) throws IllegalArgumentException {
		if(isOperand(splitStr.get(splitStr.size() - 1))) {
			n++;
		} else if(isOperator(splitStr.get(splitStr.size() - 1))) {
			n--;
		} else throw new IllegalArgumentException();
		
		if(n != 0)return getOperatorIndexPrefix(splitStr.subList(0, splitStr.size() - 1), n);
		else return splitStr.size() - 1;
	}
	
	/**
	 * Method that evaluates given pretfix notation recursively which contains + - * / 
	 * operations and every element seperated with spaces
	 * @param str the prefix notation to be evaluated
	 * @return the result as float
	 * @throws IllegalArgumentException if String contains a characters which is not allowed
	 */
	public static float calculatePrefix(String str) throws IllegalArgumentException {
		final String splitCharacter = " ";
		List<String> splitStr = new ArrayList<String>(Arrays.asList(str.split(splitCharacter)));
		
		if(splitStr.size() == 1) return Float.parseFloat(splitStr.get(0));
		
		if(isOperator(splitStr.get(splitStr.size() - 3))) {
			float num2 = Float.parseFloat(splitStr.remove(splitStr.size() - 1));
			float num1 = Float.parseFloat(splitStr.remove(splitStr.size() - 1));
			String opr = splitStr.remove(splitStr.size() - 1);
			
			splitStr.add(Float.toString(calculate(opr, num1, num2)));
			
			return calculatePrefix(String.join(splitCharacter, splitStr));
		} else if(isOperand(splitStr.get(splitStr.size() - 3))){
			int operatorIndex = getOperatorIndexPrefix(splitStr.subList(0, splitStr.size() - 1), 0);
			
			
			float num2 = Float.parseFloat(splitStr.get(splitStr.size() - 1));
			float num1 = calculatePrefix(String.join(splitCharacter, splitStr.subList(operatorIndex + 1, splitStr.size() - 1)));
			String opr = splitStr.get(operatorIndex);
			
			splitStr = splitStr.subList(0, operatorIndex);
			splitStr.add(Float.toString(calculate(opr, num1, num2)));
			
			return calculatePrefix(String.join(splitCharacter, splitStr));
		} else throw new IllegalArgumentException();
	}
	
	private static int getOperatorIndexPostfix(List<String> splitStr, int n) throws IllegalArgumentException {
		if(isOperand(splitStr.get(0))) {
			n++;
		} else if(isOperator(splitStr.get(0))) {
			n--;
		} else throw new IllegalArgumentException();
		
		if(n != 0)return getOperatorIndexPostfix(splitStr.subList(1, splitStr.size()), n);
		else return splitStr.size();
	}
	
	/**
	 * Method that evaluates given postfix notation recursively which contains + - * / 
	 * operations and every element seperated with spaces
	 * @param str the postfix notation to be evaluated
	 * @return the result as float
	 * @throws IllegalArgumentException if String contains a characters which is not allowed
	 */
	public static float calculatePostfix(String str) throws IllegalArgumentException {
		final String splitCharacter = " ";
		List<String> splitStr = new ArrayList<String>(Arrays.asList(str.split(splitCharacter)));
		
		if(splitStr.size() == 1) return Float.parseFloat(splitStr.get(0));
		
		if(isOperator(splitStr.get(2))) {
			float num1 = Float.parseFloat(splitStr.remove(0));
			float num2 = Float.parseFloat(splitStr.remove(0));
			String opr = splitStr.remove(0);
			
			splitStr.add(0, Float.toString(calculate(opr, num1, num2)));
			
			return calculatePostfix(String.join(splitCharacter, splitStr));
		} else if(isOperand(splitStr.get(2))){
			int operatorIndex = splitStr.size() - getOperatorIndexPostfix(splitStr.subList(1, splitStr.size()), 0);
			
			
			float num1 = Float.parseFloat(splitStr.get(0));
			float num2 = calculatePostfix(String.join(splitCharacter, splitStr.subList(1, operatorIndex)));
			String opr = splitStr.get(operatorIndex);
			
			splitStr = splitStr.subList(operatorIndex + 1, splitStr.size());
			splitStr.add(0, Float.toString(calculate(opr, num1, num2)));
			
			return calculatePostfix(String.join(splitCharacter, splitStr));
		} else throw new IllegalArgumentException();
	}
	
	/**
	 * Method that travels given 2d array and prints every element from the given coordinates 
	 * recursively by following a fractal path as from outer elements to inner elements
	 * @param arr array to be printed
	 * @param startY y index to be started printing from
	 * @param startX x index to be started printing from
	 * @throws IllegalArgumentException if indexes are out of bounds or array is null
	 */
	public static void recursiveTravel(int[][] arr, int startY, int startX) throws IllegalArgumentException {
		int sizeY = arr.length;
		int sizeX = arr[0].length;
		
		int minEdgeLength;
		
		int endY;
		int endX;
		
		if(startY < 0 || startY >= sizeY || startX < 0 || startX >= sizeX || arr == null) throw new IllegalArgumentException();
		
		if(sizeY > sizeX) {
			minEdgeLength = sizeX;
			
			endY = minEdgeLength / 2;
			endX = (minEdgeLength - 1) / 2;
			endY += ((minEdgeLength % 2) * (sizeY - minEdgeLength));
		} else if(sizeY < sizeX){
			minEdgeLength = sizeY;
			
			endY =  minEdgeLength / 2;
			endX = (minEdgeLength - 1) / 2;
			endX += ((minEdgeLength % 2) * (sizeX - minEdgeLength));
		} else {
			minEdgeLength = sizeY;
			
			endY = minEdgeLength / 2;
			endX = (minEdgeLength - 1) / 2;
		}			
			
		System.out.print(arr[startY][startX] + (startY != endY || startX != endX ? ", " : ""));
		
		if(startX != endX || startY != endY) {
			if     (	startY <= startX + 1 						&& startY < minEdgeLength/2 				&& startY < (sizeX-1) - startX				)recursiveTravel(arr, startY, startX + 1); 
			else if(	(sizeX-1) - startX <= startY 				&& (sizeX-1) - startX < minEdgeLength/2 	&& (sizeX-1) - startX < (sizeY-1) - startY	)recursiveTravel(arr, startY + 1, startX);
			else if(	(sizeY-1) - startY <= (sizeX-1) - startX 	&& (sizeY-1) - startY < minEdgeLength/2 	&& (sizeY-1) - startY < startX				)recursiveTravel(arr, startY, startX - 1);
			else if(	startX <= (sizeY-1) - startY				&& startX < minEdgeLength/2 				&& startX + 1 < startY						)recursiveTravel(arr, startY - 1, startX);
			else if(	minEdgeLength % 2 != 0 						&& minEdgeLength == sizeY 					&& startY == minEdgeLength/2				)recursiveTravel(arr, startY, startX + 1);
			else if(	minEdgeLength % 2 != 0 						&& minEdgeLength == sizeX 					&& startX == minEdgeLength/2				)recursiveTravel(arr, startY + 1, startX);
		}
	}
}
