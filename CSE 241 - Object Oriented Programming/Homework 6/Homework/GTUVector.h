#ifndef GTU_VECTOR_H
#define GTU_VECTOR_H
#include "GTUContainer.h"

namespace gtu{
	template<class T>
	class GTUVector : public GTUContainer<T>{
		public:
			bool empty();
			int size();
			int max_size();
			void insert(GTUIterator<T>&, const T&);
			void earse(GTUIterator<T>&);
			void clear();
			GTUIterator<T> begin();
			GTUIterator<T> end();
			T operator [](int);
	};
}
#endif
