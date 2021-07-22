

public class Edge {
	/**
	 * The destination vertex for an edge
	 */
	private int dest;
	/**
	 * The source vertex for an edge
	 */
	private int source;
	/**
	 * The weight
	 */
	private double weight;
	
	/**
	 * Constructs an Edge from source to dest. Sets the weight to 1.0
	 * @param source the source vertex of the edge
	 * @param dest the destination vertex of the edge
	 */
	public Edge(int source, int dest) {
		this.source = source;
		this.dest = dest;
	}
	
	/**
	 * Constructs an Edge from source to dest with given weight
	 * @param source the source vertex of the edge
	 * @param dest the destination vertex of the edge
	 * @param weight the weight of the edge
	 */
	public Edge(int source, int dest, double weight) {
		this.source = source;
		this.dest = dest;
		this.weight = weight;
	}
	
	/**
	 * Returns the destination vertex
	 * @return the destination vertex
	 */
	public int getDest() {
		return dest;
	}
	
	/**
	 * Returns the source vertex
	 * @return the source vertex
	 */
	public int getSource() {
		return source;
	}
	
	/**
	 * Returns the weight
	 * @return the weight
	 */
	public double getWeight() {
		return weight;
	}
	
	/**
	 * Compares two edges for equality. Edges are equal if their source 
	 * and destination vertices are the same. The weight is not considered
	 */
	public boolean equals(Object o) {
		if(o instanceof Edge && this.dest == ((Edge) o).dest && this.source == ((Edge) o).source) {
			return true;
		} else {
			return false;
		}
	}
	
	/**
	 * Returns the hash code for an edge. The hash code depends only 
	 * on the source and destination
	 */
	public int hashCode() {
		int result = 17;
		result = 31 * result + dest;
		result = 31 * result + source;
		return result;
	}
	
	/**
	 * Returns a string representation of the edge
	 */
	public String toString() {
		return String.format("%d - %f - %d", source, weight, dest);
	}
}
