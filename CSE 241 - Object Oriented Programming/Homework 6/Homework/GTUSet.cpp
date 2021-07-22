#include "GTUSet.h"

namespace gtu{
	template<class T>
	bool GTUSet<T>::empty(){
		if(this->length == 0)return true;
		else return false;
	}

	template<class T>
	int GTUSet<T>::size(){
		return this->length;
	}

	template<class T>
	int GTUSet<T>::max_size(){
		return this-> max_length;
	}

	template<class T>
	void GTUSet<T>::insert(GTUIterator<T> &iterator, const T &object){
		for(int i = 0; i < this->length; i++){
			if(this->array[i] == object)throw std::invalid_argument("The object you are trying to insert is already in the set.");
		}
		
		if(this->length == this->max_length)this->max_length += 10;
		this->length++;
		
		std::shared_ptr<T[]> temp(new T[this->max_length]);
		
		GTUIterator<T> new_iter(temp.get());
		if(this->length == 1){
			*new_iter = object;
			iterator = new_iter;
		} else{
			for(auto old_iter = this->begin(); !(old_iter == this->end()); old_iter++){
				if(old_iter == iterator){
					*new_iter = object;
					iterator = new_iter;
					new_iter++;
				}
				
				*new_iter = *old_iter;
				new_iter++;
			}
		}
		
		this->array = temp;
	}

	template<class T>
	void GTUSet<T>::earse(GTUIterator<T> &iterator){
		if(this->length > 0){
			this->length--;
			if(this->length == this->max_length - 10)this->max_length -= 10;
				
			if(this->length == 0){
				this->array = nullptr;
			}
			else{
				std::shared_ptr<T[]> temp(new T[this->max_length]);
				
				GTUIterator<T> new_iter(temp.get());
				for(auto old_iter = this->begin(); !(old_iter == this->end()); old_iter++){
					if(!(old_iter == iterator)){
						*new_iter = *old_iter;
						new_iter++;
					} else{
						iterator = new_iter;
					}
				}
				
				this->array = temp;
			}
		}
	}

	template<class T>
	void GTUSet<T>::clear(){
		this->array = nullptr;
		this->length = 0;
		this->max_length = 0;
	}

	template<class T>
	GTUIterator<T> GTUSet<T>::begin(){
		return this->array.get();
	}

	template<class T>
	GTUIterator<T> GTUSet<T>::end(){
		return this->array.get() + this->length;
	}
	
	template<class T>
	T GTUSet<T>::operator [](int index){
		return this->array[index];
	}
}
