// Student Management System (Binary Search Tree)

/*
binary search tree is the binary tree which is having : left child < root < right child

*/
#include <iostream>
using namespace std;

class sms {
  public:
  //data to accept
    string name;
    string email;
    string seatno;
    string mothername;
    float cet;
//leftc and rightc of class type  
    sms *leftc;
    sms *rightc;

    void create();
    void insert(sms *root, sms *next, float cet);
    void display(sms *root);
    void displayIIT(sms *root);
    void displayNonIIT(sms *root);
    void searchstudent(sms *root, string ss, string mothername);
    void modifystudent(sms *root, string ss, string mothername);
    int height(sms *root);
    int countnode(sms *root);
    void displayroot(sms *root);
    void mirror(sms *root);
    void topper(sms *root);
    void lowestScore(sms *root); 
} *root = NULL, *nextn = NULL, *stk[50], *temp = NULL, *arr[10];

void sms::create() {
    int choice;
    if (root == NULL) {  // node has not created yet 
        root = new sms;    //memory allocation

        cout << "Enter Student Details" << endl;
        cout << "Enter Student Name: ";
        cin.ignore();
        getline(cin, root->name);

        cout << "Enter Student Email Address: ";
        getline(cin, root->email);
        cout << "Enter Student Seat No: ";
        getline(cin, root->seatno);
        cout << "Enter Student Mother Name: ";
        getline(cin, root->mothername);
        cout << "Enter Student CET Score: ";
        cin >> root->cet;
        cin.ignore();

        //set left and right child of root to NULL
        root->leftc = root->rightc = NULL;
    }
    do {
        cout << "Do You Want to Enter the Details Again (yes:1 | no:0): ";
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            nextn = new sms;

            cout << "Enter Student Details" << endl;
            cout << "Enter Student Name: ";
            getline(cin, nextn->name);

            cout << "Enter Student Email Address: ";
            getline(cin, nextn->email);
            cout << "Enter Student Seat No: ";
            getline(cin, nextn->seatno);
            cout << "Enter Student Mother Name: ";
            getline(cin, nextn->mothername);
            cout << "Enter Student CET Score: ";
            cin >> nextn->cet;
            cin.ignore();

            nextn->leftc = nextn->rightc = NULL;
            insert(root, nextn, nextn->cet);
        }
    } while (choice == 1);
}

void sms::insert(sms *root, sms *next, float cet) {
    if (next->cet < root->cet) {
        if (root->leftc == NULL) {
            root->leftc = next;
        } else {
            insert(root->leftc, next, cet);
        }
    } else {
        if (root->rightc == NULL) {
            root->rightc = next;
        } else {
            insert(root->rightc, next, cet);
        }
    }
}

void sms::display(sms *root) {  // Function to display student data using non-recursive in-order traversal.
    int i = 0, top = -1;  // 'i' tracks the index for the array, 'top' tracks the top of the stack.
    temp = root;  // Start with the root node of the tree.

    // If the tree is empty, display an appropriate message and exit the function.
    if (temp == NULL) {
        cout << "No Student Data Available" << endl;
        return;
    }

    // Perform non-recursive in-order traversal of the binary tree.
    do {
        // Traverse to the leftmost node of the current subtree.
        while (temp != NULL) {
            arr[i] = temp;  // Store the current node in the array 'arr'.
            i++;  // Increment the array index to prepare for the next node.
            stk[++top] = temp;  // Push the current node onto the stack for backtracking.
            temp = temp->leftc;  // Move to the left child of the current node.
        }

        // Backtrack using the stack and visit the right subtree.
        if (top != -1) {  // If there are still nodes in the stack to process:
            temp = stk[top--];  // Pop the top node from the stack (backtracking).
            temp = temp->rightc;  // Move to the right child of the current node.
        }
    } while (temp != NULL || top != -1);  // Repeat until all nodes are processed (stack is empty and no more nodes).

    // Print the details of all the nodes stored in 'arr' after traversal.
    for (int j = 0; j < i; j++) {
        cout << arr[j]->name << "\t"       // Print the name of the student.
             << arr[j]->email << "\t"      // Print the email of the student.
             << arr[j]->seatno << "\t"     // Print the seat number of the student.
             << arr[j]->cet << "\t"        // Print the CET (exam score) of the student.
             << arr[j]->mothername << endl; // Print the mother's name of the student.
    }
}

void sms::displayIIT(sms *root) {
    if (root == NULL){
        return;
    }
    //traverse both side and check the cet score greater than equal to 90 and accordingly print the details
    displayIIT(root->leftc);
    if (root->cet >= 90){
        cout << root->name << "\t" << root->email << "\t" << root->seatno << "\t" << root->cet << endl;
    }
    displayIIT(root->rightc);
}

void sms::displayNonIIT(sms *root) {
    if (root == NULL) {
        return;
    }

    //traverse both side and check the cet score less than 90 and accordingly print the details
    displayNonIIT(root->leftc);
    if (root->cet < 90) {
        cout << root->name << "\t" << root->email << "\t" << root->seatno << "\t" << root->cet << endl;
    }
    displayNonIIT(root->rightc);
}

int sms::countnode(sms *root) {
    //default condition
    if (root == NULL) {
        return 0;
    }
    //count the number of nodes in the left and right child and return the total count
    //1 is added to count the current node
    return 1 + countnode(root->leftc) + countnode(root->rightc);
}

void sms::searchstudent(sms *root, string ss, string mothername) {
//default condition
    if (root == NULL) {
        cout << "Student not found" << endl;
        return;
    }
    //comparison (for finding)
    if (root->seatno == ss && root->mothername == mothername) {
        cout << "Student Found: " << root->name << "  Email: " << root->email << "  PRN: " << root->seatno
             << "  CET Score: " << root->cet << "  Mother Name: " << root->mothername << endl;
        return;
    }
    //traversal - update
    if (ss < root->seatno) {
        searchstudent(root->leftc, ss, mothername);
    } 
    else {
        searchstudent(root->rightc, ss, mothername);
    }
}

void sms::modifystudent(sms *root, string ss, string mothername) {
    if (root == NULL) {
        cout << "Student not found" << endl;
        return;
    }
    if (root->seatno == ss && root->mothername == mothername) {
        cout << "Enter New Details for " << root->name << endl;
        cout << "Enter New Email Address: ";
        cin.ignore();
        getline(cin, root->email);
        cout << "Enter New Mother Name: ";
        getline(cin, root->mothername);
        cout << "Enter New CET Score: ";
        cin >> root->cet;
        cin.ignore();
        cout << "Details Updated Successfully" << endl;
        return;
    }
    if (ss < root->seatno) {
        modifystudent(root->leftc, ss, mothername);
    } else {
        modifystudent(root->rightc, ss, mothername);
    }
}

void sms::topper(sms *root) {
    //default condition
    if (root == NULL) {
        cout << "No Student Record Found in Database" << endl;
    } 
    else{
        while (root->rightc != NULL){
            root = root->rightc;
        }
        cout << "Topper Name: " << root->name << "  CET Score: " << root->cet << endl;
    }
}

void sms::lowestScore(sms *root) {
    if (root == NULL) {
        cout << "No Student Record Found in Database" << endl;
    } else {
        while (root->leftc != NULL) {
            root = root->leftc;
        }
        cout << "Lowest Scorer Name: " << root->name << "  CET Score: " << root->cet << endl;
    }
}

int sms::height(sms *root) {
    //default condtion
    if (root == nullptr) {
        return 0;
    }

    int leftHeight = height(root->leftc);
    int rightHeight = height(root->rightc);
    return 1 + max(leftHeight, rightHeight);
}

void sms::displayroot(sms *root) {
    if (root != NULL) {
        cout << "Root Node: " << root->name << endl;
    } 
    else {
        cout << "Tree is empty" << endl;
    }
}

void sms::mirror(sms *root) {
    //default condition
    if (root == NULL){
        return;
    }

    swap(root->leftc, root->rightc);
    mirror(root->leftc);
    mirror(root->rightc);
    /*
    can use the third variable to swap
    sms *temp = root->leftc;
    root->leftc = root->rightc;
    root->rightc = temp;
    */
}

// object creation
sms stud;
int main() {
    int choice;
    do {
        cout << "Student Management System\n"
             << "1.Insert Student Details\n"
             << "2.Display all student information\n"
             << "3.Display only IITian student information\n"
             << "4.Display non-IITian student information\n"
             << "5.Height of the tree\n"
             << "6.Mirror image of the tree\n"
             << "7.Count number of nodes\n"
             << "8.Search student information\n"
             << "9.Modify student information\n"
             << "10.Display Root Node\n"
             << "11.Display The Topper\n"
             << "12.Display The Lowest Scorer\n"
             << "13.Exit Student Management System" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                stud.create();
                cout << "Student Created Successfully" << endl;
                break;

            case 2:
                cout << "Name\tEmail\tSeat No\tCET Score\tMother Name" << endl;
                stud.display(root);
                break;

            case 3:
                cout << "Name\tEmail\tSeat No\tCET Score\tMother Name" << endl;
                stud.displayIIT(root);
                break;

            case 4:
                cout << "Name\tEmail\tSeat No\tCET Score\tMother Name" << endl;
                stud.displayNonIIT(root);
                break;

            case 5:
                cout << "Height of the tree: " << stud.height(root) << endl;
                break;

            case 6:
                stud.mirror(root);
                cout << "Mirror image of the tree created successfully" << endl;
                break;

            case 7:
                cout << "Number of nodes: " << stud.countnode(root) << endl;
                break;

            case 8: {
                string ss, mothername;
                cout << "Enter PRN to search: ";
                cin >> ss;
                cout << "Enter Mother Name to search: ";
                cin.ignore();
                getline(cin, mothername);
                stud.searchstudent(root, ss, mothername);
            }
                break;

            case 9: {
                string ss, mothername;
                cout << "Enter PRN to modify: ";
                cin >> ss;
                cout << "Enter Mother Name to modify: ";
                cin.ignore();
                getline(cin, mothername); 
                stud.modifystudent(root, ss, mothername);
            }
                break;

            case 10:
                stud.displayroot(root);
                break;

            case 11:
                stud.topper(root);
                break;

            case 12:
                stud.lowestScore(root);
                break;

            case 13:
                cout << "Exiting Student Management System" << endl;
                break;

            default:
                cout << "Invalid Choice, please try again!" << endl;
                break;
        }
    } while (choice != 13);

    return 0;
}
