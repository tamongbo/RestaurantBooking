#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <iostream>
#include "../Project2/BookingScheduler.cpp"
#include "TestableSmsSender.cpp"
#include "TestableMailSender.cpp"
//#include "SundayBookingScheduler.cpp"
//#include "MondayBookingScheduler.cpp"
#include "TestableBookingScheduler.cpp"

using namespace testing;
using namespace std;

class BookingItem :public testing::Test {
protected:
	void SetUp() override {
		NOT_ON_THE_HOUR = getTime(2021, 3, 26, 9, 5);
		ON_THE_HOUR = getTime(2021, 3, 26, 9, 0);
		SUNDAY = getTime(2021, 3, 28, 17, 0);
		MONDAY = getTime(2024, 6, 3, 17, 0);

		bookingScheduler.setSmsSender(&testableSmsSender);
		bookingScheduler.setMailSender(&testableMailSender);

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
	Customer CUSTOMER_WITH_MAIL{ "Fake Name", "010-1234-5678", "test@test.com" };

	const int UNDER_CAPACIRT = 1;
	const int CAPACITY_PER_HOUR = 3;

	BookingScheduler bookingScheduler{ CAPACITY_PER_HOUR };
	TestableSmsSender testableSmsSender;
	TestableMailSender testableMailSender;

	tm SUNDAY;
	tm MONDAY;
};

TEST_F(BookingItem, 예약은_정시에만_가능하다_정시가_아닌경우_예약불가) {
	//arrange
	Schedule* schedule = new Schedule{ NOT_ON_THE_HOUR, UNDER_CAPACIRT, CUSTOMER };

	//act
	EXPECT_THROW({
		bookingScheduler.addSchedule(schedule);
		}, std::runtime_error);

	//assert
	//expected runtime exception
}

TEST_F(BookingItem, 예약은_정시에만_가능하다_정시인_경우_예약가능) {
	//arrange
	Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACIRT, CUSTOMER };

	//act
	bookingScheduler.addSchedule(schedule);

	//assert
	EXPECT_THAT(bookingScheduler.hasSchedule(schedule), Eq(true));
}

TEST_F(BookingItem, 시간대별_인원제한이_있다_같은_시간대에_Capacity_초과할_경우_예외발생) {
	//arrange
	Schedule* schedule = new Schedule{ ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };
	bookingScheduler.addSchedule(schedule);

	//act
	try {
		Schedule* newSchedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACIRT, CUSTOMER };
		bookingScheduler.addSchedule(newSchedule);
		FAIL(); // Exception이 발생할 예정이기에, FAIL() 함수에 도달하지 않는다.
	}
	catch (std::runtime_error& e) {
		EXPECT_EQ(string{ e.what() }, string{ "Number of people is over restaurant capacity per hour" });
	}
}

TEST_F(BookingItem, 시간대별_인원제한이_있다_같은_시간대가_다르면_Capacity_차있어도_스케쥴_추가_성공) {
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

TEST_F(BookingItem, 예약완료시_SMS는_무조건_발송) {
	//arrage
	Schedule* schedule = new Schedule{ ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };

	//act
	bookingScheduler.addSchedule(schedule);

	//assert
	EXPECT_EQ(true, testableSmsSender.isSendMethodIsCalled());
}

TEST_F(BookingItem, 이메일이_없는_경우에는_이메일_발송) {
	//arrage
	Schedule* schedule = new Schedule{ ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };

	//act
	bookingScheduler.addSchedule(schedule);

	//assert
	EXPECT_EQ(0, testableMailSender.getCountSendMailMethodIsCalled());
}

TEST_F(BookingItem, 이메일이_있는_경우에는_이메일_발송) {
	//arrage
	Schedule* schedule = new Schedule{ ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER_WITH_MAIL };

	//act
	bookingScheduler.addSchedule(schedule);

	//assert
	EXPECT_EQ(1, testableMailSender.getCountSendMailMethodIsCalled());
}

TEST_F(BookingItem, 현재날짜가_일요일인_경우_예약불가_예외처리) {
	//arrage
	TestableBookingScheduler* testableBookingScheduler = new TestableBookingScheduler{ CAPACITY_PER_HOUR, SUNDAY};
	
	try {
		//act
		Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACIRT, CUSTOMER_WITH_MAIL };
		testableBookingScheduler->addSchedule(schedule);
		FAIL();
	}
	catch (std::runtime_error& e) {
		//assert
		EXPECT_EQ(string{ e.what() }, string{ "Booking system is not available on sunday" });
	}
}

TEST_F(BookingItem, 현재날짜가_일요일이_아닌경우_예약가능) {
	//arrage
	TestableBookingScheduler* testableBookingScheduler = new TestableBookingScheduler{ CAPACITY_PER_HOUR, MONDAY };

	//act
	Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACIRT, CUSTOMER_WITH_MAIL };
	testableBookingScheduler->addSchedule(schedule);
	
	//assert
	EXPECT_EQ(true, testableBookingScheduler->hasSchedule(schedule));
}