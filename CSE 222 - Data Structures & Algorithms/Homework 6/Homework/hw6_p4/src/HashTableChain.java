import java.util.Iterator;
import java.util.LinkedList;

/**
 * Hash table implementation using chaining.
 * @author Berke Belgin 171044065
 * @param <K> Key of the entries
 * @param <V> Value of the entries
 */
public class HashTableChain<K,V> implements KWHashMap<K,V> {
    /**
     * A table of references to linked lists of Entry<K, V>objects
     */
    private LinkedList<Entry<K,V>> [] table;
    /**
     * The number of keys (entries) in the table
     */
    private int numKeys;
    /**
     * The capacity of the table
     */
    private static final int CAPACITY = 101;
    /**
     * The maximum load factor
     */
    private static final double LOAD_THRESHOLD = 3.0;
    
    public HashTableChain(){
        table = new LinkedList[CAPACITY];
    }
    
    /**
     * Returns the size of the table
     */
    @Override
    public int size() {
        return numKeys;
    }
    
    /**
     * Method that returns the size of the table
     */
    @Override
    public boolean isEmpty() {
        return numKeys == 0;
    }
    
    /**
     * Method get for class HashTableChain.
     * @param key The key being sought
     * @return The value associated with this key if found; otherwise, null
     */
    @Override
    public V get(Object key) {
        int index = key.hashCode() % table.length;
        if(index < 0) index += table.length;
        if(table[index] == null) return null;
        for(Entry<K,V> nextItem : table[index])
            if(nextItem.getKey().equals(key)) return nextItem.getValue();
        return null;
    }
    
    /**
     * Method put for class HashTableChain.
     * post: This key-value pair is inserted in the table and numKeys is incremented. 
     * If the key is already in the table, its value is changed to the argument value
     * and numKeys is not changed.
     * @param key The key of item being inserted
     * @param value The value for this key
     * @return The old value associated with this key if found; otherwise, null
     */
    @Override
    public V put(K key, V value) {
        int index = key.hashCode() % table.length;
        if(index < 0) index += table.length;
        if(table[index] == null) table[index] = new LinkedList<Entry<K,V>>();
        for(Entry<K,V> nextItem : table[index]){
            if(nextItem.getKey().equals(key)){
                V oldVal = nextItem.value;
                nextItem.setValue(value);
                return oldVal;
            }
        }
        table[index].addFirst(new Entry<K,V>(key,value));
        numKeys++;
        if(numKeys > (LOAD_THRESHOLD * table.length)) rehash();
        return null;
    }
    
    /**
     * Removes the mapping for this key from this table if it is present.
     * Returns the previous value associated with specified key, or null if there was no mapping.
     */
    @Override
    public V remove(Object key) {
    	for(LinkedList<Entry<K, V>> kvEntryLL : table) {
    		if(kvEntryLL != null) {
    			Iterator<Entry<K, V>> iter = kvEntryLL.iterator();
        		while(iter.hasNext()) {
        			Entry<K, V> kvEntry = iter.next();
            		if(kvEntry != null && kvEntry.getValue().equals(key)) {
            			iter.remove();
            			numKeys--;
            			return kvEntry.getValue();
            		}
            	}
        	}
    	}
    	return null;
    }
    
    /**
     * Expands table size when loadFactor exceeds LOAD_THRESHOLD
     * @post: The size of the table is doubled and is an odd integer.
     * Each nondeleted entry from the original table is
     * reinserted into the expanded table.
     * The value of numKeys is reset to the number of items
     * actually inserted.
     */
    private void rehash() {
        LinkedList<Entry<K,V>> [] oldTable = table;
        table = new LinkedList[2 * oldTable.length + 1];
        numKeys = 0;
        for(LinkedList<Entry<K, V>> kvEntryLL : oldTable) {
        	if(kvEntryLL != null) {
        		for(Entry<K, V> kvEntry : kvEntryLL) {
            		if(kvEntry != null) put(kvEntry.getKey(), kvEntry.getValue());
            	}
        	}
        }
    }
    
    /**
     * Contains key-value pairs for a hash table.
     */
    private static class Entry<K,V>{
        /**
         * The key
         */
        private K key;
        /**
         * The value
         */
        private V value;
        
        /**
         * Creates a new key-value pair.
         * @param key The key
         * @param value The value
         */
        public Entry(K key, V value){
            this.key = key;
            this.value = value;
        }
        /**
         * Retrieves the key.
         * @return The key
         */
        public K getKey(){
            return key;
        }
        /**
         * Retrieves the value.
         * @return The value
         */
        public V getValue() {
            return value;
        }
        /**
         * Sets the value.
         * @param val The new value
         * @return The old value
         */
        public V setValue(V val) {
            V oldVal = value;
            this.value = val;
            return oldVal;
        }
    }
}
