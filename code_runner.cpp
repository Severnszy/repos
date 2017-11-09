#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

using namespace std;

FILE *fp;
int ntest;
int ch;
string prog_name, std_prog_name;
string ifile_name, std_ofile_name;
string std_ofile_contents;
string cmd;

string to_string(int);
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

	cout << "Enter the name of the standard program (without file extension):\n";
	cin >> std_prog_name;
	cout << "Enter the name of the program to be judged:\n";
	cin >> prog_name;
	cout << "Enter the amount of test data files:\n";
	cin >> ntest;
	cout << '\n';

	for (int i = 1; i <= ntest; i++)
	{
		ifile_name = "data\\" + prog_name + to_string(i) + ".in";
		std_ofile_name = "data\\" + prog_name + to_string(i) + ".out";
		cmd = std_prog_name + " < " + ifile_name + " > " + std_ofile_name;
		system(cmd.c_str());

		std_ofile_contents.clear();

		fp = fopen(std_ofile_name.c_str(), "r");
		while ((ch = fgetc(fp)) != EOF) std_ofile_contents += ch;
		fclose(fp);

		if (std_ofile_contents[std_ofile_contents.length() - 1] == '\n') std_ofile_contents.resize(std_ofile_contents.size() - 1);

		cout
			<< "****** " << std_ofile_name << '\n'
			<< std_ofile_contents << '\n'
			<< "*****\n";

		cout << "Test data file #" << i << ": Completed.\n\n";
	}

	cout << "Done.\n";
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

void disp_description()
{
	cout
		<< "Description:\n"
		<< "This program should be used together with CodeJudge. While the CodeJudge judges\n"
		<< "programs, this program generates the output data by running the standard\n"
		<< "program with given inputs.\n";
}

void disp_info()
{
	cout
		<< "CodeRunner\n"
		<< "Version 1.0.0.0\n"
		<< "Copyright (c) 2017 Medoric\n";
}

void disp_instructions()
{
	cout
		<< "How to use CodeRunner:\n\n"
		<< "Location of the files:\n"
		<< "The standard program (the program which produces the correct answer) and the\n"
		<< "the CodeRunner must be under the same directory and the test data under a\n"
		<< "subdirectory \"data\".\n"
		<< '\n'
		<< "I/O:\n"
		<< "The standard program must read input from standard input and write output to\n"
		<< "standard output. (NOT file I/O!)\n"
		<< '\n'
		<< "Test data:\n"
		<< "The file extension must be .in (input). The format of the test data file name\n"
		<< "must be: program name + test# + extension. For instance, the 5th test data\n"
		<< "input file of a program named \"hello_world\" must be named \"hello_world5.in\".\n"
		<< '\n'
		<< "Before you proceed, please check all of the above. After you've done that,\n"
		<< "press any key to continue.\n";
	getch();
}
