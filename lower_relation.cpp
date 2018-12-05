#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;




//--------------------------------------------- MAIN CODE ----------------------------------------------------------------
int main()
{
	//------------------------------------------ Declarations -------------------------------------------------------------

	string line, main_n, noun1, n1, newline, sum, c2, main_c, value, n2, n3, n4, trust_n, trusted_noun, noun, line1;
	int i = 0, j = 0, a = 1, con2_len, counter = 0, omega_2 = 0;
	size_t start, pos, len, length1, start1, ttc_len,start2;
	vector <string> total_trusted_context; vector<string>con2; vector<double>membership; vector<string>new_trusted_noun;
	double m = 0, m1 = 0;
//	clock_t t1, t2;
	//float seconds, diff;


	//-------------------------------------- Opening of the Files ------------------------------------------------------

//	t1 = clock();

	ifstream datafile;
	datafile.open("COOCS.txt");
	ifstream tt;
	tt.open("total_trusted.txt");
	ofstream lower;
	lower.open("lower.txt");





	while (!tt.eof())
	{
		getline(tt, line);
		total_trusted_context.push_back(line);
	}
	ttc_len = total_trusted_context.size();
	omega_2 = (ttc_len * 3) / 100;


	//-------------------------------------------------------------------------- for the complete dataset ----------------------------------------------------------------------------------------
	while (!datafile.eof())
	{
		getline(datafile, line);
		cout << a << "\t";
		if (line == "\0")
		{
			break;
		}

		start = line.find('\t');
		noun = line.substr(pos = 0, len = start);
		length1 = noun.size();

		line1 = line.substr(length1 + 1);
		newline = line1;

		while (newline != "\0")
		{
			start1 = newline.find('\t');
			c2 = newline.substr(pos = 2, len = start1);
			start2 = c2.find("-#-");
			c2 = c2.substr(pos = 0, len = start2);
			con2.push_back(c2);
			newline = newline.substr(start1 + 1);
		}
		con2_len = con2.size();

		if (con2_len >= omega_2)
		{
			for (i = 0; i < con2_len; i++)
			{
				c2 = con2[i];
				for (j = 0; j < ttc_len; j++)
				{
					main_c = total_trusted_context[j];
					if (main_c == c2)
					{
						counter++;
					}
				}
			}
			if (counter >= omega_2)
			{
				lower << a << "\t" << counter << "\t" << line << "\n";
			}
		}

		counter = 0; con2.clear(),a++;
	}




	/*------------------------------------ Closing all the files ----------------------------------------------------*/


/*	t2 = clock();
	diff = t2 - t1;
	seconds = diff / CLOCKS_PER_SEC;

	lower << seconds; */



	datafile.close();
	tt.close();
	lower.close();

	return 0;
}








