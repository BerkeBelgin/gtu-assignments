import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

/** 
 * A ListGraph is an extension of the AbstractGraph abstract class 
 * that uses an array of lists to represent the edges.
 */
public class ListGraph extends AbstractGraph {
	/** 
	 * An array of Lists to contain the edges that originate with each vertex.
	 */
	private List<Edge>[] edges;
	 
	/** 
	 * Construct a graph with the specified number of vertices and directionality. 
	 * @param numV The number of vertices 
	 * @param directed The directionality flag
	 */
	public ListGraph(int numV, boolean directed) {
		super(numV, directed);
		edges = new List[numV];
		for (int i = 0; i < numV; i++) {
			edges[i] = new LinkedList<Edge>();
		}
	}
	
	/** 
	 * Insert a new edge into the graph.
	 * @param edge The new edge
	 */
	@Override
	public void insert(Edge edge) {
		edges[edge.getSource()].add(edge);
		if (!isDirected()) edges[edge.getDest()].add(new Edge(edge.getDest(), edge.getSource(), edge.getWeight()));
	}

	/** 
	 * Determine whether an edge exists.
	 * @param source The source vertex 
	 * @param dest The destination vertex 
	 * @return true if there is an edge from source to dest
	 */
	@Override
	public boolean isEdge(int source, int dest) {
		return edges[source].contains(new Edge(source, dest));
	}

	/** 
	 * Get the edge between two vertices.
	 * @param source The source
	 * @param dest The destination
	 * @return the edge between these two vertices or null if an edge does not exist.
	 */
	@Override
	public Edge getEdge(int source, int dest) {
		Edge target = new Edge(source, dest, Double.POSITIVE_INFINITY);
		for (Edge edge: edges[source]) {
			if (edge.equals(target)) return edge;
		}
		return null;
	}

	/**
	 * An iterator to iterate over the edges of a vertex
	 */
	@Override
	public Iterator<Edge> edgeIterator(int source) {
		return edges[source].iterator();
	}

	@Override
	public String toString(){
		StringBuilder sb = new StringBuilder();
		int end = edges.length;
		for(int i=0; i < end; i++){
			sb.append("Node " + i + "-->\n");
			for(Edge e : edges[i]){
				sb.append("\tnode: " + e.getDest() + ", weight: " + e.getWeight() + "\n");
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
			Edge e = parseFileString(scan.nextLine());
			edges[e.getSource()].add(e);
		}
	}

	private Edge parseFileString(String input) {
		Edge toReturn = null;
		Scanner sc = new Scanner(input);
		sc.useDelimiter(",");
		try { 
			int source = sc.nextInt();
			int dest = sc.nextInt();
			double weight = 1.0;
			if(sc.hasNextDouble()) weight = sc.nextDouble();
			toReturn = new Edge(source, dest, weight);
		}
		catch(Exception e) {
			System.out.println("Failed to parse Edge: "+input);
		}		
		sc.close();//close scanner
		return toReturn;//return the scanned point
	}
}
