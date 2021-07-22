public interface KWHashMap<K,V>{
    /**
     * Returns the value associated with the specified key.
     * Returns null if the key is not present.
     */
    V get(Object key);
    
    /**
     * Returns true if this table contains no key-value mappings.
     */
    boolean isEmpty();
    
    /**
     * Associates the specified value with the specified-key.
     * Returns te previous value associated with the specified key, or
     * null if there was no mapping for the key.
     */
    V put(K key , V value);
    
    /**
     * Removes the mapping for this key from this table if it is present (optional operation).
     * Returns the previous value associated with specified key, or null if there was no mapping.
     */
    V remove(Object key);
    
    /**
     * Returns the size of the table
     */
    int size();
}
