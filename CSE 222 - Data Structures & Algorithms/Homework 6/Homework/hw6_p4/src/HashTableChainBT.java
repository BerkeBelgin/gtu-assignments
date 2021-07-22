
/**
 * Hash table implementation using chaining with Binary Search Trees.
 * @author Berke Belgin 171044065
 * @param <K> Key of the entries
 * @param <V> Value of the entries
 */
public class HashTableChainBT<K extends Comparable<K>,V> implements KWHashMap<K,V> {
    
	/**
	 * Table
	 */
	private BinarySearchTree<Entry<K,V>> [] table;
    /**
     * The number of keys
     */
    private int numKeys;
    /**
     * The capacity
     */
    private static final int CAPACITY = 101;
    /**
     * The maximum load factor
     */
    private static final double LOAD_THRESHOLD = 3.0;
    
    public HashTableChainBT(){
        table = new BinarySearchTree[CAPACITY];
    }
    
    /**
     * Returns the size of the table
     */
    @Override
    public int size() {
        return table.length;
    }
    
    /**
     * Method that returns the size of the table
     */
    @Override
    public boolean isEmpty() {
        return table.length == 0;
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
    	return table[index].find(new Entry<K,V>((K)key, null)).getValue();
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
        if(table[index] == null) table[index] = new BinarySearchTree<Entry<K,V>>();
        if(table[index].contains(new Entry<K,V>(key, value))) {
        	Entry<K,V> temp = table[index].find(new Entry<K,V>(key, value));
        	table[index].add(new Entry<K,V>(key, value));
        	return temp.getValue();
    	}
        table[index].add(new Entry<K,V>(key, value));
        numKeys++;
        if(numKeys > (LOAD_THRESHOLD * table.length)) rehash();
        return null;
    }
    
    private void rehash(){
    	BinarySearchTree<Entry<K,V>> [] oldTable = table;
        table = new BinarySearchTree[2 * oldTable.length + 1];
        numKeys = 0;
        for(BinarySearchTree<Entry<K, V>> kvEntryBT : oldTable) {
        	while(kvEntryBT.root != null) {
        		put(kvEntryBT.root.data.getKey(), kvEntryBT.root.data.getValue());
        		kvEntryBT.remove(kvEntryBT.root.data);
        	}
        }
    }
    
    @Override
    public V remove(Object key) {
    	int index = key.hashCode() % table.length;
        if(index < 0) index += table.length;
        if(table[index] == null) return null;
        if(table[index].contains(new Entry<K,V>((K)key, null))) {
        	Entry<K,V> temp = table[index].find(new Entry<K,V>((K)key, null));
        	table[index].remove(new Entry<K,V>((K)key, null));
        	numKeys--;
        	if(table[index].getData() == null)table[index] = null;
        	return temp.getValue();
        }
        return null;
    }
    
    /**
     * Contains key-value pairs for a hash table
     */
    private static class Entry<K extends Comparable<K>,V> implements Comparable<Entry<K,V>>{
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
         * Retrieves the key
         * @return The key
         */
        public K getKey(){
            return key;
        }
        
        /**
         * Retrieves the value
         * @return The value
         */
        public V getValue() {
            return value;
        }
        
        /**
         * Sets the value
         * @param val The new value
         * @return The old value
         */
        public V setValue(V val) {
            V oldVal = value;
            this.value = val;
            return oldVal;
        }

		@Override
		public int compareTo(Entry<K, V> o) {
			return key.compareTo(o.getKey());
		}
    }
}
