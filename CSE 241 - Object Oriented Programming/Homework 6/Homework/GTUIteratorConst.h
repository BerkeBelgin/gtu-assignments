#ifndef GTU_ITERATOR_CONST_H
#define GTU_ITERATOR_CONST_H

namespace gtu{
	template<class T>
	class GTUIteratorConst{
		private:
			const T *p = nullptr;
		public:
			GTUIteratorConst();
			GTUIteratorConst(T *);
			T& operator * () const;
			T* operator -> () const;
			GTUIteratorConst<T>& operator ++();
			GTUIteratorConst<T> operator ++(int);
			GTUIteratorConst<T>& operator --();
			GTUIteratorConst<T> operator --(int);
			void operator = (const GTUIteratorConst<T> &object);
			bool operator == (const GTUIteratorConst<T> &object) const;
	};
}

#endif

