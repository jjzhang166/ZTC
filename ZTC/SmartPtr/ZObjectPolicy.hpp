#ifndef ZTC_SMARTPTR_ZOBJECTPOLICY_HPP
#define ZTC_SMARTPTR_ZOBJECTPOLICY_HPP

namespace ZTC
{
	class ZStandarObjectPolicy
	{
	public:
		template<typename T>
		void Dispose(T *&object)
		{
			delete object;
		}
	};

	class ZStandarArrayPolicy
	{
	public:
		template<typename T>
		void Dispose(T *arry)
		{
			delete [] arry;
		}
	};
}
#endif //ZTC_SMARTPTR_ZOBJECTPOLICY_HPP