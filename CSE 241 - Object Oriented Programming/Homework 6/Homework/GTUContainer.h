#ifndef GTU_CONTAINER_H
#define GTU_CONTAINER_H
#include <memory>
#include "GTUIterator.h"

namespace gtu{
	template<class T>
	class GTUContainer{
		protected:
			std::shared_ptr<T[]> array = nullptr;
			int length = 0;
			int max_length = 0;
		public:
			virtual bool empty() = 0;
			virtual int size() = 0;
			virtual int max_size() = 0;
			virtual void insert(GTUIterator<T>&, const T&) = 0;
			virtual void earse(GTUIterator<T>&) = 0;
			virtual void clear() = 0;
			virtual GTUIterator<T> begin() = 0;
			virtual GTUIterator<T> end() = 0;
	};
}

#endif
