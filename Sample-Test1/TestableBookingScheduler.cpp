#include <iostream>
#include "pch.h"
#include "../Project2/BookingScheduler.cpp"

class TestableBookingScheduler: public BookingScheduler {
public:
	TestableBookingScheduler(int capacityPerHour, tm dateTime) :
		BookingScheduler(capacityPerHour), dateTime(dateTime) {

	}
	
	void setBookingScheduler(BookingScheduler* bookingScheduler) {
		this->bookingScheduler = bookingScheduler;
	}

	time_t getNow() override {
		return mktime(&dateTime);
		//return bookingScheduler->getNow();
	}

private:
	tm dateTime;
	BookingScheduler* bookingScheduler;
};