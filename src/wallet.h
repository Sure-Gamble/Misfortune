//wallet.h
#pragma once

struct Wallet
{
int scrip = 0;
int luckyCoins = 0;
Wallet(int scripStart, int luckyStart)
{
	scrip = scripStart;
	luckyCoins = luckyStart;
}

bool CanAffordScrip(int amount) const;
void AddScrip(int amount);
};