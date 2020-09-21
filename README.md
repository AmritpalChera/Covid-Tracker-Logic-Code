# Covid-Tracker-Logic-Code
This program implements AVL Trees to rapidly retrieve and store data about Covid cluster. 
The code uses basic logic with no GUI.

The *Person* instances were stored as pointers in an AVL tree. The contacts were stored as a vector in each *Person* instance.
One advantage of using AVL was that the search function could be used as many times as needed without worrying for efficiency.


**Documentation**

*Mutators*
```
Bool updateTestingDate(string, string) : updates the date at which the Person was tested

Bool updatePosi(string, bool): updates the virus status of the Person

Bool updateContactDays(string, string, int): updates when the 2 individuals last met

Bool updateContactLoco(sting,string, string): updates where the 2 individuals last met

Bool setContacts(string, vector<Contact>): sets the contacts for a specific Person

Bool insert(Person): inserts the Person into the tree and rotates tree according to the Person's id.
```

*Key Functions*
```
Int count_virus_positive_contacts(): returns the total number of Persons positive in a cluster

Int find_largest_cluster_with_two_positive(): returns the largest cluster size with 2+ positive cases
```

*Key Helpers*
```
Bool exists(string): returns if a specific Person exists within the database
Person* search(string): returns the node of the Person given the id
```
