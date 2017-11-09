#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

using namespace std;

FILE *fp;
int ch;
int ntest;
int nac = 0;
string prog_name/*, std_prog_name*/;
string ifile_name, std_ofile_name, ofile_name;
string ofile_content, std_ofile_content;
string cmd;

string to_string(int);
void gotoxy(int x, int y);
void show_info();
void show_instructions();

int main()
{
	// Info
	show_info();
	Sleep(1000);

	// Instructions
	show_instructions();

	system("cls");

	/*cout << "Enter the name of the standard program (without file extension):\n";
	cin >> std_prog_name;*/
	cout << "Enter the name of the program to be judged (without file extension):\n";
	cin >> prog_name;
	cout << "Enter the number of test datas:\n";
	cin >> ntest;
	cout << '\n';
	
	for (int i = 1; i <= ntest; i++)
	{
		ifile_name = "data\\" + prog_name + to_string(i) + ".in";
		std_ofile_name = "data\\" + prog_name + to_string(i) + ".out";
		ofile_name = "data\\" + prog_name + ".out";
		cmd = prog_name + " < " + ifile_name + " > " + ofile_name;

		system(cmd.c_str());

		fp = fopen(ofile_name.c_str(), "r");
		while ((ch = fgetc(fp)) != EOF) ofile_content += ch;
		fclose(fp);

		fp = fopen(std_ofile_name.c_str(), "r");
		while ((ch = fgetc(fp)) != EOF) std_ofile_content += ch;
		fclose(fp);

		if (ofile_content[ofile_content.length() - 1] == '\n') ofile_content.resize(ofile_content.size() - 1);
		if (std_ofile_content[std_ofile_content.length() - 1] == '\n') std_ofile_content.resize(std_ofile_content.size() - 1);

		cout << "****** " << ofile_name << '\n';
		cout << ofile_content << '\n';
		cout << "****** " << std_ofile_name << '\n';
		cout << std_ofile_content << '\n';
		cout << "*****\n";

		if (ofile_content == std_ofile_content)
		{
			cout << "Test #" << i << ": Accepted.\n";
			nac++;
		}
		else
		{
			cout << "Test #" << i << ": Unaccepted.\n";
		}
	}

	cout << "Your final score: " << (double)nac / (double)ntest * 100.0 << '\n';
	if (nac == ntest) cout << "Congratulations! Your program produced all correct answers!\n";
	else cout << "You program produced " << nac << "/" << ntest << " correct answers. Please check your source code for mistakes and try again.\n";

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

void show_info()
{
	cout
		<< "CodeJudge\n"
		<< "Version 1.0.0.0\n"
		<< "Copyright (c) 2017 Medoric\n\n";
	cout
		<< "Note:\n"
		<< "This is CodeJudge v1.0.0.0, and is not fully developed yet. It still can't tell\n"
		<< "if some mistakes in the source code make the program crash (runtime error) or\n"
		<< "if the program runs too slowly and exceeded the time limit (time limit\n"
		<< "exceeded).\n"
		<< "To be fixed and improved . . .\n\n";
}

void show_instructions()
{
	cout
		<< "How to use CodeJudge:\n\n"
		<< "Location:\n"
		<< "The program to be judged and the CodeJudge must be in the same directory and\n"
		<< "the test data in a subfolder named \"data\".\n"
		<< '\n'
		<< "I/O:\n"
		<< "The program to be judged must read input from standard input and write output\n"
		<< "to standard output. (NOT file I/O!)\n"
		<< '\n'
		<< "Test data:\n"
		<< "The file extension must be .in (input) and .out (output). The format of the\n"
		<< "test data file name must be: program name + test# + extension. For instance,\n"
		<< "the 5th test data input file of a program named \"hello_world\" must be named\n"
		<< "\"hello_world5.in\".\n"
		<< '\n'
		<< "Before you proceed, please check all of the above. After you've done that,\n"
		<< "press any key to continue.\n";
	getch();
}
