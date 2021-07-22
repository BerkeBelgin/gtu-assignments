import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * Class that extends BinaryTree class and holds arithmetic operations in its nodes as operands in its leaves and operators in inner nodes.
 * @author Berke Belgin 171044065
 * @see BinaryTree
 */
public class ExpressionTree extends BinaryTree<String>{
	/**
	 * Constructor that constructs the tree with a given infix or prefix expression.
	 * @param expression The expression to be constructed.
	 * @throws NullPointerException if expression is null
	 * @throws IllegalArgumentException if expression is not valid
	 */
	public ExpressionTree(String expression) throws NullPointerException, IllegalArgumentException {
		if(expression == null) throw new NullPointerException("Given argument cannot be null");
		else if(expression.equals("")) throw new IllegalArgumentException("Given argument is not valid");
		else {
			Scanner scn = new Scanner(expression);
			this.root = readBinaryTree(scn).root;
			scn.close();
		}
	}
	
	/**
	 * Method that checks if given string is operand.
	 * @param str The string to be checked.
	 * @return true if given string is operand or false.
	 */
	private static boolean isNumeric(String str) {
		try {
			Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
	}
	
	/**
	 * Helper method that converts given prefix expression which is represented as a list of strings, into expression tree.
	 * @param strList The prefix expression to be constructed. In order to make easier to manuplate expression,
	 * instead of passing whole expression as a string, method expects to take the expression 
	 * which every operator and operand are divided with a space character as a list of strings.
	 * @return the constructed expression tree.
	 */
	private static BinaryTree<String> readBinaryTreePrefix(List<String> strList) {
		String data = strList.remove(0);
		if(isNumeric(data)) {
			return new BinaryTree<String>(data, null, null);
		}
		else {
			BinaryTree<String> leftTree = readBinaryTreePrefix(strList);
			BinaryTree<String> rightTree = readBinaryTreePrefix(strList);
			return new BinaryTree<String>(data, leftTree, rightTree);
		}
	}
	
	/**
	 * Helper method that converts given postfix expression which is represented as a list of strings, into expression tree.
	 * @param strList The postfix expression to be constructed. In order to make easier to manuplate expression,
	 * instead of passing whole expression as a string, method expects to take the expression 
	 * which every operator and operand are divided with a space character as a list of strings.
	 * @return the constructed expression tree.
	 */
	private static BinaryTree<String> readBinaryTreePostfix(List<String> strList) {
		String data = strList.remove(0);
		if(isNumeric(data)) {
			return new BinaryTree<String>(data, null, null);
		}
		else {
			BinaryTree<String> rightTree = readBinaryTreePostfix(strList);
			BinaryTree<String> leftTree = readBinaryTreePostfix(strList);
			return new BinaryTree<String>(data, leftTree, rightTree);
		}
	}
	
	/**
	 * Method that takes an expression in a scanner, decides the expression is either prefix or postfix then passes it to the related method.
	 * @param scan Scanner that holds expression.
	 * @return the constructed tree.
	 */
	public static BinaryTree<String> readBinaryTree(Scanner scan) {
		List<String> strList = new ArrayList<String>();
		while(scan.hasNext()) {
			strList.add(scan.next());
		}
		if(isNumeric(strList.get(0))) {
			for(int i = 0; i < strList.size() - 1; i++) {
				strList.add(i, strList.remove(strList.size() - 1));
			}
			return readBinaryTreePostfix(strList);
		} else {
			return readBinaryTreePrefix(strList);
		}
	}
	
	/**
	 * Performs a postorder traversal (left, right, root) of the tree. Each node and its depth are passed to the consumer function.
	 * @param node The local root
	 * @param depth The depth
	 * @param sb The string buffer to save the output
	 */
	public void postOrderTraverse (Node<String> node, int depth, StringBuilder sb) {
		if(node == null) {
			for(int i = 1; i < depth; i++) sb.append(" ");
			sb.append("null\n");
		} else {
			preOrderTraverse(node.left, depth + 1, sb);
			preOrderTraverse(node.right, depth + 1, sb);
			for(int i = 1; i < depth; i++) sb.append(" ");
			sb.append(node.toString()+ "\n");
		}
	}
	
	/**
	 * Returns a String representation of the tree in postorder.
	 * @return A String representation of the tree.
	 */
	public String toString2() {
		StringBuilder sb = new StringBuilder();
		postOrderTraverse(root, 1, sb);
		return sb.toString();
	}
	
	/**
	 * Helper that evaluates tree and returns result as int.
	 * @param node local root 
	 * @return result as int.
	 * @throws IllegalArgumentException if operator is not valid
	 */
	private int eval(Node<String> node) throws IllegalArgumentException {
		if(isNumeric(node.data)) {
			return Integer.parseInt(node.data);
		} else {
			int left = eval(node.left);
			int right = eval(node.right);
			if(node.data.equals("+"))return left + right;
			else if(node.data.equals("-"))return left - right;
			else if(node.data.equals("*"))return left * right;
			else if(node.data.equals("/"))return left / right;
			else throw new IllegalArgumentException("The operator " + node.data + " is not legal");
		}
	}
	
	/**
	 * Evaluates tree by calling its helper method and returns result as int.
	 * @return result as int.
	 */
	public int eval() {
		return eval(root);
	}
}
