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

TEST(BookingSchedulerTest, 예약은_정시에만_가능하다_정시가_아닌경우_예약불가) {
	BookingScheduler sche(3);
}

TEST(BookingSchedulerTest, 예약은_정시에만_가능하다_정시인_경우_예약가능) {

}

TEST(BookingSchedulerTest, 시간대별_인원제한이_있다_같은_시간대에_Capacity_초과할_경우_예외발생) {

}

TEST(BookingSchedulerTest, 시간대별_인원제한이_있다_같은_시간대가_다르면_Capacity_차있어도_스케쥴_추가_성공) {

}

TEST(BookingSchedulerTest, 예약완료시_SMS는_무조건_발송) {

}

TEST(BookingSchedulerTest, 이메일이_없는_경우에는_이메일_미발송) {

}

TEST(BookingSchedulerTest, 이메일이_있는_경우에는_이메일_발송) {

}

TEST(BookingSchedulerTest, 현재날짜가_일요일인_경우_예약불가_예외처리) {

}

TEST(BookingSchedulerTest, 현재날짜가_일요일이_아닌경우_예약가능) {

}