#include<iostream>
#include <algorithm>
using namespace std;

template <class T> class Tree;
template <class T>
class TreeNode{
	friend class Tree<T>;

public:
	TreeNode(const T &d)
		: data(d), leftptr(0), rightptr(0){}
private:
	T data;
	TreeNode<T> *leftptr;
	TreeNode<T> *rightptr;


};

template <class T>
class Tree{
public:
	Tree();  //constructor
	void insertNode(const T &value);
	void preOrderTraversal() const;
	void inOrderTraversal() const;
	void postOrderTraversal() const;
	bool find(T value);
	int get_height();
	void m_delete(T data);
	~Tree();//destructor

private:
	TreeNode<T> *rootPtr;
	//utility function-helpers
	void insertNodeHelper(TreeNode <T> **ptr, const T &value);
	void preOrderHelper(TreeNode< T> *ptr) const;
	void inOrderHelper(TreeNode< T> *ptr) const;
	void postOrderHelper(TreeNode< T> *ptr) const;
	bool findHelper(TreeNode< T> *ptr, T value);
	int get_heightHelper(TreeNode< T> *root);
	//this function is written for remove
	TreeNode<T>* findMin(TreeNode<T> *ptr);
	TreeNode<T>* deleteHelper(TreeNode<T> *root, T data);
	//this for destructor
	void removeSubTree(TreeNode<T> *root);

};

template <class T>
Tree<T>::Tree(){
	rootPtr = NULL;
}

template <class T>
void Tree<T>::insertNode(const T &value){
	cout << value << " was inserted" << endl;
	insertNodeHelper(&rootPtr, value);
}

template <class T>
void Tree<T>::insertNodeHelper(TreeNode <T> **ptr, const T &value){
	if (*ptr == NULL){
		*ptr = new TreeNode<T>(value);
	}

	else {
		if (value< (*ptr)->data){
			insertNodeHelper(&((*ptr)->leftptr), value);
		}
		else{
			if (value>(*ptr)->data){
				insertNodeHelper(&((*ptr)->rightptr), value);
			}
		}
	}

}

template <class T>
void Tree<T>::preOrderTraversal() const{
	cout << "Pre order traversal :";
	preOrderHelper(rootPtr);

}

template <class T>
void Tree<T>::preOrderHelper(TreeNode<T>* ptr) const {
	{
		if (ptr != NULL){
			cout << ptr->data << " ";
			preOrderHelper(ptr->leftptr);
			preOrderHelper(ptr->rightptr);
		}
	}
}


template <class T>
void Tree<T>::inOrderTraversal() const {
	cout << "In order traversal  :";
	inOrderHelper(rootPtr);

}

template <class T>
void Tree<T>::inOrderHelper(TreeNode< T>* ptr)const {
	{
		if (ptr != NULL)
		{

			inOrderHelper(ptr->leftptr);
			cout << ptr->data << " ";
			inOrderHelper(ptr->rightptr);
		}
	}
}


template <class T>
void Tree<T>::postOrderTraversal() const{
	cout << "Post order traversal:";
	postOrderHelper(rootPtr);

}

template <class T>
void Tree<T>::postOrderHelper(TreeNode< T>* ptr)const {
	{
		if (ptr != NULL)
		{

			postOrderHelper(ptr->leftptr);
			postOrderHelper(ptr->rightptr);
			cout << ptr->data << " ";
		}
	}
}

template <class T>
int Tree<T>::get_height(){
	int height = get_heightHelper(rootPtr);
	cout << "The height is: ";
	return height;
}


template <class T>
int Tree<T>::get_heightHelper(TreeNode<T> *ptr){
	if (ptr == NULL)
	{
		return 0;
	}
	return max(get_heightHelper(ptr->leftptr), get_heightHelper(ptr->rightptr)) + 1;
}

template <class T>
bool Tree<T>::find(T value){
	return findHelper(rootPtr, value);

}

template <class T>
bool Tree<T>::findHelper(TreeNode<T> *ptr, T value){
	if (ptr == NULL)
	{
		return false;
	}

	else if (value == ptr->data)
	{
		return true;
	}

	else if (value<ptr->data)
	{
		findHelper(ptr->leftptr, value);
	}

	else if (value>  ptr->data)
	{
		findHelper(ptr->rightptr, value);
	}
}

template <class T>
TreeNode<T> * Tree<T>::findMin(TreeNode<T> *root){
	while (root->leftptr != NULL){
		root = root->leftptr;
	}
	return root;
}

template <class T>
void Tree<T>::m_delete(T data){
	deleteHelper(rootPtr, data);
	cout << data << " was deleted" << endl;
}

template <class T>
TreeNode<T> * Tree<T>::deleteHelper(TreeNode<T> *root, T data){
	//First we need to find the node
	if (root == NULL) return root;
	else if (data<root->data){ root->leftptr = deleteHelper(root->leftptr, data); }
	else if (data>root->data){ root->rightptr = deleteHelper(root->rightptr, data); }
	//so here we have found it, and we discuss cases
	else {
		// Case 1:: NO CHILD
		if (root->leftptr == NULL && root->rightptr == NULL) {
			delete root;
			root = NULL;
		}

		//Case 2:: ONE CHILD
		else if (root->leftptr == NULL) {
			TreeNode<T> *temp = root;
			root = root->rightptr;
			delete temp;
		}
		else if (root->rightptr == NULL) {
			TreeNode<T> *temp = root;
			root = root->leftptr;
			delete temp;
		}

		// case 3: 2 CHILDREN
		else {
			TreeNode<T> *temp = findMin(root->rightptr);
			root->data = temp->data;
			root->rightptr = deleteHelper(root->rightptr, temp->data);
		}
	}
	return root;
}


template <class T>
Tree<T>::~Tree(){
	cout << "Destructor is called" << endl;
	removeSubTree(rootPtr);
}

template <class T>
void Tree<T>::removeSubTree(TreeNode<T> *root){
	if (root != NULL){

		removeSubTree(root->leftptr);
		removeSubTree(root->rightptr);
		//I just wrote this for checking weather dealocation is done properly
		//cout << root->data << " is deleting" << endl;
		delete  root;
	}


}


//I just wrote this function for readable code, when I return bool in find function, just pass here to be written properly
//weather value was found or not
template <class T>
void writeFind(bool find, T value){
	if (find == 1){
		cout << value << " was found in tree" << endl;
	}
	else cout << value << " isnt in tree" << endl;

}

int main(){
	{
		//After insertion my tree must look like this
		//          60
		//         /  \
			    //       20   70
		//      / \ 
		//    10  40 
		//       / \
			    //      30 50


		Tree<int> t;
		t.insertNode(60);
		t.insertNode(20);
		t.insertNode(70);
		t.insertNode(10);
		t.insertNode(40);
		t.insertNode(30);
		t.insertNode(50);
		t.preOrderTraversal();
		cout << endl;
		t.inOrderTraversal();
		cout << endl;
		t.postOrderTraversal();
		cout << endl;
		cout << t.get_height();
		cout << endl;

		bool f1 = t.find(10);
		writeFind(f1, 10);
		bool f2 = t.find(100);
		writeFind(f2, 100);
		t.m_delete(10);
		t.inOrderTraversal();
		cout << endl;

		t.m_delete(20);
		t.inOrderTraversal();
		cout << endl;
		t.m_delete(60);
		t.inOrderTraversal();
		cout << endl;

	}
	
	system("pause");

}
