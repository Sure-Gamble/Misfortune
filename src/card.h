#pragma once

struct Card{
	int rank;
	int suit; // spades is 4, hearts is 3, diamonds is 2, and clubs is 1.
	bool has_been_played;
	bool isAce;
};

void ShuffleDeck(Card* cards[52]);