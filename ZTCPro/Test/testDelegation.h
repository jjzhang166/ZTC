#include <iostream>
#include <string>
#include <vector>

#include "../ZTC/include/ZDelegationImp.hpp"
#include "../ZTC/include/ZEvent.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

using namespace ZTC;

/*
*	委托：调用者与执行者的解耦，对一系列的方法定义一个通用的调用规则
*	接口：对一系列的类定义一个规则
*
* 本测试文件旨在说明为什么需要用委托？考虑以下场景：
*	当原告需要委托律师打官司时，我们至少要定义两个类，原告类和律师类。
*	采用接口的形式见 --@接口形式
*	采用委托的形式见 --@委托形式
*
*	在考虑一个场景：如果原告张三想委托律师A打遗产官司，想委托B打离婚官司。接口形式和委托形式该如何实现？
*/


//--@ 接口形式
//原告
class Plaintiff
{
public:
	Plaintiff(string name) : m_name(name)
	{

	}
	string getName() const
	{
		return m_name;
	}
private:
	string m_name;
};
//律师
class Lawyer
{
public:
	~Lawyer(){}
	virtual void heritage(const Plaintiff&) = 0;  
	virtual void divorce(const Plaintiff&) = 0;
	//.........
};


class LawyerA : public Lawyer
{
public:
	virtual void heritage(const Plaintiff& who)
	{
		//TODO: add your code
		cout<<who.getName()<<" : LawyerA heritage!"<<endl;
	}

	virtual void divorce(const Plaintiff& who)
	{
		//TODO: add your code
		cout<<who.getName()<<" : LawyerA divorce!"<<endl;
	}
};

class LawyerD : public Lawyer
{
public:
	virtual void heritage(const Plaintiff& who)
	{
		//TODO: add your code
		cout<<who.getName()<<" : LawyerD heritage!"<<endl;
	}

	virtual void divorce(const Plaintiff& who)
	{
		//TODO: add your code
		cout<<who.getName()<<" : LawyerD divorce!"<<endl;
	}
};

//--@打官司
void engageInLawsuit()
{
	Plaintiff one("张三");

	//让律师A 打离婚官司
	Lawyer *pLawyer = new LawyerA();
	pLawyer->divorce(one);

	//让律师D 打遗产官司
	Lawyer *pLawyer0 = new LawyerD();
	pLawyer0->heritage(one);

	delete pLawyer;
	delete pLawyer0;
};
//-----@

//--@委托形式
class LawyerB
{
public:
	void heritage(Plaintiff who)
	{
		//TODO: add your code
		cout<<who.getName()<<" : LawyerB heritage!"<<endl;
	}

	void divorce(Plaintiff who)
	{
		//TODO: add your code
		cout<<who.getName()<<" : LawyerB divorce!"<<endl;
	}
};

class LawyerC
{
public:
	void divorce(Plaintiff who)
	{
		//TODO: add your code
		cout<<who.getName()<<" : LawyerC divorce!"<<endl;
	}
};
//--@打官司1

void engageFun(Plaintiff one)
{
	cout<<"engageFun!"<<endl;
}

void testFun0()
{
	cout<<"0"<<endl;
}

void testFun1(int)
{
	cout<<"1"<<endl;
}

void testFun2(int , int)
{
	cout<<"2"<<endl;
}

void testFun3(int, int, int)
{
	cout<<"3"<<endl;
}

void testFun4(int, int, int, int)
{
	cout<<"4"<<endl;
}

void engageInLawsuit1()
{
	Plaintiff one("李四");

	//让律师B 打遗产官司
	LawyerB lawyerB;
	ZDelegation1<LawyerB, void, Plaintiff> engageHeritage(&lawyerB, &LawyerB::heritage);
	ZDelegation1<LawyerB, void, Plaintiff> engageDiv(&lawyerB, &LawyerB::divorce);

	//让律师C 打离婚官司
	LawyerC lawyerC;
	ZDelegation1<LawyerC, void, Plaintiff> engageDivorce(&lawyerC, &LawyerC::divorce);

	ZDelegation1<void, void, Plaintiff> fun(engageFun);

	vector<ZDelegationBase1<void, Plaintiff> *> engage;
	engage.push_back(&engageHeritage);
	engage.push_back(&engageDiv);
	engage.push_back(&engageDivorce);
	engage.push_back(&fun);

	for(vector<ZDelegationBase1<void, Plaintiff> * >::iterator iter = engage.begin(); iter != engage.end(); ++iter)
	{
		(*iter)->invoke(one);
	}
	
	//-----委托，有点信号槽的味道
	cout<<"----------------------------------"<<endl;
	LawyerB lawyerQ;
	ZDelegationImp1<void, Plaintiff> delegationImp; //一个信号
	delegationImp.pushBack(&lawyerB, &LawyerB::heritage); //槽
	delegationImp.pushBack(&lawyerB, &LawyerB::divorce);//槽
	delegationImp.pushBack(&lawyerC, &LawyerC::divorce);//槽
	delegationImp.pushBack(engageFun);//槽
	delegationImp.pushBack(&lawyerQ, &LawyerB::divorce);//槽
	delegationImp.invoke(one); //触发信号
	cout<<"----------------------------------"<<endl;
	delegationImp.remove(&lawyerB, &LawyerB::divorce);
	delegationImp.remove(engageFun);
	delegationImp.invoke(one);

	cout<<"------------事件begin---------------------"<<endl;
	ZEvent1<void, Plaintiff> eventImp;
	bool bo = eventImp.connect(&lawyerB, &LawyerB::heritage);
	eventImp.connect(engageFun);
	eventImp(one);
	cout<<eventImp.numSlots()<<endl;
	if(bo)
		cout<<"Yes"<<endl;
	//eventImp.disconnect(&lawyerB, &LawyerB::heritage);
	//eventImp.disconnect(engageFun);
	eventImp.disconnectAllSlots();
	eventImp(one);
	cout<<eventImp.numSlots()<<endl;
	cout<<"---------------事件end--------------------"<<endl;

	ZDelegationImp0<void> imp0;
	imp0.pushBack(testFun0);
	imp0.invoke();

	ZDelegationImp1<void, int> imp1;
	imp1.pushBack(testFun1);
	imp1.invoke(1);

	ZDelegationImp2<void, int, int> imp2;
	imp2.pushBack(testFun2);
	imp2.invoke(1,1);

	ZDelegationImp3<void, int, int, int> imp3;
	imp3.pushBack(testFun3);
	imp3.invoke(1, 1, 1);

	ZDelegationImp4<void, int, int, int, int> imp4;
	imp4.pushBack(testFun4);
	imp4.invoke(1, 1, 1, 1);
}


