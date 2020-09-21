#ifndef LAB4_TESTS_HPP
#define LAB4_TESTS_HPP

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

#include "final_assignment.hpp"
#include <algorithm>
#include <sstream>
#include <queue>
#include <iostream>
using namespace std;



class GraphTest {
public:
	
	bool insert_AVLnodes(AVLTree& tree, string* in, int nin) {
		for (int i = 0; i < nin; i++) {
			ASSERT_TRUE(tree.insert(AVLTree::Person(in[i],in[i], "none", false)));
		}
		return true;
	}

	bool insert_AVLnodes(AVLTree& tree, string* in, int nin, string* loco, bool* posi) {
		for (int i = 0; i < nin; i++) {
			ASSERT_TRUE(tree.insert(AVLTree::Person(in[i], in[i], loco[i], posi[i])));
		}
		return true;
	}

	bool insertContacts(AVLTree& tree, string* in, vector<vector<BinarySearchTree::Contact>> arr, int nin) {
		for (int a = 0; a < nin; a++) {
			tree.setContacts(in[a], arr[a]);
		}
		return true;
	}

	std::string getContacts(AVLTree& tree, string n) {
		vector<BinarySearchTree::Contact> arr;
		string cont = "";
		if (tree.search(n)) {
			arr = (tree.search(n))->contacts;
			for (auto element : arr) cont += element.target->id + " ";
		}
		return cont;
	}
	


	std::string level_order(BinarySearchTree::Person* root) {
		if (!root) {
			return "";
		}
		std::stringstream ss;
		std::queue<BinarySearchTree::Person*> node_queue;
		node_queue.push(root);
		while (!node_queue.empty()) {
			BinarySearchTree::Person* cur_node = node_queue.front();
			node_queue.pop();
			ss << cur_node->firstName << " ";
			if (cur_node->left) {
				node_queue.push(cur_node->left);
			}
			if (cur_node->right) {
				node_queue.push(cur_node->right);
			}
		}

		std::string level_order_str = ss.str();

		return level_order_str.substr(0, level_order_str.size() - 1);
	}
	//Insert, print and retreive individual persons with no contacts
	bool test1() {
		AVLTree tree;
		string in[] = { "Andy", "Dar", "Mar", "Mike", "Kelsy" };
		insert_AVLnodes(tree, in, 5);
		string c = level_order(tree.get_root_node());
		string expected = "Dar Andy Mar Kelsy Mike";
		ASSERT_TRUE(c == expected);
		ASSERT_TRUE((tree.search("Dar"))->firstName == "Dar");
		ASSERT_TRUE((tree.search("Mar"))->firstName == "Mar");
		ASSERT_TRUE((tree.search("Kelsy"))->firstName == "Kelsy");
		ASSERT_TRUE((tree.search("Mike"))->firstName == "Mike");
		ASSERT_TRUE((tree.search("Andy"))->firstName == "Andy");
		return true;
	}

	//Insert, print and retreive individual persons with contacts; only one cluster
	bool test2() {
		AVLTree tree;
		//tree up and ready at this point, retreive all nodes and add contacts
		vector<BinarySearchTree::Contact> arr;
		vector<vector<BinarySearchTree::Contact>> node;
		node.resize(5);

		//isPositive Irrelevant for now
		
		string in[] = { "Andy","Dar", "Mar", "Mike", "Kelsy" };
		ASSERT_TRUE(insert_AVLnodes(tree, in, 5));

		//andy's contacts
		
		node[0].push_back(BinarySearchTree::Contact(tree.search("Kelsy"), 1, "the market")); //contact 1
		node[0].push_back(BinarySearchTree::Contact(tree.search("Dar"), 1, "the palace")); //contact 2

		//dar's contacts
		node[1].push_back(BinarySearchTree::Contact(tree.search("Mar"), 1, "the market")); //contact 1
		//contact 2 is already Andy

		//mar's contacts
		node[2].push_back(BinarySearchTree::Contact(tree.search("Kelsy"), 1, "the house")); //contact 1
		node[2].push_back(BinarySearchTree::Contact(tree.search("Mike"), 1, "the palace")); //contact 2
		//contact 3 is already dar

		//mike's contacts
		node[3].push_back(BinarySearchTree::Contact(tree.search("Andy"), 1, "the house")); //contact 1
		//contact 2 is already Mike

		//Kelsy's contacts are already taken care of; as other people met Kelsy
		ASSERT_TRUE(insertContacts(tree, in, node, 5));
		
		//insertContacts(tree, "Dar", node[1]);
		//tree.print();
		ASSERT_TRUE((tree.getEdges(tree.search("Andy")) == 3));
		ASSERT_TRUE((tree.getEdges(tree.search("Dar")) == 2));
		ASSERT_TRUE((tree.getEdges(tree.search("Mar")) == 3));
		ASSERT_TRUE((tree.getEdges(tree.search("Mike")) == 2));
		ASSERT_TRUE((tree.getEdges(tree.search("Kelsy")) == 2));
		return true;

	}

	//Testing Function one with one cluster only
	bool test3() {
		AVLTree tree;
		vector<BinarySearchTree::Contact> arr;
		vector<vector<BinarySearchTree::Contact>> node;
		node.resize(5);

		//3 parallel arrays
		string in[] = { "Andy","Dar", "Mar", "Mike", "Kelsy" };
		string dateTested[] = { "1", "2", "3","4", "5" };
		bool positive[] = { false, true, true, false, true };

		ASSERT_TRUE(insert_AVLnodes(tree, in, 5, dateTested, positive));

		//andy's contacts

		node[0].push_back(BinarySearchTree::Contact(tree.search("Kelsy"), 1, "the market")); //contact 1
		node[0].push_back(BinarySearchTree::Contact(tree.search("Dar"), 1, "the palace")); //contact 2

		//dar's contacts
		node[1].push_back(BinarySearchTree::Contact(tree.search("Mar"), 1, "the market")); //contact 1
		//contact 2 is already Andy

		//mar's contacts
		node[2].push_back(BinarySearchTree::Contact(tree.search("Kelsy"), 1, "the house")); //contact 1
		node[2].push_back(BinarySearchTree::Contact(tree.search("Mike"), 1, "the palace")); //contact 2
		//contact 3 is already dar

		//mike's contacts
		node[3].push_back(BinarySearchTree::Contact(tree.search("Andy"), 1, "the house")); //contact 1
		//contact 2 is already Mike

		//Kelsy's contacts are already taken care of; as other people met Kelsy
		ASSERT_TRUE(insertContacts(tree, in, node, 5));
		//tree.print();
		ASSERT_TRUE(tree.count_virus_positive_contacts("Andy") == 3);
		//not counting the first person
		ASSERT_TRUE(tree.count_virus_positive_contacts("Dar") == 2);
		//heal Dar and Kelsy
		tree.updatePosi("Dar", false); 
		tree.updatePosi("Kelsy", false); 
		ASSERT_TRUE(tree.count_virus_positive_contacts("Mar") == 0);
		ASSERT_TRUE(tree.count_virus_positive_contacts("Kelsy") == 1);
		return true;
	}

	//test number of cases positive with multiple (2) clusters
	bool test4() {
		AVLTree tree;
		//3 parallel arrays of each individual and their data
		ASSERT_TRUE(tree.count_virus_positive_contacts("Empty Me") == -1);
		string in[] = { "Andy","Dar", "Mar", "Mike", "Kelsy", "Nate", "Oli", "Shell", "Jess" };
		string dateTested[] = { "1", "2", "3","4", "5", "6", "7", "8", "9" };
		bool positive[] = { false, true, true, false, true, true, false, true, false };
		ASSERT_TRUE(insert_AVLnodes(tree, in, 9, dateTested, positive));

		//tree readt at this point, insert contacts

		//contacts
		vector<BinarySearchTree::Contact> arr;
		vector<vector<BinarySearchTree::Contact>> node;
		node.resize(9);

		//__________________________CLUSTER 1_____________________________
		//andy's contacts
		node[0].push_back(BinarySearchTree::Contact(tree.search("Kelsy"), 1, "the market")); //contact 1
		node[0].push_back(BinarySearchTree::Contact(tree.search("Dar"), 1, "the palace")); //contact 2

		//dar's contacts
		node[1].push_back(BinarySearchTree::Contact(tree.search("Mar"), 1, "the market")); //contact 1
		//contact 2 is already Andy

		//mar's contacts
		node[2].push_back(BinarySearchTree::Contact(tree.search("Kelsy"), 1, "the house")); //contact 1
		node[2].push_back(BinarySearchTree::Contact(tree.search("Mike"), 1, "the palace")); //contact 2
		//contact 3 is already dar

		//mike's contacts
		node[3].push_back(BinarySearchTree::Contact(tree.search("Andy"), 1, "the house")); //contact 1
		//contact 2 is already Mike

		//___________________________CLUSTER 2_____________________________
		//nodees -> 5: Nate, 6 : Oli, 7: Shell, 8:Jess

		//Nate's Contacts
		node[5].push_back(BinarySearchTree::Contact(tree.search("Jess"), 5, "the house")); //contact 1
		node[5].push_back(BinarySearchTree::Contact(tree.search("Oli"), 2, "the house")); //contact 2

		//Oli's contacts, nate already there
		node[6].push_back(BinarySearchTree::Contact(tree.search("Jess"), 5, "the house")); //contact 2
		node[6].push_back(BinarySearchTree::Contact(tree.search("Shell"), 7, "the mall")); //contact 3

		//Shell's contacts, Oli already there
		node[7].push_back(BinarySearchTree::Contact(tree.search("Jess"), 5, "the mall")); //contact 2
		//______________________________________________________________________________

		ASSERT_TRUE(insertContacts(tree, in, node, 9))
		ASSERT_TRUE(tree.count_virus_positive_contacts("Andy") == 3);
		ASSERT_TRUE(tree.count_virus_positive_contacts("Oli") == 2);
		tree.updatePosi("Dar", false); //heal dar
		ASSERT_TRUE(tree.count_virus_positive_contacts("Mike") == 2);
		//test on an invalid name
		ASSERT_TRUE(tree.count_virus_positive_contacts("Hanna") == -1);
		//heal nate and shell
		tree.updatePosi("Nate", false);
		tree.updatePosi("Shell", false);
		ASSERT_TRUE(tree.count_virus_positive_contacts("Oli") == 0);
		return true;

	}


	//testing the second function with 2 clusters
	//test number of cases positive with multiple (2) clusters
	bool test5() {
		AVLTree tree;
		//3 parallel arrays of each individual and their data
		ASSERT_TRUE(tree.find_largest_cluster_with_two_positive() == -1);
		string in[] = { "Andy","Dar", "Mar", "Mike", "Kelsy", "Nate", "Oli", "Shell", "Jess" };
		string dateTested[] = { "1", "2", "3","4", "5", "6", "7", "8", "9" };
		bool positive[] = { false, true, true, false, true, true, false, true, false };
		ASSERT_TRUE(insert_AVLnodes(tree, in, 9, dateTested, positive));

		//tree readt at this point, insert contacts

		//contacts
		vector<BinarySearchTree::Contact> arr;
		vector<vector<BinarySearchTree::Contact>> node;
		node.resize(9);

		//__________________________CLUSTER 1_____________________________
		//andy's contacts
		node[0].push_back(BinarySearchTree::Contact(tree.search("Kelsy"), 1, "the market")); //contact 1
		node[0].push_back(BinarySearchTree::Contact(tree.search("Dar"), 1, "the palace")); //contact 2

		//dar's contacts
		node[1].push_back(BinarySearchTree::Contact(tree.search("Mar"), 1, "the market")); //contact 1
		//contact 2 is already Andy

		//mar's contacts
		node[2].push_back(BinarySearchTree::Contact(tree.search("Kelsy"), 1, "the house")); //contact 1
		node[2].push_back(BinarySearchTree::Contact(tree.search("Mike"), 1, "the palace")); //contact 2
		//contact 3 is already dar

		//mike's contacts
		node[3].push_back(BinarySearchTree::Contact(tree.search("Andy"), 1, "the house")); //contact 1
		//contact 2 is already Mike

		//___________________________CLUSTER 2_____________________________
		//nodees -> 5: Nate, 6 : Oli, 7: Shell, 8:Jess

		//Nate's Contacts
		node[5].push_back(BinarySearchTree::Contact(tree.search("Jess"), 5, "the house")); //contact 1
		node[5].push_back(BinarySearchTree::Contact(tree.search("Oli"), 2, "the house")); //contact 2

		//Oli's contacts, nate already there
		node[6].push_back(BinarySearchTree::Contact(tree.search("Jess"), 5, "the house")); //contact 2
		node[6].push_back(BinarySearchTree::Contact(tree.search("Shell"), 7, "the mall")); //contact 3

		//Shell's contacts, Oli already there
		node[7].push_back(BinarySearchTree::Contact(tree.search("Jess"), 5, "the mall")); //contact 2
		//______________________________________________________________________________

		ASSERT_TRUE(insertContacts(tree, in, node, 9));
		ASSERT_TRUE(tree.find_largest_cluster_with_two_positive() == 5);
		tree.updatePosi("Dar", false); //dar cures, now there are only 2 poitive cases in both clusters
		ASSERT_TRUE(tree.find_largest_cluster_with_two_positive() == 5);
		tree.updatePosi("Mar", false); //Mar cures, now there are only 1 poitive case in cluster with 5 people
		ASSERT_TRUE(tree.find_largest_cluster_with_two_positive() == 4);
		tree.updatePosi("Shell", false); //Shell cures, now there are only 1 poitive case in both clusters
		ASSERT_TRUE(tree.find_largest_cluster_with_two_positive() == -1);
		return true;

	}


};

#endif
