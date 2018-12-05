#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

double lower, base = 0;
int used_len = 0,i,j;

//--------------------------------------------------------------------- S-function ------------------------------------------------------------------

float s_function(double y1)
{
	double alpha = 0.001, beta = 0.02;

	if (y1 > 0.5)
	{
		y1 = 1;
	}

	else if (y1 <= 0.5 && y1 > 0.05)
	{
		y1 = (y1 - beta) / (beta - alpha);	
		if (y1 > 1)
		{
			y1 = 1;
		}
		else
		{
			y1 = y1;
		}
	}

	else if (y1 <= 0.05 && y1 >= 0.005)
	{
		y1 = (y1 - alpha) / (beta - alpha);
		if (y1 > 1)
		{
			y1 = 1;
		}
		else
		{
			y1 = y1;
		}
	}

	else
	{
		y1 = 2;
	}
	return y1;
}

//------------------------------------------ getting the lowset membership from the trusted set -------------------------------------------------------

float lower_f(vector <double> low)
{
	int i, low_len;
	double low_1;

	low_len = low.size();
	lower = 0;

	for (i = 0; i < low_len; i++)
	{
		low_1 = low[i];
		{	lower = low_1 + lower;	}
	}

	lower = lower / 5;
	lower = (lower * 30) / 100;

	return(lower);
}

//------------------------------------- finding the top seeds ---------------------------------------------------------

float top(vector <double> t)
{
	int t_len, i, position_len, p, j;
	t_len = t.size();
	float a, b = 0;
	vector <float> position;

	position_len = position.size();

	for (i = 0; i < t_len; i++)
	{
		a = t[i];
		if (t[i] > b)
		{
			b = t[i];
		}
	}

	for (j = 0; j < t_len; j++)
	{
		a = t[j];
		if (b == t[j])
		{
			p = j;
			break;
		}
	}

	return (p);
}


//--------------------------------------------- MAIN CODE ----------------------------------------------------------------
int main()
{
	//------------------------------------------ Declarations -------------------------------------------------------------

	string line, main_n, noun1, n1, newline, sum, c2, main_c, value, n2, n3, n4, trust_n, trusted_noun,m2,u1,u2;
	int noun_len, a = 0, con2_len, con_len, k, mem_len, location,b=0;
	size_t length,start,pos,len,length1,start1,delim,break_len,sum_len,membership_len,m2_len;
	vector <string> trustn; vector <string> comcon; vector<string>con2; vector<double>membership; vector<string>new_trusted_noun; vector<string>used1;
	double val, x, s, m = 0, m1 = 0, fuz_mem;
	float theta_1=0, theta_2=0;
/*	clock_t t1, t2;
	float seconds, diff;*/
	 

	//-------------------------------------- Opening of the Files ------------------------------------------------------
	
//	t1 = clock();

	ifstream datafile;
	datafile.open("lower.txt");
	ifstream comc;
	comc.open("matched_context.txt");
	ifstream trusted;
	trusted.open("trusted.txt");
	ifstream row;
	row.open("row_sum.txt");
	ofstream fuzzy;
	fuzzy.open("fuzzy.txt");
	ifstream used;
	used.open("used.txt");

	while (!used.eof())
	{
		getline(used, line);
		used1.push_back(line);
	}
	used_len = used1.size();
	line.clear();
	
	while (!comc.eof())
	{
		getline(comc, line);
		comcon.push_back(line);
	}
	con_len = comcon.size();
	line.clear();

	//------------------------------------ Calculating membership for the trusted nouns ----------------------------------------

	while (!trusted.eof())
	{
		getline(trusted, line);
		trustn.push_back(line);
	}
	noun_len = trustn.size();
	line.clear();
	
	for (i = 0; i < noun_len; i++)
	{

		line = trustn[i];
	//	length = line.size();
		sum_len = line.find('\t');
		sum = line.substr(pos = 0,len=sum_len);
		a = stoi(sum);
		line = line.substr(sum_len+1);
		start = line.find('\t');
		trust_n = line.substr(pos = 0, len = start);
		length1 = trust_n.size();
		break_len = trust_n.find('|');
		n3 = trust_n.substr(pos = 0, len = break_len - 1);
		n4 = trust_n.substr(pos = break_len + 3, len = length1);
		line = line.substr(length1 + 1);
		newline = line;

		while (newline != "\0")
		{
			start1 = newline.find('\t');
			c2 = newline.substr(pos = 2, len = start1);
			con2.push_back(c2);
			newline = newline.substr(start1 + 1);
		}
		con2_len = con2.size();

		if (row.is_open())
		{
			for (j = 1; j <= a; j++)
			{
				getline(row, sum);
			}

			row.clear();
			row.seekg(0, ios::beg);
			s = stof(sum);
		}

	

		for (j = 0; j < con_len; j++)
		{
			main_c = comcon[j];
			length = main_c.size();
			main_c = main_c.substr(pos = 0,len= length - 1);
			for (k = 0; k < con2_len; k++)
			{
				c2 = con2[k];
				delim = c2.find("-#-");
				value = c2.substr(delim + 3);
				c2 = c2.substr(pos = 0, len = delim - 1);
				if (main_c == c2)

					//----------------------- calaculating membership --------------------------------------
				{
					val = stof(value);
					x =	val / s;
					m = s_function(x);
					if (m == 2)
					{
						m = 0;
					}
					m1 = m1 + m;
				}
			}

		}
		membership.push_back(m1);
		datafile.clear();
		datafile.seekg(0, ios::beg);
		a = 1;	m = 0;	m1 = 0;
		con2.clear();
	}
	mem_len = membership.size();
	lower = lower_f(membership);
	membership.clear();
	line.clear();

	//-------------------------------------------------------------------------- for the complete dataset ----------------------------------------------------------------------------------------
	while (!datafile.eof())
	{
		getline(datafile, line);
		if (line == "\0")
		{
			break;
		}

		sum_len = line.find('\t');
		sum = line.substr(pos = 0, len = sum_len);
		a = stoi(sum);
		line = line.substr(sum_len+1);

		m2_len = line.find('\t');
		m2 = line.substr(pos=0,len = m2_len);
		theta_2 = stof(m2);
		line = line.substr(m2_len + 1);
		
		start = line.find('\t');
		trust_n = line.substr(pos = 0, len = start);
		line = line.substr(start + 1);
		newline = line;

		while (newline != "\0")
		{
			start1 = newline.find('\t');
			c2 = newline.substr(pos = 2, len = start1);
			con2.push_back(c2);
			newline = newline.substr(start1 + 1);
		}
		con2_len = con2.size();

		if (row.is_open())
		{
			for (j = 1; j <= a; j++)
			{
				getline(row, sum);
			}

			row.clear();
			row.seekg(0, ios::beg);
			s = stof(sum);
		}

		for (j = 0; j < con_len; j++)
		{
			main_c = comcon[j];
			length = main_c.size();
			main_c = main_c.substr(pos = 0, len = length - 1);
			for (k = 0; k < con2_len; k++)
			{
				c2 = con2[k];
				delim = c2.find("-#-");
				value = c2.substr(delim + 3);
				c2 = c2.substr(pos = 0, len = delim - 1);
				if (main_c == c2)

	//----------------------- calaculating membership --------------------------------------
				{
					val = stof(value);
					x = val / s;
					m = s_function(x);
					if (m == 2)
					{
						m = 0;
					}
					m1 = m1 + m;
				}
			}

		}
		if (m1 > lower)
		{
			theta_1 = m1 + theta_2;
			membership.push_back(theta_1);
			new_trusted_noun.push_back(trust_n);
			theta_1 = 0; theta_2 = 0;
		}
				
		b++;	m = 0;	m1 = 0;
		con2.clear();
		cout << b << '\t';
	}

	membership_len = membership.size();

	for (i = 0; i < used_len; i++)
	{
		for (j = 0; j < membership_len; j++)
		{
			u1 = used1[i];
			u2 = new_trusted_noun[j];
			if (u1 == u2)
			{
				membership[j] = 0;
				break;
			}
		}
	}


	for (i = 0; i < membership_len;)
	{
		location = top(membership);
		trusted_noun = new_trusted_noun[location];
		fuz_mem = membership[location];
		fuzzy << trusted_noun << '\t' << fuz_mem << '\n';
		membership[location] = 0;
		i++;
	}



	/*------------------------------------ Closing all the files ----------------------------------------------------*/


/*	t2 = clock();
	diff = t2 - t1;
	seconds = diff / CLOCKS_PER_SEC;

	fuzzy << seconds; */

	

	datafile.close();
	trusted.close();
	comc.close();
	row.close();
	fuzzy.close();

	return 0;
}








