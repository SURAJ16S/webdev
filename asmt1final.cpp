#include<iostream>
using namespace std;

//define the class 
class employee{
    public:
    //variable to accept 
    string name,id;

    employee *leftc,*rightc; //left and right child
  
    void create();                          //function to create the first node (root)
    void insert(employee *root, employee *next); //function to insert the next node
    void display(employee *root);                //function to display the employee details
    void preorder(employee *root);               //function to display the employee details in preorder
    void inorder(employee *root);                //function to display the employee details in inorder
    void postorder(employee *root);              //function to display the employee details in postorder
    void searchemp(employee *root, string ss);   //function to search the employee details
    void modifyemp(employee *root, string ss);   //function to modify the employee details
    int height(employee *root);                  //function to find the height of the tree
    int countnode(employee *root);               //function to count the total number of nodes
    void displayroot(employee *root);            //function to display the root node
    void mirror(employee *root);                 //function to mirror the tree

}*root=NULL ,*nextn=NULL ,*temp=NULL;

void employee::create(){
    cout<<"Enter Employee Details"<<endl;
    root = new employee;
    cout<<"Enter Employee Name : ";
    cin.ignore();
    getline(cin,root->name);
    cout<<"Enter Employee ID : ";
    getline(cin,root->id);

    //now the data is accepted for the root node now set the left and right child to NULL
    root->leftc = root->rightc = NULL;

    //ask user whether he want to add a new data 
    int choice;
     do{
          
        cout<<"Do You Want to Enter the Details Again (yes:1 | no:0): ";
        cin>>choice; //ask user whether he want to enter the details again or not

        //apply the condtion and accordingly allocate the memory and accept the data else exit the loop
        if(choice!=1){
            cout<<"Exiting..."<<endl; //exit the program
            break;
        }

        //allocate the memory for the next node 
        nextn = new employee;

        //accept and store in the next node
        cout<<"Enter Employee Name : ";
        cin.ignore();
        getline(cin,nextn->name);
        cout<<"Enter Employee ID : ";
        getline(cin,nextn->id);
        nextn->leftc = nextn->rightc = NULL;

        insert(root,nextn); //call the insert function to insert the next node
      

     }while(choice==1);
}

void employee::insert(employee *root, employee *next){
    //ask user where to store the data (Left OR Right)
    int choice;
    cout<<"Which side do want you want to store the details (1:left | 0:right):";
    cin>>choice;

    if(choice == 1){
        if (root->leftc ==NULL){
            root->leftc =next ; //store the next value in the leftc or root
        }
        else{
            insert(root->leftc,next);//traverse leftc of leftc 
        }
    }
     else{
        if(root->rightc ==NULL){
            root->rightc = next;
        }
        else{
            insert(root->rightc,next); //traverse rightc of rightc
        }
     }  
    }

void employee::display(employee *root){
//no recursive
}

void employee::preorder(employee *root){
    if(root == NULL){
        cout<<"No Data Found"<<endl;
    }
    else{
        cout<<"Employee Name : "<<root->name;
        cout<<"  Employee ID : "<<root->id<<endl;
        preorder(root->leftc);
        preorder(root->rightc);
    }
}

void employee::inorder(employee *root){
    if(root == NULL){      //root null means no data
        cout<<"No Data Found"<<endl;
    }
    else{
        inorder(root->leftc);
        cout<<"Employee Name : "<<root->name;
        cout<<"  Employee ID : "<<root->id<<endl;
        inorder(root->rightc);
    }
}

void employee::postorder(employee *root){
    if(root == NULL){      //root null means no data
        cout<<"No Data Found"<<endl;
    }
    else{
        postorder(root->leftc);
        postorder(root->rightc);

        cout<<"Employee Name : "<<root->name;
        cout<<"  Employee ID : "<<root->id<<endl;
        
    }
}

void employee::searchemp(employee *root, string ss){
    if(root ==NULL){    //not found //zero records
        cout<<"Employee Not Found"<<endl;
        return;
    }
    else{     //actual checking
        if(root->id == ss){
            cout<<"employee found"<<endl;
        }
        else{     //traversal
            searchemp(root->leftc,ss);   //traverse left
            searchemp(root->rightc,ss);  //traverse right
        }
    }
}

void employee::modifyemp(employee *root, string ss){
    if (root == NULL){
        cout<<"No Record found"<<endl;
        return;
    }
    else{
        if(root->id == ss){
            cout<<"Employee Found"<<endl;
            //accept new details
            cout<<"Enter New Name : ";
            cin.ignore();
            getline(cin,root->name);
            cout<<"Enter New ID : ";
            getline(cin,root->id);
            cout<<"Employee Details Updated"<<endl;
            return;
        }
        else{
            modifyemp(root->leftc,ss); //traverse left
            modifyemp(root->rightc,ss); //traverse right
        }
    }
}
//returning the height that's why it is 'int'
int employee::height(employee *root){
    if(root == NULL){
        cout<<"NO Data Found"<<endl; 
        return 0; //if the root is null then return 0
    }
    
        int lh = height(root->leftc); //left height
        int rh = height(root->rightc); //right height
    
        return 1 + max(lh,rh); //returning the max height + 1     //can also store the value in the new variable and then print the value
}

int employee::countnode(employee *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countnode(root->leftc) + countnode(root->rightc);
}


void employee::mirror(employee *root){
    if(root ==NULL){
        cout<<"No Employee Data Available"<<endl;
        return;
    }
    else{
        mirror(root->leftc); //traverse left
        mirror(root->rightc); //traverse right
        swap(root->leftc,root->rightc); //swap the left and right child

        /*  
        //using the third variable 
    employee *temp = root->leftc;
    root->leftc = root->rightc;
    root->rightc = temp; */
    }
}

void employee::displayroot(employee *root){
    if(root == NULL){
        cout<<"No Employee Data Available"<<endl;
        return;
    }
    else{
        cout<<"Root Node : "<<root->name<<endl; //display the root node
    }
}

int main(){
 string ss, ss1;
    int choice;
    employee emp; //creating the object of the class employee
    do
    {
        cout<<"1.insert data"<<endl;
        cout<<"2.display data"<<endl;
        cout<<"3.preorder"<<endl;
        cout<<"4.inorder"<<endl;
        cout<<"5.postorder"<<endl;
        cout<<"6.search employee"<<endl;
        cout<<"7.modify employee"<<endl;
        cout<<"8.height of the tree"<<endl;
        cout<<"9.count the number of nodes"<<endl;
        cout<<"10.display root node"<<endl;
        cout<<"11.mirror the tree"<<endl;
        cout<<"12.exit"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice; //accept the choice from the user
        switch(choice){
            case 1:
                emp.create(); //call the create function to create the first node (root)
                break;
            case 2:
                emp.display(root); //call the display function to display the employee details
                break;
            case 3:
                emp.preorder(root); //call the preorder function to display the employee details in preorder
                break;
            case 4:
                emp.inorder(root); //call the inorder function to display the employee details in inorder
                break;
            case 5:
                emp.postorder(root); //call the postorder function to display the employee details in postorder
                break;
            case 6:
                
                cout<<"Enter Employee ID to search : ";
                cin.ignore();
                getline(cin,ss); //accept the employee id to search
                emp.searchemp(root,ss); //call the searchemp function to search the employee details
                break;
            case 7:
                
                cout<<"Enter Employee ID to modify : ";
                cin.ignore();
                getline(cin,ss1); //accept the employee id to modify
                emp.modifyemp(root,ss1); //call the modifyemp function to modify the employee details
                break;
            case 8:
                cout<<"Height of the tree is : "<<emp.height(root)<<endl; //call the height function to find the height of the tree
                break;
            case 9:
                cout<<"Total number of nodes are : "<<emp.countnode(root)<<endl; //call the countnode function to count the total number of nodes
                break;
            case 10:
                emp.displayroot(root); //call the displayroot function to display the root node
                break;
            case 11:
                emp.mirror(root); //call the mirror function to mirror the tree
                cout<<"Tree Mirrored"<<endl;
                break;
            case 12:
                cout<<"Exiting..."<<endl; //exit the program
                break;
            default:    
                cout<<"Invalid choice"<<endl; //if the choice is invalid
                break;
        }

    } while (choice!=12);
    
    return 0;
}