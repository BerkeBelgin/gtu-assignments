public class Main {

	public static void main(String[] args) {
		ExpressionTree tree2 = new ExpressionTree("/ + 10 * 5 15 20");
		System.out.println(tree2.toString());
		System.out.println(tree2.eval());
		ExpressionTree expTree = new ExpressionTree("+ + 10 * 5 15 20");
		ExpressionTree expTree2 = new ExpressionTree("10 5 15 * + 20 +");
		System.out.println(expTree.eval());
		System.out.println(expTree2.eval());
	}

}
