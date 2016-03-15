#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Bank.h"

using namespace std;

class node {
	public:
		OBJECT data;
		node * next;
};

class link_list {
	private:
		node * heads;
		node * tails;
		int len;
	
	public:
		link_list();
		~link_list();
		void add( OBJECT x );
		bool isEmpty();
		int length();
		bool find( int k, OBJECT &x );
		int search( KEY_TYPE x );
		bool deleteElement( KEY_TYPE x );
		void print();
		void out_to_file( ofstream &ofs );
};

link_list::link_list()
{
	heads = NULL;
	tails = NULL;
	len = 0;
}

link_list::~link_list()
{
	node * condt;
	condt = heads;
	while ( condt ) {
		heads = heads->next;
		delete condt;
		condt = heads;
	}
}

void link_list::add( OBJECT x )
{
	node * condt = new node;
	condt->data.set( x );
	condt->next = NULL;
	if ( this->heads == NULL ) {
		this->heads = this->tails = condt;
	}
	else {
		this->tails->next = condt;
		this->tails = condt;
	}
	len++;
}

bool link_list::isEmpty()
{
	return heads == NULL;
}

int link_list::length()
{
	return len;
}

bool link_list::find( int k, OBJECT &x )
{
	if ( k < 0 || k > (len - 1) )
		return false;
	int i;
	node * condt = heads;
	for ( i = 1; i <= k; i++ )
		condt = condt->next;
	x.set( condt->data );
	return true;
}

int link_list::search( KEY_TYPE x )
{
	int i;
	node * condt = heads;
	for ( i = 0; i < len; i++ ) {
		if ( condt->data.CALL == x )
			return i;
		condt = condt->next;
	}
	return -1;
}

bool link_list::deleteElement( KEY_TYPE x )
{
	int i;
	i = this->search(x);
	if ( i != -1 ) {
		i--;
		node * condt = heads;
		node * p = new node;
		if ( i != -1 ) {
			while ( i ) {
				condt = condt->next;
				i--;
			}
			p = condt->next;
			condt->next = condt->next->next;
			delete p;
		}
		else {
			heads = condt->next;
			delete condt;
		}
		len--;
		return true;
	}
	return false;
}

void link_list::print()
{
	node * condt;
	condt = heads;
	
	if (!condt)
		cout << "Field Is Empty." << endl;
	
	while ( condt ) {
		condt->data.print();
		condt = condt->next;
	}
	cout << endl;
}

void link_list::out_to_file( ofstream &ofs )
{
	node * condt;
	condt = heads;
	
	while ( condt ) {
		condt->data.out_to_file(ofs);
		condt = condt->next;
	}
}

#endif