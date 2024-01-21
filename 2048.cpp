#include <iostream>
#include <time.h>
#include <fstream>
#pragma warning(disable:4996)
const char COMMAND_UP = 'w';
const char COMMAND_DOWN = 's';
const char COMMAND_RIGHT = 'd';
const char COMMAND_LEFT= 'a';
const int PERCENT_FOR_TWO = 80;
const int SIZE = 100;
const int MAXSIZE = 10;
bool enterGame();
void printMatrix(int matrix[][MAXSIZE], int n);
bool isMatrixFull(int matrix[][MAXSIZE],  int n);
void addRandomNumber(int matrix[][MAXSIZE], int n, int& score);
void commandInput(int matrix[][MAXSIZE], int n);
int maxNum(int matrix[][MAXSIZE], int n);
void strCat(char* first, char second)
{
	char* temp = first;
	while (!*temp)
	{
		temp++;
	} 
	*temp = second;
	temp++;
	*temp = '\0';

}
int power(int n, int m)
{
	int result = 1;
	for (int i = 0; i < m; i++)
	{
		result *= n;
	}
	return result;
}
int lengthNumber(int number)
{
	int length = 1;
	while (number > 9)
	{
		number /= 10;
		length++;
	}
	return length;
}
void intToStr(char* input, int num)
{
	int length = lengthNumber(num);
	for (int i = power(10, length - 1); i >= 1; i /= 10)
	{
		int digit = (num / i) % 10;
		char digitChar = digit + '0';
		*input = digitChar;
		input++;
	}
	*input = '\0';
}
void printLeaderBoard(int n)
{
	char* number = new char[lengthNumber(n) + 1];
	const char* extension = ".txt";
	intToStr(number, n);
	char* fileName = new char[lengthNumber(n) + 5]; //.txt length
	strcpy(fileName, number);
	strcat(fileName, extension);
	std::ifstream file(fileName);
		if (!file.is_open())
		{
			std::cout << "File not found!";
			return;
		}
		char line[1024];
		while (!file.eof()) //end of file
		{
			file.getline(line, 1024);
			std::cout << line << std::endl;
		}
	file.close();
	delete[] number;
	delete[] fileName;
}
int stringToInt(const char* input)
{
	int result = 0;
	while (*input)
	{
		result += *input - '0';
		result *= 10;
		input++;
	}
	result /= 10;
	return result;
}
void saveGame(int n, const char* nickName, int score)
{
	char* number = new char[lengthNumber(n) + 1];
	const char* extension = ".txt";
	intToStr(number, n);
	char* fileName = new char[lengthNumber(n) + 5]; //.txt length
	strcpy(fileName, number);
	strcat(fileName, extension);
	std::ifstream fileInput(fileName);
	char players[5][1024];
	char points[5][1024];
	int size = 0;
	if (fileInput.is_open())
	{
		while (!fileInput.eof() && size < 5) //end of file //5 players
		{
			fileInput.get(points[size], 1024, ' ');
			fileInput.get();
			fileInput.getline(players[size++], 1024);
		}
		fileInput.close();
		if (size < 5)
		{
			strcpy(players[size], nickName);
			char scoreStr[1024];
			intToStr(scoreStr, score);
			strcpy(points[size++], scoreStr);
		}
		else if (score > stringToInt(points[size - 1]))
		{
			strcpy(players[size - 1], nickName);
			char scoreStr[1024];
			intToStr(scoreStr, score);
			strcpy(points[size - 1], scoreStr);
		}
		else return;
		for (int i = size - 1; i >= 1; i--)
		{
			if (stringToInt(points[i]) > stringToInt(points[i - 1]))
			{
				char tempPlayer[1024];
				char tempScore[1024];
				strcpy(tempPlayer, players[i]);
				strcpy(tempScore, points[i]);

				strcpy(players[i], players[i - 1]);
				strcpy(points[i], points[i - 1]);

				strcpy(players[i - 1], tempPlayer);
				strcpy(points[i - 1], tempScore);
			}
			else break;
		}
	}
	std::ofstream fileOutput(fileName); 
	if (!fileOutput.is_open())
	{
		return;
	}
	if (size == 0)
	{
		fileOutput << score << " " << nickName << std::endl;
	}
	else for (int i = 0; i < size; i++)
	{
		fileOutput << points[i] << " " << players[i] << std::endl;
	}
	fileOutput.close();
	delete[] number;
	delete[] fileName;
}
int main()
{
	srand(time(0));
	if (enterGame())
	{
		char nickName[SIZE];
		int n = 0;
		int score = 0;
		int matrix[MAXSIZE][MAXSIZE] = { 0 };
		std::cout << "Nickname: ";
		std::cin.ignore();
		std::cin.getline(nickName, SIZE);
		std::cout << "Enter a numeber of rows and columns: ";
		std::cin >> n;
		if (n < 4 || n > 10)
		{
			std::cout << "Enter a dimension from 4 to 10!";
			return 0;
		}
		while (true)
		{
			system("CLS");
			addRandomNumber(matrix, n, score);
			printMatrix(matrix, n);
			if (isMatrixFull(matrix, n))
			{
				break;
			}
			commandInput(matrix, n);
		}
		std::cout << "Game ended! Your score is: " << score;
		saveGame(n, nickName, score);
	}
	else 
	{
		int n = 0;
		std::cout << "Enter dimension: ";
		std::cin >> n;
		if (n < 4 || n > 10)
		{
			std::cout << "Enter a dimension from 4 to 10!";
			return 0;
		}
		printLeaderBoard(n);
	}
}
bool enterGame()
{
	int startNum = 0;
	std::cout << "1. Start game" << std::endl;
	std::cout << "2. Leaderboard" << std::endl;
	std::cout << "3. Quit" << std::endl;
	std::cin >> startNum;
	if (startNum == 3)
	{
		exit(0);
	}
	return startNum == 1;
}
void printMatrix(int matrix[][MAXSIZE], int n)
{
	int max = maxNum(matrix, n);
	int maxLength = lengthNumber(max);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int spaces = maxLength - lengthNumber(matrix[i][j]);
			std::cout << matrix[i][j] << "   ";
			for (int i = 0; i < spaces; i++)
			{
				std::cout << " " ;
			}
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}
bool isMatrixFull(int matrix[][MAXSIZE], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] == 0)
			{
				return false;
			}
			if (i < n-1 && matrix[i][j] == matrix[i+1][j])
			{
				return false;
			}
			if (j < n-1 && matrix[i][j] == matrix[i][j+1])
			{
				return false;
			}
		}
	}
	return true;
}
void addRandomNumber(int matrix[][MAXSIZE], int n, int& score)
{
	bool isFull = true;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] == 0)
			{
				isFull = false;
			}
		}
	}
	if (isFull)
	{
		return;
	}
	int x = 0;
	int y = 0;
	do
	{
		x = rand() % n;
		y = rand() % n;
	} while (matrix[x][y] != 0);
	int odds = rand() % 100;
	if (odds < PERCENT_FOR_TWO)
	{
		matrix[x][y] = 2;
	}
	else { matrix[x][y] = 4; }
	score += matrix[x][y];
}
void commandInput(int matrix[][MAXSIZE], int n)
{
	char command;
	bool isInvalid = false;
	do
	{
		if (isInvalid)
		{
			std::cout << "Invalid input!" << std::endl;
		}
		std::cout << "Enter command: ";
		std::cin >> command;
		isInvalid = command != COMMAND_UP && command != COMMAND_DOWN &&
			command != COMMAND_LEFT && command != COMMAND_RIGHT;
	} while (isInvalid);
	switch (command)
	{
	  case COMMAND_LEFT:
		  for (int i = 0; i < n; i++)
		  {
			  int firstZero = -1;
			  for (int j = 0; j < n; j++)
			  {
				  if (matrix[i][j] != 0)
				  {
					  if (j > 0 && matrix[i][j] == matrix[i][j - 1])
					  {
						  matrix[i][j - 1] += matrix[i][j];
						  matrix[i][j] = 0;
						  firstZero = j;
					  }
					  else if (firstZero > 0 && matrix[i][j] == matrix[i][firstZero - 1])
					  {
						  matrix[i][firstZero - 1] += matrix[i][j];
						  matrix[i][j] = 0;
					  }
					  else if (firstZero != -1)
					  {
						  matrix[i][firstZero] = matrix[i][j];
						  matrix[i][j] = 0;
						  firstZero++;
					  }
				  }
				  else if (firstZero == -1)
				  {
					  firstZero = j;
				  }
			  }
		  }
		  break;
	  case COMMAND_RIGHT:
		  for (int i = 0; i < n; i++)
		  {
			  int firstZero = -1;
			  for (int j = n - 1; j >= 0; j--)
			  {
				  if (matrix[i][j] != 0)
				  {
					  if (j < n - 1 && matrix[i][j] == matrix[i][j + 1])
					  {
						  matrix[i][j + 1] += matrix[i][j];
						  matrix[i][j] = 0;
						  firstZero = j;
					  }
					  else if (firstZero!= -1 && firstZero != n-1 && matrix[i][j] == matrix[i][firstZero + 1])
					  {
						  matrix[i][firstZero + 1] += matrix[i][j];
						  matrix[i][j] = 0;
					  }
					  else if (firstZero != -1)
					  {
						  matrix[i][firstZero] = matrix[i][j];
						  matrix[i][j] = 0;
						  firstZero--;
					  }
				  }
				  else if (firstZero == -1)
				  {
					  firstZero = j;
				  }
			  }
		  }
		  break;
	  case COMMAND_UP:
		  for (int i = 0; i < n; i++)
		  {
			  int firstZero = -1;
			  for (int j = 0; j < n; j++)
			  {
				  if (matrix[j][i] != 0)
				  {
					  if (j > 0 && matrix[j][i] == matrix[j - 1][i])
					  {
						  matrix[j -1][i] += matrix[j][i];
						  matrix[j][i] = 0;
						  firstZero = j;
					  }
					  else if (firstZero > 0 && matrix[j][i] == matrix[firstZero - 1][i])
					  {
						  matrix[firstZero - 1][i] += matrix[j][i];
						  matrix[j][i] = 0;
					  }
					  else if (firstZero != -1)
					  {
						  matrix[firstZero][i] = matrix[j][i];
						  matrix[j][i] = 0;
						  firstZero++;
					  }
				  }
				  else if (firstZero == -1)
				  {
					  firstZero = j;
				  }
			  }
		  }
		  break;
	  case COMMAND_DOWN:
		  for (int i = 0; i < n; i++)
		  {
			  int firstZero = -1;
			  for (int j = n - 1; j >= 0; j--)
			  {
				  if (matrix[j][i] != 0)
				  {
					  if (j < n - 1 && matrix[j][i] == matrix[j + 1][i])
					  {
						  matrix[j + 1][i] += matrix[j][i];
						  matrix[j][i] = 0;
						  firstZero = j;
					  }
					  else if (firstZero != -1 && firstZero != n - 1 && matrix[j][i] == matrix[firstZero +1][i])
					  {
						  matrix[firstZero + 1][i] += matrix[j][i];
						  matrix[j][i] = 0;
					  }
					  else if (firstZero != -1)
					  {
						  matrix[firstZero][i] = matrix[j][i];
						  matrix[j][i] = 0;
						  firstZero--;
					  }
				  }
				  else if (firstZero == -1)
				  {
					  firstZero = j;
				  }
			  }
		  }
		  break;


	default:
		break;
	}
}
int maxNum(int matrix[][MAXSIZE], int n)
{
	int max = INT_MIN;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] > max)
			{
				max = matrix[i][j];
			}
		}
	}
	return max;
}
