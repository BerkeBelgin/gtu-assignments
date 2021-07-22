import java.util.Iterator;

public class Main {
	public static void main(String[] args) {
		String format = "    %-24s%s";
		String format2 = "    %-48s%-24s%s";
		
		GtuDeque<Integer> deq = new GtuDeque<Integer>();
		System.out.println("Integer deque:");
		
		deq.add(4);
		System.out.println(String.format(format, "add(4)", ": [" + deq.toString() + "]"));
		
		deq.add(5);
		System.out.println(String.format(format, "add(5)", ": [" + deq.toString() + "]"));
		
		deq.push(3);
		System.out.println(String.format(format, "push(3)", ": [" + deq.toString() + "]"));
		
		deq.addFirst(1);
		System.out.println(String.format(format, "addFirst(1)", ": [" + deq.toString() + "]"));
		
		deq.addLast(8);
		System.out.println(String.format(format, "addLast(8)", ": [" + deq.toString() + "]"));
		
		try {
			deq.offer(null);
			System.out.println(String.format(format, "trying offer(null)", ": [" + deq.toString() + "]"));
		} catch(IllegalArgumentException e) {
			System.out.println(String.format(format, "trying offer(null)", ": [" + deq.toString() + "] - catched!"));
		}
		
		deq.offerFirst(-5);
		System.out.println(String.format(format, "offerFirst(-5)", ": [" + deq.toString() + "]"));
		
		deq.offerLast(11);
		System.out.println(String.format(format, "offerLast(11)", ": [" + deq.toString() + "]"));
		
		deq.pop();
		System.out.println(String.format(format, "pop()", ": [" + deq.toString() + "]"));
		
		deq.remove();
		System.out.println(String.format(format, "remove()", ": [" + deq.toString() + "]"));
		
		deq.removeFirst();
		System.out.println(String.format(format, "removeFirst()", ": [" + deq.toString() + "]"));
		
		deq.removeLast();
		System.out.println(String.format(format, "removeLast()", ": [" + deq.toString() + "]"));
		
		deq.poll();
		System.out.println(String.format(format, "poll()", ": [" + deq.toString() + "]"));
		
		deq.pollFirst();
		System.out.println(String.format(format, "pollFirst()", ": [" + deq.toString() + "]"));
		
		deq.pollLast();
		System.out.println(String.format(format, "pollLast()", ": [" + deq.toString() + "]"));
		
		GtuDeque<String> deq2 = new GtuDeque<String>();
		System.out.println("\nString deque:");
		deq2.add("Implement");
		deq2.add("a");
		deq2.add("Deque");
		deq2.add("class");
		deq2.add("which");
		deq2.add("implements");
		deq2.add("Deque");
		deq2.add("interface");
		deq2.add("and");
		deq2.add("can");
		deq2.add("extend");
		deq2.add("AbstractCollection");
		
		System.out.println(String.format(format2, "element()", ": " + deq2.element(), ": [" + deq2.toString() + "]"));
		System.out.println(String.format(format2, "getFirst()", ": " + deq2.getFirst(), ": [" + deq2.toString() + "]"));
		System.out.println(String.format(format2, "getLast()", ": " + deq2.getLast(), ": [" + deq2.toString() + "]"));
		System.out.println(String.format(format2, "peek()", ": " + deq2.peek(), ": [" + deq2.toString() + "]"));
		System.out.println(String.format(format2, "peekFirst()", ": " + deq2.peekFirst(), ": [" + deq2.toString() + "]"));
		System.out.println(String.format(format2, "peekLast()", ": " + deq2.peekLast(), ": [" + deq2.toString() + "]"));
		System.out.println(String.format(format2, "removeFirstOccurrence(\"can\")", ": " + deq2.removeFirstOccurrence("can"), ": [" + deq2.toString() + "]"));
		System.out.println(String.format(format2, "removeLastOccurrence(\"AbstractCollection\")", ": " + deq2.removeLastOccurrence("AbstractCollection"), ": [" + deq2.toString() + "]"));
		
		String out = "";
		Iterator<String> itr = deq2.iterator();
		while(itr.hasNext()) {
			out += itr.next();
			if(itr.hasNext())out += ", ";
		}
		System.out.println(String.format(format2, "print using iterator()", ": ", ": [" + out + "]"));
		
		String out2 = "";
		Iterator<String> desItr = deq2.descendingIterator();
		while(desItr.hasNext()) {
			out2 += desItr.next();
			if(desItr.hasNext())out2 += ", ";
		}
		System.out.println(String.format(format2, "print using descending iterator()", ": ", ": [" + out2 + "]"));
	}

}
