#include <iostream>
#include <algorithm>
#include <random>
#include <vector>


std::vector<int> cards = { 0,0,0,0,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,11,11,11,11,12,12,12,12,13,13,13,13 };
//No i am not keeping track of suits
std::vector<int> PlayerHand;
std::vector<int> DealerHand;
std::vector<int> InPlay;
int GameOver;
int Wins;
int Losses;
int Ties;
void print(std::vector<int> Count)
{
	for (int y = 0; y < size(Count); y++)
	{
		
		switch (Count[y]) {
		case 0:
			printf("A ");
			break;
		case 11:
			printf("J ");
			break;
		case 12:
			printf("Q ");
			break;
		case 13:
			printf("K ");
			break;
		default:
			std::cout << Count[y];
			printf(" ");
		}
	}
	printf("\n");
}
void randomizer()
{
	std::random_shuffle(InPlay.begin(), InPlay.end());
}
void draw()
{
	PlayerHand.emplace_back(InPlay.back());
	InPlay.pop_back();
	DealerHand.emplace_back(InPlay.back());
	InPlay.pop_back();
}
int analyse()
{
	//This algorithm will not card count because it doesn't want to get kicked out of casinos
	//Nor will there be special hand rules, those are annoying
	std::vector<int> Scores = {};
	std::vector<std::vector<int>> PotentialHandCount;
	std::vector<int> Start = {};
	PotentialHandCount.emplace_back(Start);
	for (int y = 0; y < size(PlayerHand); y++)
	{
		switch (PlayerHand[y]) {
		case 0:
			if (size(PotentialHandCount) == 1)
			{
				Start.emplace_back(1);
				std::vector<int> z = { 11 };
				PotentialHandCount.emplace_back(z);
			}
			else
			{
				for (std::vector<int>& e : PotentialHandCount)
				{
					std::vector<int> y = e;
					y.emplace_back(1);
					PotentialHandCount.emplace_back(y);
					std::vector<int> z = e;
					z.emplace_back(11);
					PotentialHandCount.emplace_back(z);
				}
			}
			break;
		case 11:
			for (std::vector<int>& e : PotentialHandCount)
			{
				e.emplace_back(10);

			}
			break;
		case 12:
			for (std::vector<int>& e : PotentialHandCount)
			{
				e.emplace_back(10);
			}
			break;
		case 13:
			for (std::vector<int>& e : PotentialHandCount)
			{
				e.emplace_back(10);
			}
			break;
		default:
			for (std::vector<int>& e : PotentialHandCount)
			{
				e.emplace_back(PlayerHand[y]);
			}
		}
	}
	for (std::vector<int> e : PotentialHandCount)
	{
		int total = 0;
		for (int x : e)
		{
			total += x;
		}
		if (total < 21)
		{
			Scores.emplace_back(total);
		}

	}
	if (size(Scores) == 0)
	{
		return 0;
	}
	if (size(Scores) == 1)
	{
		for (int x : Scores)
		{
			if (x > 15)
			{
				return x;
			}
			
		}
	}
	else
	{
		for (int y = 21; y > 15; y--)
		{
			for (int x : Scores)
			{
				if (x == y)
				{
					return x;
				}
			}
		}
	}
	
	return -1;
}
int dealeranalyse()
{
	//reusing old code? why would i do that when i can make new code
	std::vector<int> Scores = {};
	std::vector<std::vector<int>> PotentialHandCount;
	std::vector<int> Start = {};
	PotentialHandCount.emplace_back(Start);
	for (int y = 0; y < size(DealerHand); y++)
	{
		switch (DealerHand[y]) {
		case 0:
			if (size(PotentialHandCount) == 1)
			{
				Start.emplace_back(1);
				std::vector<int> z = { 11 };
				PotentialHandCount.emplace_back(z);
			}
			else
			{
				for (std::vector<int>& e : PotentialHandCount)
				{
					std::vector<int> y = e;
					y.emplace_back(1);
					PotentialHandCount.emplace_back(y);
					std::vector<int> z = e;
					z.emplace_back(11);
					PotentialHandCount.emplace_back(z);
				}
			}
			break;
		case 11:
			for (std::vector<int>& e : PotentialHandCount)
			{
				e.emplace_back(10);

			}
			break;
		case 12:
			for (std::vector<int>& e : PotentialHandCount)
			{
				e.emplace_back(10);
			}
			break;
		case 13:
			for (std::vector<int>& e : PotentialHandCount)
			{
				e.emplace_back(10);
			}
			break;
		default:
			for (std::vector<int>& e : PotentialHandCount)
			{
				e.emplace_back(DealerHand[y]);
			}
		}
	}
	for (std::vector<int> e : PotentialHandCount)
	{
		int total = 0;
		for (int x : e)
		{
			total += x;
		}
		if (total < 21)
		{
			Scores.emplace_back(total);
		}

	}
	if (size(Scores) == 0)
	{
		return 0;
	}
	if (size(Scores) == 1)
	{
		for (int x : Scores)
		{
			return x;
		}
	}
	for (int y = 21; y > 0; y--)
	{
		for (int x : Scores)
		{
			if (x == y)
			{
				return x;
			}
		}
	}
	return -1;
}
void lose()
{
	printf("You overdrew");
	Losses++;
	PlayerHand.clear();
	DealerHand.clear();
	GameOver = 1;
}
void results(int PlayerScore)
{
	printf("\n");
	printf("Dealer hand is:");
	print(DealerHand);
	int x = dealeranalyse();
	if (x == 0)
	{
		printf("Dealer overdrew you win");
		Wins++;
	}
	else if (PlayerScore > x)
	{
		printf("You win");
		Wins++;
	}
	else if (PlayerScore == x)
	{
		printf("Tie");
		Ties++;
	}
	else
	{
		printf("Dealer scores higher, you lose");
		Losses++;
	}
	PlayerHand.clear();
	DealerHand.clear();
	GameOver = 1;

}
void game()
{
	InPlay = cards;
	randomizer();
	draw();
	draw();
	printf("Current hand is:");
	print(PlayerHand);
	while (GameOver == 0)
	{
		switch (int x = analyse()) {
		case -1:
			printf("\n");
			printf("Draw");
			printf("\n");
			draw();
			printf("Current hand is:");
			print(PlayerHand);
			break;
		case 0:
			lose();
			break;
		default:
			printf("\n");
			printf("Stay");
			printf("\n");
			results(x);
			break;
		}
	}

}
int main()
{
	int GameCount = 1;
	while (GameCount < 101)
	{
		game();
		GameCount++;
		GameOver = 0;
		printf("\n");
		printf("----------------------");
		printf("\n");
	}
	printf("Wins: ");
	std::cout << Wins;
	printf("\n");
	printf("Ties: ");
	std::cout << Ties;
	printf("\n");
	printf("Losses: ");
	std::cout << Losses;
}
