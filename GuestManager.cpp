#include <iostream>
#include <vector>
#include "GuestManager.h"

Guest::Guest() {
	guestType = GuestType::Family;
	roomType = RoomType::Standard;
	numDaysBooked = 1;
}

Guest::Guest(const GuestType& gType, const RoomType& rType, const int StayDuration) {
	guestType = gType;
	roomType = rType;
	numDaysBooked = StayDuration;
}

GuestType Guest::GetGuestType()const {
	return guestType;
}

RoomType Guest::GetRoomType()const {
	return roomType;
}

int Guest::GetBookedDays()const {
	return numDaysBooked;
}

Guest::~Guest() {};

Family::Family(const GuestType& gType, const RoomType& rType, const int stayDuration):Guest(gType, rType, stayDuration) {}

int Family::GetRoomBusyDays() const {
	return numDaysBooked;
}

int Family::GetAdditionalIncome() const {
	return 0;
}

Family::~Family() {}

Businessman::Businessman(const GuestType& gType, const RoomType& rType, const int stayDuration, const int additionalIncome) {
	guestType = gType;
	roomType = rType;
	numDaysBooked = stayDuration;
	addIncome = additionalIncome;
}

int Businessman::GetRoomBusyDays() const {
	return numDaysBooked;
}

int Businessman::GetAdditionalIncome() const {
	return addIncome;
}

Businessman::~Businessman() {}

Rockstar::Rockstar(const GuestType& gType, const RoomType& rType, const int stayDuration):Guest(gType, rType, stayDuration) {}

int Rockstar::GetRoomBusyDays() const {
	return numDaysBooked + 10;
}

int Rockstar::GetAdditionalIncome() const {
	return 0;
}

Rockstar::~Rockstar() {}

GuestManager::GuestManager(const int numStrdRooms, const int dayPriceStandard, const int numComfRooms, const int dayPriceComfort) {
	numOfStandardRooms = numStrdRooms;
	numOfAvailableStandard = numStrdRooms;
	standardPrice = dayPriceStandard;
	numOfComfortRooms = numComfRooms;
	numOfAvailableComfort = numComfRooms;
	comfortPrice = dayPriceComfort;
}

bool GuestManager::AddGuest(const GuestType& gType, const RoomType& rType, const int stayDays, const int additionalIncome) {
	if (!IsAvailable(rType, 0)) {
		std::cout << "Unable to add Guest due to unavailable room selection." << std::endl;
		return false;
	}
	
	if (gType == GuestType::Rockstar) {
		guestList.push_back(new Rockstar(gType, rType, stayDays));
		std::cout << "Rooms booked: " << BookRoom(rType) << std::endl;
		std::cout << "Rockstar Guest added." << std::endl;

		return true;
	}
	else if (gType == GuestType::Businessman) {
		guestList.push_back(new Businessman(gType, rType, stayDays, additionalIncome));
		std::cout << "Rooms booked: " << BookRoom(rType) << std::endl;
		std::cout << "Businessman Guest added." << std::endl;

		return true;
	}
	else {
		guestList.push_back(new Family(gType, rType, stayDays));
		std::cout << "Rooms booked: " << BookRoom(rType) << std::endl;
		std::cout << "Family Guest added." << std::endl;

		return true;
	}

	return false;
}

bool GuestManager::IsAvailable(const RoomType& rType, const int inDays) const {
	if (rType == RoomType::Comfort) {
		std::cout << "num of comfort: " << numOfAvailableComfort << std::endl;
		if (numOfAvailableComfort > 0) {
			std::cout << "Yes the room is or will be availiable!" << std::endl;
			return true;
		}
	}
	if (rType == RoomType::Standard) {
		std::cout << "num of standard: " << numOfAvailableStandard << std::endl;
		if (numOfAvailableStandard > 0) {
			std::cout << "Yes the room is or will be availiable!" << std::endl;
			return true;
		}
	}

	for (int i = 0; i < guestList.size(); i++) {
		if (guestList[i]->GetRoomType() == rType) {
			if (guestList[i]->GetRoomBusyDays() <= inDays) {
				std::cout << "Yes the room is or will be availiable!" << std::endl;
				return true;
			}
		}
	}

	std::cout << "I'm sorry, but the room is not or will not be availiable." << std::endl;
	return false;
}

bool GuestManager::BookRoom(const RoomType& rType) {
	if (rType == RoomType::Comfort) {
		numOfAvailableComfort--;
		return true;
	}
	if(rType == RoomType::Standard) {
		numOfAvailableStandard--;
		return true;
	}
	return false;
}

int GuestManager::IncomingProfit() {
	int totalIncomingProfit = 0;
	for (int i = 0; i < guestList.size(); i++) {
		totalIncomingProfit += guestPerDayPayment(guestList[i]) * guestList[i]->GetBookedDays();
		totalIncomingProfit += guestList[i]->GetAdditionalIncome() * guestList[i]->GetBookedDays();
	}

	std::cout << "Incoming Profit: " << totalIncomingProfit << std::endl;
	return totalIncomingProfit;
}

float GuestManager::EarningEfficiency() {
	float currentPerDayIncome = 0;
	float maxPerDayIncome = ((float)numOfStandardRooms * (float)standardPrice) + ((float)numOfComfortRooms * (float)comfortPrice);

	for (int i = 0; i < guestList.size(); i++) {
		currentPerDayIncome += (float)guestPerDayPayment(guestList[i]) + (float)guestList[i]->GetAdditionalIncome();
	}

	std::cout << "Earning Efficiency: " << currentPerDayIncome / maxPerDayIncome << std::endl;
	return currentPerDayIncome / maxPerDayIncome;
}

int GuestManager::guestPerDayPayment(Guest*& guest) const {
	if (guest->GetRoomType() == RoomType::Comfort) {
		return comfortPrice;
	}
	return standardPrice;
}

bool GuestManager::operator<(GuestManager& gManager2) {
	if (IncomingProfit() < gManager2.IncomingProfit()) {
		return true;
	}
	return false;
}

GuestManager::~GuestManager() {
	for (int i = 0; i < guestList.size(); i++) {
		delete guestList[i];
		guestList[i] = nullptr;
	}
};