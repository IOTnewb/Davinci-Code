#include "main.h"

void CalculateScore(int* score, int* turn)
{
	*score = *score - *turn * 10;
}

int main()
{
	srand((int)time(NULL));
	
	int card[24] = {	10 , 11 , 20 , 21 , 30 , 31 , 
							40 , 41 , 50 , 51 , 60 , 61 , 
							70 , 71 , 80 , 81 , 90 , 91 , 
							100 , 101 , 110 , 111 , 120 , 121 };

	// 1. 24장의 카드중 무작위 4장을 플레이어들이 받는다.
	Player *player = new Player();
	
	player->Drawcard(card);
	player->Printcard();

	Computer computer;
	
	computer.Drawcardcom(card);
	computer.Printcardcom();


	// 2. 플레이어들은 받은 4장의 카드를 룰에 맞게 정렬한다.

	computer.SortArray();

	// 3. 남은 카드 더미에서 한장을 뽑고, 재정렬 후 상대방의 카드를 추측한다.

	Guess guess;
	
	int result[4] = { 0 , 0 , 0 , 0 };
	int turn = 0;
	int score = 1040;
	int b;

	while (1)
	{
		player->Drawdummy(card);
		PrintColor(&computer, result);

		cout << endl;
		cout << "더미에서 나온 카드 : " << player->Getplayer()[player->Getcount()] << endl;
		cout << "현재 카드 : " << " ";

		player->Printcard();

		cout << "추측할 위치와 카드숫자" << endl;

		GetGuess(&guess);

		ConfirmAnswer(&computer, result , &guess , &score);

		player->Addcount();
		turn++;
		// 4. 컴퓨터의 카드배열이 다 공개되면 턴수를 공개하고 게임 끝

		ConfirmResult(&computer, result, &b);
		if (b == 1) break;
	}

	CalculateScore(&score, &turn);
	
	cout << "점수 : " << score << endl;

	return 0;
}
