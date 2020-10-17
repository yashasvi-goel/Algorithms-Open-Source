#include<bits/stdc++.h>

using namespace std;

unordered_map<char,list<string>> expressions;//Key is state--Value is list of expressions as strings
unordered_set<char> states;//all states/non_terminals
int num_states=0,num_expressions=0;
char new_state='A';
//===========================

void print(){
	for(auto node:expressions){
                cout<<node.first<<"->";

                for(auto point:node.second){
                        cout<<point<<"->";
                }
                cout<<"end"<<endl;
        }
	cout<<"======="<<endl;
}

unordered_map<char,char> changed;

list<string> clean(list<string> &actual, char g){//returns a linkedList with E'
        char ne=new_state;
        list<string> nl;
        cout<<"Changed--\t"<<g<<"'--"<<ne<<endl;
        changed[g]=ne;
        states.insert(ne);
        for(auto j=actual.begin();j!=actual.end();j++){//iterate the list
                if(!((*j)[0]-g)){//has LR
			nl.push_back((*j).substr(1)+ne);
			*j="";

                }
                else{
                        *j=*j+ne;

                }
        }
        nl.push_back("epsl");//add epsilon

        while(states.count(new_state))new_state++;

        return nl;

        
}

void findLL(){
        for(auto i:expressions){//iterate the map, ie. for each determinant
                for(auto j:i.second){//iterate th linked list
                        if((j[0]-i.first)==0){//LR detected
                               expressions[changed[i.first]]=clean(i.second,i.first);
//			       cout<<i.first<<endl;
			       expressions[i.first]=i.second;
/*			       for(auto l=i.second.begin();l!=i.second.end();l++)
			       {
				       cout<<*l<<":";
			       }*/
                               break;
                        }
                }
        }
}

//=============================
void func(){

	string line;
	ifstream input("input.txt");

	//File Reading for Input-------------------------------------
	try{
	if(input.is_open()){
		while(getline(input,line)){
			//cout<<line<<endl;
			char key=line[0];
			string val=line.substr(3);

			expressions[key].push_back(val);
			num_expressions++;
		}
		input.close();
	}

	else{
		cout<<"Some problem occured in opening the file!!"<<endl;
	}
	}
	catch(exception e){
	cout<<"Input Error"<<endl;
	}

	//Storing all the States in a vector--------------------------
	
	for(auto node:expressions){

		states.insert(node.first);
		if(states.count(new_state))new_state++;
	}
	num_states=states.size();
}

int get_num_expressions(){
	int c=0;

	for(auto node:expressions){
		for(auto point:node.second)c++;
	}

	return c; 
}

void update(){
	for(auto node:expressions){
		node.second.remove("");
		expressions[node.first]=node.second;
	}

}


//--------------------------------------------------------------------------------

unordered_map<char,vector<string>> first,new_follow;
unordered_map<char,set<string>> follow;
vector<string>val;


void first_helper(char key){
	bool flag=0;
	char x;
	int p=0;
	for(auto point:expressions[key]){
		p=0;
		label:
		x=point[p++];
		
		flag=0;
		if(states.count(x)){
			first_helper(x);
		}else{
			
			if(point=="epsl"){
				flag=1;
				goto bahar;
			}
			val.push_back(point.substr(0,1));
		}
		bahar:

		if(flag){
			if(p>=point.size()){val.push_back("epsl");continue;}
			goto label;
		}
	}
}



void firsts(){

	for(auto node:expressions){
		val.clear();
		first_helper(node.first);
		first[node.first]=val;
	}

}

bool follow_helper(char key,set<string> &vec){
	bool flag=0;
	for(auto s:first[key]){
		if(s!="epsl"){
			vec.insert(s);
		}
		else{
			flag=1;
		}
	}
	return flag;
}

void follows(char key){

	if(follow.count(key))
		return ;

	set<string> vec;

	for(auto node:expressions){

		for(auto point:node.second){
			if(point!="epsl"){
				for(int i=0;i<point.size();i++){
					if(point[i]==key){
						again:
						if(i+1<point.size()){
							if(states.count(point[i+1])){
								if(follow_helper(point[i+1],vec)){
									i++;
									goto again;
								}
							}else{
								vec.insert(point.substr(i+1,1));
							}
						}
						else{
							if(key!=node.first){
								follows(node.first);
								for(auto elememt:follow[node.first])
									vec.insert(elememt);
							}
						}
					}
				}
			}
		}

	}

	for(auto elememt:vec){
		follow[key].insert(elememt);
	}
}

//--------------------------------------------------------------------------------

map<pair<char, char>, string> predict_table(unordered_map<char,
                                            list<string>> &expressions, unordered_map<char,
                                            vector<string>> &first, unordered_map<char, vector<string>> &follow ){
	

	map<pair<char, char>, string> table;

	for(auto i: expressions){
	for(auto j : i.second){
		int eps_exist = 0;
		if ( !isupper(j[0]) && j[0]!='#'){
			char sss;
		    sss = j[0];
			table[make_pair(i.first, sss)] = j;
		}
		else if(j[0]=='#'){
			eps_exist = 1;
			for(auto k: follow[i.first]){
			table[make_pair(i.first, k[0])] = "#";
			}
		}
		else{
			eps_exist = 1;
		
			for(auto l: first[i.first]){
				if(l[0] == '#'){
					if(eps_exist==0){
					for(auto kk: follow[i.first]){
                        			table[make_pair(i.first, kk[0])] = j;
                        		}
				}
				}
				else{
				table[make_pair(i.first, l[0])] = j;
			}
			}

		}
	}
	}

	cout<<"Parser Table"<<endl<<endl;

	 for(auto node: table){
	 	cout << node.first.first << ","<< node.first.second<<":" << node.second << endl;
	
	 }
return table;
}


//--------------------------------------------------------------------------------

map<pair<char, char>, string> parsed_table;

int main(){

	//Initializing all variables---------------------------------
	num_expressions=0;
	num_states=0;
	expressions.clear();

	//Calling function to store in DataStructure---------------------
	func();


	//Iterating through the expressions------------------------------
	cout<<"With Left Recursion--\n\n";
	for(auto node:expressions){
		cout<<node.first<<"->";

		for(auto point:node.second){
			cout<<point<<"->";
		}
		cout<<"end"<<endl;
	}
	cout<<"\n\n";
	findLL();//&expressions);

	cout<<"\n\n\nWithout Left Recursion--\n\n";
	print();

	//------------------Update-------------------------------

	update();

	//Details Printing---------------------------------------------

	cout<<"Number of States-- "<<states.size()<<endl<<"States--\n";
	for(auto c:states)cout<<c<<endl;
	cout<<"Number of expressions-- "<<get_num_expressions()<<endl;
	print();
	

	cout<<"\n\nFirsts\n\n\n";

	firsts();
	// follow();

	for(auto node:first){
		cout<<node.first<<"==   ";
		for(auto i:node.second){
			cout<<i<<" > ";
		}
		cout<<"end"<<endl;
	}

	cout<<endl<<endl;

	cout<<"Follow\n\n\n";

	follows('E');
	follow['E'].insert("$");
	for(auto node:expressions){
		if(node.first!='E'){
			follows(node.first);
		}
	}

	for(auto node:follow){
		cout<<node.first<<"==   ";
		for(auto i:node.second){
			cout<<i<<" > ";
		}
		cout<<"end"<<endl;
	}

	cout<<"\n\n\n\n";

	//----------------------------------------------------

	for(auto node:follow){
		for(auto i:node.second){
			new_follow[node.first].push_back(i);
		}
	}

	for(auto node=first.begin();node!=first.end();node++){

		for(auto i=node->second.begin();i!=node->second.end();i++){
			if(*i=="epsl")
				*i="#";
			if(*i=="id")
				*i="i";
			if(*i=="num")
				*i="n";
		}
		
		//first[node.first]=node.second;

	}

	for(auto node=expressions.begin();node!=expressions.end();node++){

		for(auto i=node->second.begin();i!=node->second.end();i++){

			if(*i=="epsl")
				*i="#";
			if(*i=="id")
                                *i="i";
                        if(*i=="num")
                                *i="n";

		}

		//expressions[node.first]=node.second;
	
	}

	/*cout<<"----\n";
	for(auto node:first){
                cout<<node.first<<"==   ";
                for(auto i:node.second){
                        cout<<i<<" > ";
                }
                cout<<"end"<<endl;
        }

	for(auto node:follow){
                cout<<node.first<<"==   ";
                for(auto i:node.second){
                        cout<<i<<" > ";
                }
                cout<<"end"<<endl;
        }

	print();*/


	cout<<"-----\n";

	map<pair<char, char>, string> m=predict_table(expressions,first,new_follow);

	//----------------------------------------------------

	/*for(auto node:m){
		cout<<node.first.first<<node.first.second<<endl;

		for(auto s:node.second){
			cout<<s;
		}
		cout<<"\n====\n\n";
	}*/

	cout<<"Input Reading Starts"<<endl<<endl;

	ifstream infile;
	infile.open("lexout.txt");
	string s;
	infile >> s;
	cout<<"Input:"<<s<<endl;
	//cin>>s;
	s.push_back('$');
	deque<char> q;
	q.push_front('$');
	q.push_front('E');
	int i=0,f=0;
	string s1="",s2;
	while(1){
		while(1){
			if(q.front()==s[i]){
                                i++;
                                cout<<"Yay"<<endl; //When each token matches.
                                break;
                        }
			if(m.find({q.front(),s[i]})!=m.end()){
				s1=m[{q.front(),s[i]}];
				//cout<<s1<<endl;
				if(s1=="#")
					break;
				q.pop_front();
				for(int j=s1.length()-1;j>=0;j--)
					q.push_front((s1[j]));
			}
			else{
			//cout<<"Not Matched"<<endl;
			f=1;
			break;
			}
			/*if(q.front()==s[i]){
				i++;
				cout<<"Yay"<<endl; //When each token matches.
				break;
			}*/
			if(q.front()=='$'&&s[i]=='$'){
                        cout<<"Matched"<<endl;
                        break;
                	}
			//cout<<q.front()<<" "<<s[i]<<endl;

			//cout<<"HAha";
		}
		q.pop_front();
		if(q.front()=='$'&&s[i]=='$'){
			cout<<"Matched"<<endl;
			break;
		}
		else if(q.front()=='$'&&s[i]!='$'){
			//cout<<"Not Matched"<<endl;
			f=1;
		}
		if(f==1){
			cout<<"Not Matched"<<endl;
			break;
		}

	}

	return 0;
}
