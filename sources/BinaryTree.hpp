#include <iostream>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <list>
#include <map>

using namespace std;

namespace ariel {

template <typename T>
class BinaryTree {

private:

struct Node{
  explicit Node(T val)
  : value(val){}

  T value;
  Node *left = nullptr, *right = nullptr;
};


Node * find_n( T & find, Node * node){

        if(node == nullptr) {return nullptr;}
        if(node->value == find) {return node;}

        Node *  l  = find_n(find,node->left);

        if(l!=nullptr) {return l;}

        Node *  r  = find_n(find,node->right);

        return r;
}

	void rec_copy_childs(const Node& from, Node& to){
		if(from.right!=nullptr) {
			to.right = new Node(from.right->value);
			rec_copy_childs(*from.right, *to.right);
		}
		if(from.left!=nullptr) {
			to.left = new Node(from.left->value);
			rec_copy_childs(*from.left, *to.left);
		}
	}

Node * root_tree = nullptr;
map<T,Node *> map_tree;

public:
  BinaryTree()= default;

	//Shallow copy ctor (move ctor)
	BinaryTree(BinaryTree<T> && other) noexcept {
		std::cout << "/* message */" << '\n';
		root_tree = other.root_tree;
		other.root_tree = nullptr;
	}

  //deep copy ctor
  BinaryTree(const BinaryTree<T> & other){
      std::cout << "/* message */" << '\n';
          if(other.root_tree!=nullptr) {
                  root_tree = new Node(other.root_tree->value);
	          rec_copy_childs(*other.root_tree, *root_tree);
          }
  }


  //------Operators-----
   BinaryTree& operator=(BinaryTree other){
       std::cout << "/* message */" << '\n';
       if(this == &other){
           return *this;
       }
       if(root_tree != nullptr){
           delete this->root_tree;
       }
      root_tree = new Node(other.root_tree->value);
	  rec_copy_childs(*other.root_tree, *this->root_tree);
       return *this;

   }

   BinaryTree& operator=(BinaryTree&& other) noexcept{
       std::cout << "/* message */" << '\n';
       *this->root_tree = other.root_tree;
   }

  ~BinaryTree() {};

BinaryTree& add_root(T x);
BinaryTree& add_left(T exsist,T insert_);
BinaryTree& add_right(T exsist,T insert_);

class it
{
private:

  void recu_in(Node* v){
    if(v == nullptr){return ;}
    recu_in(v->left);
    inner.push_back(v);
    recu_in(v->right);
  }
  void recu_pre(Node* v){
    if(v == nullptr){return ;}
    inner.push_back(v);
    recu_pre(v->left);
    recu_pre(v->right);
  }
  void recu_post(Node* v){
    if(v == nullptr){return ;}
    recu_post(v->left);
    recu_post(v->right);
    inner.push_back(v);
  }

public:
  Node * current;
  list<Node*> inner;
  it():current(nullptr){}
  explicit it(Node* temp):current(temp){}
  it(Node* root , char type)
  {
	  if (root == nullptr)
	  {
		  current = nullptr;
		  return;
	  }
	  switch (type)
	  {
		  case 'i':
			  recu_in(root);
			  current = *inner.begin();
			  break;
		  case 'e':
			  recu_pre(root);
			  current = *inner.begin();
			  break;
		  case 't':
			  recu_post(root);
			  current = *inner.begin();
			  break;
	  }
  }

T &operator*() const {
        return current->value;
}

T *operator->() const {
        return &(current->value);
}

it &operator++(){
    if(inner.size()>1){
      inner.erase(inner.begin());
      current = *inner.begin();
    }else{
      current =nullptr;
    }
  return *this;
}

 it operator++(int){
          it temp(*inner.begin());
          ++*this;
        return temp;
}

bool operator==(const it &other) const {
        return current == nullptr;
}

bool operator!=(const it &other) const {
        return !(*this == other);
}

};
it begin(){
  return it(root_tree,'i');

}
it end(){
  return it();
  }
it   begin_preorder(){
  return it(root_tree,'e');
}
it  end_preorder(){
  return it();
}
it   begin_inorder(){
  return it(root_tree,'i');
}
it   end_inorder(){
  return it();
}
it   begin_postorder(){
  return it(root_tree,'t');
}
it end_postorder(){

    return it();
}
friend ostream& operator<<(ostream& os, const BinaryTree<T>& tree){


        for (auto& x: tree.map_tree){
            os << ' ' << x.first;
         }
        return os;
}
};
template <typename T>
BinaryTree<T>& BinaryTree<T>::add_root(T x){
  if(root_tree == nullptr){
    root_tree=new Node(x);
  }else{
    root_tree->value=x;
  }

            return *this;
    }
template <typename T>
BinaryTree<T>& BinaryTree<T>::add_left(T exsist,T insert_){

Node * found = find_n(exsist,root_tree);
  if(found==nullptr){  throw invalid_argument{" not exist"};}
  if(found->left ==nullptr){
    found->left = new Node(insert_);

  }else{
    found->left ->value = insert_;

  }
        return *this;
}
template <typename T>
BinaryTree<T>& BinaryTree<T>::add_right(T exsist,T insert_){
  Node * found = find_n(exsist,root_tree);
    if(found==nullptr){  throw invalid_argument{" not exist"};}
    if(found->right ==nullptr){
      found->right = new Node(insert_);

    }else{
      found->right ->value = insert_;

    }
          return *this;
}


}
