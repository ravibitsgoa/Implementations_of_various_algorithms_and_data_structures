#include <iostream>
#include <cassert>
using namespace std;
class Node
{
public:
	Node* left;
	Node* right;	
	Node* parent;	//notice this parent pointer.
	int data;
	Node(int x, Node* par)
	{
		data = x;
		left = nullptr;
		right = nullptr;
		parent = par;
	}
};

class BST
{
private:
	Node* root;

	//returns the node containing the value x, in subtree of head.
	Node* search(int x, Node* head)
	{
		if(head == nullptr)					//if this node doesn't exist, the value is not there in whole BST.
			return nullptr;
		if(head->data == x)					//if this node has value x, we return it.
			return head;
		if(head-> data < x)					//if x is more than data of this node, recurse on right subtree.
			return search(x, head->right);	
		else								//if x is less than data of this node, recurse on left subtree.
			return search(x, head->left);
	}

	//inserts value x into subtree of head.
	Node* insert(int x, Node* head)
	{
		if(head == nullptr)						//if we hit a null pointer, something has gone wrong.
			assert(false);

		if(head->data == x)						//if we already have this value, we don't insert again.
			return head;
		
		if(head-> data < x)						//if x is more than data of this node, recurse on right subtree.
		{	if(head->right != nullptr)			//if right subtree exists, recurse on it.
				return insert(x, head->right);
			else								//otherwise make a right child.
			{
				head->right = new Node(x, head);
				return head->right;
			}
		}
		else									//if x is less than data of this node, recurse on left subtree.
		{	if(head->left != nullptr)			//if left subtree exists, recurse on it.
				return insert(x, head->left);
			else								//otherwise make a left child.
			{
				head->left = new Node(x, head);
				return head->left;
			}
		}
	}

	//deletes passed node.
	bool delet(Node* node)
	{
		if(node == nullptr)					//if this node already doesn't exist, don't do anything. 
			return false;
		
		if(node->right != nullptr)			//if node has a right child, it will have a successor.
		{	Node* right_child = node->right;
			if(right_child -> left != nullptr)
			{
				while(right_child->left->left != nullptr)
					right_child = right_child->left;
				node->data = right_child->left->data;
				Node* to_be_deleted = right_child->left;	//Delete successor of 'node'.
				right_child->left = right_child->left->right;
				delete to_be_deleted;
			}
			else
			{
				node->data = right_child->data;
				Node* to_be_deleted = right_child;			//Delete successor of 'node'.
				node->right = right_child->right;
				delete to_be_deleted;
			}
		}
		else if(node->left != nullptr)		//if node has a left child, it has a predecessor.
		{	Node* left_child = node->left;
			if(left_child -> right != nullptr)
			{
				while(left_child->right->right != nullptr)
					left_child = left_child->right;
				node->data = left_child->right->data;
				Node* to_be_deleted = left_child->right;	//Delete predecessor of 'node'.
				left_child->right = left_child->right->left;
				delete to_be_deleted;
			}
			else
			{
				node->data = left_child->data;
				Node* to_be_deleted = left_child;			//Delete predecessor of 'node'.
				node->left = left_child->left;
				delete to_be_deleted;
			}
		}
		else	//if node doesn't have any child (i.e. it's leaf) , just delete this node.
		{
			Node* parent_of_node = node->parent;
			
			if(parent_of_node == nullptr)			//if node is root, and doesn't have any child.
			{
				delete node;
				root = nullptr;
				return true;
			}

			if(parent_of_node->left == node)		//if node is left child of its parent, make parent's left pointer null.
				parent_of_node->left = nullptr;
			else if(parent_of_node->right == node)	//if it's right child of its parent, make parent's right pointer null.
				parent_of_node->right = nullptr;
			else									//if it's neither. Something has gone wrong while constructing 'node'.
				assert(false);
			delete node;
		}
		return true;
	}

	void print_pre_order(Node* head)
	{
		if(head == nullptr)
			return;
		cout << head->data << ' ';
		print_pre_order(head->left);
		print_pre_order(head->right);
	}

public:
	BST()
	{
		root = nullptr;
	}

	void insert(int x)
	{
		if(root == nullptr)
			root = new Node(x, nullptr);
		else
			insert(x, root);
	}

	bool search(int x)
	{
		if(search(x, root) != nullptr)
			return true;
		return false;
	}

	bool delet(int x)
	{
		if(root == nullptr)
			return false;
		delet(search(x, root));
	}

	void print_pre_order()
	{
		print_pre_order(root);
	}
};

int main()
{
	BST b;
	b.insert(2);
	b.insert(4);
	b.insert(3);
	b.insert(5);
	b.insert(0);
	b.insert(1);
	b.insert(-1);

	b.print_pre_order();
	cout << endl;
	b.delet(1);
	b.print_pre_order();
}