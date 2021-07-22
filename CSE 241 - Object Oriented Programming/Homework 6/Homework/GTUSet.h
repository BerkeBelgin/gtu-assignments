#ifndef GTU_SET_H
#define GTU_SET_H
#include "GTUContainer.h"

namespace gtu{
	template<class T>
	class GTUSet : public GTUContainer<T>{
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
