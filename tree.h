


#ifndef TREE_H
#define TREE_H

#include "Bank.h"																			//Header files

using namespace std;

class tree_node {
	public:
		OBJECT data;
		int height;
		tree_node * parent;
		tree_node * left_child;
		tree_node * right_child;
};

class bst {
	protected:
		tree_node * root;
	
	public:
		bst();
//		~bst();
		int height( tree_node * b );
		bool search( KEY_TYPE x );															//Returns true if element found in the tree
		bool insert( OBJECT x );															//Returns true if insert successfull
		tree_node * minimum( tree_node * x );
		tree_node * maximum( tree_node * x );
		tree_node * successor( tree_node * x );
		bool deleteElement( KEY_TYPE x );													//Returns true if delete successfull
		bool isEmpty();
		int max( int a, int b );
//		void deleteTree( tree_node * b );
		void print();
		void out( ofstream &ofs );
		void out_inOrder( tree_node * b, ofstream &ofs );
		void out_preOrder( tree_node * b, ofstream &ofs );
		void out_postOrder( tree_node * b, ofstream &ofs );
		void display( KEY_TYPE x );															//Displays a single record detail from the tree
		void inOrder( tree_node * b );
		void preOrder( tree_node * b );
		void postOrder( tree_node * b );
};





bst::bst()
{
	root = NULL;
}
/*
bst::~bst()
{
	this->deleteTree( root );
	
}
*/
int bst::height( tree_node * b )
{
	if ( !b )
		return 0;
	return ( this->max( this->height(b->left_child), this->height(b->right_child) ) + 1 );
}

bool bst::search( KEY_TYPE x )
{
	tree_node * condt;
	condt = root;
	
	while ( condt ) {																		//Move to appropiate position
		if ( x.compare(condt->data.CALL) > 0 )
			condt = condt->right_child;
		else if ( x.compare(condt->data.CALL) < 0 )
			condt = condt->left_child;
		else
			return true;
	}
	
	return false;
}

bool bst::insert( OBJECT x )
{
	tree_node * condt;
	tree_node * prnt = NULL;
	condt = root;
	
	while ( condt ) {																		//Move to location for insert
		prnt = condt;
		if ( x.CALL.compare(condt->data.CALL) > 0 )
			condt = condt->right_child;
		else if ( x.CALL.compare(condt->data.CALL) < 0 )
			condt = condt->left_child;
		else
			return false;
	}
	
	condt = new tree_node;																	//Create new node with data
	condt->data.set( x );
	condt->parent = prnt;
	condt->left_child = condt->right_child = NULL;
	
	if ( !root ) {
		root = condt;
		return true;
	}
	
	if ( prnt->data.CALL.compare(condt->data.CALL) > 0 )
		prnt->left_child = condt;
	else
		prnt->right_child = condt;
	
	return true;
}

tree_node * bst::minimum( tree_node * x )
{
	while ( x->left_child )
		x = x->left_child;
	return x;
}

tree_node * bst::maximum( tree_node * x )
{
	while ( x->right_child )
		x = x->right_child;
	return x;
}

tree_node * bst::successor( tree_node * x )
{
	if ( x->right_child )
		return this->minimum( x->right_child );
	
	tree_node * condt = x->parent;
	if ( condt == NULL )
		return NULL;
	tree_node * prnt = condt->parent;
	while ( prnt->left_child != condt ) {
		condt = condt->parent;
		if ( condt == NULL )
			return NULL;
		prnt = condt->parent;
	}
	return condt;
}

bool bst::isEmpty()
{
	return root == NULL;
}

int bst::max( int a, int b )
{
	if ( a > b )
		return a;
	return b;
}
/*
void bst::deleteTree( tree_node * b )
{
	if ( b ) {
		this->deleteTree( b->left_child );
		this->deleteTree( b->right_child );
		delete b;
	}
}
*/
bool bst::deleteElement( KEY_TYPE x )
{
	tree_node * condt;
	tree_node * prnt = NULL;
	tree_node * sucsser = NULL ;
	condt = root;
	OBJECT d;
		
	while ( condt ) {
		if ( x.compare(condt->data.CALL) > 0 ) {
			prnt = condt;
			condt = condt->right_child;
		}
		else if ( x.compare(condt->data.CALL) < 0 ) {
			prnt = condt;
			condt = condt->left_child;
		}
		else
			break;
	}
	
	if ( !condt )
		return false;
	
	if ( condt == root ) {
		if ( !condt->left_child && !condt->right_child ) {
			delete condt;
			root = NULL;
			return true;
		}
		
		if ( !condt->left_child || !condt->right_child ) {
			if ( !condt->left_child )
				root = condt->right_child;
			else if ( !condt->left_child )
				root = condt->right_child;
			
			delete condt;
			return true;
		}
		
		sucsser = this->successor( condt );
		d.set( sucsser->data );
		this->deleteElement( d.CALL );
		condt->data.set( d );
		return true;
	}
	
	if ( !condt->left_child && !condt->right_child ) {
		if ( prnt->left_child == condt )
			prnt->left_child = NULL;
		else
			prnt->right_child = NULL;
		delete condt;
		return true;
	}
	
	if ( !condt->left_child || !condt->right_child ) {
		prnt = condt->parent;
		
		if ( !condt->left_child && prnt->right_child == condt )
			prnt->right_child = condt->right_child;
		else if ( !condt->left_child && prnt->left_child == condt )
			prnt->left_child = condt->right_child;
		else if ( !condt->right_child && prnt->left_child == condt )
			prnt->left_child = condt->left_child;
		else
			prnt->right_child = condt->left_child;
		
		delete condt;
		return true;
	}
	
	sucsser = this->successor( condt );
	d.set( sucsser->data );
	this->deleteElement( d.CALL );
	condt->data.set( d );
	return true;
}

void bst::print()
{
	if ( !root ) {
		cout << "Tree Is Empty." << endl;
		return;
	}
	
	int flag;
	
	do {
		cout << "Select Traversal Mathod: " << endl;
		cout << "1: Pre-Order" << endl;
		cout << "2: In-Order" << endl;
		cout << "3: Post-Order" << endl;
		cin >> flag;
		cout << endl;
	} while ( flag != 1 && flag != 2 && flag != 3 );
	
	if ( flag == 1 )
		this->preOrder( root );
	else if ( flag == 2 )
		this->inOrder( root );
	else
		this->postOrder( root );
}

void bst::out( ofstream &ofs )
{
	this->out_inOrder( root, ofs );
}

void bst::inOrder( tree_node * b )
{
	if ( b ) {
		this->inOrder( b->left_child );
		b->data.print();
		this->inOrder( b->right_child );
	}
}

void bst::preOrder( tree_node * b )
{
	if ( b ) {
		b->data.print();
		this->preOrder( b->left_child );
		this->preOrder( b->right_child );
	}
}

void bst::postOrder( tree_node * b )
{
	if ( b ) {
		this->postOrder( b->left_child );
		this->postOrder( b->right_child );
		b->data.print();
	}
}

void bst::out_inOrder( tree_node * b, ofstream &ofs )
{
	if ( b ) {
		this->out_inOrder( b->left_child, ofs );
		b->data.out_to_file( ofs );
		this->out_inOrder( b->right_child, ofs );
	}
}

void bst::out_preOrder( tree_node * b, ofstream &ofs )
{
	if ( b ) {
		b->data.out_to_file( ofs );
		this->out_preOrder( b->left_child, ofs );
		this->out_preOrder( b->right_child, ofs );
	}
}

void bst::out_postOrder( tree_node * b, ofstream &ofs )
{
	if ( b ) {
		this->out_postOrder( b->left_child, ofs );
		this->out_postOrder( b->right_child, ofs );
		b->data.out_to_file( ofs );
	}
}























class avl_tree : public bst {
	public:
		bool insert_avl( OBJECT x );
		bool deleteElement( KEY_TYPE x );
		void left_rotate( tree_node * b );
		void right_rotate( tree_node * b );
		bool balance( tree_node * b );
		int bal_factor( tree_node * b );
		int ht( tree_node * b );
};

bool avl_tree::insert_avl( OBJECT x )
{
	tree_node * condt;
	tree_node * prnt = NULL;
	condt = root;
	
	while ( condt ) {
		prnt = condt;
		if ( x.CALL.compare(condt->data.CALL) > 0 )
			condt = condt->right_child;
		else if ( x.CALL.compare(condt->data.CALL) < 0 )
			condt = condt->left_child;
		else
			return false;
	}
	
	condt = new tree_node;
	condt->data.set( x );
	condt->height = 0;
	condt->parent = prnt;
	condt->left_child = condt->right_child = NULL;
	
	if ( !root ) {
		root = condt;
		return true;
	}
	
	if ( prnt->data.CALL.compare(condt->data.CALL) > 0 )
		prnt->left_child = condt;
	else
		prnt->right_child = condt;
	
	this->balance( condt );
	return true;
}

bool avl_tree::deleteElement( KEY_TYPE x )
{
	tree_node * condt;
	tree_node * prnt = NULL;
	tree_node * sucsser = NULL ;
	condt = root;
	OBJECT d;
		
	while ( condt ) {
		if ( x.compare(condt->data.CALL) > 0 ) {
			prnt = condt;
			condt = condt->right_child;
		}
		else if ( x.compare(condt->data.CALL) < 0 ) {
			prnt = condt;
			condt = condt->left_child;
		}
		else
			break;
	}
	
	if ( !condt )
		return false;
	
	if ( condt == root ) {
		if ( !condt->left_child && !condt->right_child ) {
			delete condt;
			root = NULL;
			return true;
		}
		
		if ( !condt->left_child || !condt->right_child ) {
			if ( !condt->left_child )
				root = condt->right_child;
			else if ( !condt->left_child )
				root = condt->right_child;
			
			delete condt;
			return true;
		}
		
		sucsser = this->successor( condt );
		d.set( sucsser->data );
		this->deleteElement( d.CALL );
		condt->data.set( d );
		
		return true;
	}
	
	if ( !condt->left_child && !condt->right_child ) {
		if ( prnt->left_child == condt )
			prnt->left_child = NULL;
		else
			prnt->right_child = NULL;
		delete condt;
		this->balance( prnt );
		return true;
	}
	
	if ( !condt->left_child || !condt->right_child ) {
		prnt = condt->parent;
		
		if ( !condt->left_child && prnt->right_child == condt )
			prnt->right_child = condt->right_child;
		else if ( !condt->left_child && prnt->left_child == condt )
			prnt->left_child = condt->right_child;
		else if ( !condt->right_child && prnt->left_child == condt )
			prnt->left_child = condt->left_child;
		else
			prnt->right_child = condt->left_child;
		
		delete condt;
		this->balance( prnt );
		return true;
	}
	
	sucsser = this->successor( condt );
	d.set( sucsser->data );
	this->deleteElement( d.CALL );
	condt->data.set( d );
	return true;
}

void avl_tree::left_rotate( tree_node * z )
{
	tree_node * y;
	tree_node * p;
	tree_node * yl;
	y = z->right_child;
	p = z->parent;
	if ( p ) {
		y->parent = p;
		if ( p->left_child == z )
			p->left_child = y;
		else
			p->right_child = y;
	}
	else {
		y->parent = NULL;
		root = y;
	}
	yl = y->left_child;
	z->right_child = yl;
	if (yl)
		yl->parent = z;
	y->left_child = z;
	z->parent = y;
	z->height = this->ht(z);
	y->height = this->ht(y);
}

void avl_tree::right_rotate( tree_node * z )
{
	tree_node * y;
	tree_node * p;
	tree_node * yr;
	y = z->left_child;
	p = z->parent;
	if ( p ) {
		y->parent = p;
		if ( p->left_child == z )
			p->left_child = y;
		else
			p->right_child = y;
	}
	else {
		y->parent = NULL;
		root = y;
	}
	yr = y->right_child;
	z->left_child = yr;
	if (yr)
		yr->parent = z;
	y->right_child = z;
	z->parent = y;
	z->height = this->ht(z);
	y->height = this->ht(y);
}

bool avl_tree::balance( tree_node * b )
{
	int bf, h, bfc;
	tree_node * condt = NULL;
	tree_node * prnt = NULL;
	tree_node * y;
	
	condt = b;
	while ( condt ) {
		prnt = condt-> parent;
		
		bf = this->bal_factor( condt );
		if ( bf != -1 && bf != 0 && bf != 1  )
			break;
		
		condt->height = this->ht( condt );
		condt = prnt;
	}
	
	if ( !condt )
		return true;
		
	if ( bf != -1 && bf != 0 && bf != 1  ) {
		if ( bf == 2 ) {
			y = condt->left_child;
			bfc = this->bal_factor(y);
			if ( bfc == 1 || bfc == 0 ) {
				this->right_rotate(condt);
			}
			else {
				this->left_rotate(y);
				this->right_rotate(condt);
			}
		}
		else {
			y = condt->right_child;
			bfc = this->bal_factor(y);
			if ( bfc == -1 || bfc == 0 ) {
				this->left_rotate(condt);
			}
			else {
				this->right_rotate(y);
				this->left_rotate(condt);
			}
		}
		this->balance(prnt);
	}
	return true;
}

int avl_tree::bal_factor( tree_node * b) {
	int lh, rh;
	lh = rh = -1;
	
	if ( b->left_child )
		lh = b->left_child->height;
	if ( b->right_child )
		rh = b->right_child->height;
	
	return (lh - rh);
}

int avl_tree::ht( tree_node * b )
{
	int lh, rh;
	lh = rh = -1;
	
	if ( b->left_child )
		lh = b->left_child->height;
	if ( b->right_child )
		rh = b->right_child->height;
	
	if ( lh > rh )
		return (lh + 1);
	return (rh + 1);
}




















#endif
