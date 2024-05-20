#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <iostream>
#include "../Project2/calc.cpp"
#include "../Project2/BookingScheduler.cpp"

using namespace testing;
using namespace std;

class MockCalculator : public Calc {
public:
	MOCK_METHOD(int, getValue, (), (override));
	MOCK_METHOD(int, getSum, (int, int), (override));
};

TEST(a, DISABLED_b1) {
	cout << "----------------" << endl;
	MockCalculator calc;
	
	int expected = 10000;
	//calc.getValue();
	cout << "Stub ----------------" << endl;
	EXPECT_CALL(calc, getValue())
		.Times(2)
		.WillRepeatedly(Return(expected));


	EXPECT_THAT(calc.getValue(), Eq(expected));
	EXPECT_THAT(calc.getValue(), Eq(expected));
}

TEST(a, b3) {
	MockCalculator calc;
	SUT sut{ &calc };
	
	EXPECT_CALL(calc, getSum(1, 2))
		.Times(3);

	sut.go();
}

TEST(BookingSchedulerTest, ������_���ÿ���_�����ϴ�_���ð�_�ƴѰ��_����Ұ�) {
	BookingScheduler sche(3);
}

TEST(BookingSchedulerTest, ������_���ÿ���_�����ϴ�_������_���_���డ��) {

}

TEST(BookingSchedulerTest, �ð��뺰_�ο�������_�ִ�_����_�ð��뿡_Capacity_�ʰ���_���_���ܹ߻�) {

}

TEST(BookingSchedulerTest, �ð��뺰_�ο�������_�ִ�_����_�ð��밡_�ٸ���_Capacity_���־_������_�߰�_����) {

}

TEST(BookingSchedulerTest, ����Ϸ��_SMS��_������_�߼�) {

}

TEST(BookingSchedulerTest, �̸�����_����_��쿡��_�̸���_�̹߼�) {

}

TEST(BookingSchedulerTest, �̸�����_�ִ�_��쿡��_�̸���_�߼�) {

}

TEST(BookingSchedulerTest, ���糯¥��_�Ͽ�����_���_����Ұ�_����ó��) {

}

TEST(BookingSchedulerTest, ���糯¥��_�Ͽ�����_�ƴѰ��_���డ��) {

}