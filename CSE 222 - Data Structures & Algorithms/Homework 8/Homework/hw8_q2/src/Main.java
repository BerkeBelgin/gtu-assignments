import java.util.Random;

public class Main {

	public static void main(String[] args) {
		for(int j = 0; j < 3; j++) {
			Random rand = new Random();
			int maxSize = 6;
			LL2DGraph graph = new LL2DGraph(maxSize, false);
			
			for(int i = 0; i < 8; i++) {
				int s = rand.nextInt(maxSize - 1);
				int d = rand.nextInt(maxSize - 1);
				double w = Math.floor(rand.nextDouble() * 100) / 100;
				while(s == d)d = rand.nextInt(maxSize - 1);
				
				graph.insert(new Edge(s, d, w));
			}
			System.out.println("Insert: Undirected - " + j);
			System.out.println(graph.toString());
			
			for(int i = 0; i < 8; i++) {
				int s = rand.nextInt(maxSize - 1);
				int d = rand.nextInt(maxSize - 1);
				while(s == d)d = rand.nextInt(maxSize - 1);
				
				graph.delete(s, d);
			}
			System.out.println("Delete: Undirected - " + j);
			System.out.println(graph.toString());
			
			Random rand2 = new Random();
			int maxSize2 = 6;
			LL2DGraph graph2 = new LL2DGraph(maxSize2, true);
			
			for(int i = 0; i < 8; i++) {
				int s = rand2.nextInt(maxSize2 - 1);
				int d = rand2.nextInt(maxSize2 - 1);
				double w = Math.floor(rand2.nextDouble() * 100) / 100;
				while(s == d)d = rand2.nextInt(maxSize2 - 1);
				
				graph2.insert(new Edge(s, d, w));
			}
			System.out.println("Insert: Directed - " + j);
			System.out.println(graph2.toString());
			
			for(int i = 0; i < 8; i++) {
				int s = rand.nextInt(maxSize - 1);
				int d = rand.nextInt(maxSize - 1);
				while(s == d)d = rand.nextInt(maxSize - 1);
				
				graph2.delete(s, d);
			}
			System.out.println("Delete: Directed - " + j);
			System.out.println(graph2.toString());
		}
	}

}
