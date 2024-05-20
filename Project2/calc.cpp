class Calc {
public:
	virtual int getValue() {
		return 0;
	}
	virtual int getSum(int a, int b) {
		return a + b;
	}
};

class SUT {
public:
	SUT(Calc* calc) {
		this->calc = calc;
	}
	void go() {
		calc->getSum(1, 2);
		calc->getSum(1, 2);
		calc->getSum(1, 2);
	}
private:
	Calc* calc;
};




