#include "antra.hpp"


class A{
public:
	static int a;
	static int fn(){}
};

class B : public A {};

class C {
	void test(){
		A::a = 4;
	}
};

class D {
	T t;
	void test(){
		if(A::fn());
	}
};



int main(){
	return 0;
}
