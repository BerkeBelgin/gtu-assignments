
/**
 * Hash table implementation using open addressing.
 * @author Berke Belgin 171044065
 * @param <K> Key of the entries
 * @param <V> Value of the entries
 */
public class HashTableOpen<K,V> implements KWHashMap<K,V> {
	/**
     * The hash table array
     */
    private Entry<K,V> [] table;
    /**
     * The initial capacity
     */
    private static final int START_CAPACITY = 101;
    /**
     * The maximum load factor
     */
    private double LOAD_THRESHOLD = 0.75;
    /**
     * The number of keys in the table excluding keys that were deleted
     */
    private int numKeys;
    /**
     * The number of deleted keys
     */
    private int numDeletes;
    /**
     * A special object to indicate that an entry has been deleted
     */
    private final Entry<K,V> DELETED = new Entry<K,V>(null,null);
    
    public HashTableOpen(){
        table = new Entry[START_CAPACITY];
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
    public boolean isEmpty(){
        return numKeys == 0;
    }
    
    /**
     * Finds either the target key or first empty slot in the search chain using linear probing.
     * @pre: The table is not full.
     * @param key The key of the target object
     * @return The position of the target of the first empty slot if the target is not in the table
     */
    private int find(Object key){
        int index = key.hashCode() % table.length;
        if(index < 0) index += table.length;
        while ((table[index] != null) && (!key.equals(table[index].getKey()))){
            index++;
            if(index >= table.length) index = 0;
        }
        return index;
    }
    
    /**
     * Method for class HashTableOpen
     * @param key the key being sought
     * @return the value associated with this key if found; otherwise, null
     */
    @Override
    public V get(Object key) {
        int index = find(key);
        if(table[index] != null)  return table[index].getValue();
        else return null;
    }
    
    /**
     * Method put for class HashTableOpen.
     * post: This key-value pair is inserted in the table and numKeys is incremented.
     * If the key is already in the table, its value is changed to the argument value
     * and numKeys is not changed. If the LOAD_THRESHOLD is exceeded, the table is expanded.
     * @param key The key of item being inserted
     * @param value The value for this key
     * @return Old value associated with this key if found; otherwise, null
     */
    @Override
    public V put(K key, V value) {
        int index = find(key);
        if(table[index] == null){
            table[index] = new Entry<>(key,value);
            numKeys++;
            double loadFactor = (double) (numKeys + numDeletes) / table.length;
            if(loadFactor > LOAD_THRESHOLD) rehash();
            return null;
        }
        V oldVal = table[index].value;
        table[index].value = value;
        return oldVal;
    }
    
    /**
     * Removes the mapping for this key from this table if it is present.
     * Returns the previous value associated with specified key, or null if there was no mapping.
     */
    @Override
    public V remove(Object key) {
    	int index = find(key);
    	Entry<K, V> temp = table[index];
    	if(temp == null)return null;
    	table[index] = DELETED;
    	numDeletes++;
    	numKeys--;
    	return temp.getValue();
    }
    
    /**
     * Expands table size when loadFactor exceeds LOAD_THRESHOLD
     * @post: The size of the table is doubled and is an odd integer.
     * Each nondeleted entry from the original table is
     * reinserted into the expanded table.
     * The value of numKeys is reset to the number of items
     * actually inserted; numDeletes is reset to 0.
     */
    private void rehash(){
        Entry<K,V> [] oldTable = table;
        table = new Entry[2 * oldTable.length + 1];
        numKeys = 0;
        numDeletes = 0;
        for (Entry<K, V> kvEntry : oldTable) {
        	if ((kvEntry != null) && (kvEntry != DELETED)) put(kvEntry.getKey(), kvEntry.getValue());
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
