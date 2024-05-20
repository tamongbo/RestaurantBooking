#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <iostream>
#include "../Project2/BookingScheduler.cpp"
#include "TestableSmsSender.cpp"

using namespace testing;
using namespace std;

class BookingItem :public testing::Test {
protected:
	void SetUp() override {
		NOT_ON_THE_HOUR = getTime(2021, 3, 26, 9, 5);
		ON_THE_HOUR = getTime(2021, 3, 26, 9, 0);
	}
public:
	tm getTime(int year, int mon, int day, int hour, int min) {
		tm result = { 0, min, hour, day, mon - 1, year - 1900, 0, 0, -1 };
		mktime(&result);
		return result;
	}

	tm plusHour(tm base, int hour) {
		base.tm_hour += hour;
		mktime(&base);
		return base;
	}

	tm NOT_ON_THE_HOUR;
	tm ON_THE_HOUR;
	Customer CUSTOMER{ "Fake name", "010-1234-5678" };

	const int UNDER_CAPACIRT = 1;
	const int CAPACITY_PER_HOUR = 3;

	BookingScheduler bookingScheduler{ CAPACITY_PER_HOUR };
};

TEST_F(BookingItem, ������_���ÿ���_�����ϴ�_���ð�_�ƴѰ��_����Ұ�) {
	//arrange
	Schedule* schedule = new Schedule{ NOT_ON_THE_HOUR, UNDER_CAPACIRT, CUSTOMER };

	//act
	EXPECT_THROW({
		bookingScheduler.addSchedule(schedule);
		}, std::runtime_error);

	//assert
	//expected runtime exception
}

TEST_F(BookingItem, ������_���ÿ���_�����ϴ�_������_���_���డ��) {
	//arrange
	Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACIRT, CUSTOMER };

	//act
	bookingScheduler.addSchedule(schedule);

	//assert
	EXPECT_THAT(bookingScheduler.hasSchedule(schedule), Eq(true));
}

TEST_F(BookingItem, �ð��뺰_�ο�������_�ִ�_����_�ð��뿡_Capacity_�ʰ���_���_���ܹ߻�) {
	//arrange
	Schedule* schedule = new Schedule{ ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };
	bookingScheduler.addSchedule(schedule);

	//act
	try {
		Schedule* newSchedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACIRT, CUSTOMER };
		bookingScheduler.addSchedule(newSchedule);
		FAIL(); // Exception�� �߻��� �����̱⿡, FAIL() �Լ��� �������� �ʴ´�.
	}
	catch (std::runtime_error& e) {
		EXPECT_EQ(string{ e.what() }, string{ "Number of people is over restaurant capacity per hour" });
	}
}

TEST_F(BookingItem, �ð��뺰_�ο�������_�ִ�_����_�ð��밡_�ٸ���_Capacity_���־_������_�߰�_����) {
	//arrange
	Schedule* schedule = new Schedule{ ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };
	bookingScheduler.addSchedule(schedule);

	//act
	tm differenctHour = plusHour(ON_THE_HOUR, 1);
	Schedule* newSchedule = new Schedule{ differenctHour, UNDER_CAPACIRT, CUSTOMER };
	bookingScheduler.addSchedule(newSchedule);

	EXPECT_EQ(true, bookingScheduler.hasSchedule(schedule));
	EXPECT_EQ(true, bookingScheduler.hasSchedule(newSchedule));
}

TEST_F(BookingItem, ����Ϸ��_SMS��_������_�߼�) {
	//arrage
	TestableSmsSender testableSmsSender;
	Schedule* schedule = new Schedule{ ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };
	bookingScheduler.setSmsSender(&testableSmsSender);

	//act
	bookingScheduler.addSchedule(schedule);

	//assert
	EXPECT_EQ(true, testableSmsSender.isSendMethodIsCalled());
}

TEST(BookingSchedulerTest, �̸�����_����_��쿡��_�̸���_�̹߼�) {

}

TEST(BookingSchedulerTest, �̸�����_�ִ�_��쿡��_�̸���_�߼�) {

}

TEST(BookingSchedulerTest, ���糯¥��_�Ͽ�����_���_����Ұ�_����ó��) {

}

TEST(BookingSchedulerTest, ���糯¥��_�Ͽ�����_�ƴѰ��_���డ��) {

}