// Partterns.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//#define FUNCTION_POITER
#ifdef FUNCTION_POITER
template<typename arrayType,typename func>
void FillArray(arrayType *arr, size_t arrSize, func fc)
{
	for (size_t i = 0; i < arrSize; i++)
	{
		arr[i] = fc();
	}
}

class FunctionClass
{
public:
	FunctionClass()
	{
	}

	~FunctionClass()
	{
	}
	int const operator()()const
	{
		return rand();
	}
private:

};
template<typename arrayType>
void PrintArray(arrayType *arr, size_t size)
{
	cout << "Array contains the following elements:" << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl << endl;
}
int main()
{
	int intArray[10];
	FillArray(intArray, 10, FunctionClass());
	PrintArray(intArray, 10);
	getchar();
	return 0;
}
#endif // FUNCTION_POITER
//#define COMMAND_DEGIGN_PARTERN
#ifdef COMMAND_DEGIGN_PARTERN
//COmman interface for commands must implement pure virtual function Execute
class ICommand
{
public:
	virtual void Execute() = 0;
};
// The TV
class Television
{
public:
	Television():volume(0),chanel(0)
	{
	}

	~Television()
	{
	}
	void turnOn()
	{
		cout << "The television is on " << endl;
	}
	void turnOFF()
	{
		cout << "The television is off " << endl;
	}
	void volumeUp()
	{
		cout << "Turn volume up lever is " << ++this->volume << endl;
	}
	void volumeDown()
	{
		cout << "Turn volume down lever is " << --this->volume << endl;
	}
	void chanelUP()
	{
		cout << "Turn chanel up lever is " << ++this->chanel << endl;
	}
	void chanelDown()
	{
		cout << "Turn chanel down lever is " << --this->chanel << endl;
	}
private:
	int volume;
	int chanel;
};
template<class T>
class TVCommand:public ICommand
{
public:
	TVCommand(T &obj,void (T::*func)()):obj(obj),func(func)
	{
	}

	~TVCommand()
	{
	}
	virtual void Execute()
	{
		(obj.*func)();
	}
private:
	T & obj;
	void (T::*func)();
};
class ITVRemov{};
class TVRemove:public ITVRemov
{
public:
	TVRemove(ICommand & tvOnCommad,
		ICommand & tvOffCommad,
		ICommand & chanelUpCommand,
		ICommand & chanelDownCommad,
		ICommand & volumeUpCommad,
		ICommand & voLumeDownCommand) :
		tvOnCommand(tvOnCommad),
		tvOffCommand(tvOffCommad),
		chanelDownCommand(chanelDownCommad),
		chanelUpCommand(chanelUpCommand),
		volumeDownCommand(voLumeDownCommand),
		volumeUpCommand(volumeUpCommad)
	{}

	~TVRemove()
	{
	}
	virtual void tvOn()
	{
		this->tvOffCommand.Execute();
	}
	void tvOff()
	{
		this->tvOffCommand.Execute();
	}
	void chanelDown()
	{
		this->chanelUpCommand.Execute();
	}
	void chanelUp()
	{
		this->chanelUpCommand.Execute();
	}
	void volumeUp()
	{
		this->volumeUpCommand.Execute();
	}
	void volumeDown()
	{
		this->volumeDownCommand.Execute();
	}
private:
	ICommand & tvOnCommand;
	ICommand & tvOffCommand;
	ICommand & chanelUpCommand;
	ICommand & chanelDownCommand;
	ICommand & volumeUpCommand;
	ICommand & volumeDownCommand;
};
class DerTVRemove:virtual public TVRemove
{
public:
	DerTVRemove(ICommand & tvOnCommad,
		ICommand & tvOffCommad,
		ICommand & chanelUpCommand,
		ICommand & chanelDownCommad,
		ICommand & volumeUpCommad,
		ICommand & voLumeDownCommand):
		TVRemove( tvOnCommad,
			tvOffCommad,
			chanelUpCommand,
			chanelDownCommad,
			volumeUpCommad,
			voLumeDownCommand)
	{}
	~DerTVRemove() {}
	virtual void tvOn()
	{
		cout << "deriver class"<<endl;
		TVRemove::tvOn();
	}
private:

};
int main()
{
	Television myTv;
	TVCommand<Television> tvOn(myTv, &Television::turnOn);
	TVCommand<Television> tvOff(myTv, &Television::turnOFF);
	TVCommand<Television> chDwnCmd(myTv, &Television::chanelDown);
	TVCommand<Television> chUpCmd(myTv, &Television::chanelUP);
	TVCommand<Television> volUpCmd(myTv, &Television::volumeUp);
	TVCommand<Television> volDowCmd(myTv, &Television::volumeDown);
	TVRemove remove(tvOn, tvOff, chUpCmd, chDwnCmd, volUpCmd, volDowCmd);
	remove.tvOn();
	remove.chanelUp();
	remove.chanelDown();
	remove.volumeUp();
	remove.volumeDown();
	remove.tvOff();
	void (TVRemove::*func)() = &TVRemove::tvOn;
	(remove.*func)();
	DerTVRemove irem(tvOn, tvOff, chUpCmd, chDwnCmd, volUpCmd, volDowCmd);
	(irem.*func)();
	void (DerTVRemove::*funv)() = &DerTVRemove::chanelDown;
	(irem.*funv)();
	getchar();
	return 0;
}
#endif // COMMAND_DEGIGN_PARTERN
//#define MIXIN_CLASSES
#ifdef MIXIN_CLASSES
class A
{
public:
	A()
	{
	}
	void PrintName()
	{
		cout << "A\n";
	}
	~A()
	{
	}

private:

};
template<class classType>
class B :public classType
{
public:
	void PrintName()
	{
		cout << "Class B call class A" << endl;
		classType::PrintName();
	}
};
template<class classType>
class C :public classType
{
public:
	void PrintName()
	{
		cout << "Class C call class V" << endl;
		classType::PrintName();
	}
};
int main()
{
	C<B<A>> myMixn;
	myMixn.PrintName();
	A *poiter = dynamic_cast<A*>(&myMixn);
	if (poiter)
	{
		cout << "dinamic cast complete succefully" << endl;
		poiter->PrintName();
	}
	cout << typeid(myMixn).name() << "  " << typeid(poiter).name() << endl;
	getchar();
	return 0;
}
#endif // MIXIN_CLASSES
//#define ADAPTER_PARTERN
//#define ADATER_PARTERN_OBJ
#ifdef ADATER_PARTERN_OBJ
#ifndef ADAPTER_PARTERN
#define ADAPTER_PARTERN
#endif
#endif // ADATER_PARTERN_OBJ

#ifdef ADAPTER_PARTERN
class VendingMachine1
{
public:
	VendingMachine1():name("Vending machine 1"),solItems(5)
	{}
	string &GetName() { return this->name; }
	int &GetSolItems() { return this->solItems; }
private:
	string name;
	int solItems;
};

class VendingMachine2
{
public:
	VendingMachine2() :name("Vending machine 2"), solItems(50)
	{}
	string &ReadName() { return this->name; }
	int &ReadSolItems() { return this->solItems; }
private:
	string name;
	int solItems;
};

class VendingMachine3
{
public:
	VendingMachine3() :name("Vending machine 3"), solItems(555)
	{}
	string &TakeName() { return this->name; }
	int &TakeSolItems() { return this->solItems; }
private:
	string name;
	int solItems;
};
class Imachine
{
public:
	virtual ~Imachine() {};
	virtual vector<string> &GetNames() = 0;
	virtual vector<int> &GetSolItems() = 0;
};

class Machine :protected virtual Imachine, protected virtual VendingMachine1,
	protected virtual VendingMachine2, protected  virtual VendingMachine3
{
public:
	virtual vector<string> &GetNames()
	{
		names.clear();
		names.push_back(VendingMachine1::GetName());
		names.push_back(VendingMachine2::ReadName());
		names.push_back(VendingMachine3::TakeName());
		return names;
	}
	virtual vector<int> &GetSolItems()
	{
		solItems.clear();
		solItems.push_back(VendingMachine1::GetSolItems());
		solItems.push_back(VendingMachine2::ReadSolItems());
		solItems.push_back(VendingMachine3::TakeSolItems());
		return solItems;
	}
private:
	vector<string> names;
	vector<int> solItems;
};
class WrapObj: virtual public Imachine
{
public:
	virtual vector<string> &GetNames()
	{
		names.clear();
		names.push_back(this->vd1.GetName());
		names.push_back(this->vd2.ReadName());
		names.push_back(this->vd3.TakeName());
		return names;
	}
	virtual vector<int> &GetSolItems()
	{
		solItems.clear();
		solItems.push_back(this->vd1.GetSolItems());
		solItems.push_back(this->vd2.ReadSolItems());
		solItems.push_back(this->vd3.TakeSolItems());
		return solItems;
	}
private:
	vector<string> names;
	vector<int> solItems;
	VendingMachine1 vd1;
	VendingMachine2 vd2;
	VendingMachine3 vd3;
};
int main()
{
	//Machine machine;
	WrapObj machine;
	vector<string> names = machine.GetNames();
	vector<int> solItems = machine.GetSolItems();
	vector<string>::iterator it = names.begin();
	for (vector<int>::iterator i = solItems.begin(); i < solItems.end(); i++)
	{
		cout << "Name: " << *it++ << " Items: " << *i << endl;
		
	}
	getchar();
	return 0;
}
#endif // ADAPTER_PARTERN
//#define SINGLETON
#ifdef SINGLETON
class Singleton
{
public:
	static Singleton *GetInstance()
	{
		if (!instance)
		{
			instance = new Singleton;
		}
		return instance;
	}
	void execute()
	{
		cout << " Hello from unique singleton" << endl;
	}
	~Singleton()
	{
	}
	void Try(int&& a)
	{
		cout << "value printting: " <<a<< endl;
	}
private:
	Singleton(){}
	Singleton(Singleton&){}
	Singleton &operator=(Singleton&){}
	static Singleton *instance;
};
Singleton* Singleton::instance = nullptr;
enum class Abc: int{one, two, three, fouth,five};
class Iterator
{
public:
	Iterator(string* poiter):poiter((char*)poiter){}
	Iterator(char* poiter):poiter(poiter){}
	void operator++() { ++poiter;}
	void operator++(int) { poiter++;}
	char& operator*() { return *(this->poiter); }
	char& operator&() { return *(this->poiter); }
	char& operator[](int i) { return poiter[i]; }
	bool operator==(Iterator& b) { return this->poiter == b.poiter; }
	bool operator!=(Iterator& b) { return this->poiter != b.poiter; }
private:
	char* poiter;
};
class Str
{
public:
	Str()=default;
	Str( const char* str):str(str){}
	~Str();
	string & getStr() { return this->str; }
	void setStr(const char* str)const
	{
		string a;
		a = str;
		a = "2334";
	}
	Iterator begin() { return &str; }
	Iterator end() { string* pt = &str; pt += str.length() - 1; return pt; }
private:
	string str;
};

Str::~Str()
{
}
struct MyStruct
{
	int a;
	char b;
	double c;
	string d;
};
template<class... Arg> double Sum(Arg... a)
{
	double result = 0;
	for (auto i : { a... })
	{
		result += i;
	}
	return result;
}
union Sf
{
	int a;
	char b;
};
void (*Event)(const int a) {};
void EventHandler(const int a) { cout << "Event Hander Run" << a<< endl; }
#define TYPEDEF
TYPEDEF void think() TYPEDEF
{
	return;
}
template <bool T> void Print() { cout << T <<endl; }
#include <thread>
int main()
{
	int msx = sizeof(double);
	Singleton*a= Singleton::GetInstance();
	a->execute();
	a->Try(4);
	Abc abc = Abc::one;
	Str str[] = { "Hello","How are you","What's up","How's it goin" };
	cout << "address of a:" << a <<" "<<&a<< endl;
	Str *newStr = new Str;
	delete newStr;
	new(newStr) Str();
	newStr->~Str();
	Str sstr;
	Str *dsstr = &sstr;
	dsstr->getStr();
	for (auto &i : str)
	{
		cout << i.getStr() << endl;
	}
	auto sss = str[0];
	string name = typeid(sss).name();
	/*for (auto i : sss)
	{
		cout << i << endl;
	}*/
	char temp[] = "Hello";
	const char* hx = "jjjj";
	char he[] = {'h','b'};
	int ind[] = { 1,2 };
	char* ge = he;
	cout <<"value:"<< ge << endl;
	int intArr[] = { 1,4,7,3,68,34,12,44,59 };
	Iterator t1(temp);
	Print<false>();
	Event = &EventHandler;
	Event(2);
	for (size_t i = 0; i < 5; i++)
	{
		cout << (*t1)<< endl;
		t1++;
	}
	MyStruct my = { 2,'d',6,"hellow" };
	my.a;
	double sum = Sum(2, 3, 5, 7);
	getchar();
	return 0;
}
#endif // SINGLETON
//#define NESTED
#ifdef NESTED
class Enclosing
{
	class Nested
	{
	public:
		Nested():var1(rand()),var2("Hello from nested")
		{
		}

		~Nested()
		{
		}
		void PrintNested(Enclosing *enc)
		{
			cout << "Enclosing value is " << enc->enclosingIn << endl;
			cout << "Nested val1 is: " << this->var1 << " Val2 is: " << this->var2 << endl;
		}
	private:
		int var1;
		string var2;
	};

public:
	Enclosing():nested(new Nested),enclosingIn(rand())
	{
	}

	~Enclosing()
	{
		if (nested) delete nested;
	}
	void Print()
	{
		nested->PrintNested(this);
	}
private:
	int enclosingIn;
	Nested *nested;
};

int main()
{
	Enclosing enc;
	enc.Print();
	getchar();
	return 0;
}
#endif // NESTED
//#define PROXY_PARTEN
#ifdef PROXY_PARTEN
class EmbeddedInterface
{
public:
	virtual string &GetMachineName() = 0;
	virtual int GetNumberProcesses() = 0;
	virtual void SetProcessLevel(int level) = 0;
	virtual int &GetProcessLevel() = 0;
};
class EmbeddedConcrete:public EmbeddedInterface
{
public:
	EmbeddedConcrete()
	{
	}

	~EmbeddedConcrete()
	{
	}
	virtual string &GetMachineName()
	{
		return name;
	}
	virtual int GetNumberProcesses()
	{
		return (rand() % this->prosessLevel);
	}
	virtual void SetProcessLevel(int level)
	{
		this->prosessLevel = level;
	}
	virtual int &GetProcessLevel()
	{
		return this->prosessLevel;
	}
private:
	string name = "XHTRV150";
	int prosessLevel = 5;
};
class EmbeddedProxy : public EmbeddedInterface
{
public:
	EmbeddedProxy():ec(nullptr)
	{
	}

	~EmbeddedProxy()
	{
	}
	virtual string &GetMachineName()
	{
		return this->GetembeddedObj()->GetMachineName();
	}
	virtual int GetNumberProcesses()
	{
		return this->GetembeddedObj()->GetNumberProcesses();
	}
	virtual void SetProcessLevel(int level)
	{
		if (level >= 0 && level <= 100)
		{
			this->GetembeddedObj()->SetProcessLevel(level);
		}
	}
	virtual int &GetProcessLevel()
	{
		return this->GetembeddedObj()->GetProcessLevel();
	}
private:
	EmbeddedConcrete * ec;
	EmbeddedConcrete *GetembeddedObj()
	{
		if (!ec) ec = new EmbeddedConcrete;
		return ec;
	}
};

int main()
{
	EmbeddedProxy ep;
	cout << "The embedded machine name is: " << ep.GetMachineName() << endl;
	cout << "The embedded machine have: " << ep.GetNumberProcesses() << " processes running\n";
	cout << "The embedded machine current process level is" << ep.GetProcessLevel() << endl;
	ep.SetProcessLevel(100);
	cout << "The embedded machine current process level is" << ep.GetProcessLevel() << endl;
	ep.SetProcessLevel(1000);
	cout << "The embedded machine current process level is" << ep.GetProcessLevel() << endl;
	getchar();
	return 0;
}
#endif // PROXY_PARTEN
//#define NULL_OBJECT_PARTEN
#ifdef NULL_OBJECT_PARTEN
class HardwareInterface
{
public:
	virtual void doSomething() = 0;
	virtual vector<string> *GetUser() = 0;
};
class NullObject :public HardwareInterface
{
public:
	NullObject()
	{
		usr.push_back("");
	}

	~NullObject()
	{
	}
	virtual void doSomething()
	{

	}
	virtual vector<string> *GetUser()
	{
		return &this->usr;
	}
private:
	vector<string> usr;
};

int main()
{
	NullObject no;
	no.doSomething();
	vector<string> *ptr;
	ptr = no.GetUser();
	for (vector<string>::iterator i = ptr->begin(); i < ptr->end(); i++)
	{
		cout << " Vector string is not empty" << endl;;
	}
	getchar();
	return 0;
}
#endif // NULL_OBJECT_PARTEN
//#define SMART_POINTER
//#define LAZY_LOADING
#ifdef LAZY_LOADING
#ifndef SMART_POINTER
#define SMART_POINTER
#endif
#endif // LAZY_LOADING

#ifdef SMART_POINTER
class SomeObj
{
public:
	SomeObj():var1(rand()),var2("Hello world.")
	{
	}

	~SomeObj()
	{
		cout << "some Object decontructor called\n";
	}
	void PrintAttr()
	{
		cout << "var1 is: " << var1 << "var2 is: " << var2 << endl;
	}
	void SetVar2(string var2)
	{
		this->var2 = var2;
	}
private:
	int var1;
	string var2;
};
template<class Type>
class SmartPoiter
{
public:
	SmartPoiter(Type * obj):obj(obj)
	{
	}

	~SmartPoiter()
	{
		delete obj;
	}
	Type &operator*()
	{
		return *(this->obj);
	}
	Type*operator->()
	{
		return obj;
	}
private:
	Type * obj;
};
template<class Type>
class LazyObject
{
public:
	LazyObject():point(nullptr)
	{
	}

	~LazyObject()
	{
		if(point)
		delete point;
	}
	Type &operator*()
	{
		return *(this->GetPoint());
	}
	Type *operator->()
	{
		return this->GetPoint();
	}
private:
	Type * point;
	Type* GetPoint()
	{
		if (!point) point = new Type;
		return point;
	}
};


int main()
{
	SmartPoiter<SomeObj> point(new SomeObj);
	point->PrintAttr();
	point->SetVar2("how's it going");
	(*point).PrintAttr();
	vector<LazyObject<SomeObj>> vec;
	for (size_t i = 0; i < 10; i++)
	{
		vec.push_back(LazyObject<SomeObj>());
	}
	vector<LazyObject<SomeObj>>::iterator it = vec.begin();
	for (size_t i = 0; i < 5; i++)
	{
		(*it++)->PrintAttr();
	}
	getchar();
	return 0;
}
#endif // SMART_POINTER
#define EVENT
#ifdef EVENT
#include <list>
#include<memory>
class Events;
class IEvenHandler
{
public:
	IEvenHandler()
	{
	}

	~IEvenHandler()
	{
	}
	virtual void RegisterEvent() = 0;
	virtual void OncreateEvent()=0;
	unique_ptr<Events> &getEvent() { return event; }
private:
	static unique_ptr<Events> event;
};

class Events
{
public:
	Events()
	{
	}
	void OnRegister(IEvenHandler* event) { a.push_back(event); }
	~Events()
	{
		a.clear();
	}
	void implementEvent()
	{
		for (auto i : this->a)i->OncreateEvent();
	}
private:
	list<IEvenHandler*> a;
};
unique_ptr<Events> IEvenHandler::event(new Events);
class EvenHandler:virtual public IEvenHandler
{
public:
	EvenHandler()
	{
		this->RegisterEvent();
	}

	~EvenHandler()
	{
	}
	virtual void OncreateEvent()
	{
		cout << "implement Event" << endl;
	}
	void RegisterEvent() { this->getEvent()->OnRegister(this); }
private:

};

class Child1 :virtual public EvenHandler
{
public:
	Child1():EvenHandler()
	{
		//this->RegisterEvent();
	}
	virtual void OncreateEvent()
	{
		cout << "Chid1 implement Event" << endl;
	}
	//void RegisterEvent() { this->getEvent()->OnRegister(this); }
};
class Child2 :virtual public EvenHandler
{
public:
	Child2():EvenHandler()
	{
		//this->RegisterEvent();
	}
	virtual void OncreateEvent()
	{
		cout << "Chid2 implement Event" << endl;
	}
	//void RegisterEvent() { this->getEvent()->OnRegister(this); }
};
int main()
{
	Child1 child1; Child2 child2; Child1 ch;
	child1.getEvent()->implementEvent();
	return 0;
}
#endif // EVENT