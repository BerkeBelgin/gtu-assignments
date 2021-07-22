import java.util.ArrayDeque;
import java.util.Iterator;
import java.util.Queue;
import java.util.Scanner;
import java.util.function.Consumer;

/** 
 * A MatrixGraph is an extension of the AbstractGraph abstract class 
 * that uses a 2D array to represent the edges.
 */
public class MatrixGraph extends AbstractGraph {
	/**
	 * A matrix of edge weights
	 */
	private double[][] edges;
	
	/**
	 * Construct a matrix graph with the given number of vertices and directionality.
	 * @param numV Number of vertices in the graph
	 * @param directed Flag indicating whether the graph is directed or not
	 */
	public MatrixGraph(int numV, boolean directed) {
		super(numV, directed);
		edges = new double[numV][numV];
		for(int i=0; i<numV; i++){
			for(int j=0; j<numV; j++){
				edges[i][j] = Double.POSITIVE_INFINITY;
			}
		}
	}
	
	/** 
	 * Insert a new edge into the graph.
	 * @param edge The new edge
	 */
	@Override
	public void insert(Edge edge) {
		edges[edge.getSource()][edge.getDest()] = edge.getWeight();
		if(!isDirected()) edges[edge.getDest()][edge.getSource()] = edge.getWeight();
	}

	/** 
	 * Determine whether an edge exists.
	 * @param source The source vertex 
	 * @param dest The destination vertex 
	 * @return true if there is an edge from source to dest
	 */
	@Override
	public boolean isEdge(int source, int dest) {
		return edges[source][dest] != Double.POSITIVE_INFINITY;
	}

	/** 
	 * Get the edge between two vertices.
	 * @param source The source
	 * @param dest The destination
	 * @return the edge between these two vertices or null if an edge does not exist.
	 */
	@Override
	public Edge getEdge(int source, int dest) {
		return new Edge(source, dest, edges[source][dest]);
	}

	/**
	 * An iterator to iterate over the edges of a vertex
	 */
	@Override
	public Iterator<Edge> edgeIterator(int source) {
		Queue<Edge> adjacentEdges = new ArrayDeque<Edge>();
		int end = edges.length;
		for(int i = 0; i < end; i++){
			double weight = edges[source][i];
			if(weight != Double.POSITIVE_INFINITY){
				adjacentEdges.offer(new Edge(source, i, weight));
			}
		}
		return new Iter<Edge>(adjacentEdges);
	}
	
	@Override
	public String toString(){
		StringBuilder sb = new StringBuilder();
		int end = edges.length;
		for(int i=0; i<end; i++){
			sb.append("Node " + i + "-->\n");
			for(int j=0; j<end; j++){
				if(edges[i][j] == Double.POSITIVE_INFINITY){
					sb.append("\tnode: " + j + " is not adjacent to " + i + "\n");
				} else {
					sb.append("\tnode: " + j + ", weight: " + edges[i][j] + "\n");
				}
			}
		}
		return sb.toString();
	}
	
	/**
	 * Method that loads edges from scanner
	 */
	@Override
	public void loadEdgesFromFile(Scanner scan){
		while(scan.hasNextLine()) {
			String input = scan.nextLine();
			Scanner sc = new Scanner(input);
			sc.useDelimiter(",");
			try {
				int source = sc.nextInt();
				int dest = sc.nextInt();
				if(sc.hasNextDouble())edges[source][dest] = sc.nextDouble();
				else edges[source][dest] = 1.0;
			}
			catch(Exception e){
				System.out.println("Failed to parse Edge: "+input);
			}		
			sc.close();
		}
	}
	
	private class Iter<Edge> implements Iterator {
		/**
		 * A list of nodes adjacent to the node of the iterator
		 */
		private Queue<Edge> adjacentEdges;

		/**
		 * Constructs an iterator for the given set of edges
		 * @param adjacentEdges A queue of the edges adjacent to the source node
		 */
		public Iter(Queue<Edge> adjacentEdges){
			this.adjacentEdges = adjacentEdges;
		}

		@SuppressWarnings("unchecked")
		public void forEachRemaining(Consumer arg0) {
			((Iterator) adjacentEdges).forEachRemaining(arg0);
		}

		/**
		 * Returns whether there are any unexplored edges adjacent to the node we are iterating on
		 * @return true if there are more nodes to explore, false otherwise
		 */
		public boolean hasNext() {
			return adjacentEdges.peek() != null;
		}

		/**
		 * Returns the next unexplored edge adjacent to the node we are iterating on
		 * @return the next unexplored edge adjacent to the node we are iterating on
		 */
		public Object next() {
			return adjacentEdges.poll();
		}

		/**
		 * Remove the next edge adjacent to the node we are iterating on from the queue 
		 */
		public void remove() {
			adjacentEdges.poll();
		}

		public String toString(){
			StringBuilder sb = new StringBuilder();
			int end = edges.length;
			for(int i=0; i<end; i++){
				sb.append("Node " + i + "-->\n");
				for(int j=0; j<end; j++){
					if(edges[i][j] == Double.POSITIVE_INFINITY){
						sb.append("\tnode: " + j + " is not adjacent to " + i + "\n");
					} else {
						sb.append("\tnode: " + j + ", weight: " + edges[i][j] + "\n");
					}
				}
			}
			return sb.toString();
		}
	}
}
