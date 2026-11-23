//converter.h
#pragma once
#include "wallet.h"

struct Converter
{
	int scripExchange = 100; //vaexelkurs
	
	Converter(int rate = 100){
		scripExchange = rate;
	}

	void SetRate(int newRate);

	bool BuyLuckyCoins(Wallet* wallet, int luckyCoinAmount) const;
	//Svarar på om du kan köpa lucky coins

	bool SellLuckyCoins(Wallet* wallet, int luckyCoinAmount) const;
	//Svarar på om du kan sälja lucky coins

	void SpendScrip(Wallet* wallet, int scripAmount);

	
};

