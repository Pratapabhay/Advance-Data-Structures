#ifndef SEQUENTIAL_LIST_H
#define SEQUENTIAL_LIST_H

#include "Bank.h"

using namespace std;

class seqlist {
	private:
		OBJECT *elem;
		int max_size;
		int len;
	
	public:
		seqlist( int size );															//Constructor
		~seqlist();																		//Destructor
		bool isEmpty();
		bool isFull();
		int length();
		int max_s();
		void resize( int size );
		bool find( int index, OBJECT &x );
		int search( KEY_TYPE x );
		bool deleteElement( KEY_TYPE x );
		void deleteElement_R( KEY_TYPE x, KEY_TYPE replacement_value );
		void insert( int index, OBJECT x );
		void print( int index );
		void out_to_file( ofstream &ofs );
};

seqlist::seqlist( int size )
{
	max_size = size;
	elem = new OBJECT [size];
	len = 0;
}

seqlist::~seqlist()
{
	delete [] elem;
}

bool seqlist::isEmpty()
{
	return len == 0;
}

bool seqlist::isFull()
{
	return len == max_size;
}

int seqlist::length()
{
	return len;
}

int seqlist::max_s()
{
	return max_size;
}

void seqlist::resize( int size )
{
	max_size = size;
	elem = new OBJECT [max_size];
	len = 0;
}

bool seqlist::find( int index, OBJECT &x )
{
	if ( index < 0 || index > (max_size - 1) )
		return false;
	else if ( !elem[index].CALL2 )
		return false;
	x = elem[index];
	return true;
}

int seqlist::search( KEY_TYPE x )
{
	int i;
	for ( i = 0; i < max_size; i++ ) {
		if ( elem[i].CALL == x )
			return i;
	}
	return -1;
}

bool seqlist::deleteElement( KEY_TYPE x )
{
	int i;
	i = search( x );
	if ( i != -1 ) {
		elem[i].clear_key();
		len--;
		return true;
	}
	return false;
}

void seqlist::deleteElement_R( KEY_TYPE x, KEY_TYPE replacement_value )
{
	int i;
	i = search( x );
	if ( i != -1 ) {
		elem[i].clear_key();
		elem[i].set_key( replacement_value );
		len--;
	}
}

void seqlist::insert( int index, OBJECT x )
{
	elem[index].set( x );
	len++;
}

void seqlist::print( int index )
{
	OBJECT d;
	if (this->find(index,d))
		d.print();
	else
		cout << "Field Is Empty." << endl;
}

void seqlist::out_to_file( ofstream &ofs )
{
	int i, maxSize;
	maxSize = this->max_s();
	
	OBJECT d;
	
	for ( i = 0; i < maxSize; i++ ) {
		if ( this->find(i,d) )  
			d.out_to_file(ofs);
	}
}

#endif