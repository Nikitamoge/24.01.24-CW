#include <iostream>
#include <string.h>
#include <time.h>

using namespace std;

class Machine
{
	int* Reel;
	int MaxReelLength;
	int ReelLength;
public:
	Machine() {
		Reel = nullptr;
		MaxReelLength = 0;
		ReelLength = 0;
	}
	//Конструктор
	Machine(int m);
	~Machine();
	void AddSymbol(int c);
	bool Spin();
	bool IsEmpty();
	bool IsFull();
	void ShowReel(const Machine& second, const Machine& third);
	bool RandomSpin();
	bool CheckWin(const Machine& second, const Machine& third);
};

Machine::~Machine()
{
	delete[]Reel;
}
Machine::Machine(int m)
{
	MaxReelLength = m;
	Reel = new int[MaxReelLength];
	ReelLength = 0;
}

void Machine::ShowReel(const Machine& second, const Machine& third) {

	cout << endl;
	for (int i = 0; i < ReelLength; i++) {

		cout << i + 1 << " line: " << Reel[i] << " " << second.Reel[i] << " " << third.Reel[i] << endl;
	}
	cout << endl;
}

bool Machine::IsEmpty()
{
	return ReelLength == 0;
}

bool Machine::IsFull()
{
	return ReelLength == MaxReelLength;
}

void Machine::AddSymbol(int c)
{
	if (!IsFull())
		Reel[ReelLength++] = c;
}

bool Machine::Spin()
{
	if (!IsEmpty()) {

		int temp = Reel[0];
		for (int i = 1; i < ReelLength; i++)
			Reel[i - 1] = Reel[i];
		Reel[ReelLength - 1] = temp;
		return 1;
	}
	else return 0;
}

bool Machine::RandomSpin() {

	int randomSpin = rand() % 5 + 1;
	cout << " " << randomSpin;
	for (int i = 0; i < randomSpin; i++) {

		Spin();
	}
	return true;
}

bool Machine::CheckWin(const Machine& second, const Machine& third) {

	for (int i = 0; i < ReelLength; i++) {
		if (Reel[i] == second.Reel[i] && Reel[i] == third.Reel[i] && second.Reel[i] == third.Reel[i]) {
			cout << "Coincidence " << i + 1 << " line: " << Reel[i] << " " << second.Reel[i] << " " << third.Reel[i] << endl;
			return true;
		}
	}
	return false;
}

int main()
{
	srand(time(0));
	Machine firstReel(3);
	Machine secondReel(3);
	Machine thirdReel(3);

	for (int i = 0; i < 3; i++) {

		firstReel.AddSymbol(rand() % 2 + 1);
		secondReel.AddSymbol(rand() % 2 + 1);
		thirdReel.AddSymbol(rand() % 2 + 1);
	}

	cout << "====================" << endl;
	cout << "Before rolling:" << endl;
	firstReel.ShowReel(secondReel, thirdReel);

	cout << "Rolling" << endl;
	firstReel.RandomSpin();
	secondReel.RandomSpin();
	thirdReel.RandomSpin();

	cout << "====================" << endl;

	cout << "After rolling:" << endl;
	firstReel.ShowReel(secondReel, thirdReel);

	if (firstReel.CheckWin(secondReel, thirdReel)) {
		cout << "You won!" << endl;
	}
	else {
		cout << "You lost!" << endl;
	}

	return 0;
}


