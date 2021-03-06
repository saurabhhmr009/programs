/* Program to construct a Binary search tree in C. Functions used till now is
 * create root, insert node, Breadth level transverse.
 * Inorder transverse, pre order transverse and post order transverse.
 */

#include <stdio.h>
#include <stdlib.h>

// Structure having elements data and two pointers, one points to left and another to right. 
typedef struct Node {
    int data;
    struct Node *leftchild, *rightchild;
}node;

// Delete a BST using the Post order traversal method.
node* delete_nodes(node* root) {
    if(root == NULL) {
        return root;
    }
    delete_nodes(root->leftchild);
    delete_nodes(root->rightchild);

    free(root);
    root = NULL;
    return root;
}

// Get the minimum value of the left most leaf.
node* getMinNode(node* min)
{
    node* current = min;
 
    /* loop down to find the leftmost leaf */
    while (current && current->leftchild != NULL)
        current = current->leftchild;
    return current;
}

// Delete the node according to the key entered in BST menu.
node *delete_key(node* root, int key) {
    if(root == NULL) {
        return root;
    }
    // check if key is less than root node, go left.
    if(key < root->data) {
        root->leftchild = delete_key(root->leftchild, key);
    }
    // else  go right.
    else if(key > root->data) {
        root-> rightchild = delete_key(root->rightchild, key);
    }
    // Check for the one node root.
    else {
        if(root->leftchild == NULL) {
            node* temp = root->rightchild;
            free(root);
            root = NULL;
            return temp;
        }
        else if(root-> rightchild == NULL) {
            node *temp = root->leftchild;
            free(root);
            root = NULL;
            return temp;
        }
        node *temp = getMinNode(root->rightchild);
        root->data = temp->data;
        root->rightchild = delete_key(root->rightchild, temp->data);
    }
    return root;
}

/* Function to traverse BST in INORDER manner.
 * Procedure :  Traverse the left subtree and print node.
 * Visit Root node and print.
 * Traverse the right subtree.
 */
void print_inorder(node* root) {
    if(root == NULL) {
        return;
    }
    print_inorder(root->leftchild);
    printf("%d ", root->data);
    print_inorder(root->rightchild);

}

// Function to traverse in the Preorder manner in BST.
// Procedure: Print root, traverse left, traverse right.
void print_preorder(node *root) {
    if(root == NULL) {
        return;
    }
    printf("%d ", root->data);
    print_preorder(root->leftchild);
    print_preorder(root->rightchild);

}

// Function to traverse in the POST order manner in BST.
void print_postorder(node* root) {
    if(root == NULL) {
        return;
    }
    print_postorder(root->leftchild);
    print_postorder(root->rightchild);
    printf("%d ", root->data);
}

// Function to print nodes in the Breadth level manner.
void breadth_level(node* root, int level) {
    if(root == NULL) {
        return;
    }
    if(level == 1) {
        printf("%d ", root->data);
    }
    else if(level > 1) {
        breadth_level(root->leftchild, level -1);
        breadth_level(root->rightchild, level - 1);
    }
}

// Calculate the depth of a BST.
int calculate_depth(node *root) {
    int left_height, right_height;
    int depth;
    if(root == NULL) {
        return -1;
    }
    else {
        left_height = calculate_depth(root->leftchild);
        right_height = calculate_depth(root->rightchild);

        if(left_height > right_height) {
            depth = left_height + 1;
            //printf("Left %d\n", depth);
        }
        else {
            depth = right_height + 1;
            //printf("Right %d\n", depth);
        }
    }
    return depth;
}

// Function to create the node in BST
node* create_node(int key) {
    node* temp = NULL;
    temp = (node*)malloc(sizeof(node));
    temp->data = key;
    temp->leftchild = NULL;
    temp->rightchild = NULL;
    return temp;
}

// Function to insert the node in the BST.
node* insert_node(node* insert, int key) {
    node* temp = NULL;

    if(insert == NULL) {
        temp = create_node(key);
        return temp;
    }
    else {
        if(key < insert->data) {
            insert->leftchild = insert_node(insert->leftchild, key);
        }
        else {
            insert->rightchild = insert_node(insert->rightchild, key);
        }
    }
    return insert;
}

// Function to create the root node of the BST.
node* root_node(node *temp) {
    int data;
    if(temp !=  NULL) {
        printf("The root node is already created.\n");
    }
    else {
        printf("Enter the node data: \n");
        scanf("%d", &data);
        temp = create_node(data);
    }
    return temp;
}

// BST menu to be displayed.
int bst_menu() {
    int choice;
    printf("1. Create the root of the BST.\n");
    printf("2. Insert the node in the BST.\n");
    printf("3. Calculate the Depth of the BST.\n");
    printf("4. Print the nodes in Breadth/ Level search manner.\n");
    printf("5. Traverse the nodes in the Inorder manner.\n");
    printf("6. Traverse the nodes in the Preorder manner.\n");
    printf("7. Traverse the nodes in the postorder manner.\n");
    printf("8. Delete the whole BST.\n");
    printf("9. Delete the node according to a particular key in BST.\n");
    printf("10: Quit.\n");
    printf("Enter the operation to be perfomed on the BST: \n");
    scanf("%d", &choice);
    printf("\n");
    return choice;
}

int main(void) {
    node* root = NULL;
    int choice, data, i, depth = 0;
    
    while(1) {
        choice = bst_menu();
        switch(choice) {
            case 1: {
                root = root_node(root);
                printf("Root node created successfully!!!\n");
                printf("\n");
                break;
            }
            case 2: {
                printf("Enter the data to be inserted in the node: \n");
                scanf("%d", &data);
                root = insert_node(root, data);
                printf("Node is inserted successfully!!!\n");
                printf("\n");
                break;
            }
            case 3: {
                depth = calculate_depth(root);
                printf("Depth of the BST is %d\n", depth);
                break;
            }
            case 4: {
                depth = calculate_depth(root);
                for(i=1; i<=depth+1; i++) {
                    //printf("%d\n", depth);
                    breadth_level(root, i);
                }
                printf("\n");
                break;
            }
            case 5: {
                print_inorder(root);
                printf("\n");
                break;
            }
            case 6: {
                print_preorder(root);
                printf("\n");
                break;
            }
            case 7: {
                print_postorder(root);
                printf("\n");
                break;
            }
            case 8: {
                root = delete_nodes(root);
                printf("Tree Deleted!!!\n");
                break;
            }
            case 9: {
                int delete;
                printf("Enter the key node to be deleted:\n");
                scanf("%d", &delete);
                root = delete_key(root, delete);
                break;
            }
            case 10: {
                printf("Quitting\n");
                return 0;
            }
            default: {
                printf("Wrong input!!!!\n");
                return 1;
            }
        }
    }
    return 0;
}
