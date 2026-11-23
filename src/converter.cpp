//converter.cpp
#include "converter.h"
#include "wallet.h"

void SetRate(Converter* converter, int newRate);

bool BuyLuckyCoins(const Converter* converter, Wallet* wallet, int luckyCoinAmount);
//Svarar på om du kan köpa lucky coins

bool SellLuckyCoins(const Converter* converter, Wallet* wallet, int luckyCoinAmount);
//Svarar på om du kan sälja lucky coins