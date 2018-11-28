// Partterns.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <deque>
#include <mutex>
#include "Header.h"
using namespace std;
//#define FUNCTION_POITER
#ifdef FUNCTION_POITER
template<typename arrayType, typename func>
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
	Television() :volume(0), chanel(0)
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
class TVCommand :public ICommand
{
public:
	TVCommand(T &obj, void (T::*func)()) :obj(obj), func(func)
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
class ITVRemov {};
class TVRemove :public ITVRemov
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
class DerTVRemove :virtual public TVRemove
{
public:
	DerTVRemove(ICommand & tvOnCommad,
		ICommand & tvOffCommad,
		ICommand & chanelUpCommand,
		ICommand & chanelDownCommad,
		ICommand & volumeUpCommad,
		ICommand & voLumeDownCommand) :
		TVRemove(tvOnCommad,
			tvOffCommad,
			chanelUpCommand,
			chanelDownCommad,
			volumeUpCommad,
			voLumeDownCommand)
	{}
	~DerTVRemove() {}
	virtual void tvOn()
	{
		cout << "deriver class" << endl;
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
	VendingMachine1() :name("Vending machine 1"), solItems(5)
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
class WrapObj : virtual public Imachine
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
		cout << "value printting: " << a << endl;
	}
private:
	Singleton() {}
	Singleton(Singleton&) {}
	Singleton &operator=(Singleton&) {}
	static Singleton *instance;
};
Singleton* Singleton::instance = nullptr;
enum class Abc : int { one, two, three, fouth, five };
class Iterator
{
public:
	Iterator(string* poiter) :poiter((char*)poiter) {}
	Iterator(char* poiter) :poiter(poiter) {}
	void operator++() { ++poiter; }
	void operator++(int) { poiter++; }
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
	Str() = default;
	Str(const char* str) :str(str) {}
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
void(*Event)(const int a) {};
void EventHandler(const int a) { cout << "Event Hander Run" << a << endl; }
#define TYPEDEF
TYPEDEF void think() TYPEDEF
{
	return;
}
template <bool T> void Print() { cout << T << endl; }
#include <thread>
int main()
{
	int msx = sizeof(double);
	Singleton*a = Singleton::GetInstance();
	a->execute();
	a->Try(4);
	Abc abc = Abc::one;
	Str str[] = { "Hello","How are you","What's up","How's it goin" };
	cout << "address of a:" << a << " " << &a << endl;
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
	char he[] = { 'h','b' };
	int ind[] = { 1,2 };
	char* ge = he;
	cout << "value:" << ge << endl;
	int intArr[] = { 1,4,7,3,68,34,12,44,59 };
	Iterator t1(temp);
	Print<false>();
	Event = &EventHandler;
	Event(2);
	for (size_t i = 0; i < 5; i++)
	{
		cout << (*t1) << endl;
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
		Nested() :var1(rand()), var2("Hello from nested")
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
	Enclosing() :nested(new Nested), enclosingIn(rand())
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
class EmbeddedConcrete :public EmbeddedInterface
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
	EmbeddedProxy() :ec(nullptr)
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
	SomeObj() :var1(rand()), var2("Hello world.")
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
	SmartPoiter(Type * obj) :obj(obj)
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
	LazyObject() :point(nullptr)
	{
	}

	~LazyObject()
	{
		if (point)
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
//#define EVENT
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
	virtual void OncreateEvent() = 0;
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
class EvenHandler :virtual public IEvenHandler
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
	Child1() :EvenHandler()
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
	Child2() :EvenHandler()
	{
		//this->RegisterEvent();
	}
	virtual void OncreateEvent()
	{
		cout << "Chid2 implement Event" << endl;
	}
	//void RegisterEvent() { this->getEvent()->OnRegister(this); }
};
typedef enum class DCV
{
	AppMode = 0x006u,
	Dmcc = 0x0034u
};
typedef void(*event_)(int *t);
void print(int *t) { cout << "event running;" << (*t)++ << endl; }
int main()
{
	// Changing somethings from merging
	Child1 child1; Child2 child2; Child1 ch;
	child1.getEvent()->implementEvent();
	//new comment
	//change commit
	//New file adding
	int fg = static_cast<int>(DCV::AppMode);
	cout << fg << endl;
	event_ pr = print;
	std::thread t1(pr, &fg);
	t1.detach();
	cout << fg << std::strlen(t) << endl;
	return 1;
}
#endif // EVENT
//#define THREAD_MY
#ifdef THREAD_MY
#include<time.h>
#include<future>
#include<list>
#include <map>
#define ToString(a) #a
#define ToStrings(a,b) ToString(a##b)
#define Print(a) ("Value of:" + string(ToStrings(function:,a)) +"is :" + std::to_string(a))
#include<tuple>
class Th
{
public:
	Th()
	{
		dq.begin();
		this->f = this->p.get_future();
	}

	~Th()
	{
		dq.end();
		th.clear();
		//delete locker;
	}

	void init()
	{
		//locker = new unique_lock<mutex>(this->mu);
		fu = std::async(std::launch::async, [this] {output(std::ref(f)); });
		th.push_back(std::thread(&Th::input, this));
		//th.push_back(std::thread(&Th::output, this));

		//std::async(std::launch::async,output,std::ref(f));
		th[0].join();
		//th[1].join();
	}

	void input()
	{
		while (true)
		{
			//std::unique_lock<mutex> locker(mu);
			//locker.lock();
			cout << " enter a numble:" << endl;
			int t;
			cin >> t;
			if (t)
			{
				dq.push_front(t);
				//locker.unlock();
				//con.notify_all();
				this->p.set_value(1);
			}
			else {
				//locker.unlock();
				//con.notify_all();
				this->p.set_value(1);
				break;
			}
			//std::this_thread::sleep_for(chrono::milliseconds(10));
		}

	}

	void output(std::future<int> &f)
	{
		while (true)
		{
			//std::unique_lock<mutex> locker(mu);
			//locker.lock();
			//con.wait(locker);
			int pdq = f.get();
			if (dq.empty()) break;
			cout << " value a numble:" << dq.back() << endl;
			dq.pop_back();
			cout << dq.size() << endl;
			//locker.unlock();
			//this->time = clock();
			/*while (clock() - this->time < 30*CLOCKS_PER_SEC)
			{

			}*/

		}

	}
private:
	int t;
	deque<int> dq;
	std::mutex mu;
	std::condition_variable con;
	std::condition_variable any;
	std::vector<thread> th;
	std::promise<int> p;
	std::future<int> f;
	std::future<void> fu;
	clock_t time;
};
enum class k { ONE, TWO, THREE, FORE, FIVE };
typedef enum class k numner;
void print(numner &&a) { cout << (int)a << endl; }
void print(numner &a) { cout << (int)a << endl; }
void write(const int &&s) { cout << s << endl; }
class Test
{
public:
	typedef enum class TEMP : int16_t
	{
		ONE = 1000, TWO = 200, THREE = -3, FORE = 6, FIVE = -64, SIX = 1235
	};
	Test()
	{
		this->addALL();
	}
	bool isRange(const TEMP &val) { return std::find(tem.begin(), tem.end(), val) != tem.end(); }
	void add(const TEMP &&name, const int16_t &val) { if (this->isRange(name)) value[name] = val; }
	void add(const TEMP &name, const int16_t &val) { if (this->isRange(name)) value[name] = val; }
	const int16_t & read(const TEMP &name) { return this->value[name]; }
	void addALL() { for (auto i : tem) { value[i] = 5; } }
	~Test()
	{
	}
	const static list<TEMP> tem;
private:
	map<TEMP, int16_t> value;
};
const list<Test::TEMP> Test::tem = { TEMP::ONE, TEMP::TWO, TEMP::THREE, TEMP::FORE, TEMP::FIVE };
#define WEEKDAY \
X(MONDAY, "Monday", true) \
X(TUESDAY, "Tuesday", true) \
X(WEDNESDAY, "Wednesday", true) \
X(THURDAY, "Thurday", true) \
X(FRIDAY, "Friday", true) \
X(SATUDAY, "Satuday", false) \
X(SUNDAY, "Sunday", false)

#define X(day,name,isWeekday) day,
typedef enum class Weekday : int8_t
{
	WEEKDAY
};
#undef X
#define X(day,name,isWeekday) name,
const char * NameDay[] =
{
	WEEKDAY
};
#undef X
#define X(day,name,isWeekday) isWeekday,
bool weeday[] = { WEEKDAY };

class Poiter
{
public:
	Poiter()
	{
		a = nullptr;
	}
	void setA(const int &a) { this->a = &a; }
	int * getA()const { return const_cast<int *>(a); }
	~Poiter()
	{
	}

private:
	const int *a;
};

int main()
{
	list<numner> t = { numner::FIVE,k::FORE,k::THREE,k::ONE };
	map<numner, int> m;
	//Th t; t.init();
	for (auto i : t)
	{
		print(i);
		m[i] = (int)i;
	}
	for (auto i : t)
	{
		print((numner)m[i]);
	}
	/*try
	{
		while (true)
		{

		}
	}
	catch(...){}*/
	write(5);
	Test test; bool a6 = false, a7 = true;
	const Test::TEMP & tpm = Test::TEMP((a6 || a7) && !a7);
	const bool * tpmm = &a6;
	cout << (int)tpm << endl;
	getchar();
	for (size_t i = 0; i < 10000; i++)
	{
		int n = 0;
		for (auto &j : Test::tem)
		{
			test.add(j, i + (n++));
			test.add(Test::TEMP::SIX, i + (n++));
			test.add(Test::TEMP::ONE, -1000 - i);
		}
		//cout << i;
	}
	cout << endl;
	int value = 5;
	Poiter poiter;
	poiter.setA(value);
	int & variable = *(poiter.getA());
	variable = 7;
	cout << "value variable" << value << endl;
	for (const auto &j : Test::tem)
	{
		cout << test.read(j) << endl;
	}
	string sts = Print(test.read(Test::TEMP::ONE));
	cout << sts << endl;
	cout << ToStrings(Test::TEMP::FIVE, Test::TEMP::FORE) << endl;
	return 1;
}

#endif // THREAD_MY
#define R_VALUE
#ifdef R_VALUE
#include <functional>
#include <unordered_map>
#include <cstdarg>
#include <array>
#include <map>
using byte = unsigned char;

template< typename T > std::array< byte, sizeof(T) >  to_bytes(const T& object)
{
	std::array< byte, sizeof(T) > bytes;

	const byte* begin = reinterpret_cast<const byte*>(std::addressof(object));
	const byte* end = begin + sizeof(T);
	std::copy(begin, end, std::begin(bytes));

	return bytes;
}

template< typename T >
T& from_bytes(const std::array< byte, sizeof(T) >& bytes, T& object)
{
	// http://en.cppreference.com/w/cpp/types/is_trivially_copyable
	//static_assert(std::is_trivially_copyable<T>::value, "not a TriviallyCopyable type");

	byte* begin_object = reinterpret_cast<byte*>(std::addressof(object));
	std::copy(std::begin(bytes), std::end(bytes), begin_object);

	return object;
}
class Rvalue
{
public:
	Rvalue() = default;

	~Rvalue()
	{
	}
	typedef enum class TYPE :std::int8_t
	{
		ONE = 100,
		TWO = 28,
		THREE = 35
	};
	void determine(Rvalue::TYPE && type)
	{
		this->value = 100;
		switch (type)
		{
		case TYPE::ONE:
			this->set(TYPE::THREE);
			cout << "value" << endl;
			break;
		case TYPE::TWO:
			this->set(TYPE::TWO);
			break;
		case TYPE::THREE:
			this->set(TYPE::ONE);
			break;
		default:
			break;
		}

		
	}
	void set(Rvalue::TYPE && type)
	{
		this->type = type;
	}
	const TYPE &get()const { return this->type; }
	const int &getValue()const { return this->value; }
	const TYPE &get(const TYPE & value)const
	{
		switch (value)
		{
		case TYPE::ONE:
			return TYPE::ONE;
		case TYPE::TWO:
			return TYPE::TWO;
		case TYPE::THREE:
			return TYPE::THREE;
		default:
			break;
		}
	}
private:
	TYPE type=TYPE::ONE;
	int value=0;
};
using CallBack = std::function<void(Rvalue::TYPE &&)>;
void print1(Rvalue::TYPE && th) { cout << int(th) << endl; }
void(*temp)(Rvalue::TYPE && th);
template <class T>
class Controler
{
public:
	Controler(T & t, void (T::*exe)(Rvalue::TYPE &&)) :obj(t), exe(exe)
	{
	}

	void Exe()
	{
		(obj.*exe)(Rvalue::TYPE::THREE);
	}
	~Controler()
	{
	}

private:
	T & obj;
	void (T::*exe)(Rvalue::TYPE &&);
};

void Print_all(const char*var...)
{
	std::va_list args;
	va_start(args, var);
	while (*var != '\0')
	{

		if (*var == 'd') {
			int value = va_arg(args, int);
			cout << value << endl;
		}
		else if (*var == 'c') {
			int value1 = va_arg(args, int);
			cout << static_cast<char>(value1) << endl;
		}
		else if (*var == 'f') {
			float value2 = va_arg(args, double);
			cout << value2 << endl;
		}
		else if (*var == 'r') {
			double value3 = va_arg(args, double);
			cout << value3 << endl;
		}

		var++;
	}
	va_end(args);
}
extern int variable;
extern void updateExtern(TestExtern & x, int val);
int main()
{
	using namespace std::placeholders;
	Rvalue r;
	CallBack a = print1;
	Controler<Rvalue> ctl(r, &(Rvalue::determine));
	//	temp = r->determine;
	//	temp(Rvalue::TYPE::ONE);
	a(Rvalue::TYPE::TWO);
	ctl.Exe();
	cout << (int)r.get(Rvalue::TYPE::TWO) << endl;
	char * mb;
	cout <<"Value cast is:"<< (mb=reinterpret_cast<char*>(&r)) << endl;
	string st(mb); 
	char* cdt = const_cast<char*>(st.c_str());
	Rvalue *Pt = reinterpret_cast<Rvalue*>(cdt);
	cout << (int)r.get() << endl;
	cout << "Value cast is: "<<(int)Pt->get()<<"  "<<Pt->getValue() << endl;
	Pt = reinterpret_cast<Rvalue*>(mb);
	cout << "Value cast is: " << (int)Pt->get() << "  " << Pt->getValue() << endl;
	auto ccv = std::bind(print1, Rvalue::TYPE::ONE);
	ccv;
	Print_all("dfrcr", 20, 3.14, 1257.789, 'h', 145.67);
	string *newVar;
	try
	{
		std::array< byte, sizeof(r) > ngArray = to_bytes<Rvalue>(r);
		cout <<"Value" << ngArray.data() << endl;
		char singArry[sizeof(r)];
		for (register int i = 0; i < sizeof(r); i++)
		{
			singArry[i]= reinterpret_cast<char>(&(ngArray[i]));
		}
		cout << "Uvalue : " << singArry << endl;
		newVar = new string(singArry, sizeof(r));
		cout << "String value"<< newVar->c_str() << endl;
		const int size = newVar->size();
		const char* lvalue = newVar->c_str();
		cout << lvalue << endl;
		std::array< byte, sizeof(r) > cgArray;
		for (register int i = 0; i < std::strlen(lvalue); i++)
		{
			char c = (lvalue[i]);
			byte b = reinterpret_cast<byte>(&c);
			cgArray.at(i) = b;
		}
		Rvalue nR; nR = from_bytes(cgArray, nR);
		cout << "Value cast is: " << (int)nR.get() << "  " << nR.getValue() << endl;
	}
	catch (exception)
	{
		cout << "I don't known";
	}
	map<const char *, int> mp;
	vector<const char*> vt = { "one","two","three","fore" };
	int value1 = 0;
	for (auto i : vt)
	{
		mp[i] = value1++;
	}
	for (auto j: mp)
	{
		cout << j.first<<"  " << j.second << endl;
	}
	TestExtern testExtern;
	for (register int j = 0; j < 10; j++,updateExtern(testExtern,j))
	{
		cout << "extern value" << variable << endl;
	}
	getchar();
	return 1;
}
#endif // R_VALUE
