#ifndef ZTC__Include__ZSingleton_hpp
#define ZTC__Include__ZSingleton_hpp

#include "ZUncopy.hpp"

template <typename Type>
class ZSingleton : public ZUncopy
{
public:
	static Type & getInstance()
	{
		static Type obj;
		m_interiorCreator.doNothing();
		return obj;
	}	
private:
	struct InteriorCreator
	{
		InteriorCreator()
		{
			ZSingleton<Type>::getInstance();
		}
		void doNothing(){}
	};
	
	static InteriorCreator m_interiorCreator;
};

template <typename Type>
typename ZSingleton<Type>::InteriorCreator ZSingleton<Type>::m_interiorCreator;

#endif //ZTC__Include__ZSingleton_hpp