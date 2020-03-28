#include<stdio.h>
#include<stdlib.h>

typedef enum {FALSE,TRUE} Bool;
typedef enum {NOT_YET_TRAVERSED,LEFT_COMPLETED,COMPLETED} Status;
 
typedef struct Tree_Node_tag
{
    int data;
    Bool marked;//For method 2(By MorrisInorder Traversal)
    Status s;//For method 1
    struct Tree_Node_tag *left;
    struct Tree_Node_tag *right;
}Tree_Node; 

//------------Make a tree node---------------------
//Check in other functions if returned value is null
Tree_Node * MakeNode(int data)
{
    Tree_Node *node;
    node=(Tree_Node *)malloc(sizeof(Tree_Node));
    if(node!=NULL)
    {
        node->data=data;
        node->left=NULL;
        node->right=NULL;
        node->marked=FALSE;
        node->s=NOT_YET_TRAVERSED;
    }
    return node;
}
//-------------------------------------------------
//Will have to handle to condition of multiple entries
Tree_Node* InsertBST(Tree_Node *root,Tree_Node *new_node)
{
    Tree_Node *ptr,*retval;
    ptr=root;
    int flag=0;
    retval=root;
    if(ptr==NULL)
    {
        retval=new_node;
    }
    else
    {
        while(flag==0)
        {
            if(ptr->data>new_node->data)
            {
                if(ptr->left!=NULL)
                {
                    ptr=ptr->left;
                }
                else
                {
                    ptr->left=new_node;
                    flag=1;
                }
            }
            else if(ptr->data<new_node->data)
            {
                if(ptr->right!=NULL)
                {
                    ptr=ptr->right;
                }
                else
                {
                    ptr->right=new_node;
                    flag=1;
                }
            }
            else
            {
                printf("\n Data already exists!");
            }
            
        }
    }
    return retval;
}




Tree_Node* CreateBST()
{
    int flag=0;
    int code,data;
    Tree_Node *root=NULL,*new_node;
    while(flag==0)
    {
        printf("\nWhat operation do you want:");
        printf("\n1.Add Node");
        printf("\n2.Exit function:");
        scanf("%d",&code);
        switch (code)
        {
        case 1:
            printf("\nEnter data:");
            scanf("%d",&data);
            new_node=MakeNode(data);
            if(new_node!=NULL)
            {
                root=InsertBST(root,new_node);
            }
            else
            {
                printf("\nFailure");
            }
            break;
        
        default:
            flag=1;
            break;
        }
    }
    return root;
}
//------------------------------------------
void GarbageMark(Tree_Node *root)
{
    Tree_Node *prev,*curr,*tmp;
    //Initialisations
    prev=NULL;
    curr=root;
    int flag=0;
    while(flag==0)
    {
        //Visit the root(if not NULL)
        if(curr!=NULL)
        {
            curr->marked=TRUE;
            if(curr->s==NOT_YET_TRAVERSED)
            {
                curr->s=LEFT_COMPLETED;
                //left traversal will be done
                tmp=curr->left;
                curr->left=prev;
                prev=curr;
                curr=tmp;
            }
            else if(curr->s==LEFT_COMPLETED)
            {
                curr->s=COMPLETED;
                tmp=curr->right;
                curr->right=prev;
                prev=curr;
                curr=tmp;
                
            }
            else
            {
                //This node has been visited via elsewhere,stop here i.e go back
                if(prev!=NULL)
                {
                    if(prev->s==LEFT_COMPLETED)
                    {
                        tmp=prev->left;
                        prev->left=curr;
                        curr=prev;
                        prev=tmp;
                    }
                    else if(prev->s==COMPLETED)
                    {
                        tmp=prev->right;
                        prev->right=curr;
                        curr=prev;
                        prev=tmp;
                    }
                }
                else
                {
                    if(curr==root)
                    {
                        flag=1;
                    }
                }
                
            }
        }
        else
        { 
            //if prev!=NULL
            if(prev!=NULL)
            {
                if(prev->s==LEFT_COMPLETED)
                {
                    tmp=prev->left;
                    prev->left=curr;
                    curr=prev;
                    prev=tmp;
                }
                else
                {
                    tmp=prev->right;
                    prev->right=curr;
                    curr=prev;
                    prev=tmp;
                }
            }
            else
            {
                //Given tree was null
                flag=1;
                printf("Given tree was null");
            }
               
        }
    }
}

void GarbageMarkByMorrisInorderTraversal(Tree_Node *root)
{
    Tree_Node *prev,*trav;
    while(root!=NULL)
    {
        if(root->left==NULL)
        {
            root->marked=TRUE;
            root=root->right;
        }
        else
        {
            prev=root->left;
            while(prev->right!=NULL && prev->right!=root)
            {
                prev=prev->right;
            }
            if(prev->right==NULL)//New inorder link to be established
            {
                prev->right=root;
                root=root->left;
            }
            else
            {
                //The inorder link was already made
                //This is the visit of the inorder link made
                (prev->right)->marked=TRUE;
                prev->right=NULL;
                root=root->right;
            }
            
        }
        
    }
}

void PrintTree(Tree_Node *root,Bool mode)
{
    //Mode 0 means print according to GarbageMark method
    //Mode 1 means according to morris inorder traversal
    //Inorder
    if(root!=NULL)
    {
        if(root->left!=NULL)
        {
            PrintTree(root->left,mode);
        }
        printf("\nNode_data:%d",root->data);
        if(mode==TRUE)
        {
            if(root->marked==TRUE)
            {
                printf("\nMarked Bit:True");
            }
            else
            {
                printf("\nMarked Bit:False");
            }
        }
        else
        {
           if(root->s==NOT_YET_TRAVERSED)
            {
                printf("\nNOT_YET_TRAVERSED");
            }
            else if(root->s==LEFT_COMPLETED)
            {
                printf("\nLEFT_COMPLETED");
            }
            else
            {
                printf("\nCOMPLETED");
            }   
        }
        
        
        printf("\n-------------------------");
        if(root->right!=NULL)
        {
            PrintTree(root->right,mode);
        }
    }
}

void main()
{
    Tree_Node *root;
    Bool mode=FALSE;
    int temp;
    root=CreateBST();
    printf("\nWhich Method would you like:");
    printf("\n1.Method of reversing the tree links  or");
    printf("\n2.Method of Morris Inorder Traversal");
    printf("\n(Any other choice will result in method 1):");
    scanf("%d",&temp);
    if(temp==2)
    {
        mode=TRUE;
        PrintTree(root,mode);
        GarbageMarkByMorrisInorderTraversal(root);
    }
    else
    {
        PrintTree(root,mode);
        GarbageMark(root);
    }
    
    //PrintTree(root);
    //GarbageMark(root);
    
    printf("\n-------------------**************----------------------");
    PrintTree(root,mode);
}