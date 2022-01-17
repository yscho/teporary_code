
//#include "main.cpp"
#include <iostream>
#include <vector>
#include <algorithm>

#define MAXUSER 1000;
using namespace std;



////=================Post class define===========
class cPost_node {
private:
	int uID;
	int pID;
	int like;
	int timestamp;
	cPost_node* next_node;
public:
	
	cPost_node(int uid, int pid, int t_stamp, cPost_node* pre_node);
	void set_likebt();
	int get_likebt();

	void set_timestamp(int t_stamp);
	int get_timestamp();

	void set_next_node(cPost_node* next_P_node);
	cPost_node* get_next_node();
	
	int get_pid();
	cPost_node* get_this();
};

cPost_node::cPost_node(int uid, int pid, int t_stamp,  cPost_node* pre_node)
{
	pre_node->next_node = this;
	this->uID = uid;
	this->pID = pid;
	this->like = 0;
	this->timestamp = t_stamp;
	this->next_node = NULL;
}
void cPost_node::set_likebt(){this->like += 1; }
void cPost_node::set_timestamp(int t_stamp){this->timestamp = t_stamp; }
int cPost_node::get_timestamp() {	return this->timestamp;}
void cPost_node::set_next_node(cPost_node* next_P_node) { this->next_node = next_P_node; }
cPost_node* cPost_node::get_next_node() { return this->next_node; }
int cPost_node::get_likebt()
{
	return this->like;
}
int cPost_node::get_pid()
{
	return this->pID;
}
cPost_node* cPost_node::get_this()
{
	return this;
}


//Post class define END===========

//########################User class define===========
class cUser_node {
private:
	int uID;
	cUser_node* followed;
	cPost_node* post_head;
public:
	cUser_node(); // for make UserArr [need default generator]
	cUser_node(int n); //생성자 uID 항상 입력 해야 함.
	~cUser_node();

	void		setUID(int id);
	int			getUID();
	void		set_follow(cUser_node* other_User);
	cUser_node* get_follow();
	void		set_post_head(cPost_node* p_cPostnode);
	cPost_node* get_post_head();
	cUser_node* get_this();
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

int cUser_node::getUID()
{
	return this->uID;
}

void cUser_node::set_follow(cUser_node* other_User)
{
	this->followed = other_User;
}

cUser_node* cUser_node::get_follow()
{
	return this->followed;
}

void cUser_node::set_post_head(cPost_node* p_cPostnode) {
	this->post_head = p_cPostnode;
}

cPost_node* cUser_node::get_post_head() {
	return this->get_post_head();
}

cUser_node* cUser_node::get_this()
{
	return this;
}

//foloow 하고 있는 User의 포스트 는 This->followed->post_head;
//User class define ENDe===========


//global Value define 
static cUser_node* UserArr; //모든 User를 가리킬 수 있는 Arr
static std::vector<cPost_node*> vPID; // 모든 post를 가리킬 수 있는 자료형 vector.
static int iNumofUser = 0;


//=========END ===========global Value define 

static void printhello(int number) //test function.
{
	for (int index = 1; index < number; index++)
	{
		UserArr[index].setUID(index);
	}
}

//first initial User 

cUser_node* find_user_byuid(int uid)
{
	for (int index = 1; index < iNumofUser; index++)
	{
		if (UserArr[index].getUID() == uid)
		{
			return UserArr[index].get_this();
		}
		else
		{
			return NULL;
		}
	}
}

cPost_node* find_post_bypid(int pid)
{
	for (vector<cPost_node*>::iterator iter = vPID.begin(); iter != vPID.end(); iter++)
	{
		if ((*iter)->get_pid() == pid)
			return (*iter)->get_this();
		else
			return NULL;
	}//= find(vPID.begin(),vPID.end(),vPID->)
}

void init(int input_numofuser)
{
	cin.tie(NULL);

	iNumofUser = input_numofuser;
	//static cUser_node* UserArr = new cUser_node[input_numofuser];
	UserArr = new cUser_node[input_numofuser];
	for (int index = 1; index < input_numofuser; index++)
	{
		UserArr[index].setUID(index); // Uid initialize;

	}
}

void follow(int uId1, int uId2, int timestamp) {
	
	cUser_node* temp_cUser2;
	cUser_node* temp_cUser1;

	temp_cUser1 = find_user_byuid(uId1);
	temp_cUser2 = find_user_byuid(uId2);
	temp_cUser1->set_follow(temp_cUser2);

}

void makePost(int uId, int pId, int timestamp) {
	//UID가 존재하는지 검사는 생량
	cUser_node* temp_User_node = find_user_byuid(uId);
	cPost_node* temp_Users_Post_node;
	//UID user 의 
	if (temp_User_node->get_post_head() == NULL) // 해당 유저의 포스트가 없으면 추가.
	{
		temp_User_node->set_post_head(new cPost_node(uId, pId, timestamp, NULL));
		vPID.push_back(temp_User_node->get_post_head());//Post vector에 추가.
	}
	else // 포스트가 이미 있다면, 끝에 추가
	{
		temp_Users_Post_node = temp_User_node->get_post_head();
		
		while (temp_Users_Post_node->get_next_node() != NULL) {
			temp_Users_Post_node = temp_Users_Post_node->get_next_node();
		}

		temp_Users_Post_node->set_next_node( new cPost_node(uId, pId, timestamp, temp_Users_Post_node->get_this() ) );
		vPID.push_back(temp_User_node->get_post_head());//Post vector에 추가.
	}
}

void like(int pId, int timestamp) {
	cPost_node* temp_Postnode = find_post_bypid(pId);
	temp_Postnode->set_timestamp(timestamp);
}

static bool compare(cPost_node* a, cPost_node* b)
{
	if (a->get_likebt() > b->get_likebt()) return true;
	else if (a->get_likebt() < b->get_likebt()) return false;
	else if (a->get_likebt() == b->get_likebt())
	{
		if (a->get_timestamp() > b->get_timestamp()) return true;
	}
}

void getFeed(int uId, int timestamp, int pIdList[]) {
	//UID 포스트 수집
	cPost_node* uids_post_node = find_user_byuid(uId)->get_post_head();
	cPost_node* uids_followed_post_head = find_user_byuid(uId)->get_follow()->get_post_head();
	std::vector<cPost_node*> vPost_group;
	std::vector<cPost_node*> post_g1;
	std::vector<cPost_node*> post_g2;
	std::vector<cPost_node*> post_merge;
	int cnt = 0;
	if (uids_post_node != NULL) {
		while (1) {
			vPost_group.push_back(uids_post_node->get_this());
			if (uids_post_node->get_next_node() == NULL) break;
			else uids_post_node = uids_post_node->get_next_node();
		}
	}//UID 가 follow 한 post 수집  // follow 한 User 많아지면, 안통함.
	if (uids_followed_post_head != NULL) {
		while (1) {
			vPost_group.push_back(uids_followed_post_head->get_this());
			if (uids_followed_post_head->get_next_node() == NULL) break;
			else uids_followed_post_head = uids_followed_post_head->get_next_node();
		}
	}
	//1그룹
	//timestamp - written t/s 가 1000 이하인 것 수집
	for (vector<cPost_node*>::iterator iter = vPost_group.begin(); iter == vPost_group.end(); iter++)
	{
		if ((timestamp - (*iter)->get_timestamp()) <= 1000)
		{
			post_g1.push_back(*iter);
		}
		else
		{
			post_g2.push_back(*iter);
		}
	}
	// 1그룹내, like 순으로 정렬
	// like 순이 같으면, ts가 큰 것이 우선순위 높음.
	sort(post_g1.begin(), post_g1.end(), compare);
	//2그룹
	//2 tsr가 큰 순서로 정렬
	sort(post_g2.begin(), post_g2.end(), compare);

	//1그룹 + 2그룹
	//상위 10개 pid return.
	if(!post_g1.empty())
	{
		for (vector<cPost_node*>::iterator iter = post_g1.begin(); iter == post_g1.end(); iter++)
		{
			pIdList[cnt] = (*iter)->get_pid();
			cnt++;
		}
	}

	if (!post_g2.empty())
	{
		for (vector<cPost_node*>::iterator iter = post_g2.begin(); iter == post_g2.end(); iter++)
		{
			pIdList[cnt] = (*iter)->get_pid();
			cnt++;
		}
	}
}
