#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string encrypt(string plaintext, int key);
string decrypt(string ciphertext, int key);
void encryptFile(string inputFileName, string outputFileName, int key);
void decryptFile(string inputFileName, string outputFileName, int key);
bool isPrime(int num);
int nextPrime(int num);
int previousPrime(int num);

int main()
{
	string choice, inputFile, outputFile;
	int key;

	cout << string(36, ' ');
	cout << "Welcome to my encryption algorithm\n";
	cout << endl;

	cout << string(30, ' ');
	cout << "||==========================================||\n";

	cout << string(34, ' ');
	cout << "3. Enter 'Encrypt' to encrypt a .txt file.\n";
	cout << string(34, ' ');
	cout << "2. Enter 'Decrypt' to decrypt a .txt file.\n";
	cout << string(34, ' ');
	cout << "1. Enter 'Exit' to exit the program.\n";

	cout << string(30, ' ');
	cout << "||==========================================||\n";
	cout << string(30, ' ');
	cout << "Enter choice: ";
	cin >> choice;

	if (choice == "Exit" || choice == "exit")
	{
		exit(0);
	}

	bool correct = false;
	while (!correct)
	{
		if (choice == "Encrypt" || choice == "encrypt" || choice == "Decrypt" || choice == "decrypt")
		{
			correct = true;
		}
		else if (choice == "Exit" || choice == "exit")
		{
			exit(0);
		}
		else
		{
			cout << string(30, ' ');
			cout << "Choose 'Encrypt' , 'Decrypt', or 'Exit': ";
			cin >> choice;
		}
	}

	correct = false;
	while (!correct)
	{
		cout << string(30, ' ');
		cout << "Input file name: ";
		cin >> inputFile;

		size_t found = inputFile.find(".txt");

		if (found != string::npos)
		{
			correct = true;
		}
		else
		{
			cout << string(30, ' ');
			cout << "It must be a .txt file.\n";
		}
	}

	correct = false;
	while (!correct)
	{
		cout << string(30, ' ');
		cout << "Output file name: ";
		cin >> outputFile;

		size_t found = outputFile.find(".txt");

		if (found != string::npos)
		{
			correct = true;
		}
		else
		{
			cout << string(30, ' ');
			cout << "It must be a .txt file.\n";
		}
	}

	correct = false;
	while (!correct)
	{
		cout << string(30, ' ');
		cout << "Enter key (whole number): ";
		cin >> key;

		if (key >= 0)
		{
			correct = true;
		}
		else
		{
			cout << string(30, ' ');
			cout << "It must be a positive number.\n";
		}
	}

	if (choice == "Encrypt" || choice == "encrypt")
	{
		encryptFile(inputFile, outputFile, key);

		string choice = "";
		cout << string(30, ' ');
		cout << "Would you like to decrypt the file into " << inputFile << "? (Y/N): ";
		cin >> choice;

		if (choice == "Y" || choice == "y")
		{
			decryptFile(inputFile, outputFile, key);
		}
	}
	else
	{
		decryptFile(inputFile, outputFile, key);
		string choice = "";
		cout << string(30, ' ');
		cout << "Would you like to encrypt the file into " << outputFile << "? (Y/N): ";
		cin >> choice;

		if (choice == "Y" || choice == "y")
		{
			decryptFile(inputFile, outputFile, key);
		}
	}

	return 0;
}

string encrypt(string plaintext, int key)
{
	string encryptedText = plaintext;
	for (char& c : encryptedText)
	{
		if (isPrime(c))							// Checks if character is a prime number
		{
			c = nextPrime(c);
		}
		else if (c % 2 == 0 && key % 2 == 0)	// Checks if character and key are even
		{
			c = c - (key + 32);
		}
		else if (c % 2 != 0 && key % 2 == 0)	// Checks if character is odd and key is even
		{
			c = c + 18;
		}
		else
		{
			c = c + key;
		}
	}
	return encryptedText;
}

string decrypt(string ciphertext, int key)
{
	string decryptedText = ciphertext;
	for (char& c : decryptedText)
	{
		if (isPrime(c))
		{
			c = previousPrime(c);
		}
		else if (c % 2 == 0 && key % 2 == 0)
		{
			c = c + (key + 32);
		}
		else if (c % 2 != 0 && key % 2 == 0)
		{
			c = c - 18;
		}
		else
		{
			c = c - key;
		}
	}
	return decryptedText;
}

void encryptFile(string inputFileName, string outputFileName, int key)
{
	ifstream inputFile(inputFileName);
	ofstream outputFile(outputFileName);
	string line;

	if (inputFile.is_open() && outputFile.is_open())
	{
		while (getline(inputFile, line))
		{
			outputFile << encrypt(line, key) << endl;
		}
	}
	else
	{
		cout << "Error! Cannot find file!" << endl;
	}
	inputFile.close();
	outputFile.close();
}

void decryptFile(string inputFileName, string outputFileName, int key) 
{
	ifstream inputFile(inputFileName);
	ofstream outputFile(outputFileName);
	string line;

	if (inputFile.is_open() && outputFile.is_open())
	{
		while (getline(inputFile, line))
		{
			outputFile << decrypt(line, key) << endl;
		}
	}
	else
	{
		cout << "Error! Cannot find file!" << endl;
	}

	inputFile.close();
	outputFile.close();
}

bool isPrime(int num)
{
	if (num <= 1)
	{
		return false;
	}

	for (int i = 2; i < num; ++i)
	{
		if (num % i == 0)
		{
			return false;
		}
	}
	return true;
}

int nextPrime(int num)
{
	if (num <= 1)
	{
		return 2;
	}

	int prime = num;
	bool found = false;

	while (!found)
	{
		++prime;

		if (isPrime(prime))
		{
			found = true;
		}
	}
	return prime;
}

int previousPrime(int num)
{
	if (num <= 1)
	{
		return 2;
	}

	int prime = num;
	bool found = false;

	while (!found)
	{
		--prime;

		if (isPrime(prime))
		{
			found = true;
		}
	}
	return prime;
}