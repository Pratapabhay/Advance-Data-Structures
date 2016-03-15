#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>


#define OBJECT trans_data													//Macro For The Object Data Defined
#define CALL get_tid()														//Function That Returns Key Field
#define CALL2 get_lenID()													//Function That Returns Value Associated With Key Field
#define KEY_TYPE string														//Data Type For Key Field
#define DECOY "****"


using namespace std;

class trans_data {
	private:
		string transID, date;
		int from_ac, to_ac, debit, credit, total_bal, len_ID;
	
	public:
		void set( trans_data x );
		void set_p( string tid, string dt, int from, int to, int deb, int cred, int total );
		void set_key( string key );
		void read_file( ifstream &ifs );
		void in();
		void clear_key();
		string get_tid();
		string get_date();
		int get_from();
		int get_to();
		int get_deb();
		int get_cred();
		int get_total();
		int get_lenID();
		void print();
		void out_to_file( ofstream &ofs );
		trans_data returnElement();
};

void trans_data::set( trans_data x )
{
	transID = x.get_tid();
	date = x.get_date();
	from_ac = x.get_from();
	to_ac = x.get_to();
	debit = x.get_deb();
	credit = x.get_cred();
	total_bal = x.get_total();
	len_ID = x.get_lenID();
}

void trans_data::set_p( string tid, string dt, int from, int to, int deb, int cred, int total )
{
	transID = tid;
	date = dt;
	from_ac = from;
	to_ac = to;
	debit = deb;
	credit = cred;
	total_bal = total;
	len_ID = tid.length();
}

void trans_data::set_key( string key )
{
	transID = key;
}

void trans_data::read_file( ifstream &ifs )
{
	ifs >> transID;
	ifs >> date;
	ifs >> from_ac;
	ifs >> to_ac;
	ifs >> debit;
	ifs >> credit;
	ifs >> total_bal;
}

void trans_data::in()
{
	cout << "Enter Transection_ID, date, from Account, to Account, Debit, Credit, Total balance (respectively): " << endl;
	cin >> transID;
	cin >> date;
	cin >> from_ac;
	cin >> to_ac;
	cin >> debit;
	cin >> credit;
	cin >> total_bal;
	cout << endl;
}

void trans_data::clear_key()
{
	transID.clear();
}

string trans_data::get_tid()
{
	return transID;
}

string trans_data::get_date()
{
	return date;
}

int trans_data::get_from()
{
	return from_ac;
}

int trans_data::get_to()
{
	return to_ac;
}

int trans_data::get_deb()
{
	return debit;
}

int trans_data::get_cred()
{
	return credit;
}

int trans_data::get_total()
{
	return total_bal;
}

int trans_data::get_lenID()
{
	return len_ID;
}

void trans_data::print()
{
	cout << "Transection ID: " << transID << "\t" << "Date: " << date << "\t\t" << "From Account: " << from_ac << "\t\t" << "To Account: " << to_ac << "\t" << "Debit: " << debit << "\t" << "Credit: " << credit << "\t" << "Total Balance: " << total_bal << endl;
}

void trans_data::out_to_file( ofstream &ofs )
{
	ofs << this->get_tid() << "\t" << this->get_date() << "\t" << this->get_from() << "\t" << this->get_to() << "\t" << this->get_deb() << "\t" << this->get_cred() << "\t" << this->get_total() << endl;
}

trans_data trans_data::returnElement()
{
	return *this;
}

#endif