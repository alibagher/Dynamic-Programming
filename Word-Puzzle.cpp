#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

struct Node
{
	pair<int, int> p;
	Node* next;
};


struct linkedList{
	Node * head;
public:
	linkedList(){
		head = NULL;
	}
	void addToFront(pair<int,int> newp){
		Node * newNode = new Node;
		newNode->next = NULL;
		newNode->p = newp;
		newNode->next = head;
		head = newNode;
	}
	
	void printL(){
	    Node* head = this->head;
        //int i = 1;
        while(head){
            cout << head->p.first << " " << head->p.second << endl;
            head = head->next;
            //i++;
        }
	}

	~linkedList(){
     		head = head->next;
     		delete head;
	}
};


int main(int argc, char const *argv[])
{

	string word;
	cin >> word;

	int wordLen = word.length();

	string firstLine;
	cin >> firstLine;

	int len = firstLine.length();
	
	//cout << "length of the first word " << len << endl;

	string M[len];

	M[0] = firstLine;

	for (int i = 1; i < len; ++i)
	{
		cin >> M[i];
	}
	
	//holds te table for DP
	bool D[len+1][len+1][wordLen+1];

    for (int i = 0; i <= len; ++i){
		for (int j = 0; j <= len; ++j){
		    for (int k = 0; k <= wordLen; ++k){
		        D[i][j][k] = 0;  
		    }  
		}
    }

	for (int i = 1; i <= len; ++i){
		for (int j = 1; j <= len; ++j)
		{
			D[i][j][0] = 1;
		}
	}


    // check if the first char is the same
//	if (M[0][0] == word[0])
//	{
//		D[0][0][0] = 1;
//	}


/*
 //testing the D matrix
    cout << "starting D" << endl;
    for (int i = 0; i <= len; ++i){
		for (int j = 0; j <= len; ++j){
		    for (int k = 0; k <= wordLen; ++k){
		        cout << D[i][j][k];
		    }  
		    //cout << endl;
		}
        cout << endl;
    }
    cout << "end of D" <<endl;
  */

	for (int i = 1; i <= len; ++i){
		for (int j = 1; j <= len; ++j){
			for (int k = 1; k <= wordLen; ++k){
				if (i == 1 && j == 1 && k == 1){
					D[i][j][k] = (M[i-1][j-1] == word[k-1]);
				}
				else{
					D[i][j][k] = ((D[i-1][j][k-1] || D[i][j-1][k-1]) && (M[i-1][j-1] == word[k-1]));
				}
			}
		}
	}


/*
    //testing the D matrix
    cout << "starting D" << endl;
    for (int i = 0; i <= len; ++i){
		for (int j = 0; j <= len; ++j){
		       for (int k = 0; k <= wordLen; ++k){
		            cout << D[i][j][k];  
		       }
		}
        cout << endl;
    }
    cout << "end of D" <<endl;
  */
  
    // finds a location satisfying all requirememnts
	vector<pair<int,int>> v;
	for (int i = 1; i <= len; ++i){
		for (int j = 1; j <= len; ++j){
			if (D[i][j][wordLen] ){//&& i+j+1 == wordLen){
				v.push_back(make_pair(i,j));
				//cout << "found a i and j: " << i<<j<< endl;
			}
		}
	}

	int vLen = v.size();
	//cout << "length of vector " << vLen << endl;
	if (vLen == 0){
		cout << "0" << endl;
		return 0;
	}
    


    
    
    
    for (int m = 0; m < vLen; ++m)
	{

		//int i = v[m].first;
		//int j = v[m].second;
		
		int lasti = v[m].first;
	    int lastj = v[m].second;
	
	    int i = lasti;
	    int j = lastj;


        //cout << "printing the i and j of current loop" << endl;
        //cout << i << "," << j << endl;

		linkedList L;
        //goes through the D matrix and finds the word. 
	    for (int k = wordLen; k >= 1; --k){
	        // if one of the var went over the param, return
	        //if(i < 0 || j < 0) break;
		    L.addToFront(make_pair(i-1,j-1));
		        
		    //if(k = 1){
		    
		    if (D[i-1][j][k-1] && (i > 1)){
	  		    i = i-1;
		    }else if (D[i][j-1][k-1] && (j > 1)){
	  	    	j = j-1;
	   	    }else{
	   	        break;
	   	    }
	   }
		
		//cout << "printing the linkedlist" << endl;
        //L.printL();
        
        Node* head = L.head;
        i = head->p.first;
        j = head->p.second;
        int w = 0;
        bool found = true;
        //int i = 1;
        while(head){
            //cout << head->p.first << " " << head->p.second << endl;
            if(M[head->p.first][head->p.second] != word[w]){
                found = false;
            }
            //cout << "M value: " <<M[head->p.first][head->p.second]<< "word[] " << word[w] <<endl;

            w++;
            head = head->next;
        }
		
		if (found){
		    cout << i+1 << " " << j+1 << " " << lasti << " " << lastj << endl;
		    return 0;
		}
	}

	cout << "0" << endl;
    
    

	return 0;
}
