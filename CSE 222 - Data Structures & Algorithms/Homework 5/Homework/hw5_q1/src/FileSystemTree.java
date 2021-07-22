import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * This class represents a file hierarchy as a tree which every node holds its child nodes in an ArrayList if it is a DirectoryNode.
 * @author Berke Belgin 171044065
 * @see ArrayList
 */
public class FileSystemTree {
	/**
	 * The root node of the instance of this class. It holds Files and Directories.
	 */
	private DirectoryNode root;
	
	/**
	 * The constructor of the class
	 * @param path The file hierarchy of the instance that will be created.
	 * @throws NullPointerException if path argument is null.
	 * @throws IllegalArgumentException if path argument is illegal.
	 */
	FileSystemTree(String path) throws NullPointerException, IllegalArgumentException {
		if(path == null) throw new NullPointerException("Given argument cannot be null");
		else if(path.equals("") || path.charAt(0) == '/' || path.charAt(path.length() - 1) == '/') throw new IllegalArgumentException("Given path is not valid");
		else {
			for(int i = 1; i < path.length(); i++) if(path.charAt(i - 1) == '/' && path.charAt(i) == '/') throw new IllegalArgumentException("Given path is not valid");
			if(path.indexOf('/') == -1) {
				root = new DirectoryNode(path);
			} else {
				root = new DirectoryNode(path.substring(0, path.indexOf('/')));
				addDir(path);
			}
		} 
	}
	
	/**
	 * Helper method to check if given path is valid.
	 * @param path The path to be checked.
	 * @return true if path is legal or false.
	 */
	private boolean isPathValid(String path) {
		if(path == null || path.equals("") || path.charAt(0) == '/' || path.charAt(path.length() - 1) == '/' || path.indexOf("/") == -1 || !path.substring(0, path.indexOf("/")).equals(root.getName())) return false;
		for(int i = 1; i < path.length(); i++) if(path.charAt(i - 1) == '/' && path.charAt(i) == '/') return false;
		return true;
	}
	
	/**
	 * Helper method that inserts Directory or File to the given path location.
	 * @param path The path of the File or Directory which will be inserted.
	 * @param dir Local node of the recursion, generally root will be given as parameter.
	 * @param type The type of the file (DirectoryNode or FileNode).
	 * @throws IllegalArgumentException if a file or directory with the same name already exists or path is incorrect.
	 */
	private void addRecursively(String path, DirectoryNode dir, Class<?> type) throws IllegalArgumentException {
		if(path.indexOf('/') != -1) {
			String nodeName = path.substring(0, path.indexOf('/'));
			String nextPath = path.substring(path.indexOf('/') + 1, path.length());
			
			for(int i = 0; i < dir.size(); i++) {
				if(dir.get(i).getName().equals(nodeName)) {
					if(dir.get(i) instanceof DirectoryNode) {
						addRecursively(nextPath,(DirectoryNode) dir.get(i), type);
						return;
					}
					else throw new IllegalArgumentException();
				}
			}
			
			dir.addNode(new DirectoryNode(nodeName));
			addRecursively(nextPath,(DirectoryNode) dir.get(dir.size() - 1), type);
		} else {
			String nodeName = path;
			for(int i = 0; i < dir.size(); i++) if(dir.get(i).getName().equals(nodeName)) throw new IllegalArgumentException("There is already a file with the same name");
			if(type == DirectoryNode.class) dir.addNode(new DirectoryNode(nodeName));
			else dir.addNode(new FileNode(nodeName));
		}
	}
	
	/**
	 * Method which is called to create directory.
	 * @param path The path of the directory that will be created.
	 * @throws NullPointerException if path is null.
	 * @throws IllegalArgumentException if path is not valid.
	 */
	public void addDir(String path) throws NullPointerException, IllegalArgumentException {
		if(path == null) throw new NullPointerException();
		else if(isPathValid(path)) addRecursively(path.substring(path.indexOf('/') + 1, path.length()), root, DirectoryNode.class);
		else throw new IllegalArgumentException();
	}
	
	/**
	 * Method which is called to create file.
	 * @param path The path of the directory that will be created.
	 * @throws NullPointerException if path is null.
	 * @throws IllegalArgumentException if path is not valid.
	 */
	public void addFile(String path) throws NullPointerException, IllegalArgumentException {
		if(path == null) throw new NullPointerException();
		else if(isPathValid(path)) addRecursively(path.substring(path.indexOf('/') + 1, path.length()), root, FileNode.class);
		else throw new IllegalArgumentException();
	}

	/**
	 * Helper method that removes Directory or File int the given path location. If directory and also has files or directories in it, 
	 * it asks user if the user is sure to remove it with all the files in it.
	 * @param path The path of the node that will be removed from the local node.
	 * @param dir Local node of the recursion, generally root will be given as parameter.
	 * @throws IllegalArgumentException if path is not valid.
	 */
	private void removeRecursively(String path, DirectoryNode dir) throws IllegalArgumentException {
		if(path.indexOf('/') != -1) {
			String nodeName = path.substring(0, path.indexOf('/'));
			String nextPath = path.substring(path.indexOf('/') + 1, path.length());
			
			for(FileSystemNode node : dir.getNodes()) {
				if(node.getName().equals(nodeName)) {
					if(node instanceof DirectoryNode) {
						removeRecursively(nextPath, (DirectoryNode) node);
						return;
					}
					else throw new IllegalArgumentException();
				}
			}
			
			throw new IllegalArgumentException();
		} else {
			String nodeName = path;
			for(int i = 0; i < dir.size(); i++) {
				if(dir.get(i).getName().equals(nodeName)) {
					if(dir.get(i) instanceof DirectoryNode && ((DirectoryNode) dir.get(i)).size() > 0) {
						String in = "";
						while(!in.equals("y") && !in.equals("Y") && !in.equals("n") && !in.equals("N")) {
							System.out.println("\nIt seems the folder you are trying to delete is not empty.\nThe folder will be deleted along with all the files in it.\n");
							printFileSystemOfNodeAsText(dir.get(i), "");
							System.out.println("\n");
							printFileSystemOfNode(dir.get(i));
							System.out.print("\nDo you want to proceed? y/n : ");
							Scanner scn = new Scanner(System.in);
							in = scn.nextLine();
							scn.close();
						}
						if(in.equals("y") || in.equals("Y"))dir.removeNode(i);
						return;
					}
					else dir.removeNode(i);
					return;
				}
			}
			
			throw new IllegalArgumentException();
		}
	}
	
	/**
	 * Method whic is called to remove file or directory.
	 * @param path The location of the node that will be removed
	 * @throws NullPointerException if path is null.
	 * @throws IllegalArgumentException if path is not valid.
	 */
	public void remove(String path) throws NullPointerException, IllegalArgumentException {
		if(path == null) throw new NullPointerException();
		else if(isPathValid(path)) removeRecursively(path.substring(path.indexOf('/') + 1, path.length()), root);
		else throw new IllegalArgumentException();
	}
	
	/**
	 * Helper method to search if there is a file or directory which contains given string in its name.
	 * @param node Local node of the recursion, generally root will be given as parameter.
	 * @param path of the node that whose child nodes will be searched.
	 * @param str The string to be searched
	 * @return string representation of all the nodes contains given string in their names.
	 */
	private String searchRecursively(FileSystemNode node, String path, String str) {
		String output = "";
		if(path != "") output += path + "/";
		output +=node.getName();
		
		String result = "";
		if(node.getName().contains(str)) {
			if(node instanceof DirectoryNode) result += output + "(D)\n";
			else result += output + "(F)\n";
		}
		
		if(node instanceof DirectoryNode) {
			for(FileSystemNode subNode : ((DirectoryNode) node).getNodes()) {
				result += searchRecursively(subNode, output, str);
			}
		}
		return result;
	}
	
	/**
	 * Method that will be called to search if there is a file or directory which contains given string in its name.
	 * @param str The string to be searched
	 */
	public void search(String str) {
		String result = searchRecursively(root, "", str);
		if(result.equals(""))result = "Nothing found\n";
		System.out.print(result);
	}
	
	/**
	 * Helper method to write the whole tree into a 2D table in order to make it printable to console as a tree representation.
	 * @param node Local node of the recursion.
	 * @param table The 2D table, tree will be written into.
	 * @param y Y location of the node in 2d matrix. In other words its depth in the tree.
	 * @param x X location of the node in 2d matrix. Every node has a distance between the one next to it as much as its leaf count.
	 */
	private void createTreeTableRecursively(FileSystemNode node, String[][] table, int y, int x) {
		if(node instanceof DirectoryNode) table[y][x] = node.getName() + " (D)";
		else table[y][x] = node.getName() + " (F)";
		
		if(node instanceof DirectoryNode) {
			int index = x;
			for(FileSystemNode subNode : ((DirectoryNode) node).getNodes()) {
				createTreeTableRecursively(subNode, table, y + 1, index);
				index += subNode.getLeafCount();
			}
		}
	}
	
	/**
	 * Helper method that prints the file hierarchy exactly as a tree representation. 
	 * Every node has a distance of 1 step to its parent and child nodes
	 * in the y axis and every node has as much distance as the amount of its leaf count steps 
	 * to its right neighbouring node in the 2D matrix representation of the file hierarch.
	 * @param node The node that the hierarchy will be printed from.
	 */
	private void printFileSystemOfNode(FileSystemNode node) {
		int formatSize = 25;
		
		String[][] table = new String[node.getTreeDepth()][node.getLeafCount()];
		createTreeTableRecursively(node, table, 0, 0);
		
		String output = "";
		output += String.format("%-" + formatSize + "s\n", node.getName());
		output += String.format("%-" + formatSize + "s\n", "|");
		
		for(int y = 1; y < table.length; y++) {
			String reverse = "";
			boolean mark = false;
			for(int x = table[y].length - 1; 0 <= x; x--) {
				if(x < table[y].length - 1 && table[y - 1][x + 1] != null) mark = false;
				else if(x < table[y].length - 1 && table[y][x + 1] != null) mark = true;
				
				if(mark) {
					for(int i = 1; i < formatSize; i++) reverse = "-" + reverse;
					reverse = "o" + reverse;
				} else {
					if(table[y][x] == null) {
						reverse = String.format("%-" + formatSize + "s", "") + reverse;
					} else {
						reverse = String.format("%-" + formatSize + "s", "o") + reverse;
					}
				}
			}
			output += reverse + "\n";
			
			for(int x = 0; x < table[y].length; x++) {
				if(table[y][x] != null)output += String.format("%-" + formatSize + "s", "|");
				else output += String.format("%-" + formatSize + "s", "");
			}
			output += "\n";
			
			for(int x = 0; x < table[y].length; x++) {
				if(table[y][x] != null)output += String.format("%-" + formatSize + "s", table[y][x]);
				else output += String.format("%-" + formatSize + "s", "");
			}
			output += "\n";
			
			for(int x = 0; x < table[y].length; x++) {
				if(table[y][x] != null && y + 1 < table.length && table[y+1][x] != null)output += String.format("%-" + formatSize + "s", "|");
				else output += String.format("%-" + formatSize + "s", "");
			}
			output += "\n";
		}
		
		System.out.print(output);
	}
	
	/**
	 * Helper method that prints file tree hierarchy as paths one by one, every node below each other.
	 * @param node The node that the hierarchy will be printed from and also local node of the recursion.
	 * @param path the path of the local node.
	 */
	private void printFileSystemOfNodeAsText(FileSystemNode node, String path) {
		String output = "";
		if(path != "") output += path + "/";
		output +=node.getName();
		if(node instanceof DirectoryNode) System.out.println(output + "(D)");
		else System.out.println(output + "(F)");
		
		
		if(node instanceof DirectoryNode) {
			for(FileSystemNode subNode : ((DirectoryNode) node).getNodes()) {
				printFileSystemOfNodeAsText(subNode, output);
			}
		}
	}
	
	/**
	 * Method to print file hierarch as both text and as a tree representation.
	 */
	public void printFileSystem() {
		printFileSystemOfNodeAsText(root, "");
		System.out.println();
		printFileSystemOfNode(root);
	}
	
	/**
	 * Abstract FileSystemClass which represents the nodes of FileSystemTree.
	 */
	protected static abstract class FileSystemNode{
		/**
		 * Field that holds the name of the node.
		 */
		protected String name;
		
		FileSystemNode(String name){
			this.name = name;
		}
		
		public String getName() {
			return name;
		}
		
		/**
		 * The leaf count of the node
		 * @return the leaf count, returns 1 if it has not.
		 */
		public abstract int getLeafCount();
		
		/**
		 * The amount of how many nodes below that node.
		 * @return the amount of how many nodes below that node, returns 1 if it has not.
		 */
		public abstract int getTreeDepth();
	}
	
	/**
	 * Class that represents a file in the FileSystemTree hierarchy, 
	 * it has no array to represent its child directories and files since it is not a directory.
	 */
	protected static class FileNode extends FileSystemNode{
		FileNode(String name) {
			super(name);
		}
		
		public int getLeafCount() {
			return 1;
		}
		
		public int getTreeDepth() {
			return 1;
		}
	}
	
	/**
	 * Class that represents a directory in the FileSystemTree hierarchy, 
	 * it has array of nodes to represent its child directories and files since it is a directory.
	 */
	protected static class DirectoryNode extends FileSystemNode {
		private ArrayList<FileSystemNode> nodes;
		
		DirectoryNode(String name) {
			super(name);
			nodes = new ArrayList<FileSystemNode>();
		}
		
		public void addNode(FileSystemNode node) {
			nodes.add(node);
		}
		
		public void removeNode(int i) {
			nodes.remove(i);
		}
		
		public List<FileSystemNode> getNodes(){
			return nodes;
		}
		
		public FileSystemNode get(int i) {
			return nodes.get(i);
		}
		
		public int size() {
			return nodes.size();
		}
		
		public int getLeafCount() {
			if(nodes.size() > 0) {
				int leaves = 0;
				for(FileSystemNode node : nodes) {
					leaves += node.getLeafCount();
				}
				return leaves;
			} else {
				return 1;
			}
		}
		
		public int getTreeDepth() {
			if(nodes.size() == 0) {
				return 1;
			} else {
				int largestDepth = 0;
				for(FileSystemNode node : nodes) {
					int nodeDepth = node.getTreeDepth();
					if(nodeDepth > largestDepth) largestDepth = nodeDepth;
				}
				return 1 + largestDepth;
			}
		}
	}
}
