#include "GTUIterator.h"

namespace gtu{
	template<class T>
	GTUIterator<T>::GTUIterator(){
		this->p = nullptr;
	}
	
	template<class T>
	GTUIterator<T>::GTUIterator(T *p){
		this->p = p;
	}
	
	template<class T>
	T& GTUIterator<T>::operator *() const{
		return *p;
	}

	template<class T>
	T* GTUIterator<T>::operator ->() const{
		return p;
	}

	template<class T>
	GTUIterator<T>& GTUIterator<T>::operator ++(){
		p++;
		return *this;
	}

	template<class T>
	GTUIterator<T> GTUIterator<T>::operator ++(int i){
		GTUIterator<T> temp = *this;
		p++;
		return temp;
	}

	template<class T>
	GTUIterator<T>& GTUIterator<T>::operator --(){
		p--;
		return *this;
	}

	template<class T>
	GTUIterator<T> GTUIterator<T>::operator --(int i){
		GTUIterator<T> temp = *this;
		p--;
		return temp;
	}

	template<class T>
	void GTUIterator<T>::operator =(const GTUIterator<T> &object){
		p = object.p;
	}

	template<class T>
	bool GTUIterator<T>::operator ==(const GTUIterator<T> &object) const{
		return this->p == object.p;
	}
}
