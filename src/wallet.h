//wallet.h
#pragma once

struct Wallet{
	int scrip = 0;
	int luckyCoins = 0;


	Wallet(int scripStart, int luckyStart)
	{
		scrip = scripStart;
		luckyCoins = luckyStart;

	}
};

bool CanAffordScrip(const Wallet* wallet, int amount);
//Har du tillräckligt m scrip?
void AddScrip(Wallet* wallet, int amount);
//Fyll på m scrip
bool SpendScrip(Wallet* wallet, int amount);


