import java.io.Serializable;
import java.util.Scanner;

/**
 * A class to hold given information of type E in a binary tree.
 * @author Berke Belgin 171044065
 * @param <E> Any class to hold in trees nodes.
 */
public class BinaryTree<E> {
	/**
	 * The root of the binary tree.
	 */
	protected Node<E> root;
	
	/**
	 * Constructs an empty binary tree.
	 */
	public BinaryTree() {
		root = null;
	}
	
	/**
	 * Constructs a binary tree with the given node as the root.
	 * @param root The root node of the binary tree that will be the created.
	 */
	protected BinaryTree(Node<E> root) {
		this.root = root;
	}
	
	/**
	 * Constructs a new binary tree with data in its root leftTree as its left subtree and rightTree as its right subtree.
	 * @param data The root nodes data of the binary tree that will be the created.
	 * @param leftTree The root nodes left node refrence of the binary tree that will be the created.
	 * @param rightTree The root nodes right node refrence of the binary tree that will be the created.
	 */
	public BinaryTree(E data, BinaryTree<E> leftTree, BinaryTree<E> rightTree) {
		root = new Node<>(data);
		if (leftTree != null) root.left = leftTree.root;
		else root.left = null;
		if (rightTree != null) root.right = rightTree.root;
		else root.right = null;
	}
	
	/**
	 * Returns the left subtree.
	 * @return The left subtree or null if either the root or the left subtree is null 
	 */
	public BinaryTree<E> getLeftSubtree() {
		if(root != null && root.left != null) return new BinaryTree<E>(root.left);
		else return null;
	}
	
	/**
	 * Returns the right subtree.
	 * @return The right subtree or null if either the root or left subtree is null.
	 */
	public BinaryTree<E> getRightSubtree() {
		if(root != null && root.right != null) return new BinaryTree<E>(root.right);
		else return null;
	}
	
	/**
	 * Returns the data in the root.
	 * @return The data in the root.
	 */
	public E getData() {
		return root.data;
	}
	
	/**
	 * Determine whether this tree is a leaf.
	 * @return True if this tree has no children, false otherwise.
	 */
	public boolean isLeaf() {
		return (root.left == null && root.right == null);
	}
	
	/**
	 * Returns a String representation of the tree.
	 * @return A String representation of the tree.
	 */
	public String toString() {
		StringBuilder sb = new StringBuilder();
		preOrderTraverse(root, 1, sb);
		return sb.toString();
	}
	
	/**
	 * Performs a preorder traversal of the tree. Each node and its depth are passed to the consumer function.
	 * @param node The local root
	 * @param depth The depth
	 * @param sb The string buffer to save the output
	 */
	public void preOrderTraverse (Node<E> node, int depth, StringBuilder sb) {
		for(int i = 1; i < depth; i++) sb.append(" ");
		if(node == null)sb.append("null\n");
		else {
			sb.append(node.toString()+ "\n");
			preOrderTraverse(node.left, depth + 1, sb);
			preOrderTraverse(node.right, depth + 1, sb);
		}
	}
	
	/**
	 * Constructs a binary tree by reading its data using Scanner scan.
	 * @param scan the Scanner attached to the input file.
	 * @return The binary tree created.
	 */
	public static BinaryTree<String> readBinaryTree(Scanner scan) {
		String data = scan.next();
		if(data.equals("null")) return null;
		else {
			BinaryTree<String> leftTree = readBinaryTree(scan);
			BinaryTree<String> rightTree = readBinaryTree(scan);
			return new BinaryTree<String>(data, leftTree, rightTree);
		}
	}
	
	
	/**
	 * Class to encapsulate a tree node.
	 */
	@SuppressWarnings("serial")
	protected static class Node<E> implements Serializable {
		/**
		 * The information stored in this node.
		 */
		protected E data;
		
		/**
		 * Refrence to the left child.
		 */
		protected Node<E> left;
		
		/**
		 * Refrence to the right child.
		 */
		protected Node<E> right;
		
		/**
		 * Construct a noden with given data and no children.
		 * @param data The data to store in this node
		 */
		public Node(E data) {
			this.data = data;
			this.left = null;
			this.right = null;
		}
		
		/**
		 * Return a string representation of the node.
		 * @return A string representation of the data fields
		 */
		public String toString() {
			return this.data.toString();
		}
	}
}
