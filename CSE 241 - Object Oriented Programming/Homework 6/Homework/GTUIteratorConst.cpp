#include "GTUIteratorConst.h"

namespace gtu{
	template<class T>
	GTUIteratorConst<T>::GTUIteratorConst(){
		this->p = nullptr;
	}
	
	template<class T>
	GTUIteratorConst<T>::GTUIteratorConst(T *p){
		this->p = p;
	}
	
	template<class T>
	T& GTUIteratorConst<T>::operator *() const{
		return *p;
	}

	template<class T>
	T* GTUIteratorConst<T>::operator ->() const{
		return p;
	}

	template<class T>
	GTUIteratorConst<T>& GTUIteratorConst<T>::operator ++(){
		p++;
		return *this;
	}

	template<class T>
	GTUIteratorConst<T> GTUIteratorConst<T>::operator ++(int i){
		GTUIteratorConst<T> temp = *this;
		p++;
		return temp;
	}

	template<class T>
	GTUIteratorConst<T>& GTUIteratorConst<T>::operator --(){
		p--;
		return *this;
	}

	template<class T>
	GTUIteratorConst<T> GTUIteratorConst<T>::operator --(int i){
		GTUIteratorConst<T> temp = *this;
		p--;
		return temp;
	}

	template<class T>
	void GTUIteratorConst<T>::operator =(const GTUIteratorConst<T> &object){
		p = object.p;
	}

	template<class T>
	bool GTUIteratorConst<T>::operator ==(const GTUIteratorConst<T> &object) const{
		return this->p == object.p;
	}
}
