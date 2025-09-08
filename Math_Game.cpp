#include <iostream>
#include <string>
#include <cstdlib>
#include <Windows.h>
using namespace std;
enum questionLevel
{
	easy = 1, medium = 2, hard = 3, mix = 4
};
enum operationType
{
	add = 1, substract = 2, multiply = 3, division = 4,MIX = 5
};
enum terminalColor
{
	green=1,red=2
};
int generateRandomNumberInRange(int, int);
operationType selectOperationType(short operationNumber)
{
	return (operationType)operationNumber;
}
questionLevel selectQuestionNumberLevel(short levelNumber)
{
	return (questionLevel)levelNumber;
}
void finalGameResultTerminalColor(short n)
{
	if (n == 1)
	{
		system("color 2f");
	}
	else if (n == 2)
	{
		system("color 4f");
	}
}

int mixLevelRandomNumberGenerator(short n)
{
	switch (n)
	{
	case 1:
		return generateRandomNumberInRange(1, 10);
	case 2:
		return generateRandomNumberInRange(1, 100);
	case 3:
		return generateRandomNumberInRange(1, 1000);
	default:
		return generateRandomNumberInRange(1, 100);
	}
}
operationType mixOperationTypeGenerator(short n) //Assuming n will be a random number between 1 and 4
{
	switch (n)
	{
	case 1:
	return operationType::add;
	case 2:
	return operationType::substract;
	case 3:
 	return operationType::multiply;
	case 4:
	return operationType::division;
	default:
	{
		return operationType::add;
	}
	    }
}
char generateOperationSymbol(operationType operation)
{
	switch (operation)
	{
	case operationType::add:
		return '+';
	case operationType::substract:
		return '-';
	case operationType::multiply:
		return '*';
	case operationType::division:
		return '/';
	default:
	{
		throw "Error Occured.. the program will close\n";
		exit(1);
	}
	}
}
int calculateOperations(int n1, int n2, operationType choice)
{
	switch (choice)
	{
	case operationType::add:
		return n1 + n2;
	case operationType::substract:
		return n1 - n2;
	case operationType::multiply:
		return n1 * n2;
	case operationType::division:
		return n1 / n2; //Integer Division
	case operationType::MIX:
		return calculateOperations(n1, n2, mixOperationTypeGenerator(generateRandomNumberInRange(1, 4)));
	default:
	{
		cerr << "Error Operation... the program will close" << endl;
		exit(1);
	}
     	}
}
int generateEquationBasedOnLevel(questionLevel difficulty,operationType choice, int &n1,int &n2)
{
	switch (difficulty)
	{
	case questionLevel::easy:
	{
		n1 = generateRandomNumberInRange(1, 10);
		n2 = generateRandomNumberInRange(1, 10);
		return calculateOperations(n1, n2, choice);
	}
	case questionLevel::medium:
	{
		n1 = generateRandomNumberInRange(1, 100);
		n2 = generateRandomNumberInRange(1, 100);
		return calculateOperations(n1, n2, choice);
	}
	case questionLevel::hard:
	{
		n1 = generateRandomNumberInRange(1, 1000);
		n2 = generateRandomNumberInRange(1, 1000);
		return calculateOperations(n1, n2, choice);
	}
	case questionLevel::mix:
	{
		int randomLevel = generateRandomNumberInRange(1, 3);
		n1=mixLevelRandomNumberGenerator(randomLevel);
		n2 = mixLevelRandomNumberGenerator(randomLevel);
		return calculateOperations(n1, n2, choice);
	}

	}

}
int generateRandomNumberInRange(int from, int to)
{
	return rand() % (to - from + 1) + from;
}

int readPositiveInteger(string message)
{
	int x;
	do
	{
		cout << message << '\a';
		cin >> x;
	} while (x <= 0);
	return x;
}
int readNumInRange(string message, int from, int to)
{
	int x;
	do
	{
		cout << message << '\a' << endl;
		cin >> x;
	} while (x < from || x>to);
	return x;
}
void newLineGenerator(short n)
{
	for (int i = 1; i <= n; i++)
	{
		cout << endl;
	}
}
bool hasWon(int numberOfCorrectAnswers, int numberOfWrongAnswers)
{
	return (numberOfCorrectAnswers>=numberOfWrongAnswers);
}
string determineOperationTypeDescriptive(operationType operation)
{
	switch (operation)
	{
	case operationType::add:
		return "Addition\n";
	case operationType::substract:
		return "Substraction\n";
	case operationType::multiply:
		return "Multiplication\n";
	case operationType::division:
		return "Division\n";
	}
}
string determineDifficultyDescriptive(questionLevel level)
{
	switch (level)
	{
	case questionLevel::easy:
		return "Easy\n";
	case questionLevel::medium:
		return "Medium\n";
	case questionLevel::hard:
		return "Hard\n";
	case questionLevel::mix:
		return "Mix\n";
	}
}
void printGameDetails(int numOfQuestion, questionLevel level, operationType operation, int totalNumberOfQuestions, int numberOfCorrectAnswers,int numberOfWrongAnswers)
{
	string word = "";
	bool didYouWin = hasWon(numberOfCorrectAnswers, numberOfWrongAnswers);
	if (didYouWin)
	{
		word = "Pass\n";
		finalGameResultTerminalColor(1);
	}
	else
	{
		word = "Fail\n";
		finalGameResultTerminalColor(2);
	}

	cout << "----------------------------------------------------------------------------------------------------\n";
	cout << "Final Result is: " << word << endl;
	cout << "----------------------------------------------------------------------------------------------------\n";
	cout << "Total Number of Questions: " << numOfQuestion << endl;
	cout << "Difficulty Level: " << determineDifficultyDescriptive(level) << endl;
	cout << "Chosen Operation Type: " << determineOperationTypeDescriptive(operation) << endl;
	cout << "Number of Right Answers: " << totalNumberOfQuestions-numberOfWrongAnswers<< endl;
	cout << "Number of Wrong Answers: " << numberOfWrongAnswers << endl;
}
void startGame()
{
	int numberOfQuestion = readPositiveInteger("How many questions do you want to answer? >0\n");
	int numberOfCorrectlySolvedQuestions=0,numberOfWrongAnswers=0;
	const string numberLevelPrompt = "Enter question level: 1 for easy 2 for meduium 3 for hard 4 for mix\n";
	const string operationTypePrompt = "Enter Operation Type: 1 for addition 2 for substraction 3 for multiplication 4 for division 5 for mix\n";
	questionLevel level = selectQuestionNumberLevel(readNumInRange(numberLevelPrompt, 1, 4));
	operationType operation = selectOperationType(readNumInRange(operationTypePrompt, 1, 5));
	int correctResult; 	char  symbol;
	for (int i = 1; i <= numberOfQuestion; i++)
	{
		operationType useForMixOnly;
		cout << "Question [" << i << "/" << numberOfQuestion << "]" << endl;
		int n1, n2,enterAnswer; //the below function will fill n1,n2 with random numbers
		if (operation == operationType::MIX)
		{
			useForMixOnly = mixOperationTypeGenerator(rand() % 3 + 1);
			correctResult = generateEquationBasedOnLevel(level, useForMixOnly, n1, n2);	
			symbol = generateOperationSymbol(useForMixOnly);
		}
		else {
			correctResult = generateEquationBasedOnLevel(level, operation, n1, n2);
			symbol = generateOperationSymbol(operation);
		}
		cout << n1 << endl;
		cout << n2 << " " << symbol<<endl;
		cout << "----------------------------------------\n";
		cin >> enterAnswer;
		if (enterAnswer == correctResult)
		{
			cout << "Correct Answer" << endl;
			system("color 2f");
			++numberOfCorrectlySolvedQuestions;
		}
		else
		{
			cout << "Wrong Result!\n";
			system("color 4f");
			cout << "The correct answer is: " << correctResult << endl;
			++numberOfWrongAnswers;
		}
		newLineGenerator(3);
	}
	cout << "Generation Game Results.. Please wait\n";
	Sleep(6000);
	printGameDetails(numberOfQuestion,level,operation, numberOfQuestion,numberOfCorrectlySolvedQuestions,numberOfWrongAnswers);
	
}
void clearScreen()
{
	system("cls");
	system("color 0f");
}
char readOneCharacter(string message)
{
	char character;
	cout << message << '\a' << endl;
	cin >> character;
	return character;
}
int main()
{
	srand((unsigned)time(NULL));
	const string playAgainPrompt = "Do you want to play again? Press Y for Yes or N for no";
	char doYouWantToPlayAgain;
	do
	{
		clearScreen();
		startGame();
		doYouWantToPlayAgain = readOneCharacter(playAgainPrompt);
	} while (toupper(doYouWantToPlayAgain) == 'Y');
}