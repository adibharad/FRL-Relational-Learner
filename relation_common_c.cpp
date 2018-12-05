#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>

using namespace std;

int main()
{
	//=================================================== DECLARATION ==============================================================

	char n[100];
	string n1,n2,n3, n4,line,con,line1,con1;
	size_t length,pos,len,break_len,start,con_len,length1;
	int counter = 0,counter1=0,i,csize,j;
	vector <string> ctext;
	clock_t t1, t2;
	float seconds, diff;

	// ============================================= INPUT/OUTPUT FILES ================================================================

	ifstream datafile;
	datafile.open("COOCS.txt");
	ofstream matched;
	matched.open("matched_context.txt");
	ofstream total;
	total.open("total_trusted.txt");
	ofstream trusted;
	trusted.open("trusted.txt");

	t1 = clock();

	for (i = 0; i < 5; i++)
	{
		//================================================== GETTING THE FIRST NOUN =========================================================

		cout << '\n'<<"Enter the Noun_Pair:";
		cin.getline(n, sizeof(n));
		string noun(n);

		length = noun.size();
		break_len = noun.find('|');
		n1 = noun.substr(pos = 0, len = break_len - 1);
		n2 = noun.substr(pos = break_len + 3);

		//================================================= GETTING ALL THE CONTEXTS ==========================================================

		if (datafile.is_open())
		{
			while (!((n1 == n3 && n2 == n4) || (n1 == n4 && n2 == n3)))
			{
				getline(datafile, line);
				counter++;
				length = line.size();
				start = line.find('\t');
				line1 = line.substr(pos = 0, len = start);
				length1 = line1.size();
				break_len = line1.find('|');
				n3 = line1.substr(pos = 0, len = break_len - 1);
				n4 = line1.substr(pos = break_len + 3);
				cout << counter << "\t";
				if ((n1 == n3 && n2 == n4) || (n1 == n4 && n2 == n3))
				{
					trusted <<counter<<"\t"<< line << "\n";
				}
				line = line.substr(pos = start + 1);
			}
			while (line != "\0")
			{
				start = line.find('\t');
				con = line.substr(pos = 1, len = start);
				con_len = con.find('#');
				con = con.substr(pos = 1, len = con_len - 2);
				ctext.push_back(con);
				total << con << "\n";
				line = line.substr(pos = start + 1);
			}
			datafile.clear();
			datafile.seekg(0, ios::beg);
			counter = 0;
		}
	}
	csize = ctext.size();
	for (i = 0; i < csize; i++)
	{
		con = ctext[i];
		for (j = 0; j < csize; j++)
		{
			con1 = ctext[j];
			if (con == con1)
			{
				counter++;
				ctext[j].erase();
			}
		}
		if (counter == 5 && con !="\0")
		{
			matched << con <<'\n';
		}
		counter = 0;
	}
	datafile.close();
	matched.close();
	trusted.close();
	total.close();
	
	t2 = clock();
	diff = t2 - t1;
	seconds = diff / CLOCKS_PER_SEC;
	
	matched << seconds;

	
	datafile.close();
	matched.close();
	total.close();
	trusted.close();
	
	return 0;
}


