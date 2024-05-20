#include <iostream>
#include "pch.h"
#include "../Project2/SmsSender.cpp"

class TestableSmsSender : public SmsSender {
public:
	void send(Schedule* schedule) override {
		std::cout << "�׽�Ʈ�� SmsSender class�� send �޼��� �����" << std::endl;
		sendMethodIsCalled = true;
	}

	bool isSendMethodIsCalled() {
		return sendMethodIsCalled;
	}

private:
	bool sendMethodIsCalled;
};