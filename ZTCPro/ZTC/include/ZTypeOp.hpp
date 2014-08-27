#ifndef ZTC_INCLUDE_ZTYPEOP_HPP
#define ZTC_INCLUDE_ZTYPEOP_HPP

namespace ZTC
{
	template <typename T>
	class TypeOp 
	{            // primary template
	public:
		typedef T         ArgT;
		typedef T         BareT;
		typedef T const   ConstT;
		typedef T &       RefT;
		typedef T &       RefBareT;
		typedef T const & RefConstT;
	};
	/**** end of typeop1.hpp ****/

	// partial specialization for const
	/**********************************
	* typeop2.hpp:
	**********************************/
	template <typename T>
	class TypeOp <T const> 
	{  // partial specialization for const types
	public:
		typedef T const   ArgT;
		typedef T         BareT;
		typedef T const   ConstT;
		typedef T const & RefT;
		typedef T &       RefBareT;
		typedef T const & RefConstT;
	};
	/**** end of typeop2.hpp ****/

	// partial specialization for references
	/**********************************
	* typeop3.hpp:
	**********************************/
	template <typename T>
	class TypeOp <T&>
	{       // partial specialization for references
	public:
		typedef T &                         ArgT;
		typedef typename TypeOp<T>::BareT   BareT;
		typedef T const                     ConstT;
		typedef T &                         RefT;
		typedef typename TypeOp<T>::BareT & RefBareT;
		typedef T const &                   RefConstT;
	};
	/**** end of typeop3.hpp ****/

	// full specialization for void
	/**********************************
	* typeop4.hpp:
	**********************************/
	template<>
	class TypeOp <void> 
	{     // full specialization for void
	public:
		typedef void       ArgT;
		typedef void       BareT;
		typedef void const ConstT;
		typedef void       RefT;
		typedef void       RefBareT;
		typedef void       RefConstT;
	};
};

#endif //ZTC_INCLUDE_ZTYPEOP_HPP