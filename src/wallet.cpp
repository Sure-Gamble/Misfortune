//wallet.cpp

#include "wallet.h"

bool CanAffordScrip(const Wallet* wallet, int amount){
	return wallet->scrip >= amount;
}

void AddScrip(Wallet* wallet, int amount){
	wallet->scrip += amount;

}

bool SpendScrip(Wallet* wallet, int amount){
	if(!CanAffordScrip(wallet, amount)) return false;
	wallet->scrip -= amount;
	return true;
}
