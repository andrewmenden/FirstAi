#include "Game.h"
#include "Network.h"
#include <time.h>

void runDefaultGame(); //runs a single network on a single game and displays every move
int runAi(Network net, Game game, int turns=-1);

int main() {

	// press enter to let ai make the next move. Also this is untrained, and I have no idea why it's naturally good at sorting the numbers
	runDefaultGame();

	//I was trying to train it
	//const int batchCount = 1000;
	//const int trialCount = 10;
	//std::vector<int> structure = { 16, 32, 32, 4 };
	//std::vector<Network> netBatch(batchCount, Network(structure, true));
	//std::vector<int> scores(batchCount);
	//Game game;
	//for (int i = 0; i < batchCount; i++)
	//{
	//	scores[i] = 0;
	//}
	//
	//for (int j = 0; j < trialCount; j++)
	//{
	//	for (int i = 0; i < batchCount; i++)
	//	{
	//		int curr = runAi(netBatch[i], game);
	//		scores[i] = scores[i]+curr;
	//	}
	//}
	//int max[2] = { 0,0 };
	//int indices[2] = {-1,-1};
	//for (int i = 0; i < batchCount; i++)
	//{
	//	if (scores[i] > max[0])
	//	{
	//		max[0] = scores[i];
	//		indices[0] = i;
	//		continue;
	//	}
	//	if (scores[i] > max[1])
	//	{
	//		max[1] = scores[i];
	//		indices[1] = i;
	//		continue;
	//	}
	//}

	return 0;
}

void runDefaultGame()
{
	std::vector<int> structure = { 16,32,32,4 };
	Network net(structure, true);
	Game game;

	do
	{
		system("cls");
		game.printBoard();
		std::cin.get();
		net.setInput(game.boardPosition());
		net.runNetwork();
	} while (game.loop(net.getOutput()));
}

int runAi(Network net,Game game, int turns)
{
	if (turns == -1)
	{
		do
		{
			net.setInput(game.boardPosition());
			net.runNetwork();
		} while (game.loop(net.getOutput()));
	}
	else if (turns > 0)
	{
		for (int i = 0; i < turns; i++)
		{
			net.setInput(game.boardPosition());
			net.runNetwork();
			if (!game.loop(net.getOutput())) break;
		}
	}
	else
	{
		return -1;
	}
	return game.getScore();
}
