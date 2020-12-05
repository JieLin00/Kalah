#include <iostream>
using namespace std;
void TopPage();
void PrintOption();
void showHouse(int house[]);
bool validate(int house[], int pickedHouse, int player);
inline bool hasSuccessors(int house[]);
bool relocation(int house[], int pickedHouse);
void finalScoring(int house[]);
inline int evaluate(int house[], int playerShop, int oppoentShop);
int minimaxDecision(int house[], int depthMax, int player);
int maxValue(int house[], int depthMax, int depth, int alpha, int beta, int playerShop);
int minValue(int house[], int depthMax, int depth, int alpha, int beta, int playerShop);

int main() {
	char playerName[2][20];
	int playerComputer[2], house[14] = { 0 }, player = 0, seeds, depth[2];
	int option = 0;
	TopPage();

	PrintOption();
	cin >> option;
	if (option == 1) {//(1)�}�l�C��
		cout << "(0)single-player or (1)two-player :";//(0)��Hor(1)���H
		int horc = -1;
		cin >> horc;
		if (horc == 0) {//��H
			int choise = 0;
			cout << "Do you want to play first? (0)Yes or (1)No ";
			cin >> choise;
			if (choise == 0) {
				playerComputer[0] = 0;//���a(��)
				playerComputer[1] = 1;//�q��
				cout << "The player's nickname: ";
				cin >> playerName[0];
				cout << "The computer's nickname: ";
				cin >> playerName[1];
				cout << "The min-max depth: ";
				cin >> depth[1];
			}
			else if (choise == 1) {
				playerComputer[0] = 1;//�q��(��)
				playerComputer[1] = 0;//���a
				cout << "The player's nickname: ";
				cin >> playerName[1];
				cout << "The computer's nickname: ";
				cin >> playerName[0];
				cout << "The min-max depth: ";
				cin >> depth[0];
			}

		}
		else if (horc == 1) {//���H
			playerComputer[0] = 0;
			playerComputer[1] = 0;
			cout << "The first player's nickname: ";
			cin >> playerName[0];
			cout << "The second player's nickname: ";
			cin >> playerName[1];
		}
	}
	else if (option == 2) {
		playerComputer[0] = 1;
		playerComputer[1] = 1;
		cout << "The computer1's nickname: ";
		cin >> playerName[0];
		cout << "The computer2's nickname: ";
		cin >> playerName[1];
		cout << "The first min-max depth: ";
		cin >> depth[0];
		cout << "The second min-max depth: ";
		cin >> depth[1];
	}
	else if (option == 3) {
		return 0;
	}
	int op2;
	printf("Seeds���t�G(0)insert the State �� (1)insert the Seeds number\n");
	printf("\n");

	cin >> op2;
	if (op2 == 0) {
		cout << "�п�J14�ӼƦr \n�Ҧp:1 2 3 4 5 6 7 8 9 10 11 12 13 14\n";
		cout << "�L����[14] , 13, 12, 11, 10, 9, 8\n";
		cout << "              1,  2,  3,  4, 5, 6, [7]\n";
		for (int i = 0; i < 14; i++) {
			cin >> house[i];//if (cin.get() == '\r') cin.get();
		}
	}
	else if (op2 == 1) {
		cout << "The house's seeds: ";
		cin >> seeds;
		for (int i = 0; i < 14; ++i) {
			if (i != 6 && i != 13) {
				house[i] = seeds;
			}
		}
	}


	while (hasSuccessors(house)) {//�P�_house�O�_������
		showHouse(house);//���house������
		int action;

		cout << playerName[player] << "'s turn to take action: ";//�Ĥ@��A�o��player=0

		if (playerComputer[player] == 1) {//��player=0�ɡA�p�GplayerComputer[0]=1�A�q���N��X�ۤv��action
			action = minimaxDecision(house, depth[player], player);
			cout << action << endl;
		}
		else
			cin >> action;

		if (!validate(house, action, player)) {
			continue;
		}

		cout << endl;

		if (relocation(house, action))
			player = (player == 0 ? 0 : 1);
		else
			player = (player == 0 ? 1 : 0);

	}

	finalScoring(house);
	showHouse(house);
	if (house[13] > house[6]) {
		cout << playerName[1] << " win" << endl;
	}
	else if (house[13] == house[6]) {
		cout << "draw" << endl;
	}
	else
		cout << playerName[0] << " win" << endl;
	system("pause");
}



void showHouse(int house[]) {
	cout << "[" << house[13] << "]";
	for (int i = 12; i > 6; i--) {
		cout << "," << house[i];
	}
	cout << endl;

	cout << "     ";
	for (int i = 0; i < 6; i++) {
		cout << house[i] << ",";
	}
	cout << "[" << house[6] << "]" << endl;
}

bool validate(int house[], int pickedHouse, int player) {
	int playerShop = 6;
	if (player == 1)
		playerShop = 13;

	if (pickedHouse >= playerShop || pickedHouse < playerShop - 6) {
		cout << "House#" << pickedHouse << " is not your house.\n" << endl;
		return false;
	}
	else if (house[pickedHouse] == 0) {
		cout << "There is no seed in house#" << pickedHouse << ".\n" << endl;
		return false;
	}
	else {
		return true;
	}
}

inline bool hasSuccessors(int house[]) {//�P�_house�O�_������
	bool player1 = false, player2 = false;
	for (int i = 0; i < 6; ++i) {
		if (house[i] != 0) {//�P�_player1 house
			player1 = true;
		}
		if (house[7 + i] != 0) {//�P�_player1 house
			player2 = true;
		}
	}
	return player1 && player2;
}

bool relocation(int house[], int pickedHouse) {
	int seedsNum = house[pickedHouse];
	house[pickedHouse] = 0;
	int pickerStore = (pickedHouse > 6) ? 13 : 6;
	int otherPickerStore = (pickerStore + 7) % 14;
	int i, originPickedHouse = pickedHouse;
	for (i = 1; i <= seedsNum; i++) {
		if ((pickedHouse + i) % 14 == otherPickerStore) {
			pickedHouse++;
		}
		house[(pickedHouse + i) % 14]++;
	}
	int end = (pickedHouse + i - 1) % 14;
	if (house[end] == 1 && end != originPickedHouse) {
		if (end < pickerStore && end > pickerStore - 7) {
			if (house[12 - end]) {
				house[pickerStore] += house[end] + house[12 - end];
				house[end] = 0;
				house[12 - end] = 0;
			}
		}
	}
	if ((pickedHouse + i) % 7)
		return false;
	else
		return true;
}

void finalScoring(int house[]) {//�Nhouse���Ѿl���ȶǤJ�쥻housestore���A�ñNhouse�M��
	for (int i = 0; i < 6; i++) {
		house[6] += house[i];
		house[13] += house[7 + i];
		house[i] = house[7 + i] = 0;
	}
}

inline int evaluate(int house[], int playerShop, int oppoentShop) {//����housestore����A��omValue�AmValue�����w���A��minimax��
	return house[playerShop] - house[oppoentShop];
}

int minimaxDecision(int house[], int depthMax, int player) {
	int alpha = -1000;
	int beta = 1000;

	int playerShop = 13;
	if (player == 0) {
		playerShop = 6;
	}

	return maxValue(house, depthMax, 0, alpha, beta, playerShop);
}

int maxValue(int house[], int depthMax, int depth, int alpha, int beta, int playerShop) {
	if (hasSuccessors(house) == false) {//�p�G�S��successor�A�N���O�@�� game-over node�A�I�sfinalScoring function &  evaluate function
		finalScoring(house);
		return evaluate(house, playerShop, (playerShop + 7) % 14);
	}
	else if (depth >= depthMax) {//�p�Gexpanded node���depthMax�A�h�I�sevaluate function�A�h�o��mValue����
		return evaluate(house, playerShop, (playerShop + 7) % 14);
	}
	else {
		int action;
		for (int i = playerShop - 6; i < playerShop; i++) {
			if (house[i] == 0) {//�p�G��house���ŴN�~��
				continue;
			}

			int tempHouse[14], tempValue;
			for (int j = 0; j < 14; j++) {
				tempHouse[j] = house[j];
			}
			//�{�btempHouse�Ҭ����house������
			if (relocation(tempHouse, i)) {//�p�G�^�Ǭ�true
				tempValue = maxValue(tempHouse, depthMax, depth + 2, alpha, beta, playerShop);//���j
			}
			else//�p�G�^�Ǭ�false
				tempValue = minValue(tempHouse, depthMax, depth + 1, alpha, beta, playerShop);//���j

			if (alpha < tempValue) {//alpha = -1000;
				alpha = tempValue;
				action = i;
			}
			//����alpha��tempValue����
			if (alpha >= beta)//beta = 1000;
				break;
		}
		if (depth == 0) {
			return action;
		}
		else
			return alpha;
	}
}

int minValue(int house[], int depthMax, int depth, int alpha, int beta, int playerShop) {
	if (hasSuccessors(house) == false) {
		finalScoring(house);
		return evaluate(house, playerShop, (playerShop + 7) % 14);
	}
	else if (depth >= depthMax) {
		return evaluate(house, playerShop, (playerShop + 7) % 14);
	}
	else {
		int action, oppoentShop = (playerShop + 7) % 14;

		for (int i = oppoentShop - 6; i < oppoentShop; ++i) {
			if (house[i] == 0)
				continue;

			int tempHouse[14], tempValue;
			for (int j = 0; j < 14; ++j)
				tempHouse[j] = house[j];

			if (relocation(tempHouse, i))
				tempValue = minValue(tempHouse, depthMax, depth + 2, alpha, beta, playerShop);
			else
				tempValue = maxValue(tempHouse, depthMax, depth + 1, alpha, beta, playerShop);

			if (beta > tempValue)
				beta = tempValue;

			if (alpha >= beta)
				break;
		}
		return beta;
	}
}void TopPage() {
	cout << "\n\n";
	cout << "     .                                     .:.                         .." << endl;
	cout << "bQ  BB:  EBB.  2B:    .BBI   BB   Bb     RBBQBB.  KBB.  .BBB   jBQv BBdgQ." << endl;
	cout << "5BiBZ   .B.BB  1B:    BX7B   BB. :Bd    BB.       B:BB  .BiBv  B7Bs BB    " << endl;
	cout << "IBqB.   BQ iB: 7B.   7B: QB  BBDQMBX    BQ  ZBB  BB :Bv  B.rB BQ BL BB2bv " << endl;
	cout << "PB vB7 JBEdKBB LBr   BQPPQBr BB   QD    PB7  BB :BZdSBQ  Bi BBB. Bj BB    " << endl;
	cout << "vQ. YB:BR    Br:BBBMIB.   BB QQ   Bq     iBBBBM MB    Bs B7 .BK  B1 EBBQB." << endl;
	cout << "\n\n";
	cout << "                              �i  KALAH GAME  �j" << endl;
	cout << "\n";
}

void PrintOption()
{
	printf("\n");
	printf("		(1)		�}�l�C��\n");
	printf("		(2)		�F�L���t(�i��J��q��depth�t�̨ܳθ�)\n");
	printf("		(3)		�����C��\n");
	printf("\n");
	printf("------------------------------�п�J�Ʀr1�B2�B3�i����----------------------------\n");
}