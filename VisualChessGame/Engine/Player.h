#pragma once
#include <string.h>

#define MAX_NAME_LENGHT	25	
#define PLAYER_WHITE	1
#define PLAYER_BLACK	2

class Player {
public:
	Player() : mfNoAvalilableMoves(false), mfActive(false), mfCheck(false) { mName = new char[MAX_NAME_LENGHT]; mName = "AI";  mId = PLAYER_BLACK; }
	Player(int id) : mfNoAvalilableMoves(false), mfActive(false), mfCheck(false) { mName = new char[MAX_NAME_LENGHT]; mName = "AI"; mId = id; }
	Player(const char *name) : mfNoAvalilableMoves(false), mfActive(false), mfCheck(false) { mName = new char[MAX_NAME_LENGHT]; strcpy(mName, name); mId = PLAYER_BLACK; }
	Player(const char *name, int id) : mfNoAvalilableMoves(false), mfActive(false), mfCheck(false) { mName = new char[MAX_NAME_LENGHT]; strcpy(mName, name); mId = id; }
	virtual ~Player(){ delete[] mName; }

	bool IsActive() { return mfActive; }
	bool IsChecked() { return mfCheck; }
	bool HasAvailableMoves() { return !mfNoAvalilableMoves; }
	char* getName() { return mName; }
	void SetActive(bool act) { mfActive = act; }
	void SetChecked(bool ch) { mfCheck = ch; }
	void SetNoAvailableMoves(bool fNoAvailable) { mfNoAvalilableMoves = fNoAvailable; }
	int getId() { return mId; }
protected:
	int mId;
	char* mName;
	bool mfActive;
	bool mfCheck;
	bool mfNoAvalilableMoves;
};