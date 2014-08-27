#ifndef ZTC__INCLUDE__ZSINGLE_HPP
#define ZTC__INCLUDE__ZSINGLE_HPP

namespace ZTC
{
	template <typename Type>
	class ZSingle
	{
	private:
		struct InteriorCreator
		{
			InteriorCreator()
			{
				ZSingle<Type>::getInstance();
			}
			void doNothing()
			{
			}
		};

		static InteriorCreator m_interiorCreator;
	public:
		static Type& getInstance()
		{
			static Type obj;
			m_interiorCreator.doNothing();
			return obj;
		}
		
	private:
		ZSingle();
		ZSingle(const ZSingle<Type> &other);
		ZSingle<Type> &operator=(const ZSingle<Type> &other);
		
	};

	template<typename Type>
	typename ZSingle<Type>::InteriorCreator  ZSingle<Type>::m_interiorCreator;
}

#endif //ZTC__INCLUDE__ZSINGLE_HPP
