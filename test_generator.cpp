#include <bits/stdc++.h>
#include <process.h>

using namespace std;

FILE *fp;
int ntest, nnum;
string prog_name;
string ifile_name;
string ifile_contents;
vector<int> num;

int rand(int, int);
string to_string(int);

int main()
{
	srand((unsigned int)(time(NULL) * _getpid()));

	cout << "Enter the name of the program (without file extension):\n";
	cin >> prog_name;
	cout << "Enter the amount of test data files:\n";
	cin >> ntest;
	cout << '\n';

	for (int i = 1; i <= ntest; i++)
	{
		/*cout << "Enter the contents of the test data input file #" << i << " (in ONE line):\n";
		do getline(cin, ifile_contents); while (ifile_contents == "\n");*/
		
		ifile_contents = to_string(rand(-1000000, 1000000)) + " " + to_string(rand(-1000000, 1000000));
		ifile_name = "data\\" + prog_name + to_string(i) + ".in";

		cout
			<< "****** " << ifile_name << '\n'
			<< ifile_contents << '\n'
			<< "******\n\n";

		fp = fopen(ifile_name.c_str(), "w");
		fprintf(fp, ifile_contents.c_str());
	}
}

string to_string(int x)
{
	stringstream ss;
	string str;
	ss << x;
	str = ss.str();
	return str;
}

int rand(int x, int y)
{
	return (int)(x + (long long)(y - x + 1) * (long long)rand() / (long long)(RAND_MAX + 1));
}

