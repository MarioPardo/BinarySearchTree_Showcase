#include<stdio.h>
#include<stdlib.h>

typedef struct Node_Struct
{
    int val;

    struct Node_Struct* left;
    struct Node_Struct* right;
}Node;

Node *newNode(int value)
{
    Node* newNode;
    newNode = (Node *) calloc(1,sizeof(Node));

    newNode->val = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node *searchNode(Node* root, int value)
{
    if(root == NULL)
        return NULL;

    if(root->val == value)
        return root;

    if(value <= root->val)
    {
        return searchNode(root->left, value);
    }else
    {
        return searchNode(root->right, value);
    }
}

Node *insert(Node* root, Node *new_node)
{
     double starVal = new_node->val;

    if(root == NULL)
    {
        return new_node;
    }

    //if not a duplicate;
    if(starVal == root->val)
    {
        printf("Duplicate node requested \n");
        return NULL;
    }

    if(starVal < root->val)
    {
        root->left = insert(root->left, new_node);
    }else
    {
        root->right = insert(root->right, new_node);
    }
    

    return root;
}

Node *findsuccessor(Node *rightChildNode)
{
    Node *temp;
    temp = rightChildNode;

    while(temp->left != NULL)
    {
        temp = temp->left;
    }

    return temp;
    
}

Node *deleteNode(Node *root, int value)
{

    if(root == NULL)
        return root;

    

  
    //traverse the tree
    if(value < root->val)
    {
        root->left = deleteNode(root->left, value);
    }else if (value > root->val)
    {
        root->right = deleteNode(root->right, value);
    }

    else //if current key is the one to be deleted
    {
        if(root->left == NULL) //leaf node or one child
        {   
            Node *q = root->right;
            free(root);
            return q;
        }else if(root->right == NULL)
        {
            Node *q = root->left;
            free(root);
            return q;
        }
        //if both are null, it will still return null, which works

        //if it continues from here, that means we have two children

        Node *successor = findsuccessor(root->right);//find successor
        root->val = successor->val;//copy values

        root->right = deleteNode(root->right, root->val);

    }
    return root;

}

void delete_BST(Node *root)
{
    //uses post order traversal since goes from bottom to top
    
         if(root == NULL) //reached end of subtree
    {
        return;
    }

        //left subtree
    delete_BST(root->left);

    //right subtree
    delete_BST(root->right);

    free(root);

}

//Traversals//

void inOrder(Node* root, int depth)
{
    if (root == NULL)
    {
        return;
    }

inOrder(root->left, depth +1);
printf("Depth: %i, Value: %i \n", depth, root->val);
inOrder(root->right, depth +1);

}

void preOrder(Node* root, int depth)
{
    if (root == NULL)
    {
        return;
    }

printf("Depth: %i, Value: %i \n", depth, root->val);
preOrder(root->left, depth +1);
preOrder(root->right, depth +1);

}

void postOrder(Node* root, int depth)
{
    if (root == NULL)
    {
        return;
    }

postOrder(root->left, depth +1);
postOrder(root->right, depth +1);
printf("Depth: %i, Value: %i \n", depth, root->val);
}

///// Misc Functions

void swapChildren(Node *root)
{
//use post order traversal
        if(root == NULL) //reached end of subtree
    {
        return;
    }

    //do the swapping
    Node *temp = root->left;
    root->left = root->right;
    root->right = temp;


    //left subtree
    swapChildren(root->left);

    //right subtree
    swapChildren(root->right);


}



/////
int main()
{

    int choice, value;
    Node *root=NULL;
    Node *new_node=NULL;
    Node *t=NULL;


      
    choice=0;
    while (choice!=7)
    {
      printf("Please select from among the following options:\n");
      printf("0 - Insert new note\n");
      printf("1 - Search for note\n");
      printf("2 - Delete note\n");
      printf("3 - Print notes in order\n");
      printf("4 - Print notes in pre-order\n");
      printf("5 - Print notes in post-order\n");
      printf("6 - Flip Tree Horizontally\n");
      printf("7 - Delete BST and exit\n");
      
      scanf("%d",&choice);
      getchar();

      if (choice==0)
      {
	printf("Enter the node's Value \n");
	scanf("%i",&value);
	getchar();
	new_node=newNode(value);
	root=insert(root,new_node);
      }
      
      if (choice==1)
      {
	printf("Please enter the Value:\n");
    scanf("%i",&value);
    getchar();
	t=searchNode(root,value);
	if (t!=NULL)
	{
	  printf("Found note with value: %i ", t->val);
	}
	else
	{
	  printf("No such note found in the tree\n");
	}	
      }
      
      if (choice==2)
      {
	printf("Please enter the Value:\n");
    scanf("%i",&value);
    getchar();
	root=deleteNode(root, value);
      }
      
      if (choice==3)
	    inOrder(root,0);
      
      if (choice==4)
	    preOrder(root,0);
      
      if (choice==5)
	    postOrder(root,0);
      
      if (choice==6)
      {
        swapChildren(root);
      }
      
      
    }	// End while (choice!=10)
    printf("Deleting Tree, Goodbye!\n");
    delete_BST(root);
    return 0;
}


  