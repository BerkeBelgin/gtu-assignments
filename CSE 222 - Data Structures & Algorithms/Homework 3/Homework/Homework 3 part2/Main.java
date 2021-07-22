import java.io.IOException;
import java.util.logging.FileHandler;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;

public class Main {
	private static Logger initLogger() {
		final String LOG_FILE_PATH= "logs/log_file.log";
		
		Logger logger = Logger.getLogger(SimpleTextEditor.class.getName());
	    FileHandler fh = null;
	    try {
			fh = new FileHandler(LOG_FILE_PATH);
		} catch (SecurityException | IOException e) {
			e.printStackTrace();
		}  
        logger.addHandler(fh);
        fh.setFormatter(new SimpleFormatter());
        return logger;
	}
	
	public static void main(String[] args) {
		final String INPUT_FILE_PATH= "input/input_text.txt";
		final String INPUT_FILE_PATH_2= "input/input_text_2.txt";
		SimpleTextEditor ArrayListTestIndex = new SimpleTextEditor(SimpleTextEditor.ARRAY_LIST);
		SimpleTextEditor ArrayListTestIterator = new SimpleTextEditor(SimpleTextEditor.ARRAY_LIST);
		SimpleTextEditor LinkedListTestIndex = new SimpleTextEditor(SimpleTextEditor.LINKED_LIST);
		SimpleTextEditor LinkedListTestIterator = new SimpleTextEditor(SimpleTextEditor.LINKED_LIST);
		Logger logger = initLogger();
		long startTime = 0;
		long endTime = 0;
		int findIndex = -1;
		String SongVerse = 
				"[Verse 1]\n" + 
				"Now you all know\n" + 
				"The bards and their songs\n" + 
				"When hours have gone by\n" + 
				"I'll close my eyes\n" + 
				"In a world far away\n" + 
				"We may meet again\n" + 
				"But now hear my song\n" + 
				"About the dawn of the night\n" + 
				"Let's sing the bard's song";
		
		startTime = System.nanoTime();
		ArrayListTestIndex.readWithIndex(INPUT_FILE_PATH_2);
		endTime = System.nanoTime();
		logger.info("ArrayList + index: Reading the text completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		startTime = System.nanoTime();
		ArrayListTestIterator.readWithIterator(INPUT_FILE_PATH_2);
		endTime = System.nanoTime();
		logger.info("ArrayList + iterator: Reading the text completed in " + ((float)(endTime - startTime)) / 1000000 + " nanoseconds\n");
		
		startTime = System.nanoTime();
		LinkedListTestIndex.readWithIndex(INPUT_FILE_PATH_2);
		endTime = System.nanoTime();
		logger.info("LinkedList + index: Reading the text completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		startTime = System.nanoTime();
		LinkedListTestIterator.readWithIterator(INPUT_FILE_PATH_2);
		endTime = System.nanoTime();
		logger.info("LinkedList + iterator: Reading the text completed in " + ((float)(endTime - startTime)) / 1000000 + " nanoseconds\n");
		
		System.out.println("----AL INDEX------------------------");
		ArrayListTestIndex.print();
		System.out.println("------------------------------------");
		System.out.println();
		System.out.println("----AL ITERATOR---------------------");
		ArrayListTestIterator.print();
		System.out.println("------------------------------------");
		System.out.println("----LL INDEX------------------------");
		LinkedListTestIndex.print();
		System.out.println("------------------------------------");
		System.out.println();
		System.out.println("----LL ITERATOR---------------------");
		LinkedListTestIterator.print();
		System.out.println("------------------------------------");
		
		
		startTime = System.nanoTime();
		ArrayListTestIndex.readWithIndex(INPUT_FILE_PATH);
		endTime = System.nanoTime();
		logger.info("ArrayList + index: Reading the text completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		startTime = System.nanoTime();
		ArrayListTestIterator.readWithIterator(INPUT_FILE_PATH);
		endTime = System.nanoTime();
		logger.info("ArrayList + iterator: Reading the text completed in " + ((float)(endTime - startTime)) / 1000000 + " nanoseconds\n");
		
		startTime = System.nanoTime();
		LinkedListTestIndex.readWithIndex(INPUT_FILE_PATH);
		endTime = System.nanoTime();
		logger.info("LinkedList + index: Reading the text completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		startTime = System.nanoTime();
		LinkedListTestIterator.readWithIterator(INPUT_FILE_PATH);
		endTime = System.nanoTime();
		logger.info("LinkedList + iterator: Reading the text completed in " + ((float)(endTime - startTime)) / 1000000 + " nanoseconds\n");
		
		System.out.println("----AL INDEX------------------------");
		ArrayListTestIndex.print();
		System.out.println("------------------------------------");
		System.out.println();
		System.out.println("----AL ITERATOR---------------------");
		ArrayListTestIterator.print();
		System.out.println("------------------------------------");
		System.out.println("----LL INDEX------------------------");
		LinkedListTestIndex.print();
		System.out.println("------------------------------------");
		System.out.println();
		System.out.println("----LL ITERATOR---------------------");
		LinkedListTestIterator.print();
		System.out.println("------------------------------------");
		
		
		
		
		
		startTime = System.nanoTime();
		findIndex = ArrayListTestIndex.findWithIndex("Tomorrow");
		endTime = System.nanoTime();
		logger.info("ArrayList + index: Finding the index of word \"Tomorrow\" completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		startTime = System.nanoTime();
		findIndex = ArrayListTestIterator.findWithIterator("Tomorrow");
		endTime = System.nanoTime();
		logger.info("ArrayList + iterator: Finding the index of word \"Tomorrow\" completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		logger.info("Finding the index of word \"Tomorrow\" using indexes...");
		startTime = System.nanoTime();
		findIndex = LinkedListTestIndex.findWithIndex("Tomorrow");
		endTime = System.nanoTime();
		logger.info("LinkedList + index: Finding the index of word \"Tomorrow\" completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		logger.info("Finding the index of word \"Tomorrow\" using iterators...");
		startTime = System.nanoTime();
		findIndex = LinkedListTestIterator.findWithIterator("Tomorrow");
		endTime = System.nanoTime();
		logger.info("LinkedList + iterator: Finding the index of word \"Tomorrow\" completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		
		
		
		startTime = System.nanoTime();
		ArrayListTestIndex.addWithIndex(findIndex, "[Chorus]\n");
		endTime = System.nanoTime();
		logger.info("ArrayList + index: Inserting word \"[Chorus]\" on top of the found word completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		startTime = System.nanoTime();
		ArrayListTestIterator.addWithIterator(findIndex, "[Chorus]\n");
		endTime = System.nanoTime();
		logger.info("ArrayList + iterator: Inserting word \"[Chorus]\" on top of the found word completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		startTime = System.nanoTime();
		LinkedListTestIndex.addWithIndex(findIndex, "[Chorus]\n");
		endTime = System.nanoTime();
		logger.info("LinkedList + index: Inserting word \"[Chorus]\" on top of the found word completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		startTime = System.nanoTime();
		LinkedListTestIterator.addWithIterator(findIndex, "[Chorus]\n");
		endTime = System.nanoTime();
		logger.info("LinkedList + iterator: Inserting word \"[Chorus]\" on top of the found word completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		System.out.println("----AL INDEX------------------------");
		ArrayListTestIndex.print();
		System.out.println("------------------------------------");
		System.out.println();
		System.out.println("----AL ITERATOR---------------------");
		ArrayListTestIterator.print();
		System.out.println("------------------------------------");
		System.out.println("----LL INDEX------------------------");
		LinkedListTestIndex.print();
		System.out.println("------------------------------------");
		System.out.println();
		System.out.println("----LL ITERATOR---------------------");
		LinkedListTestIterator.print();
		System.out.println("------------------------------------");
		
		startTime = System.nanoTime();
		ArrayListTestIndex.findAndReplaceWithIndex("???", SongVerse);
		endTime = System.nanoTime();
		logger.info("ArrayList + index: Replacing \"???\" with the verse of the song completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		startTime = System.nanoTime();
		ArrayListTestIterator.findAndReplaceWithIterator("???", SongVerse);
		endTime = System.nanoTime();
		logger.info("ArrayList + iterator: Replacing \"???\" with the verse of the song completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		startTime = System.nanoTime();
		LinkedListTestIndex.findAndReplaceWithIndex("???", SongVerse);
		endTime = System.nanoTime();
		logger.info("LinkedList + index: Replacing \"???\" with the verse of the song completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		startTime = System.nanoTime();
		LinkedListTestIterator.findAndReplaceWithIterator("???", SongVerse);
		endTime = System.nanoTime();
		logger.info("LinkedList + iterator: Replacing \"???\" with the verse of the song completed in " + ((float)(endTime - startTime)) / 1000000 + " miliseconds\n");
		
		System.out.println("----AL INDEX------------------------");
		ArrayListTestIndex.print();
		System.out.println("------------------------------------");
		System.out.println();
		System.out.println("----AL ITERATOR---------------------");
		ArrayListTestIterator.print();
		System.out.println("------------------------------------");
		System.out.println("----LL INDEX------------------------");
		LinkedListTestIndex.print();
		System.out.println("------------------------------------");
		System.out.println();
		System.out.println("----LL ITERATOR---------------------");
		LinkedListTestIterator.print();
		System.out.println("------------------------------------");
	}
}
