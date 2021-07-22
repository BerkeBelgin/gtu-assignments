import java.util.Comparator;

public class MaxHeapComparator<E extends MaxHeapNode> implements Comparator<E> {
	public int compare(E e1, E e2) {
		return e1.getCount() - e2.getCount();
	}
}
