#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

using namespace std;

FILE *fp;
int ntest, nac = 0;
int ch;
string prog_name;
string ifile_name, std_ofile_name, ofile_name;
string ofile_contents, std_ofile_contents;
string cmd;

string to_string(int);
void gotoxy(int x, int y);
void disp_description();
void disp_info();
void disp_instructions();

int main()
{
	disp_info();
	cout << '\n';
	disp_description();
	cout << "Press any key to continue . . .";
	getch();
	cout << "\r                               \r";
	cout << '\n';

	disp_instructions();

	system("cls");
	disp_info();
	cout << '\n';

	cout << "Enter the name of the program to be judged (without file extension):\n";
	cin >> prog_name;
	cout << "Enter the amount of test data files:\n";
	cin >> ntest;
	cout << '\n';

	ofile_name = "data\\" + prog_name + ".out";
	
	for (int i = 1; i <= ntest; i++)
	{
		ifile_name = "data\\" + prog_name + to_string(i) + ".in";
		std_ofile_name = "data\\" + prog_name + to_string(i) + ".out";
		cmd = prog_name + " < " + ifile_name + " > " + ofile_name;

		system(cmd.c_str());
		
		ofile_contents.clear();
		std_ofile_contents.clear();

		fp = fopen(ofile_name.c_str(), "r");
		while ((ch = fgetc(fp)) != EOF) ofile_contents += ch;
		fclose(fp);

		fp = fopen(std_ofile_name.c_str(), "r");
		while ((ch = fgetc(fp)) != EOF) std_ofile_contents += ch;
		fclose(fp);

		if (ofile_contents[ofile_contents.length() - 1] == '\n') ofile_contents.resize(ofile_contents.size() - 1);
		if (std_ofile_contents[std_ofile_contents.length() - 1] == '\n') std_ofile_contents.resize(std_ofile_contents.size() - 1);

		cout
			<< "****** " << ofile_name << '\n'
			<< ofile_contents << '\n'
			<< "****** " << std_ofile_name << '\n'
			<< std_ofile_contents << '\n'
			<< "*****\n";

		if (ofile_contents == std_ofile_contents)
		{
			cout << "Test #" << i << ": Accepted.\n\n";
			nac++;
		}
		else
		{
			cout << "Test #" << i << ": Unaccepted.\n\n";
		}
	}
	
	cmd = "del " + ofile_name;
	system(cmd.c_str());

	cout << "Your final score: " << (double)nac / (double)ntest * 100.0 << '\n';
	if (nac == ntest) cout << "Congratulations! Your program produced all correct answer(s)!\n";
	else cout << "You program produced " << nac << "/" << ntest << " correct answer(s). Please check your source code for mistakes and try again.\n";

	return 0;
}

string to_string(int x)
{
	stringstream ss;
	string str;
	ss << x;
	str = ss.str();
	return str;
}

void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x, pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	return;
}

void disp_description()
{
	cout
		<< "Description:\n"
		<< "This program is used to judge a program to see if it's correct or not. It'll\n"
		<< "need a set of test data inputs and corresponding correct outputs. It'll judge\n"
		<< "by comparing each of the outputs of the program with the corresponding correct\n"
		<< "output. A result will be given.\n";
}

void disp_info()
{
	cout
		<< "CodeJudge\n"
		<< "Version 1.0.0.0\n"
		<< "Copyright (c) 2017 Medoric\n";
}

void disp_instructions()
{
	cout
		<< "How to use CodeJudge:\n\n"
		<< "Location:\n"
		<< "The program to be judged and the CodeJudge must be under the same directory and\n"
		<< "the test data under a subdirectory \"data\".\n"
		<< '\n'
		<< "I/O:\n"
		<< "The program to be judged must read input from standard input and write output\n"
		<< "to standard output. (NOT file I/O!)\n"
		<< '\n'
		<< "Test data files:\n"
		<< "The file extension must be .in (input) and .out (output). The format of the\n"
		<< "test data file name must be: program name + test# + extension. For instance,\n"
		<< "the 5th test data input file of a program named \"hello_world\" must be named\n"
		<< "\"hello_world5.in\".\n"
		<< '\n'
		<< "Before you proceed, please check all of the above. After you've done that,\n"
		<< "press any key to continue.\n";
	getch();
}
