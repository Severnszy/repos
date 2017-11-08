#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

using namespace std;

FILE *fp;
int ch;
string prog_name, std_prog_name;
string ifile_name, std_ofile_name, ofile_name;
string ofile_content, std_ofile_content;
string cmd;

void gotoxy(int x, int y);
void pause();

int main()
{
	gotoxy(0, 0);
	cout
		<< "CodeJudge\n"
		<< "Version 1.0.0.0\n"
		<< "Copyright (c) 2017 Medoric\n\n";

	Sleep(1000);
	/*cout << "Enter the name of fucking program (no fucking file I/O needed, sonofabitch):\n";
	cin >> prog_name;*/
	/*cout
		<< "Before you use this program, make sure you've got the standard program, the\n"
		<< "program to be judged, the input data and this program in the same directory.\n"
		<< "If you haven't, then move the files into the same directory to proceed.\n\n";*/
	
	cout
		<< "The program to be judged and the CodeJudge in the same directory and the input\n"
		<< "and output data in a subfolder named \"data\" and the file extension MUST be *.in\n"
		<< "(input data file) and *.out (output data file).\n"
		<< "The program to be judged must read input from standard input and write output\n"
		<< "to standard output. (NOT file I/O!).\n"
		<< "Before you proceed, please check all of the above. After you've done that,\n"
		<< "press any key to continue.\n";
	getch();
	cout << '\n';

	cout << "Enter the name of the standard program (without file extension):\n";
	cin >> std_prog_name;
	cout << "Enter the name of the program to be judged (without file extension):\n";
	cin >> prog_name;
	cout << '\n';
	
	//ifile_name = prog_name + ".in";
	std_ofile_name = std_prog_name + ".out";
	ofile_name = prog_name + ".out";
	cmd = std_prog_name + " < " + ifile_name + " > " + std_ofile_name;
	system(cmd.c_str());
	cmd = prog_name + " < " + ifile_name + " > " + ofile_name;
	system(cmd.c_str());
	/*cmd = "type " + std_ofile_name;
	system(cmd.c_str());
	cmd = "type " + ofile_name;
	system(cmd.c_str());*/
	
	fp = fopen(ofile_name.c_str(), "r");
	while ((ch = fgetc(fp)) != EOF)
	{
		ofile_content += ch;
	}
	fclose(fp);
	
	fp = fopen(std_ofile_name.c_str(), "r");
	while ((ch = fgetc(fp)) != EOF)
	{
		std_ofile_content += ch;
	}
	fclose(fp);
	
	if (ofile_content[ofile_content.length() - 1] == '\n') ofile_content.resize(ofile_content.size() - 1);
	if (std_ofile_content[std_ofile_content.length() - 1] == '\n') std_ofile_content.resize(std_ofile_content.size() - 1);
	
	cout << "****** " << ofile_name << '\n';
	cout << ofile_content << '\n';
	cout << "****** " << std_ofile_name << '\n';
	cout << std_ofile_content << '\n';
	cout << "******\n";
	
	if (ofile_content == std_ofile_content) cout << "No differences encountered.\n";
	else cout << "Difference(s) encountered!\n";
	return 0;
}

void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x, pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	return;
}

void pause()
{
	cout << "Press any key to continue . . .";
	getch();
	cout << "\r                               \r";
}
