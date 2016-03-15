#include "hashing.h"
#include "tree.h"

using namespace std;

int main() {
	int i, k, j, flag, from, to, cred, deb, total, bucketSize;
	char flag_implement, flag_clash, contnue;
	
	string f_name, transectionID, date;
	trans_data d;
	
	do {
		cout << "Select Technique To Be Implement: " << endl;
		cout << "1: Hashing" << endl;
		cout << "2: BST" << endl;
		cout << "3: AVL Tree" << endl;
		cin >> flag_implement;
		cout << endl;
	} while ( flag_implement != '1' && flag_implement != '2' && flag_implement != '3' );
	
	
	cout << "Enter File Name( .txt ): ";
	cin >> f_name;
	cout << endl;
	
	f_name = f_name + ".txt";
	ifstream ifs(f_name.c_str());
	if ( !ifs ) {
		cout << "Unable To Open File. PROGRAM EXITING" << endl << endl;
		return 0;
	}
	
	ofstream ofs;
	
	
	switch ( flag_implement ) {
		
		case '1': {
			cout << "Enter Size Of Hash Table: ";
			cin >> bucketSize;
			cout << endl;
			
			hash H( bucketSize, 7 );
			
			do {
				cout << "Select Mathod To Handle Collision: " << endl;
				cout << "1: Linear Probing" << endl;
				cout << "2: Double Hashing" << endl;
				cout << "3: Chaining" << endl;
				cin >> flag_clash;
				cout << endl;
			} while ( flag_clash != '1' && flag_clash != '2' && flag_clash != '3' );
			
		
			switch ( flag_clash ) {
				
				case '1': {																				//Linear Probing - Collision Handle
					seqlist S( bucketSize );
					while ( ifs ) {
						d.read_file( ifs );
						H.insert_lp( S, d );
					}
					
					cout << "File Read Complete." << endl << endl;
					
					do {
						do {
							cout << "Select A Action: " << endl;
							cout << "1: Search" << endl;
							cout << "2: Insert" << endl;
							cout << "3: Delete" << endl;
							cout << "4: Print" << endl;
							cin >> flag;
							cout << endl;
						} while ( flag != 1 && flag != 2 && flag != 3 && flag != 4 );
						
						if ( flag == 1 ) {
							cout << "Enter Transection_ID: " << endl;
							cin >> transectionID;
							cout << endl;
							if ( H.search_lp( S, transectionID ) != -1 )
								cout << "Element Is Present." << endl;
							else
								cout << "Element Not Present." << endl;
						}
						
						else if ( flag == 2 ) {
							d.in();
							if ( !H.insert_lp( S, d ) )
								cout << "Element Already Present. Cannot Insert" << endl;
							else
								cout << "Element Inserted." << endl;
						}
						
						else if ( flag == 3 ) {
							cout << "Enter Transection_ID: " << endl;
							cin >> transectionID;
							cout << endl;
							if ( H.delete_lp( S, transectionID ) )
								cout << "Element Deleted" << endl;
							else
								cout << "Element Already Not Present." << endl;
						}
						
						else
							H.print_seq( S );
						
						cout << endl << "Continue (N/n for 'No'): ";
						cin >> contnue;
						cout << endl;
						
					} while ( contnue != 'N' && contnue != 'n' );
					
					ofs.open(f_name.c_str());
					H.out_to_file_seq( ofs, S );
					break;
				}
				case '2': {																				//Double Hashing - Collision Handle
					seqlist S( bucketSize );
					while ( ifs ) {
						d.read_file( ifs );
						H.insert_dh( S, d );
					}
					
					cout << "File Read Complete." << endl << endl;
					
					do {
						do {
							cout << "Select A Action: " << endl;
							cout << "1: Search" << endl;
							cout << "2: Insert" << endl;
							cout << "3: Delete" << endl;
							cout << "4: Print" << endl;
							cin >> flag;
							cout << endl;
						} while ( flag != 1 && flag != 2 && flag != 3 && flag != 4 );
						
						if ( flag == 1 ) {
							cout << "Enter Transection_ID: " << endl;
							cin >> transectionID;
							cout << endl;
							if ( H.search_dh( S, transectionID ) != -1 )
								cout << "Element Is Present." << endl;
							else
								cout << "Element Not Present." << endl;
						}
						
						else if ( flag == 2 ) {
							d.in();
							if ( !H.insert_dh( S, d ) )
								cout << "Element Already Present. Cannot Insert" << endl;
							else
								cout << "Element Inserted." << endl;
						}
						
						else if ( flag == 3 ) {
							cout << "Enter Transection_ID: " << endl;
							cin >> transectionID;
							cout << endl;
							if ( H.delete_dh( S, transectionID ) )
								cout << "Element Deleted" << endl;
							else
								cout << "Element Already Not Present." << endl;
						}
						
						else
							H.print_seq( S );
						
						cout << endl << "Continue (N/n for 'No'): ";
						cin >> contnue;
						cout << endl;
						
					} while ( contnue != 'N' && contnue != 'n' );
					
					ofs.open(f_name.c_str());
					H.out_to_file_seq( ofs, S );
					break;
				}
				case '3': {																						//Chaining - Collision Handle
					link_list A[bucketSize];
					while ( ifs ) {
						d.read_file( ifs );
						H.insert_c( A, d );
					}
					
					cout << "File Read Complete." << endl << endl;
					
					do {
						do {
							cout << "Select A Action: " << endl;
							cout << "1: Search" << endl;
							cout << "2: Insert" << endl;
							cout << "3: Delete" << endl;
							cout << "4: Print" << endl;
							cin >> flag;
							cout << endl;
						} while ( flag != 1 && flag != 2 && flag != 3 && flag != 4 );
						
						if ( flag == 1 ) {
							cout << "Enter Transection_ID: " << endl;
							cin >> transectionID;
							cout << endl;
							if ( H.search_c( A, transectionID ) != -1 )
								cout << "Element Is Present." << endl;
							else
								cout << "Element Not Present." << endl;
						}
						
						else if ( flag == 2 ) {
							d.in();
							if ( !H.insert_c( A, d ) )
								cout << "Element Already Present. Cannot Insert" << endl;
							else
								cout << "Element Inserted." << endl;
						}
						
						else if ( flag == 3 ) {
							cout << "Enter Transection_ID: " << endl;
							cin >> transectionID;
							cout << endl;
							if ( H.delete_c( A, transectionID ) )
								cout << "Element Deleted" << endl;
							else
								cout << "Element Already Not Present." << endl;
						}
						
						else
							H.print_lnk( A );
						
						cout << endl << "Continue (N/n for 'No'): ";
						cin >> contnue;
						cout << endl;
						
					} while ( contnue != 'N' && contnue != 'n' );
					
					ofs.open(f_name.c_str());
					H.out_to_file_lnk( ofs, A );
					break;
				}
			}
			break;
		}
		
		case '2': {
			bst B;
			while ( ifs ) {
				d.read_file( ifs );
				B.insert( d );
			}
			
			cout << "File Read Complete." << endl << endl;
			
			do {
				do {
					cout << "Select A Action: " << endl;
					cout << "1: Search" << endl;
					cout << "2: Insert" << endl;
					cout << "3: Delete" << endl;
					cout << "4: Print" << endl;
					cin >> flag;
					cout << endl;
				} while ( flag != 1 && flag != 2 && flag != 3 && flag != 4 );
				
				if ( flag == 1 ) {
					cout << "Enter Transection_ID: " << endl;
					cin >> transectionID;
					cout << endl;
					if ( B.search( transectionID ) )
						cout << "Element Is Present." << endl;
					else
						cout << "Element Not Present." << endl;
				}
				
				else if ( flag == 2 ) {
					d.in();
					if ( !B.insert( d ) )
						cout << "Element Already Present. Cannot Insert" << endl;
					else
						cout << "Element Inserted." << endl;
				}
				
				else if ( flag == 3 ) {
					cout << "Enter Transection_ID: " << endl;
					cin >> transectionID;
					cout << endl;
					if ( B.deleteElement( transectionID ) )
						cout << "Element Deleted" << endl;
					else
						cout << "Element Already Not Present." << endl;
				}
				
				else
					B.print();
				
					cout << endl << "Continue (N/n for 'No'): ";
					cin >> contnue;
					cout << endl;
					
			} while ( contnue != 'N' && contnue != 'n' );
			
			ofs.open(f_name.c_str());
			B.out( ofs );
			
			break;
		}
		
		case '3': {
			avl_tree B;
			while ( ifs ) {
				d.read_file( ifs );
				B.insert_avl( d );
			}
			
			cout << "File Read Complete." << endl << endl;
			
			do {
				do {
					cout << "Select A Action: " << endl;
					cout << "1: Search" << endl;
					cout << "2: Insert" << endl;
					cout << "3: Delete" << endl;
					cout << "4: Print" << endl;
					cin >> flag;
					cout << endl;
				} while ( flag != 1 && flag != 2 && flag != 3 && flag != 4 );
				
				if ( flag == 1 ) {
					cout << "Enter Transection_ID: " << endl;
					cin >> transectionID;
					cout << endl;
					if ( B.search( transectionID ) )
						cout << "Element Is Present." << endl;
					else
						cout << "Element Not Present." << endl;
				}
				
				else if ( flag == 2 ) {
					d.in();
					if ( !B.insert_avl( d ) )
						cout << "Element Already Present. Cannot Insert" << endl;
					else
						cout << "Element Inserted." << endl;
				}
				
				else if ( flag == 3 ) {
					cout << "Enter Transection_ID: " << endl;
					cin >> transectionID;
					cout << endl;
					if ( B.deleteElement( transectionID ) )
						cout << "Element Deleted" << endl;
					else
						cout << "Element Already Not Present." << endl;
				}
				
				else
					B.print();
				
					cout << endl << "Continue (N/n for 'No'): ";
					cin >> contnue;
					cout << endl;
					
			} while ( contnue != 'N' && contnue != 'n' );
			
			ofs.open(f_name.c_str());
			B.out( ofs );
			
			break;
		}
	}
	
	return 0;
	
}
