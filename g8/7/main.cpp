#include <iostream>
#include <array>
#include <ctime> // ��� time()
#include <cstdlib> // ��� rand() � srand()

enum CardSuit
{
	SUIT_CLUB,
	SUIT_DIAMOND,
	SUIT_HEART,
	SUIT_SPADE,
	MAX_SUITS
};

enum CardRank
{
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_JACK,
	RANK_QUEEN,
	RANK_KING,
	RANK_ACE,
	MAX_RANKS
};

struct Card
{
	CardRank rank;
	CardSuit suit;
};

void printCard(const Card& card)
{
	switch (card.rank)
	{
	case RANK_2:		std::cout << '2'; break;
	case RANK_3:		std::cout << '3'; break;
	case RANK_4:		std::cout << '4'; break;
	case RANK_5:		std::cout << '5'; break;
	case RANK_6:		std::cout << '6'; break;
	case RANK_7:		std::cout << '7'; break;
	case RANK_8:		std::cout << '8'; break;
	case RANK_9:		std::cout << '9'; break;
	case RANK_10:		std::cout << 'T'; break;
	case RANK_JACK:		std::cout << 'J'; break;
	case RANK_QUEEN:	std::cout << 'Q'; break;
	case RANK_KING:		std::cout << 'K'; break;
	case RANK_ACE:		std::cout << 'A'; break;
	}

	switch (card.suit)
	{
	case SUIT_CLUB:		std::cout << 'C'; break;
	case SUIT_DIAMOND:	std::cout << 'D'; break;
	case SUIT_HEART:	std::cout << 'H'; break;
	case SUIT_SPADE:	std::cout << 'S'; break;
	}
}

void printDeck(const std::array<Card, 52> deck)
{
	for (const auto& card : deck)
	{
		printCard(card);
		std::cout << ' ';
	}

	std::cout << '\n';
}

void swapCard(Card& a, Card& b)
{
	Card temp = a;
	a = b;
	b = temp;
}

// ���������� ��������� ����� ����� min � max (������������)
// ��������������, ��� srand() ��� ��� ������
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  // ���������� static, ��� ��� ��� �������� ����� ��������� ������ ���� ���
	// ���������� ������������ ���������� ����� � ����� ���������
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void shuffleDeck(std::array<Card, 52> & deck)
{
	// ���������� ������ ����� � ������
	for (int index = 0; index < 52; ++index)
	{
		// �������� ����� ��������� �����
		int swapIndex = getRandomNumber(0, 51);
		// ������ ������� � ����� ������� ������
		swapCard(deck[index], deck[swapIndex]);
	}
}

int getCardValue(const Card& card)
{
	switch (card.rank)
	{
	case RANK_2:		return 2;
	case RANK_3:		return 3;
	case RANK_4:		return 4;
	case RANK_5:		return 5;
	case RANK_6:		return 6;
	case RANK_7:		return 7;
	case RANK_8:		return 8;
	case RANK_9:		return 9;
	case RANK_10:		return 10;
	case RANK_JACK:		return 10;
	case RANK_QUEEN:	return 10;
	case RANK_KING:		return 10;
	case RANK_ACE:		return 11;
	}

	return 0;
}

char getPlayerChoice()
{
	std::cout << "(h) to hit, or (s) to stand: ";
	char choice;
	do
	{
		std::cin >> choice;
	} while (choice != 'h' && choice != 's');

	return choice;
}

bool playBlackjack(const std::array<Card, 52> deck)
{
	const Card* cardPtr = &deck[0];

	int playerTotal = 0;
	int dealerTotal = 0;

	// ����� �������� ���� �����
	dealerTotal += getCardValue(*cardPtr++);
	std::cout << "The dealer is showing: " << dealerTotal << '\n';

	// ����� �������� ��� �����
	playerTotal += getCardValue(*cardPtr++);
	playerTotal += getCardValue(*cardPtr++);

	// ����� ��������
	while (1)
	{
		std::cout << "You have: " << playerTotal << '\n';
		char choice = getPlayerChoice();
		if (choice == 's')
			break;

		playerTotal += getCardValue(*cardPtr++);

		// �������, �� �������� �� �����
		if (playerTotal > 21)
			return false;
	}

	// ���� ����� �� �������� (� ���� �� ������ 21), ����� ����� �������� ����� �� ��� ���, ���� � ���� � ����� ����� �� ������ 17
	while (dealerTotal < 17)
	{
		dealerTotal += getCardValue(*cardPtr++);
		std::cout << "The dealer now has: " << dealerTotal << '\n';
	}

	// ���� � ������ ������ 21 - �� ��������. ����� �������
	if (dealerTotal > 21)
		return true;

	return (playerTotal > dealerTotal);
}

int main()
{
	srand(static_cast<unsigned int>(time(0))); // ���������� ��������� ���� � �������� ���������� ��������
	rand(); // ������������� Visual Studio: ������ ����� ������� ���������� �����

	std::array<Card, 52> deck;

	// �������, ����� ���� �� ���������������� ������ ����� ��������, �� �����? ���� ���� �����
	int card = 0;
	for (int suit = 0; suit < MAX_SUITS; ++suit)
		for (int rank = 0; rank < MAX_RANKS; ++rank)
		{
			deck[card].suit = static_cast<CardSuit>(suit);
			deck[card].rank = static_cast<CardRank>(rank);
			++card;
		}

	shuffleDeck(deck);

	if (playBlackjack(deck))
		std::cout << "You win!\n";
	else
		std::cout << "You lose!\n";

	return 0;
}