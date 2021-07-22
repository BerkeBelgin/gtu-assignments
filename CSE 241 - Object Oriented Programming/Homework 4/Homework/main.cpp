#include <iostream>
#include <cstdlib>
#include <ctime>
#include "NPuzzle.cpp"

using namespace std;

int main(){
	srand(time(NULL));
	NPuzzle nPuzzle;
	
	const auto cleanScreen = "\033[H\033[J";
	decltype('c') choice;
	do{
		cout << "Enter \"l\" or \"c\" to start game: " << endl;
		cout << "l: load board from a text file" << endl;
		cout << "c: create board" << endl;
		cin >> choice;
		cout << endl;
		
		switch(choice){
			case 'l': case 'L': 
				nPuzzle.readFromFile();
				break;
			case 'c': case 'C': 
				nPuzzle.setSize();
				break;
			default:
				cout << "Please enter a valid key" << endl;
				break;
		}
	} while(choice != 'l' && choice != 'L' && choice != 'c' && choice != 'C');
	
	cout << cleanScreen;
	cout << nPuzzle;//Operator
	
	char moveChar;
	do {
		cout << endl << "Make a move:" << endl;
		cout << "l: Go Left" << endl;
		cout << "r: Go Right" << endl;
		cout << "u: Go Up" << endl;
		cout << "d: Go Down" << endl;
		cout << "s: Shuffle" << endl;
		cout << "v: Solve Puzzle" << endl;
		cout << "t: Print Report" << endl;
		cout << "e: Save Game" << endl;
		cout << "o: Load Game" << endl;
		cout << "q: Quit" << endl << endl;
		cin >> moveChar;
		
		switch(moveChar){
		 	case 'q': case 'Q':
		 		return 0;
			case 's': case 'S':
				nPuzzle.shuffle(18);
				break;
			case 'o': case 'O':
				cin >> nPuzzle;//Operator
				break;
			case 'l': case 'L':
			case 'r': case 'R':
			case 'u': case 'U':
			case 'd': case 'D':
				nPuzzle.move(moveChar);
				break;
		}
		
		cout << cleanScreen;
		cout << nPuzzle;//Operator
		
		switch(moveChar){
			case 'v': case 'V':
				nPuzzle.solvePuzzle();
				break;
			case 'e': case 'E':
				nPuzzle.writeToFile();
				break;
			case 't': case 'T':
				nPuzzle.printReport();
				break;
		}
	} while(!nPuzzle.isSolved());
	cout << endl << "Puzzle Solved!" << endl;
}
