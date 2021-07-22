#ifndef GTU_ITERATOR_H
#define GTU_ITERATOR_H

namespace gtu{
	template<class T>
	class GTUIterator{
		private:
			T *p = nullptr;
		public:
			GTUIterator();
			GTUIterator(T *);
			T& operator * () const;
			T* operator -> () const;
			GTUIterator<T>& operator ++();
			GTUIterator<T> operator ++(int);
			GTUIterator<T>& operator --();
			GTUIterator<T> operator --(int);
			void operator = (const GTUIterator<T> &object);
			bool operator == (const GTUIterator<T> &object) const;
	};
}

#endif
