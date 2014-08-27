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
*	ί�У���������ִ���ߵĽ����һϵ�еķ�������һ��ͨ�õĵ��ù���
*	�ӿڣ���һϵ�е��ඨ��һ������
*
* �������ļ�ּ��˵��Ϊʲô��Ҫ��ί�У��������³�����
*	��ԭ����Ҫί����ʦ���˾ʱ����������Ҫ���������࣬ԭ�������ʦ�ࡣ
*	���ýӿڵ���ʽ�� --@�ӿ���ʽ
*	����ί�е���ʽ�� --@ί����ʽ
*
*	�ڿ���һ�����������ԭ��������ί����ʦA���Ų���˾����ί��B������˾���ӿ���ʽ��ί����ʽ�����ʵ�֣�
*/


//--@ �ӿ���ʽ
//ԭ��
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
//��ʦ
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

//--@���˾
void engageInLawsuit()
{
	Plaintiff one("����");

	//����ʦA ������˾
	Lawyer *pLawyer = new LawyerA();
	pLawyer->divorce(one);

	//����ʦD ���Ų���˾
	Lawyer *pLawyer0 = new LawyerD();
	pLawyer0->heritage(one);

	delete pLawyer;
	delete pLawyer0;
};
//-----@

//--@ί����ʽ
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
//--@���˾1

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
	Plaintiff one("����");

	//����ʦB ���Ų���˾
	LawyerB lawyerB;
	ZDelegation1<LawyerB, void, Plaintiff> engageHeritage(&lawyerB, &LawyerB::heritage);
	ZDelegation1<LawyerB, void, Plaintiff> engageDiv(&lawyerB, &LawyerB::divorce);

	//����ʦC ������˾
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
	
	//-----ί�У��е��źŲ۵�ζ��
	cout<<"----------------------------------"<<endl;
	LawyerB lawyerQ;
	ZDelegationImp1<void, Plaintiff> delegationImp; //һ���ź�
	delegationImp.pushBack(&lawyerB, &LawyerB::heritage); //��
	delegationImp.pushBack(&lawyerB, &LawyerB::divorce);//��
	delegationImp.pushBack(&lawyerC, &LawyerC::divorce);//��
	delegationImp.pushBack(engageFun);//��
	delegationImp.pushBack(&lawyerQ, &LawyerB::divorce);//��
	delegationImp.invoke(one); //�����ź�
	cout<<"----------------------------------"<<endl;
	delegationImp.remove(&lawyerB, &LawyerB::divorce);
	delegationImp.remove(engageFun);
	delegationImp.invoke(one);

	cout<<"------------�¼�begin---------------------"<<endl;
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
	cout<<"---------------�¼�end--------------------"<<endl;

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


