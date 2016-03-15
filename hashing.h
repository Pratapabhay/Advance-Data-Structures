#ifndef HASHING_H
#define HASHING_H

#include "sequential_list.h"
#include "linked_list.h"

using namespace std;

class hash {
	private:
		int bucket_size, dub_hsh_key;
	
	public:
		hash( int buc_size, int dh_key );													//Constructor
		void set_buc_size( int buc_size );
		int get_buc_size();
		int get_dh_key();
		int generate_key( string x );
		int hash_value( int key );
		int double_hash( int key );
		
		int search_lp( seqlist &S, string x );
		bool insert_lp( seqlist &S, OBJECT x );
		bool delete_lp( seqlist &S, string x );
		void rehash_lp( seqlist &S );
		
		int search_dh( seqlist &S, string x );
		bool insert_dh( seqlist &S, OBJECT x );
		bool delete_dh( seqlist &S, string x );
		void rehash_dh( seqlist &S );
		
		int search_c( link_list A[], string x );
		bool insert_c( link_list A[], OBJECT x );
		bool delete_c( link_list A[], string x );
//	//	void rehash_c( link_list A[] );
		
		void print_seq( seqlist &S );
		void print_lnk( link_list A[] );
		
		void out_to_file_seq( ofstream &ofs, seqlist &S );
		void out_to_file_lnk( ofstream &ofs, link_list A[] );
		
		int generate_prime( int low, int high );
};


hash::hash( int buc_size, int dh_key )
{
	bucket_size = buc_size;
	dub_hsh_key = dh_key;
}

void hash::set_buc_size( int buc_size )
{
	bucket_size = buc_size;
}

int hash::get_buc_size()
{
	return bucket_size;
}

int hash::get_dh_key()
{
	return dub_hsh_key;
}

int hash::generate_key( string x )
{
	int key, len, i;
	len = x.length();
	
	key = 0;
	
	for ( i = 0; i < len; i++ )
		key = key + x[i];
		
	return key;
}

int hash::hash_value( int key )
{
	int val;
	val = ( key * (key + 3)) % bucket_size;
	return val;
}

int hash::double_hash( int key )
{
	int val;
	val = dub_hsh_key - (key % dub_hsh_key);
	return val;
}








int hash::search_lp( seqlist &S, string x )
{
	int probe, index, m, n;
	OBJECT dp;
	
	probe = 0;
	n = this->generate_key( x );
	index = this->hash_value( n );
	m = this->get_buc_size();
	
	while ( (S.find(index, dp)) && (probe < m) ) {
		if ( dp.CALL == x )
			return index;
		index = (index+1) % m;
		probe++;
	}
	
	if ( probe == m || (!S.find(index, dp)) )
		return -1;
}


bool hash::insert_lp( seqlist &S, OBJECT x )
{
	int probe, index, m, n;
	OBJECT dp;
	
	if ( this->search_lp( S, x.CALL ) != -1 )
		return false;
	
	probe = 0;
	n = this->generate_key( x.CALL );
	index = this->hash_value( n );
	m = this->get_buc_size();
	
	while ( (S.find(index, dp)) && (probe < m) ) {
		if ( dp.CALL != DECOY ) {
			index = (index+1) % m;
			probe++;
		}
		else
			break;
	}
	
	if ( probe == m ) {
		this->rehash_lp( S );
		n = this->generate_key( x.CALL );
		index = this->hash_value( n );
		m = this->get_buc_size();
		
		while ( S.find(index, dp) )
			index = (index+1) % m;
		S.insert( index, x );
		return true;
	}
	S.insert( index, x );
	return true;
}


bool hash::delete_lp( seqlist &S, string x )
{
	int c;
	c = this->search_lp( S, x );
	if ( c == -1 )
		return false;
	S.deleteElement_R( x, DECOY );
	return true;
}








int hash::search_dh( seqlist &S, string x )
{
	int probe, index, m, offset, n;
	OBJECT dp;
	
	probe = 0;
	n = this->generate_key( x );
	index = this->hash_value( n );
	m = this->get_buc_size();
	offset = this->double_hash( n );
	
	while ( (S.find(index, dp)) && (probe < m) ) {
		if ( dp.CALL == x )
			return index;
		index = (index+offset) % m;
		probe++;
	}
	
	if ( probe == m || (!S.find(index, dp)) )
		return -1;
}


bool hash::insert_dh( seqlist &S, OBJECT x )
{
	int probe, index, m, offset, n;
	OBJECT dp;
	
	if ( this->search_dh( S, x.CALL ) != -1 )
		return false;
	
	n = this->generate_key( x.CALL );
	index = this->hash_value( n );
	
	if ( !S.find(index, dp) ) {
		S.insert( index, x );
		return true;
	}
	
	probe = 0;
	offset = this->double_hash( n );
	m = this->get_buc_size();
	
	while ( (S.find(index, dp)) && (probe < m) ) {
		if ( dp.CALL != DECOY ) {
			index = (index + offset) % m;
			probe++;
		}
		else
			break;
	}
	
	if ( probe == m ) {
		this->rehash_dh( S );
		n = this->generate_key( x.CALL );
		index = this->hash_value( n );
		
		if ( !S.find(index, dp) ) {
			S.insert( index, x );
			return true;
		}
		
		offset = this->double_hash( n );
		m = this->get_buc_size();
		
		while ( S.find(index, dp) ) 
			index = (index + offset) % m;
		S.insert( index, x );
		return true;
	}	
	S.insert( index, x );
	return true;
}


bool hash::delete_dh( seqlist &S, string x )
{
	int c;
	c = this->search_dh( S, x );
	if ( c == -1 )
		return false;
	S.deleteElement_R( x, DECOY );
	return true;
}








int hash::search_c( link_list A[], string x )
{
	int n, k;
	n = this->generate_key( x );
	k = this->hash_value( n );
	n = A[k].search( x );
	return n;
}


bool hash::insert_c( link_list A[], OBJECT x )
{
	int n, k, max_len, i, arr_size;
	
	if ( this->search_c( A, x.CALL ) != -1 )
		return false;
	
	n = this->generate_key( x.CALL );
	k = this->hash_value( n );
	A[k].add( x );
	return true;
/*	arr_size = sizeof(A) / sizeof(link_list);
	max_len = 0;
	for ( i = 0; i < arr_size; i++ )
		if ( A[i].length() > max_len )
			max_len = A[i].length();
	if ( max_len >= (arr_size/2) )
		rehash_c( A );*/
	
}


bool hash::delete_c( link_list A[], string x )
{
	int n, k;
	n = this->generate_key( x );
	k = this->hash_value( n );
	if ( A[k].deleteElement(x) )
		return true;
	return false;
}








void hash::rehash_lp( seqlist &S )
{
	int new_size, l, h, old_size, i;
	
	OBJECT dp;
	OBJECT * p;
	
	old_size = S.max_s();
	
	seqlist T( old_size );
	
	for ( i = 0; i < old_size; i++ ) {
		S.find( i, dp );
		this->insert_lp( T, dp );
	}
	
	l = 2 * this->get_buc_size();
	h = 4 * this->get_buc_size();
	new_size = this->generate_prime( l, h );
	this->set_buc_size( new_size );

	S.resize( new_size );
	
	for ( i = 0; i < old_size; i++ ) {
		T.find( i, dp );
		this->insert_lp( S, dp );
	}
}


void hash::rehash_dh( seqlist &S )
{
	int new_size, l, h, old_size, i;
	
	OBJECT dp;
	OBJECT * p;
	
	old_size = S.max_s();
	
	seqlist T( old_size );
	
	for ( i = 0; i < old_size; i++ ) {
		S.find( i, dp );
		this->insert_dh( T, dp );
	}
	
	l = 2 * this->get_buc_size();
	h = 4 * this->get_buc_size();
	new_size = this->generate_prime( l, h );
	this->set_buc_size( new_size );

	S.resize( new_size );
	
	for ( i = 0; i < old_size; i++ ) {
		T.find( i, dp );
		this->insert_dh( S, dp );
	}
}

/*
void hash::rehash_c( link_list A[] )
{
	
}
*/








void hash::print_seq( seqlist &S )
{
	int i, size;
	OBJECT d;
	size = this->get_buc_size();
	for ( i = 0; i < size; i++ ) {
		S.find(i,d);
		if ( d.CALL != DECOY )
			S.print(i);
		else
			cout << "Field Is Empty." << endl;
	}
}	


void hash::print_lnk( link_list A[] )
{
	int i, size;
	size = this->get_buc_size();
	for ( i = 0; i < size; i++ )
		A[i].print();
	cout << "End." << endl;
}








void hash::out_to_file_seq( ofstream &ofs, seqlist &S )
{
	int i, size;
	size = this->get_buc_size();
	
	OBJECT d;
	
	for ( i = 0; i < size; i++ ) {
		if ( S.find(i,d) )
			if ( d.CALL != DECOY )
				d.out_to_file(ofs);
	}
}


void hash::out_to_file_lnk( ofstream &ofs, link_list A[] )
{
	int i, size;
	size = this->get_buc_size();
	
	OBJECT d;
	
	for ( i = 0; i < size; i++ )
		A[i].out_to_file(ofs);
}








int hash::generate_prime( int low, int high )
{
	int num[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
	int i, j, prime, flag;
	flag = 0;
	for ( i = low; i <= high; i++ ) {
		for ( j = 0; j < 12; j++ ) {
			if ( !(i%num[j]) )
				break;
		}
		if ( j == 12 || i == num[j] ) {
			prime = i;
			break;
		}
	}
	return prime;
}

#endif