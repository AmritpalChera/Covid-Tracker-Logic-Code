
#include "final_assignment.hpp"


using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() : root(NULL), size(0) {
}

void BinarySearchTree::cleanUp(Person* p) {
	if (!p) return;
	//using post-order traversal to delete nodes
	if (p->left)
		cleanUp(p->left);
	if (p->right)
		cleanUp(p->right);
	delete p;
}
// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	cleanUp(root);
	root = nullptr;
	size = 0;
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

bool BinarySearchTree::setContacts(string id, vector<Contact> arr) {
	Person* p = search(id);
	if (!p) return false;
	Contact temp;
	temp.target = p;
	for (auto element : arr) {
		p->contacts.push_back(element);
		temp.contactDays = element.contactDays;
		temp.location = element.location;
		element.target->contacts.push_back(temp);
	}
	return true;
}



int BinarySearchTree::height(Person* T) const {
	//base case: return -1 for empty tree
	if (T == NULL) return -1;
	else {
		return 1 + std::max(height(T->left), height(T->right));
	}
}
// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	int h = height(root);
	if (h < 0) h = 0;
	return h;
}

//print the data in_order
void BinarySearchTree::in_order(Person* T) const {
	if (T == NULL) return;
	in_order(T->left);
	//process data
	cout << "\n\nNEW PERSON";
	cout << "\nid: " << T->id << "\tName: " << T->firstName
		<< "\tPositive: " << T->isPositive << endl;
	for (int a = 0; a < T->contacts.size(); a++) {
		cout << "contact [" << (a+1)<<  "]\tName: " << T->contacts[a].target->firstName 
		<< "\tcontact days: " <<T->contacts[a].contactDays << "\t\tlocation: " 
			<< T->contacts[a].location<< endl;
	}
	
	in_order(T->right);
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	cout << "\n__________Cluster Data_______________\n";
	in_order(root);
	cout << "\n__________END OF THIS CLUSTER INFO___________";
}


bool BinarySearchTree::exists(Person* cur, string id) const {
	//if list is empty
	if (!cur)return false;
	//if root is the value of interest
	if (cur->id == id) return true;
	//if priority is greater than root priority, go right
	else if ((cur->id).compare(id) < 0)
		return exists(cur->right, id);
	//otherwise go left
	else
		return exists(cur->left, id);
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists(string id) const {
	return exists(root, id);
}

//returns number of edges for a particular node
int BinarySearchTree::getEdges(Person* node) {
	return node->contacts.size();
}



BinarySearchTree::Person* BinarySearchTree::search(string id) {
	if (!root) return NULL;
	Person* cur = root;
	bool found = false;
	while (cur && !found) {
		if (cur->id == id) found = true;
		else if ((cur->id).compare(id) < 0) cur = cur->right; //if (cur->id smaller, go right)
		else cur = cur->left; //otherwise cur->id must be bigger
	}
	return cur;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::Person* BinarySearchTree::get_root_node() {
	return root;
}

bool BinarySearchTree::insert(Person* cur, Person val, Person* parent) {
	if (exists(cur, val.id)) return false;

	//insertion should always be valid given that the data is valid
	Person* p; //temporary use
	//base case
	if (cur == NULL) {
		p = new Person(val);
		if (!parent) root = p;
		else if ((val.id).compare(parent->id) < 0) parent->left = p;
		else parent->right = p; //nodes with equal pririties will be on the right
		size++;
		return true;
	}

	//if val's priority is less, go left
	else if ((val.id).compare(cur->id) < 0) {
		return insert(cur->left, val, cur);
	}
	//if val's priority is higher, go right
	else
		return insert(cur->right, val, cur);

}
void BinarySearchTree::print_queue(queue<Person*> q) {
	while (q.size()) {
		cout << q.front()->firstName << " " ; q.pop();
	}
}
bool BinarySearchTree::exists(string id, vector<string> arr) const{
	for (int a = 0; a < arr.size(); a++) {
		if (arr[a] == id) return true;
	}
	return false;
}
//returns -1 if individual not in any cluster
int BinarySearchTree::count_virus_positive_contacts(string id) {
	queue<Person*> q; //for BFT traversal
	Person* cur = search(id); //returns the node to start at
	if (!cur) return -1;
	vector<string> visited; //stores the person's id
	visited.push_back(cur->id); //push current node into visited, rest will be inserted through contacts
	q.push(cur);
	int positive = 0;
	while (q.size()) {
		cur = q.front(); q.pop(); //update current
		//cout << "\nCurrent Node:\t" << cur->firstName << endl;
		if (cur->isPositive) positive++;
		for (int a = 0; a < cur->contacts.size(); a++) { //loop throguh the contacts, add unvisited to q
			//if not in visited and not null, then add to q
			Person* contact = cur->contacts[a].target;
			if (cur && (!exists(contact->id, visited))) {
				q.push(contact);
				visited.push_back(contact->id);//once pushed, mark as visited; its inevitable
			}
		}
	}
	if (search(id)->isPositive) positive--;
	return positive;
}

//returns the size of cluster if it has atleast 2 posi cases, else returns -1
int BinarySearchTree::clusterSize(Person* cur, vector<string>& visited) {
	queue<Person*> q; //for BFT traversal
	visited.push_back(cur->id); //push current node into visited, rest will be inserted through contacts
	q.push(cur);
	int positive = 0;
	int count = 0;
	while (q.size()) {
		cur = q.front(); q.pop(); //update current
		count++;
		//cout << "\nCurrent Node:\t" << cur->firstName << endl;
		if (cur->isPositive) positive++;
		for (int a = 0; a < cur->contacts.size(); a++) { //loop throguh the contacts, add unvisited to q
			//if not in visited and not null, then add to q
			Person* contact = cur->contacts[a].target;
			if (cur && (!exists(contact->id, visited))) {
				q.push(contact);
				visited.push_back(contact->id);//once pushed, mark as visited; its inevitable
			}
		}
	}
	if (positive >= 2) return count;
	return -1;
}

void BinarySearchTree::findCluster(Person* cur, vector<string>& visited, int& size) {
	if (!cur) return;
	findCluster(cur->left, visited, size);
	if ((!exists(cur->id, visited))) {
		int curSize = clusterSize(cur,visited);
		if (curSize > size) size = curSize;
	}
	findCluster(cur->right, visited, size);
}

//returns the largest sixe of cluster that has at least 2 positive cases, else returns -1
int BinarySearchTree::find_largest_cluster_with_two_positive() {
	vector<string> visited; //stores id of each visited node
	int size = 0;
	findCluster(get_root_node(), visited, size);
	if (size == 0) size = -1;
	return size;

}
//PURPOSE: to change the recent date of testing
bool BinarySearchTree::updateTestingDate(string id, string date) {
	Person* p = search(id);
	if (p) {
		p->testDate = date;
		return true;
	}
	return false;
}

bool BinarySearchTree::updatePosi(string id, bool posi) {
	Person* p = search(id);
	if (p) {
		p->isPositive = posi;
		return true;
	}
	return false;
}

//PURPOSE: to update the number of days met with contact
	//parameters: (person of interest, contact, days) 
bool BinarySearchTree::updateContactDays(string person, string contact, int days) {
	Person* p = search(person);
	Person* c = search(contact);
	if (!c || !p) return false;
	bool found = false;
	//travese through contacts, if contact found, update the days
	for (int a = 0; a < p->contacts.size() && !found; a++) {
		if (p->contacts[a].target == c) {
			p->contacts[a].contactDays = days;
			found = true;
		}
	}
	if (!found)return false;

	//if contact was found for p, it must also be in c
	for (int a = 0; a < c->contacts.size(); a++) {
		if (c->contacts[a].target == p) {
			c->contacts[a].contactDays = days;
			return true;
		}
	}
	return false;
}
//PURPOSE: to update the location at which met with contact
bool BinarySearchTree::updateContactLoco(string person, string contact, string loco) {
	Person* p = search(person);
	Person* c = search(contact);
	if (!c || !p) return false;
	bool found = false;
	//travese through contacts, if contact found, update the days
	for (int a = 0; a < p->contacts.size() && !found; a++) {
		if (p->contacts[a].target == c) {
			p->contacts[a].location = loco;
			found = true;
		}
	}
	if (!found)return false;

	//if contact was found for p, it must also be in c
	for (int a = 0; a < c->contacts.size(); a++) {
		if (c->contacts[a].target == p) {
			c->contacts[a].location = loco;
			return true;
		}
	}
	return false;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert(BinarySearchTree::Person val) {
	return insert(root, val, root);
}


// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove(string id) {
	//first task to check if the val exists
	if (!exists(root, id)) return false;

	/*
	in_order(root);
	cout << "END OF ORIGINAL__________________________\n\n";
	cout << "INFOO\n" << "val prior: " << val.priority << "\troot prior: " << root->priority <<endl;
	*/

	//now we sure its here somewhere
	Person* parent = nullptr;
	Person* cur = root;
	bool found = false; //is a mathcing node is found
	while (cur && (cur->right || cur->left) && !found) {
		if (id ==cur->id) {
			found = true;
		}
		//if value we searching for is lower in priority
		else if ((cur->id).compare(id) > 0) {
			parent = cur;
			cur = cur->left;
		}
		//takes care of equal priority but diff description
		else {
			parent = cur;
			cur = cur->right;
		}
	}

	//at this point we should have the parent node and the node to be removed. 
	bool right = (parent && parent->right == cur);
	//if lead node
	if (cur->left == NULL && cur->right == NULL) {
		delete cur; cur = nullptr;
		if (right) parent->right = nullptr;
		else if (parent)parent->left = nullptr;
		else root = nullptr; //if parent doesn't exist, means deleting root note
	}
	//cur has content on left
	else if (!cur->right) {
		//parent exists and has cur on right
		if (right) {
			parent->right = cur->left;
			delete cur;
		}
		//parent exists and has cur on left
		else if (parent) {
			parent->left = cur->left;
			delete cur;
		}
		//if parent doesn't exist; means deleting root node
		else {
			root = cur->left;
		}
	}
	//cur has content on right
	else if (!cur->left) {
		//parent has cur on right
		if (right) {
			parent->right = cur->right;
			delete cur;
		}
		//parent exists and has cur on left
		else if (parent) {
			parent->left = cur->right;
			delete cur;
		}
		//if parent doesn't exist' means deleting root node
		else {
			root = cur->right;
		}
	}
	//the above cases worked just by bypassing
	//now node has both children on both sides, so must find successor
	else {
		Person* successor = cur->right;
		Person* sParent = cur->right; //succesor's parent
		while (successor && successor->left) {
			successor = successor->left;
			if (successor->left) //if removing root node, parent will be null
				sParent = sParent->left;
		}

		//cout << "\nSuccessor: " << successor->priority << "\tsParent" << sParent->priority;

		//at this point, we will have the next lowest node and its parent
		//if cur's parent exists and cur is on the right
		if (parent && right) {
			parent->right = successor;
		}
		//if parent exists, and cur on left (not on right)
		else if (parent) {
			parent->left = successor;
		}
		//if no parent, that means its the root we are removing.
		else root = successor;
		successor->left = cur->left;

		if (successor != sParent) {
			successor->right = cur->right;
			if (sParent)sParent->left = nullptr;
		}

		//in any case, the successor would be on the left of its parent
		//unless its the immediate node after cur (it doesn't even matter then)
		delete cur;
		cur = nullptr;
	}
	//in_order(root);
	size--;
	return true;
}



//using post traversal
void AVLTree::updateAVLBalance(Person* cur, bool* rotate) {
	if (cur == nullptr) return;
	updateAVLBalance(cur->left, rotate);
	updateAVLBalance(cur->right, rotate);
	//process data here
	if (!cur->right && !cur->left) {
		cur->avlBalance = 0;
	}
	else {
		cur->avlBalance = (height(cur->left) + 1) - (height(cur->right) + 1);
		if (abs(cur->avlBalance) > 1) *rotate = true;
	}

}

//if this function is called, this means there is a node with abs(AVLBalance) > 1
void AVLTree::rotateTree(Person* cur, Person** cur_address, int a) {
	Person* q;
	Person* r;
	switch (a) {
	case 1:
		//right rotation
		q = cur->left;
		cur->left = q->right;
		q->right = cur;
		*cur_address = q;
		break;
	case 2:
		//left rotation
		q = cur->right;
		cur->right = q->left;
		q->left = cur;
		*cur_address = q;
		break;
	case 3:
		//rightLeft rotation
		q = cur->right;
		r = q->left;
		cur->right = r->left;
		q->left = r->right;
		r->left = cur;
		r->right = q;
		*cur_address = r;
		break;
	case 4:
		//left-right rotation
		q = cur->left;
		r = q->right;
		cur->left = r->right;
		q->right = r->left;
		r->left = q;
		r->right = cur;
		*cur_address = r;
		break;

	}
}
void AVLTree::rotateHelper(Person* cur, Person* parent) {
	if (cur == nullptr) return;
	//intially cur = parent;
	//node of interest

	//sometimes there can be more than 2 nodes whose balance > 2
	//and there will only be one correct one to rotate about
	bool found = false;

	if (abs(cur->avlBalance) > 1) {

		//left-right, means more nodes on the right side
		if (cur->avlBalance <= -2) {
			if (cur->right->avlBalance == -1) {
				found = true;
				//single left: 2
				//root node
				if (parent == cur) {
					rotateTree(root, &root, 2);
				}

				//cur is on the ledt side of parent
				else if (parent->left == cur) {
					//find the appropriate case
					rotateTree(cur, &parent->left, 2);

				}
				//cur is on the right side of parent
				else if (parent->right = cur) {
					rotateTree(cur, &parent->right, 2);
				}
			}


			else if (cur->right->avlBalance == 1) {
				found = true;
				//right left: 3
				//root node
				if (parent == cur) {
					rotateTree(root, &root, 3);
				}

				//cur is on the ledt side of parent
				else if (parent->left == cur) {
					//find the appropriate case
					rotateTree(cur, &parent->left, 3);

				}
				//cur is on the right side of parent
				else if (parent->right = cur) {
					rotateTree(cur, &parent->right, 3);
				}
			}
		}
		//left-right, means more nodes on the left side
		else if (cur->avlBalance >= 2) {
			if (cur->left->avlBalance == 1) {
				found = true;
				//single right: 1
				//root node
				if (parent == cur) {
					rotateTree(root, &root, 1);
				}

				//cur is on the ledt side of parent
				else if (parent->left == cur) {
					//find the appropriate case
					rotateTree(cur, &parent->left, 1);

				}
				//cur is on the right side of parent
				else if (parent->right = cur) {
					rotateTree(cur, &parent->right, 1);
				}
			}
			else if (cur->left->avlBalance == -1) {
				found = true;
				//left right: 4
				//root node
				if (parent == cur) {
					rotateTree(root, &root, 4);
				}

				//cur is on the ledt side of parent
				else if (parent->left == cur) {
					//find the appropriate case
					rotateTree(cur, &parent->left, 4);

				}
				//cur is on the right side of parent
				else if (parent->right = cur) {
					rotateTree(cur, &parent->right, 4);
				}
			}
		}

	}
	if (!found) {
		rotateHelper(cur->left, cur);
		rotateHelper(cur->right, cur);
	}
}


// PURPOSE: Inserts the value into the tree while keeping the tree balanced
// returns true if successful; returns false if val already exists
bool AVLTree::insert(BinarySearchTree::Person val) {
	if (!BinarySearchTree::insert(val)) return false;
	bool rotate = 0;
	updateAVLBalance(root, &rotate); //to update AVL values
	/*
	cout << "\nSTART OF PRINT BEFORE ROTATE\n";
	in_order(root);
	cout << "\nEND OF PRINT\n";
	cout << "\nROTATE: " << rotate << "\n";
	*/
	if (rotate) {
		rotateHelper(root, root);
	}
	rotate = false;
	updateAVLBalance(root, &rotate); //to update AVL values

	/*
	cout << "\nSTART OF PRINT AFTER ROTATE\n";
	in_order(root);
	cout << "\nEND OF PRINT\n";
	*/
	return true;
}