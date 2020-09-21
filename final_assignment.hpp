#pragma once
#ifndef LAB3_BINARY_SEARCH_TREE_HPP
#define LAB3_BINARY_SEARCH_TREE_HPP

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// PURPOSE: Models a Binary Search Tree of Task Items
class BinarySearchTree {
protected:
	// PURPOSE: Models a single Task Item as a Tree Node
	struct Contact;
	struct Person {
		string firstName; //first name of person
		string testDate; //most recent test data
		bool isPositive; //true if person tested positive
		vector<Contact> contacts; //list of connected nodes
		Person* left; //for the AVLTree only
		Person* right; //for the AVLTree only
		int avlBalance;
		string id; //unique identifier
		Person(string fName, string idnty, string tDate, bool posi) :
			firstName(fName), id(idnty), testDate(tDate), isPositive(posi)
		{
			avlBalance = 0;
			left = right = nullptr;
		};

		Person(string fName, string idnty, string tDate, bool posi, vector<Contact> v) :
			firstName(fName), id(idnty), testDate(tDate), isPositive(posi), contacts(v) 
		{
			avlBalance = 0;
			left = right = nullptr;
		};

		
	};
	struct Contact {
		Person* target;
		int contactDays; //-1 by default (didn't meet)
		string location; //location of contact
		Contact() : contactDays(-1), location(""), target(nullptr) {};
		//(target*, days since contact, location met)
		Contact(Person* tar, int days, string loc) : 
			contactDays(days), location(loc), target(tar) {};
	};


	void cleanUp(Person* p);
	int height(Person* cur) const;
	void in_order(Person* T) const;
	bool exists(Person* cur, string id) const;
	bool insert(Person* cur, Person val, Person* parent);
	bool remove(Person* cur, Person val, Person parent);
	bool search(Person*& cur, string id, Person*& parent);

	//helper of findCluster
	//returns the size of the cluster
	int clusterSize(Person*, vector<string>& visited);

	//helper of find_largest_cluster_with_two_positive()
	//finds new clusters and compares their size
	void findCluster(Person*, vector<string>&, int& size);



	friend class GraphTest;

	// pointer to the root node of the tree	
	Person* root;

	// number of nodes in the tree
	unsigned int size;

public:
	// CONSTRUCTOR AND DESTRUCTOR

	// PURPOSE: Default/empty constructor
	BinarySearchTree();

	// PURPOSE: Explicit destructor of the class BinarySearchTree
	~BinarySearchTree();

	// ACCESSORS  
	// PURPOSE: Returns the number of nodes in the tree
	unsigned int get_size() const;

	//set contacts
	bool setContacts(string, vector<Contact>);

	//returns the node or index of the person with specified id
	//if not found, returns null
	Person* search(string);
	
	//returns number of edges for a particular node
	int getEdges(Person* node);

	// PURPOSE: Returns the tree height
	unsigned int height() const;

	// PURPOSE: Prints the contents of the tree; format not specified
	void print() const;

	// PURPOSE: Returns true if a node with the value val exists in the tree	
	// otherwise, returns false
	bool exists(string id) const;
	//just for testing
	void print_queue(queue<Person*>);

	//helper of count_virus_positive_contacts(string); return if a string exists in vector
	bool exists(string, vector<string>)const;

	// PURPOSE: Optional helper function that returns a pointer to the root node
	Person* get_root_node();


	// PURPOSE: Optional helper function that returns the root node pointer address
	Person** get_root_node_address();

	// PURPOSE: Optional helper function that gets the maximum depth for a given node
	int get_node_depth(Person* n) const;

	// MUTATORS

	// PURPOSE: Inserts the value val into the tree if it is unique
	// returns true if successful; returns false if val already exists
	bool insert(Person val);

	// PURPOSE: Removes the node with the value val from the tree
	// returns true if successful; returns false otherwise
	bool remove(string val);

	//PURPOSE: to change the recent date of testing
	bool updateTestingDate(string p, string date);
	//PURPOSE: to update if the person tested positive
	bool updatePosi(string id, bool);

	//PURPOSE: to update the number of days met with contact
	//parameters: (person of interest, contact, days) 
	bool updateContactDays(string person, string contact, int days);
	//PURPOSE: to update the location at which met with contact
	bool updateContactLoco(string person, string contact, string loco);


	//FUNCTIONS

	
	//returns the number of individual declared positive in a cluster
	int count_virus_positive_contacts(string id);

	
	//returns the largest sixe of cluster that has at least 2 positive cases, else returns -1
	int find_largest_cluster_with_two_positive();
};

class AVLTree : public BinarySearchTree {
	// Define additional functions and attributes that you need below	
	void updateAVLBalance(Person* cur, bool* rotate);
	void rotateTree(Person* cur, Person** cur_address, int a);
	void rotateHelper(Person* cur, Person* parent);


public:
	// PURPOSE: Overrides the BST insert function to keep the tree balanced
	bool insert(Person val);
};
#endif