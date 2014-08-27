#ifndef ZTC_INCLUDE_ZDEFINE_H
#define ZTC_INCLUDE_ZDEFINE_H

//****IfThenElse******Begin
template<bool C, typename Ta, typename Tb>
class IfThenElse;

template<typename Ta, typename Tb>
class IfThenElse<true, Ta, Tb>
{
public:
	typedef Ta ResultT;
};

template<typename Ta, typename Tb>
class IfThenElse<false, Ta, Tb>
{
public:
	typedef Tb ResultT;
};
//****IfThenElse******End

#endif //ZTC_INCLUDE_ZDEFINE_H