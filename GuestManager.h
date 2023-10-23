#pragma once
#include <iostream>
#include <vector>

enum class RoomType { Standard, Comfort };
enum class GuestType { Family, Businessman, Rockstar };

class Guest {
public:
	Guest();
	Guest(const GuestType& gType, const RoomType& rType, const int StayDuration);
	GuestType GetGuestType() const;
	RoomType GetRoomType() const;
	int GetBookedDays() const;

	virtual int GetRoomBusyDays() const = 0;
	virtual int GetAdditionalIncome() const = 0;
	virtual ~Guest();
protected:
	RoomType roomType;
	GuestType guestType;
	int numDaysBooked;
};

class Family : public Guest {
public:
	Family(const GuestType& gType, const RoomType& rType, const int stayDuration);
	int GetRoomBusyDays() const override;
	int GetAdditionalIncome() const override;
	~Family();
};

class Businessman : public Guest {
public:
	Businessman(const GuestType& gType, const RoomType& rType, const int stayDuration, const int additionalIncome);
	int GetRoomBusyDays() const override;
	int GetAdditionalIncome() const override;
	~Businessman();
protected:
	int addIncome;
};

class Rockstar : public Guest {
public:
	Rockstar(const GuestType& gType, const RoomType& rType, const int stayDuration);
	int GetRoomBusyDays() const override;
	int GetAdditionalIncome() const override;
	~Rockstar();
};

class GuestManager {
public:
	GuestManager(const int numStrdRooms, const int dayPriceStandard, const int numComfRooms, const int dayPriceComfort);

	bool AddGuest(const GuestType& gType, const RoomType& rType, const int stayDays, const int additionalIncome = 0);
	bool IsAvailable(const RoomType& rType, const int inDays = 0) const;

	bool BookRoom(const RoomType& rType);  //subtracts the correct variable holding the num of available roomtypes by 1

	int IncomingProfit();
	float EarningEfficiency();
	
	int guestPerDayPayment(Guest*& guest) const; //returns how much the specified guest pays for the room PER DAY

	bool operator<(GuestManager& gManager2);

	~GuestManager();
private:
	int numOfStandardRooms;
	int standardPrice;
	int numOfComfortRooms;
	int comfortPrice;

	int numOfAvailableStandard;
	int numOfAvailableComfort;
	std::vector<Guest*> guestList;
};