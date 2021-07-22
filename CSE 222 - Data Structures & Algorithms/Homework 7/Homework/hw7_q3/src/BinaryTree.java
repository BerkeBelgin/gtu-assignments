import java.io.Serializable;
import java.util.Scanner;

public class BinaryTree<E> implements Serializable {
    protected Node<E> root;
    public BinaryTree(){
        root = null;
    }
    protected BinaryTree(Node<E> root){
        this.root = root;
    }
    public BinaryTree(E data, BinaryTree<E> leftTree, BinaryTree<E> rightTree){
        root = new Node<>(data);
        if(leftTree != null)
            root.left = leftTree.root;
        else
            root.left = null;
        if(rightTree != null)
            root.right = rightTree.root;
        else
            root.right = null;
    }
    /**
     * Return the left subtree
     * @return The left subtree or null if either the root or
     * the left subtree is null
     */
    public BinaryTree<E> getLeftSubtree(){
        if(root != null && root.left != null)
            return new BinaryTree<>(root.left);
        else
            return null;
    }
    /**
     * Return the right subtree
     * @return The right subtree or null if either the root or
     * the right subtree is null
     */
    public BinaryTree<E> getRightSubtree(){
        if(root != null && root.right != null)
            return new BinaryTree<>(root.right);
        else
            return null;
    }
    /**
     * Determine whether this tree is a leaf.
     * @return true if the root has no children
     */
    public Boolean isLeaf(){
        return (root.left == null && root.right == null);
    }
    /**
     * Perform a preOrder traversal.
     * @param node The local root
     * @param depth The depth
     * @param sb The string buffer to save the output
     */
    private void preOrderTraverse(Node<E> node, int depth, StringBuilder sb){
        for(int i=0;i<depth;i++){
            sb.append(" ");
        }
        if(node == null)
            sb.append("null\n");
        else{
            sb.append(node.toString());
            sb.append("\n");
            preOrderTraverse(node.left, depth+1,sb);
            preOrderTraverse(node.right,depth+1,sb);
        }
    }
    /**
     * Method to read a binary tree
     * pre: The input consists of a preOrder traversal of the binary tree
     * The line "null" indicates a null tree
     * @param scan The Scanner attached to the input file
     * @return The binary tree
     */
    public static BinaryTree<String > readBinaryTree(Scanner scan){
        String data = scan.next();
        if(data.equals("null")) {
            return null;
        }
        else{
            BinaryTree<String> leftTree = readBinaryTree(scan);
            BinaryTree<String> rightTree = readBinaryTree(scan);
            return new BinaryTree<>(data, leftTree, rightTree);
        }
    }
    public String toString(){
        StringBuilder sb = new StringBuilder();
        preOrderTraverse(root,1,sb);
        return sb.toString();
    }
    /**
     * Class to encapsulate a tree node
     */
    protected static class Node<E>{
        protected E data;
        protected Node<E> left;
        protected Node<E> right;
        public Node(E data){
            this.data = data;
            left = null;
            right = null;
        }
        public String toString(){
            return data.toString();
        }
    }
}