#include <bits/stdc++.h>
#include <conio.h>
#include <io.h>
#include <windows.h>
#include <stdio.h>

using namespace std;

bool is_timeout;
clock_t clock_begin, clock_end;
double score = 0.0;
DWORD exit_code;
FILE *fp;
int nprog;
int nt;
int nac;
int cp_return_val;
int ch;
PROCESS_INFORMATION pi;
STARTUPINFO si = {sizeof(si)};
string pn;
string path;
string tdifile_name, std_tdofile_name, tdofile_name;
string tdofile_contents, std_tdofile_contents;
string cmd, cmdtk;
vector<string> prog_name;
vector<int> ntest;

bool find_file(string, string);
void gotoxy(int x, int y);
void disp_description();
void disp_info();
void disp_instructions();
void pause();

int main()
{
	disp_info();
	cout << "\n\n";
	disp_description();
	pause();
	cout << "\n\n";

	disp_instructions();

	system("cls");
	disp_info();
	cout << "\n\n";

	prog_name.push_back("");
	ntest.push_back(0);

	cout
		<< "Enter the full path of the directory under which the test data files and the\n"
		<< "source files are kept:\n";
	do getline(cin, path);
	while (path.empty());
	cout << '\n';

	cout << "Enter the number of programs:\n";
	cin >> nprog;
	cout << '\n';

	for (int i = 1; i <= nprog; i++)
	{
		cout << '#' << i << '\n';
		cout << "Name of program: "; cin >> pn; prog_name.push_back(pn);
		cout << "Number of pairs of test data files: "; cin >> nt; ntest.push_back(nt);
		cout << '\n';
	}

	for (int i = 1; i <= nprog; i++)
	{
		nac = 0;

		cout << "#" << i << ": " << prog_name[i] << '\n';

		if (!find_file(path + "\\src\\" + prog_name[i], prog_name[i] + ".cpp"))
		{
			cout << "Source file " << prog_name[i] + ".cpp" << " not found.\n";
			continue;
		}

		cout << "Compiling source file...\n";
		cmd = "(g++ \"" + path + "\\src\\" + prog_name[i] + '\\' + prog_name[i] + ".cpp\" -o \"" + path + "\\src\\" + prog_name[i] + '\\' + prog_name[i] + ".exe\" -std=c++17)";
		system(cmd.c_str());

		cout << "Judging program...\n";
		tdofile_name = path + '\\' + prog_name[i] + ".out";
		for (int j = 1; j <= ntest[i]; j++)
		{
			cout << "Test #" << j << ":\n";
			if (!find_file(path + "\\data\\" + prog_name[i], prog_name[i] + to_string(j) + ".in") || !find_file(path + "\\data\\" + prog_name[i], prog_name[i] + to_string(j) + ".out"))
			{
				cout << "Test data file #" << j << " not found.\n";
				continue;
			}

			tdifile_name = path + "\\data\\" + prog_name[i] + '\\' + prog_name[i] + to_string(j) + ".in";
			std_tdofile_name = path + "\\data\\" + prog_name[i] + '\\' + prog_name[i] + to_string(j) + ".out";
			cmd = "cmd.exe /c (\"" + path + "\\src\\" + prog_name[i] + '\\' + prog_name[i] + ".exe\" < \"" + tdifile_name + "\" > \"" + tdofile_name + "\")";

			is_timeout = false;
			clock_begin = clock();

			if (CreateProcess(NULL, (char *)cmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
			{
				switch (WaitForSingleObject(pi.hProcess, 1500))
				{
				case WAIT_TIMEOUT:
					cmdtk = "taskkill /pid " + to_string(pi.dwProcessId) + " /f 1>nul 2>nul"; // 1>nul 2>nul
					system(cmdtk.c_str());
					cmdtk = "taskkill /im " + prog_name[i] + ".exe /f 1>nul 2>nul"; // 1>nul 2>nul
					system(cmdtk.c_str());
					is_timeout = true;
					break;
				case WAIT_FAILED:
					cout << "WaitForSingleObject WAIT_FAILED\n";
					break;
				}
			}
			clock_end = clock();

			DWORD exitCode = 0;  
			if (!GetExitCodeProcess(pi.hProcess, &exit_code))
			{
				cout << "GetExitCodeProcess() failed: " << GetLastError() << '\n';
			}

			tdofile_contents.clear();
			std_tdofile_contents.clear();

			fp = fopen(tdofile_name.c_str(), "r");
			while ((ch = fgetc(fp)) != EOF) tdofile_contents += ch;
			fclose(fp);

			fp = fopen(std_tdofile_name.c_str(), "r");
			while ((ch = fgetc(fp)) != EOF) std_tdofile_contents += ch;
			fclose(fp);

			if (tdofile_contents[tdofile_contents.length() - 1] == '\n') tdofile_contents.resize(tdofile_contents.size() - 1);
			if (std_tdofile_contents[std_tdofile_contents.length() - 1] == '\n') std_tdofile_contents.resize(std_tdofile_contents.size() - 1);


			cout << "****** " << tdofile_name << '\n';
			if (tdofile_contents.length() <= 128) cout << tdofile_contents << '\n';
			else cout << "This file contains too much characters to be shown here.\n";
			cout << "****** " << std_tdofile_name << '\n';
			if (std_tdofile_contents.length() <= 128) cout << std_tdofile_contents << '\n';
			else cout << "This file contains too much characters to be shown here.\n";
			cout << "******\n";

			cout << "Time elapsed: " << clock_end - clock_begin << " ms\n";

			if (tdofile_contents == std_tdofile_contents && clock_end - clock_begin <= 1000 && exit_code == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "ACCEPTED\n\n";
				nac++;
			}
			else if (tdofile_contents != std_tdofile_contents && !is_timeout && exit_code == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "WRONG ANSWER\n\n";
				Sleep(500);
			}
			else if (clock_end - clock_begin > 1000 || is_timeout && exit_code == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
				cout << "TIME LIMIT EXCEEDED\n\n";
				Sleep(500);
			}
			else if (exit_code != 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED);
				cout << "RUNTIME ERROR\n\n";
				Sleep(500);
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		}

		cmd = "del \"" + tdofile_name + '\"';
		system(cmd.c_str());

		cout << "Your score: " << (double)nac / (double)ntest[i] * 100.0 << '\n';
		score += (double)nac / (double)ntest[i] * 100.0;
		if (nac == ntest[i]) cout << "Congratulations! Your program produced all correct answer(s)!\n";
		else
		{
			cout
				<< "You program produced " << nac << "/" << ntest[i] << " correct answer(s).\n"
				<< "Please check your source code for mistakes and try again.\n";
		}
		pause();
		cout << '\n';
	}

	cout << "Your total score: " << score << "/" << 100 * nprog << "\n";

	return 0;
}

bool find_file(string path, string file_name)
{
	int h_file = 0;
	_finddata_t file_info;
	if ((h_file = _findfirst((path + "\\*").c_str(), &file_info)) != -1)
	{
		do
		{
			if ((file_info.attrib & _A_SUBDIR))
			{
				if (strcmp(file_info.name, ".") != 0 && strcmp(file_info.name, "..") != 0)
				{
					if (find_file(path + "\\" + file_info.name, file_name)) return true;
				}
			}
			else
			{
				if (file_info.name == file_name) return true;
			}
		} while (_findnext(h_file, &file_info) == 0);
		_findclose(h_file);
	}
	return false;
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
		<< "DESCRIPTION\n"
		<< "\n"
		<< "This program is used to judge a program to see if it's correct or not. It'll\n"
		<< "need a set of test data inputs and corresponding correct outputs. It'll judge\n"
		<< "by comparing each of the outputs of the program with the corresponding correct\n"
		<< "output. A result will be given.\n";
}

void disp_info()
{
	cout
		<< "CodeJudge\n"
		<< "Version 2.0.0.0\n"
		<< "Copyright (c) 2018 Medoric\n";
}

void disp_instructions()
{
	cout
		<< "INSTRUCTIONS\n"
		<< "\n"
		<< "1. Preparation\n"
		<< "   Put the source file of a certain program under the directory\n"
		<< "   \"{path}\\src\\{prog_name}\", where {path} is any path of the directory\n"
		<< "   under which you keep your files, and {prog_name} is the name of your\n"
		<< "   program.\n"
		<< "   Put the test data files of a certain program under the directory\n"
		<< "   \"{path}\\data\\{prog_name}\".\n"
		<< "   The full name of the source files must be {prog_name}.cpp, and the full name\n"
		<< "   of the test data input files and output files must be {prog_name}{test #}.in\n"
		<< "   and {prog_name}{test #}.out, respectively, where {test #} is the ordinal\n"
		<< "   number of the test data files.\n"
		<< "   You can judge multiple programs at once, that's why each source file and\n"
		<< "   each set of test data files must be kept in a subdirectory of \"{path}\\src\"\n"
		<< "   and \"{path}\\data\".\n"
		<< "   For example:\n"
		<< "   If a source file's full path is \"D:\\hello\\src\\hello\\hello.cpp\", that means\n"
		<< "   the {path} is \"D:\\hello\", and the {prog_name} is \"hello\". The corresponding\n"
		<< "   paths of the fifth test data files must be \"D:\\hello\\data\\hello\\hello5.in\"\n"
		<< "   and \"D:\\hello\\data\\hello\\hello5.out\", where the {test #} is 5.\n";
	pause();
	cout << '\n';
	cout
		<< "2. Running the CodeJudge\n"
		<< "   First, the Judge will ask you to enter {path}.\n"
		<< "   Then, the Judge will ask you to enter the number of programs.\n"
		<< "   After that, you'll need to enter {prog_name} and the number of pairs of test\n"
		<< "   data files.\n"
		<< "   Then you'll just have to wait while the Judge compiles, executes the\n"
		<< "   programs and compares the outputs with the correct outputs.\n";
	pause();
	cout << '\n';
	cout
		<< "3. How to handle errors\n"
		<< "   Errors which are caused by the user:\n"
		<< "   If the user's preparation is not done correctly (see step #1), there will be\n"
		<< "   messages appearing if source files and test data files don't exist or\n"
		<< "   haven't been put in the right place.\n"
		<< "   Errors which are caused by the CodeJudge:\n"
		<< "   That occurs when something went wrong when waiting for one of your programs\n"
		<< "   to end, or when the Judge couldn't retrieve the exit code of the program.\n"
		<< "   Normally this wouldn't happen, but when it does, try restarting the\n"
		<< "   CodeJudge and clear any remnants of the programs of the CodeJudge from the\n"
		<< "   RAM. If this doesn't help, then you might have to judge the programs\n"
		<< "   yourself. Sorry if it becomes a problem.\n";
	pause();
}

void get_dirs(string path, vector<string>& dirs)
{
	int h_file = 0;
	_finddata_t file_info;
	if ((h_file = _findfirst((path + "\\*").c_str(), &file_info)) != -1)
	{
		do
		{
			if ((file_info.attrib & _A_SUBDIR))
			{
				if (strcmp(file_info.name, ".") != 0 && strcmp(file_info.name, "..") != 0)
				{
					dirs.push_back(path + "\\" + file_info.name);
					get_dirs(path + "\\" + file_info.name, dirs);
				}
			}
		} while (_findnext(h_file, &file_info) == 0);
		_findclose(h_file);
	}
}

void pause()
{
	cout << "Press any key to continue . . .";
	getch();
	cout << "\r                               \r";
}
