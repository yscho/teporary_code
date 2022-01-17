//#incldue <test.cpp>
#include <iostream>
#define MAXUSER 1000;
using namespace std;

//User class define===========



class cUser_node {
private:
	int uID;
	cUser_node* followed;
	cPost_node* post_head;
public:
	cUser_node(); // for make UserArr [need default generator]
	cUser_node(int n); //생성자 uID 항상 입력 해야 함.
	~cUser_node();
	
	void setUID(int id);
	void set_follow(cUser_node* other_User);
};
cUser_node::cUser_node()
{
	this->uID = NULL;
	this->followed = NULL;
	this->post_head = NULL;
}
cUser_node::cUser_node(int n)
{
	this->uID = n;
	this->followed = NULL;
	this->post_head = NULL;
}

cUser_node::~cUser_node()
{

}
void cUser_node::setUID(int id)
{
	this->uID = id;
}

void cUser_node::set_follow(cUser_node* other_User)
{
	this->followed = other_User;
}
//foloow 하고 있는 User의 포스트 는 This->followed->post_head;
//User class define ENDe===========

//Post class define===========
class cPost_node {
private:
	int uID;
	int pID;
	int like;
	cPost_node* next_node;
public:
	cPost_node(int uid, int pid, cPost_node* pre_node);
	void set_likebt();
};

cPost_node::cPost_node(int uid, int pid, cPost_node* pre_node)
{
	pre_node->next_node = this;
	this->uID;
	this->pID;
	this->like = 0;
}

void cPost_node::set_likebt()
{
	this->like += 1;
}
//Post class define END===========

static cUser_node* UserArr;

static void printhello(int number) //test function.
{
	for (int index = 1; index < number; index++)
	{
		UserArr[index].setUID(index);
	}
}

//first initial User 
static void init(int input_numofuser)
{
	//static cUser_node* UserArr = new cUser_node[input_numofuser];
	UserArr = new cUser_node[input_numofuser];
	for (int index = 1; index < input_numofuser; index++)
	{
		UserArr[index].setUID(index); // Uid initialize;

}
