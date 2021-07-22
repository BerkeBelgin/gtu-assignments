import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.Scanner;

public class MazeSolver {
	private static int[][] readMaze(Scanner scan) {
		ArrayList<ArrayList<Integer>> matrix = new ArrayList<ArrayList<Integer>>();
		for(int y = 0; scan.hasNextLine(); y++) {
			String input = scan.nextLine();
			matrix.add(new ArrayList<Integer>());
			for(int x = 0; x < input.length(); x++) {
				matrix.get(y).add(Character.getNumericValue(input.charAt(x)));
			}
		}
		
		int[][] maze = new int[matrix.size()][matrix.get(0).size()];
		for(int y = 0; y < maze.length; y++) {
			for(int x = 0; x < maze[0].length; x++) {
				maze[y][x] = matrix.get(y).get(x);
			}
		}
		return maze;
	}
	
	private static boolean hasRightPath(int[][]maze, int y, int x) {
		return x < maze[0].length - 1 && maze[y][x + 1] == 0;
	}
	private static boolean hasUpPath(int[][]maze, int y, int x) {
		return 0 < y && maze[y - 1][x] == 0;
	}
	private static boolean hasLeftPath(int[][]maze, int y, int x) {
		return 0 < x && maze[y][x - 1] == 0;
	}
	private static boolean hasDownPath(int[][]maze, int y, int x) {
		return y < maze.length - 1 && maze[y + 1][x] == 0;
	}
	
	private static boolean isVertex(int[][]maze, int y, int x) {
		if(maze[y][x] == 0) {
			int connectionCount = 0;
			if(hasUpPath(maze, y, x))connectionCount++;
			if(hasLeftPath(maze, y, x))connectionCount++;
			if(hasDownPath(maze, y, x))connectionCount++;
			if(hasRightPath(maze, y, x))connectionCount++;
			return (y == 0 && x == 0) || (y == maze.length - 1 && x == maze[0].length - 1) || connectionCount == 1 || connectionCount == 3 || connectionCount == 4;
		} else return false;
	}
	
	private static int[] findEdge(int[][]maze, int y, int x, int prev) {
		//prev = 0 right
		//prev = 1 up
		//prev = 2 left
		//prev = 3 down
		if(isVertex(maze, y, x))return new int[] {y, x, 0};
		else {
			int[] result = null;
			if(prev != 2 && hasRightPath(maze, y, x))result = findEdge(maze, y, x + 1, 0);
			else if(prev != 3 && hasUpPath(maze, y, x))result = findEdge(maze, y - 1, x, 1);
			else if(prev != 0 && hasLeftPath(maze, y, x))result = findEdge(maze, y, x - 1, 2);
			else if(prev != 1 && hasDownPath(maze, y, x))result = findEdge(maze, y + 1, x, 3);
			else return new int[] {-1, -1, 0};
			result[2] += 1;
			return result;
		}
		
	}
	
	private static int indexOf(ArrayList<int[]> vertices, int[] vertex) {
		for(int i = 0; i < vertices.size(); i++) {
			if(vertices.get(i)[0] == vertex[0] && vertices.get(i)[1] == vertex[1]) {
				return i;
			}
		}
		return -1;
	}
	
	private static ArrayList<Edge> findEdges(int[][]maze, ArrayList<int[]> vertices, int srcIndex){
		ArrayList<Edge> edges = new ArrayList<Edge>();
		int srcY = vertices.get(srcIndex)[0];
		int srcX = vertices.get(srcIndex)[1];
		
		for(int i = 0; i < 4; i++) {
			int[] vertex = null;
			if(i == 0 && hasRightPath(maze, srcY, srcX))vertex = findEdge(maze, srcY, srcX + 1, i);
			if(i == 1 && hasUpPath(maze, srcY, srcX))vertex = findEdge(maze, srcY - 1, srcX, i);
			if(i == 2 && hasLeftPath(maze, srcY, srcX))vertex = findEdge(maze, srcY, srcX - 1, i);
			if(i == 3 && hasDownPath(maze, srcY, srcX))vertex = findEdge(maze, srcY + 1, srcX, i);
			if(vertex != null) {
				int destIndex = indexOf(vertices, vertex);
				double weight = vertex[2];
				if(destIndex != -1)edges.add(new Edge(srcIndex, destIndex, weight));
			}
		}
		return edges;
	}
	
	private static Graph convertIntoGraph(int[][] maze) {
		ArrayList<int[]> vertices = new ArrayList<int[]>();
		
		for(int y = 0; y < maze.length; y++) {
			for(int x = 0; x < maze[0].length; x++) {
				if(isVertex(maze, y, x)) vertices.add(new int[]{y, x});
			}
		}
		
		Graph graph = new LL2DGraph(vertices.size(), false);
		
		for(int i = 0; i < vertices.size(); i++) {
			ArrayList<Edge> edges = findEdges(maze, vertices, i);
			for(int j = 0; j < edges.size(); j++) {
				graph.insert(edges.get(j));
			}
		}
		return graph;
	}
	private static Path solveMaze(Graph graph, int srcIndex, Path path) {
		ArrayList<Path> paths = new ArrayList<Path>();
		Iterator<Edge> iter = graph.edgeIterator(srcIndex);
		while(iter.hasNext()) {
			Edge edge = iter.next();
			boolean travelled = false;
			for(int i = 0; i < path.travelledV.length; i++) {
				if(edge.getDest() == path.travelledV[i]) {
					travelled = true;
					break;
				}
			}
			if(!travelled) {
				int[] nextTravelledV = Arrays.copyOf(path.travelledV, path.travelledV.length + 1);
				nextTravelledV[nextTravelledV.length - 1] = edge.getDest();
				int nextDistance = path.distance + (int) edge.getWeight() + 1;
				paths.add(solveMaze(graph, edge.getDest(),new Path(nextTravelledV, nextDistance)));
			}
		}
		if(paths.size() <= 0 || (path.travelledV.length > 0 && path.travelledV[path.travelledV.length - 1] == (graph.getNumV() - 1))) {
			return path;
		} else {
			Path result = path;
			for(int i = 0; i < paths.size(); i++) {
				int pathEnd = paths.get(i).travelledV[paths.get(i).travelledV.length - 1];
				int resultEnd = result.travelledV[result.travelledV.length - 1];
				int mazeEnd = (graph.getNumV() - 1);
				
				if(pathEnd == mazeEnd && (resultEnd != mazeEnd || paths.get(i).distance < result.distance)) {
					result = paths.get(i);
				}
			}
			return result;
		}
	}
	
	public static String solveMaze(Scanner scan) {
		int[][] maze = readMaze(scan);
		Graph graph = convertIntoGraph(maze);
		Path result = solveMaze(graph, 0, new Path(new int[] {0}, 1));
		return Arrays.toString(result.travelledV) + " (" + result.distance + ")";
	}
	
	private static class Path {
		int[] travelledV;
		int distance;
		
		public Path(int[] path, int distance) {
			this.travelledV = path;
			this.distance = distance;
		}
	}
}
