import java.util.Random;

public class Main {

	public static void main(String[] args) {
		BTreeSkipList<Integer> test = new BTreeSkipList<Integer>(2, 4);
		for(int i = 0; i < 50; i++) {
			int rnd = new Random().nextInt(50);
			test.add(rnd);
			System.out.println(String.format("INS: %-2d",  rnd) + ": " + test.toString());
		}
		for(int i = 0; i < 50; i++) {
			int rnd = new Random().nextInt(50);
			test.remove(rnd);
			System.out.println(String.format("RMV: %-2d", rnd) + ": " + test.toString());
		}
		for(int i = 0; i < 50; i++) {
			test.remove(i);
			System.out.println(String.format("CLR: %-2d", i) + ": " + test.toString());
		}
	}

}
