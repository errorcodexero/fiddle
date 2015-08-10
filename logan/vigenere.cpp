/*	Author: Logan Traffas
TODO:
	- Check caps
	- Check punctuation
	- Encoding
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const vector<char> alphabet={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

template <typename T>
ostream& operator<<(ostream& o, vector<T> v){
	o<<"<";
	for(unsigned int i=0; i<v.size(); i++){
		o<<v[i]<<" ";
	}
	o<<">";
	return o;
}

ostream& operator<<(ostream& o, vector<vector<char>> v){
	for(unsigned int i=0; i<v.size(); i++){
		for(unsigned int j=0; j<v[i].size(); j++){
			o<<v[i][j];
		}
		o<<"\n";
	}
	return o;
}

void encode(const string key,const string cipher,const vector<vector<char>> square){
	
}

void decode(const string key,const string cipher,const vector<vector<char>> square){
	string s;
	unsigned int x=0;
	for(unsigned int i=0; i<cipher.size(); i++){
		if(cipher[i]==' ')s+=' ';
		else{
			s+=key[x];
			x++;
			if(x==key.size())x=0;
		}
	}
	cout<<s<<"\n";
	string decoded;
	for(unsigned int i=0; i<s.size(); i++){
		if(s[i]==' ')decoded+=' ';
		else{
			for(unsigned int j=0; j<alphabet.size(); j++){
				if(s[i]==alphabet[j]){
					for(unsigned int k=0; k<square.size(); k++){
						if(cipher[i]==square[k][j]){
							decoded+=square[k].front();
							break;
						}							
					}
				}
				//if(skip)break;
			}
			//if(skip)break;
		}
	}
	cout<<decoded<<"\n";
}

int main(){
	vector<vector<char>> square;
	square.push_back(alphabet);
	vector<char> temp=alphabet;
	for(unsigned int i=0; i<alphabet.size(); i++){
		temp.push_back(temp.front());
		temp.erase(temp.begin());
		square.push_back(temp);
	}
	cout<<square<<"\n";
	string key;
	cout<<"Input key:  ";
	getline(cin,key);
	key.erase(key.size());
	cout<<key<<"\n";
	string cipher;
	cout<<"Input cipher:  ";
	getline(cin,cipher);
	//cout<<"\nREACHED LINE:"<<__LINE__<<"\n";
	cout<<cipher<<"\n";
	decode(key, cipher, square);
	encode(key,cipher,square);
	return 0;
}
