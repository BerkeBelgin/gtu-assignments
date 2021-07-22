
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
import java.util.Stack;

public class LL2DGraph extends AbstractGraph {
	private LinkedList<Vertex> srcV;
	private LinkedList<Vertex> destV;
	
	/**
	 * Construct a 2-D linked list graph with the given number of vertices and directionality.
	 * @param numV Number of vertices in the graph
	 * @param directed Flag indicating whether the graph is directed or not
	 */
	public LL2DGraph(int numV, boolean directed) {
		super(0, directed);
		srcV = new LinkedList<Vertex>();
		destV = new LinkedList<Vertex>();
		for(int i = 0; i < numV; i++) insertVertex();
	}
	
	/**
	 * A helper method that returns previous node of the node with given source and destination indexes, on the same row
	 * @param srcIndex index in the source vertices linked list
	 * @param destIndex index in the destination vertices linked list
	 * @return previous node
	 */
	private Node prevSrcNode(int srcIndex, int destIndex) {
		if(srcIndex >= srcV.size() || destIndex >= destV.size())throw new IllegalArgumentException();
		Node node = null;
		Node next = srcV.get(srcIndex).link;
		while(next != null) {
			Node temp = next;
			while(temp.cprev != null)temp = temp.cprev;
			
			int nextIndex = 0;
			Iterator<Vertex> iter = destV.iterator();
			while(iter.hasNext() && iter.next().link != temp) nextIndex++;
			if(nextIndex < destIndex) node = next;
			
			next = next.rnext;
		}
		return node;
	}
	
	/**
	 * A helper method that returns previous node of the node with given source and destination indexes, on the same column
	 * @param srcIndex index in the source vertices linked list
	 * @param destIndex index in the destination vertices linked list
	 * @return previous node
	 */
	private Node prevDestNode(int srcIndex, int destIndex) {
		if(srcIndex >= srcV.size() || destIndex >= destV.size())throw new IllegalArgumentException();
		Node node = null;
		Node next = destV.get(destIndex).link;
		while(next != null) {
			Node temp = next;
			while(temp.rprev != null)temp = temp.rprev;
			
			int nextIndex = 0;
			Iterator<Vertex> iter = srcV.iterator();
			while(iter.hasNext() && iter.next().link != temp) nextIndex++;
			if(nextIndex < srcIndex) node = next;
			
			next = next.cnext;
		}
		return node;
	}
	
	/**
	 * Helper method that inserts given edge into the graph once
	 * @param edge Edge to be inserted
	 */
	private void insertDirected(Edge edge) {
		if(edge.getSource() >= srcV.size() || edge.getDest() >= destV.size())throw new IllegalArgumentException();
		
		Vertex col = destV.get(edge.getDest());
		Vertex row = srcV.get(edge.getSource());
		
		Node colPrev = prevDestNode(edge.getSource(), edge.getDest());
		Node rowPrev = prevSrcNode(edge.getSource(), edge.getDest());
		Node colNext = colPrev != null ? colPrev.cnext : col.link;
		Node rowNext = rowPrev != null ? rowPrev.rnext : row.link;
		
		Node node = new Node(edge.getWeight(), rowNext, rowPrev, colNext, colPrev);
		
		if(colPrev != null)colPrev.cnext = node;
		else col.link = node;
		if(rowPrev != null)rowPrev.rnext = node;
		else row.link = node;
		if(colNext != null)colNext.cprev = node;
		if(rowNext != null)rowNext.rprev = node;
	}
	
	/** 
	 * Insert a new edge into the graph.
	 * @param edge The new edge
	 */
	@Override
	public void insert(Edge edge) {
		if(edge.getSource() == edge.getDest())throw new IllegalArgumentException();
		if(!isEdge(edge.getSource(), edge.getDest())) {
			insertDirected(edge);
			if(!super.isDirected())insertDirected(new Edge(edge.getDest(), edge.getSource(), edge.getWeight()));
		}
	}
	
	/**
	 * Helper method that deletes the edge with given indexes from the graph once
	 * @param source index in the source vertices linked list
	 * @param dest index in the destination vertices linked list
	 */
	private void deleteDirected(int source, int dest) {
		if(source >= srcV.size() || dest >= destV.size())throw new IllegalArgumentException();
		
		Vertex col = destV.get(dest);
		Vertex row = srcV.get(source);
		
		Node colPrev = prevDestNode(source, dest);
		Node rowPrev = prevSrcNode(source, dest);
		Node colNext = colPrev != null ? colPrev.cnext.cnext : col.link.cnext;
		Node rowNext = rowPrev != null ? rowPrev.rnext.rnext : row.link.rnext;
		
		if(colPrev != null)colPrev.cnext = colNext;
		else col.link = colNext;
		if(rowPrev != null)rowPrev.rnext = rowNext;
		else row.link = rowNext;
		if(colNext != null)colNext.cprev = colPrev;
		if(rowNext != null)rowNext.rprev = rowPrev;
	}
	
	
	/**
	 * Remove the edge with given indexes from the graph
	 * @param source index in the source vertices linked list
	 * @param dest index in the destination vertices linked list
	 */
	public void delete(int source, int dest) {
		if(source == dest)throw new IllegalArgumentException();
		if(isEdge(source, dest)) {
			deleteDirected(source, dest);
			if(!super.isDirected())deleteDirected(dest, source);
		}
	}
	
	/**
	 * Inserts a new vertex into the end of the graph
	 */
	public void insertVertex() {
		srcV.add(new Vertex());
		destV.add(new Vertex());
		super.numV++;
	}
	
	/**
	 * Deletes the vertex with given index
	 * @param index of the vertex to be deleted
	 */
	public void deleteVertex(int index) {
		if(index >= srcV.size())throw new IllegalArgumentException();
		
		Node srcNode = srcV.get(index).link;//every row
		Node destNode = destV.get(index).link;//every column
		
		while(srcNode != null) {
			if(srcNode.cprev != null) srcNode.cprev.cnext = srcNode.cnext;
			if(srcNode.cnext != null) srcNode.cnext.cprev = srcNode.cprev;
			srcNode = srcNode.rnext;
		}
		
		while(destNode != null) {
			if(destNode.rprev != null) destNode.rprev.rnext = destNode.rnext;
			if(destNode.rnext != null) destNode.rnext.rprev = destNode.rprev;
			destNode = destNode.rnext;
		}
		
		srcV.remove(index);
		destV.remove(index);
		super.numV--;
	}

	/** 
	 * Determine whether an edge exists.
	 * @param source The source vertex 
	 * @param dest The destination vertex 
	 * @return true if there is an edge from source to dest
	 */
	@Override
	public boolean isEdge(int source, int dest) {//!
		Node colPrev = prevDestNode(source, dest);
		Node rowPrev = prevSrcNode(source, dest);
		
		Node colNode = colPrev != null ? colPrev.cnext : destV.get(dest).link;
		Node rowNode = rowPrev != null ? rowPrev.rnext : srcV.get(source).link;
		
		if(colNode != null && rowNode != null && colNode == rowNode)return true;
		else return false;
	}

	/** 
	 * Get the edge between two vertices.
	 * @param source The source
	 * @param dest The destination
	 * @return the edge between these two vertices or null if an edge does not exist.
	 */
	@Override
	public Edge getEdge(int source, int dest) {
		Node colPrev = prevDestNode(source, dest);
		Node rowPrev = prevSrcNode(source, dest);
		
		Node colNode = colPrev != null ? colPrev.cnext : destV.get(dest).link;
		Node rowNode = rowPrev != null ? rowPrev.rnext : srcV.get(source).link;
		
		if(colNode != null && rowNode != null && colNode == rowNode) {
			Edge edge = new Edge(source, dest, colNode.data);
			return edge;
		} else return null;
	}

	/**
	 * An iterator to iterate over the edges of a vertex
	 */
	@Override
	public Iterator<Edge> edgeIterator(int source) {
		ArrayList<Edge> adjacentEdges = new ArrayList<Edge>();
		
		int end = srcV.size();
		for(int i = 0; i < end; i++){
			Edge edge = getEdge(source,i);
			if(edge != null){
				adjacentEdges.add(edge);
			}
		}
		return adjacentEdges.iterator();
	}

	@Override
	public String toString(){
		StringBuilder sb = new StringBuilder();
		int end = srcV.size();
		for(int i = 0; i < end; i++){
			sb.append("Node " + i + "-->\n");
			for(int j = 0; j < end; j++){
				Edge edge = getEdge(i,j);
				if(edge == null) sb.append("\tnode: " + j + " is not adjacent to " + i + "\n");
				else sb.append("\tnode: " + j + ", weight: " + edge.getWeight() + "\n");
			}
		}
		return sb.toString();
	}
	
	/**
	 * Method that loads edges from scanner
	 */
	@Override
	public void loadEdgesFromFile(Scanner scan) {
		while(scan.hasNextLine()) {
			String input = scan.nextLine();
			Scanner sc = new Scanner(input);
			sc.useDelimiter(",");
			try { 
				int source = sc.nextInt();	
				int dest = sc.nextInt();
				if(sc.hasNextDouble())insert(new Edge(source, dest, sc.nextDouble()));
				else insert(new Edge(source, dest, 1.0));
			}
			catch(Exception e){
				System.out.println("Failed to parse Edge: " + input);
			}		
			sc.close();
		}
	}
	
	/**
	 * Method that searches the graph with Breadth First Search technique
	 * @param start index of the vertex to be started from
	 * @return int array in the right order
	 */
	public int[] breadthFirstSearch(int start) {
		Queue<Integer> theQueue = new LinkedList<Integer>();
		
		boolean[] identified = new boolean[super.getNumV()];
		int[] parent = new int[super.getNumV()];
		for(int i = 0; i < super.getNumV(); i++)parent[i] = -1;
		
		identified[start] = true;
		theQueue.offer(start);

		while(!theQueue.isEmpty()){
			int current = theQueue.remove();
			Iterator<Edge> itr = edgeIterator(current);
			while(itr.hasNext()){
				Edge edge = itr.next();
				int neighbor = edge.getDest();
				if(!identified[neighbor]){
					identified[neighbor] = true;
					theQueue.offer(neighbor);
					parent[neighbor] = current;
				}
			}
		}
		return parent;
	}

	/**
	 * Method that searches the graph with Depth First Search technique
	 * @param start index of the vertex to be started from
	 * @return int array in the right order
	 */
	public int[] depthFirstSearch(int start) {
		Stack<Integer> s = new Stack<Integer>();
		
		boolean[] visited = new boolean[super.getNumV()];
		int[] parent = new int[super.getNumV()];
		for(int i = 0; i < super.getNumV(); i++)parent[i] = -1;
		
		int[] discoveryOrder = new int[super.getNumV()];
		int[] finishOrder = new int[super.getNumV()];
		
		int discoverIndex = 0;
		int finishIndex = finishOrder.length;
		
		s.push(start);
		while(!s.isEmpty()){
			int v = s.pop();
			if(!visited[v]){
				visited[v] = true;
				discoveryOrder[discoverIndex++] = v;
				Iterator<Edge> itr = edgeIterator(v);
				while(itr.hasNext()){
					int u = itr.next().getDest();
					s.push(u);
					parent[u] = v;
				}
				finishIndex = finishIndex - 1;
				finishOrder[finishIndex] = v;
			}
		}
		return parent;
	}
	
	private class Vertex {
		Node link = null;
	}

	private class Node {
		double data;
		Node rnext;
		Node rprev;
		Node cnext;
		Node cprev;
		
		public Node(double data, Node rnext, Node rprev, Node cnext, Node cprev) {
			this.data = data;
			this.rnext = rnext;
			this.rprev = rprev;
			this.cnext = cnext;
			this.cprev = cprev;
		}
	}
}
