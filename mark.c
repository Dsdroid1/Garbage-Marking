#include<stdio.h>
#include<stdlib.h>

typedef enum {FALSE,TRUE} Bool;
typedef enum {NOT_YET_TRAVERSED,LEFT_COMPLETED,COMPLETED} Status;
 
typedef struct Tree_Node_tag
{
    int data;
    Bool marked;
    Status s;
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
            }
               
        }
    }
}

void PrintTree(Tree_Node *root)
{
    //preorder
    if(root!=NULL)
    {
        printf("\nNode_data:%d",root->data);
        if(root->marked==TRUE)
        {
            printf("\nMarked Bit:True");
        }
        else
        {
            printf("\nMarked Bit:False");
        }
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
        printf("\n-------------------------");
        PrintTree(root->left);
        PrintTree(root->right);
    }
    
}

void main()
{
    Tree_Node *root;
    root=CreateBST();
    PrintTree(root);
    GarbageMark(root);
    printf("\n-------------------**************----------------------");
    PrintTree(root);
}