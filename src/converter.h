//converter.h
#pragma once
#include "wallet.h"

struct Converter
{
	int scripExchange = 100; //vaexelkurs
	
	Converter(int rate = 100){
		scripExchange = rate;
	}
};

	void SetRate(Converter* converter, int newRate);

	bool BuyLuckyCoins(const Converter* converter, Wallet* wallet, int luckyCoinAmount);
	//Svarar på om du kan köpa lucky coins

	bool SellLuckyCoins(const Converter* converter, Wallet* wallet, int luckyCoinAmount);
	//Svarar på om du kan sälja lucky coins



	


