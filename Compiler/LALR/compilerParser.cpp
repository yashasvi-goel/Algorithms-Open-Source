#include<bits/stdc++.h>
using namespace std;

void find_first(vector< pair<char, string> > gram,	map< char, set<char> > &firsts,char non_term) {
	for(auto iter = gram.begin(); iter != gram.end(); ++iter) {
		if(iter->first != non_term) {	continue;}
		string rhs = iter->second;
		for(auto ch = rhs.begin(); ch != rhs.end(); ++ch) {
			if(!isupper(*ch)) {
				firsts[non_term].insert(*ch);
				break;
			}
			else {

				if(firsts[*ch].empty()) {
					find_first(gram, firsts, *ch);
				}
				if(firsts[*ch].find('e') == firsts[*ch].end()) {
					firsts[non_term].insert(firsts[*ch].begin(), firsts[*ch].end());
					break;
				}

				set<char> firsts_copy(firsts[*ch].begin(), firsts[*ch].end());
				if(ch + 1 != rhs.end()) {
					firsts_copy.erase('e');
				}
				firsts[non_term].insert(firsts_copy.begin(), firsts_copy.end());
			}
		}

	}
}
void find_follow(vector< pair<char, string> > gram,map< char, set<char> > &follows,	map< char, set<char> > firsts,char non_term) {
	for(auto iter = gram.begin(); iter != gram.end(); ++iter) {
		bool finished = true;
		auto ch = iter->second.begin();
		for(;ch != iter->second.end() ; ++ch) {
			if(*ch == non_term) {
				finished = false;
				break;
			}
		}
		++ch;
		for(;ch != iter->second.end() && !finished; ++ch) {
			if(!isupper(*ch)) {
				follows[non_term].insert(*ch);
				finished = true;
				break;
			}
			set<char> firsts_copy(firsts[*ch]);
			if(firsts_copy.find('e') == firsts_copy.end()) {
				follows[non_term].insert(firsts_copy.begin(), firsts_copy.end());
				finished = true;
				break;
			}
			firsts_copy.erase('e');
			follows[non_term].insert(firsts_copy.begin(), firsts_copy.end());
		}
		if(ch == iter->second.end() && !finished) {
			if(follows[iter->first].empty()) {
				find_follow(gram, follows, firsts, iter->first);
			}
			follows[non_term].insert(follows[iter->first].begin(), follows[iter->first].end());
		}
	}

}



int main(int argc, char const *argv[])
{
	
	if(argc != 3) {
		cout<<"Arguments should be <grammar file> <input string>\n";
		return 1;
	}
	fstream grammar_file;
	grammar_file.open(argv[1], ios::in);
	if(grammar_file.fail()) {
		cout<<"Error in opening grammar file\n";
		return 2;
	}
	int idx = 0;
	cout<<"Grammar parsed from grammar file: \n";
	map<int,pair<char,string> > mp;
	vector< pair<char, string> > gram;
	int count = 0;
	while(!grammar_file.eof()) {
		char buffer[20];
		grammar_file.getline(buffer, 19);
		char lhs = buffer[0];
		string rhs = buffer+3;
		gram.push_back({lhs,rhs});
		cout<<count++<<".  "<<gram.back().first<<" -> "<<gram.back().second<<"\n";
		mp[idx++]={gram.back().first,gram.back().second};
	}
	cout<<"\n";
	ifstream string_file;
string_file.open(argv[2],ios::in);

string input_string="";
string ans;
while(string_file)
{
								//char buffer[200];
								//string_file.getline(buffer,200);
								getline(string_file,ans);
								//input_string=buffer;
								//cout<<input_string<<endl;
								input_string+=ans;
}

cout<<"Input string is:"<<'\n';
cout<<input_string<<'\n';

//=========================================================================================================================

	set<char> non_terms;
	for(auto i = gram.begin(); i != gram.end(); ++i) {
		non_terms.insert(i->first);
	}
	cout<<"The non terminals in the grammar are: ";
	for(auto i = non_terms.begin(); i != non_terms.end(); ++i) {
		cout<<*i<<" ";
	}
	cout<<"\n";
	set<char> terms;
	for(auto i = gram.begin(); i != gram.end(); ++i) {
		for(auto ch = i->second.begin(); ch != i->second.end(); ++ch) {
			if(!isupper(*ch)) {
				terms.insert(*ch);
			}
		}
	}
	terms.erase('e');
	terms.insert('$');
	cout<<"The terminals belonging in this grammar are: ";
	for(char ch: terms)
	{
		cout<<ch<<" ";
	}
	cout<<"\n\n";
	char start_sym = gram.begin()->first;
	map< char, set<char> > firsts;
	for(auto non_term = non_terms.begin(); non_term != non_terms.end(); ++non_term) {
		if(firsts[*non_term].empty()){
			find_first(gram, firsts, *non_term);
		}
	}
	cout<<"List of Firsts : \n";
	for(auto iter = firsts.begin(); iter != firsts.end(); ++iter) {
		cout<<iter->first<<" : ";
		for(auto firsts_it = iter->second.begin(); firsts_it != iter->second.end(); ++firsts_it) {
			cout<<*firsts_it<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n";


	map< char, set<char> > follows;
	char start_var = gram.begin()->first;
	follows[start_var].insert('$');
	find_follow(gram, follows, firsts, start_var);
	for(auto iter = non_terms.begin(); iter != non_terms.end(); ++iter) {
		if(follows[*iter].empty()) {
			find_follow(gram, follows, firsts, *iter);
		}
	}

	cout<<"Follows list: \n";
	for(auto iter = follows.begin(); iter != follows.end(); ++iter) {
		cout<<iter->first<<" : ";
		for(auto follows_it = iter->second.begin(); follows_it != iter->second.end(); ++follows_it) {
			cout<<*follows_it<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n";

	int count_non_terminals = non_terms.size();
	int count_terminals = terms.size();
	int parse_table[count_non_terminals][count_terminals];
	for(int i=0;i<count_non_terminals;i++)
	{
		for(int j=0;j<count_terminals;j++)
		{
			parse_table[i][j]=-1;
		}
	}

// =============================================================================================================================================

	for(auto prod = gram.begin(); prod != gram.end(); ++prod) {
		string rhs = prod->second;
		cout<<prod->first<<" "<<rhs<<'\n';
		set<char> next_list;
		bool finished = false;
		for(auto ch = rhs.begin(); ch != rhs.end(); ++ch){
			if(!isupper(*ch)) {
				if(*ch != 'e') {
					next_list.insert(*ch);
					finished = true;
					break;
				}
				continue;
			}
			set<char> firsts_copy(firsts[*ch].begin(), firsts[*ch].end());
			if(firsts_copy.find('e') == firsts_copy.end()) {
				next_list.insert(firsts_copy.begin(), firsts_copy.end());
				finished = true;
				break;
			}
			firsts_copy.erase('e');
			next_list.insert(firsts_copy.begin(), firsts_copy.end());
		}
		//Special case when there is epsilon.
		if(!finished) {
			next_list.insert(follows[prod->first].begin(), follows[prod->first].end());
		}
		//Filling the parse table.
		for(auto ch = next_list.begin(); ch != next_list.end(); ++ch) {
			cout<<*ch<<" ";
			int row = distance(non_terms.begin(), non_terms.find(prod->first));
			int col = distance(terms.begin(), terms.find(*ch));
			int prod_num = distance(gram.begin(), prod);
			if(parse_table[row][col] != -1) {
				cout<<"Collision at ["<<row<<"]["<<col<<"] for production "<<prod_num<<"\n";
				continue;
			}
			parse_table[row][col] = prod_num;
		}
		cout<<'\n';
	}
	cout<<"The parse Table is below\n";
	cout<<"   ";
	for(auto i = terms.begin(); i != terms.end(); ++i) {
		cout<<*i<<" ";
	}
	cout<<"\n";
	for(auto row = non_terms.begin(); row != non_terms.end(); ++row) {
		cout<<*row<<"   ";
		for(int col = 0; col < terms.size(); ++col) {
			int row_num = distance(non_terms.begin(), row);
			if(parse_table[row_num][col] == -1) {
				cout<<" - ";
				continue;
			}
			cout<<mp[parse_table[row_num][col]].first<<"->"<<mp[parse_table[row_num][col]].second<<"  ";
		}
		cout<<"\n";
	}
	cout<<"\n";
//========================================================================================================================


	input_string.push_back('$');
	stack<char> st;
	st.push('$');
	st.push('S');
	for(char ch : input_string)
	{	if(terms.find(ch)==terms.end())
		{cout<<"Input string is invalid"<<'\n';
			return 2;}}
	bool flag = true;
	while(!st.empty() && !input_string.empty()){
		if(input_string[0] == st.top()) {
			st.pop();
			input_string.erase(0, 1);
		}
		else if(!isupper(st.top())) {
			cout<<"Terminal not found\n";
			flag = false;
			break;
		}
		else {
			char stack_top = st.top();
			int row = distance(non_terms.begin(), non_terms.find(stack_top));
			int col = distance(terms.begin(), terms.find(input_string[0]));
			int prod_num = parse_table[row][col];
			if(prod_num == -1) {
				cout<<"Production does not exist, The input string will be rejected \n";
				flag = false;
				break;
			}
			st.pop();
			string rhs = gram[prod_num].second;
			if(rhs[0] == 'e') {
				continue;
			}
			for(auto ch = rhs.rbegin(); ch != rhs.rend(); ++ch) {
				st.push(*ch);
			}
		}
	}
	if(flag) {
		cout<<"Input string is accepted\n";
	}
	else {
		cout<<"Input string is rejected\n";
	}

	return 0;
}




//STEPS TO RUN THE FILE

/* INPUT 


1.Store the grammar(After removing left Recursion) in the file "graminp.txt".

2.After this enter the input string to be parsed (Eg: a+9*y) 
  in the file named lexinp.txt.

3. Then we run the lexer.l in the following way:
   flex lexer.l
   gcc lex.yy.c -ll
   ./a.out lexinp.txt
4. The above step will generate a file named file2.txt which will contain a generic input string 
   (Eg: i+i*i).

5. In the final step we run compilerParser.cpp in the following way,

   g++ compilerParser.cpp
   ./a.out graminp.txt file2.txt

6. And...You are done! The result can be found in the command line.

*/


/* OUTPUT




Grammar parsed from grammar file: 
0.  E -> TA
1.  A -> +TA
2.  A -> e
3.  T -> FD
4.  D -> *FD
5.  D -> e
6.  F -> (E)
7.  F -> i
8.   -> i

Input string is:
n+i*in+i*i
The non terminals in the grammar are:  A D E F T 
The terminals belonging in this grammar are: $ ( ) * + i 

List of Firsts : 
 : i 
A : + e 
D : * e 
E : ( i 
F : ( i 
T : ( i 

Follows list: 
 : 
A : $ ) 
D : $ ) + 
E : $ ) 
F : $ ) * + 
T : $ ) + 

E TA
( i 
A +TA
+ 
A e
$ ) 
T FD
( i 
D *FD
* 
D e
$ ) + 
F (E)
( 
F i
i 
 i
i 

The parse Table is below
   $ ( ) * + i 
    -  -  -  -  - ->i  
A   A->e   - A->e   - A->+TA   - 
D   D->e   - D->e  D->*FD  D->e   - 
E    - E->TA   -  -  - E->TA  
F    - F->(E)   -  -  - F->i  
T    - T->FD   -  -  - T->FD  

Input string is invalid



*/
