/*	Author: Logan Traffas
TODO:
	- 
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

string keyed(const string key,const string message){
	string s;
	unsigned int x=0;
	for(unsigned int i=0; i<message.size(); i++){
		if(message[i]==' ')s+=' ';
		else{
			s+=key[x];
			x++;
			if(x==key.size())x=0;
		}
	}
	cout<<"Keyed:         "<<s<<"\n";
	return s;
}

string encode(const string s,const string message,const vector<vector<char>> square,const string punct){
	string encoded;
	for(unsigned int i=0; i<s.size(); i++){
		if(s[i]==' ')encoded+=' ';
		else{
			for(unsigned int j=0; j<alphabet.size(); j++){
				if(tolower(s[i])==tolower(alphabet[j])){
					for(unsigned int k=0; k<square.size(); k++){
						if(tolower(message[i])==tolower(square[k].front())){
							encoded+=square[k][j];
							break;
						}							
					}
				}
			}
		}
	}
	for(unsigned int i=0; i<punct.size(); i++){
		if(punct[i]!=' ')encoded.insert(encoded.begin()+i,punct[i]);
	}
	return encoded;
}

string decode(const string s,const string cipher,const vector<vector<char>> square,const string punct){
	string decoded;
	for(unsigned int i=0; i<s.size(); i++){
		if(s[i]==' ')decoded+=' ';
		else{
			for(unsigned int j=0; j<alphabet.size(); j++){
				if(tolower(s[i])==tolower(alphabet[j])){
					for(unsigned int k=0; k<square.size(); k++){
						if(tolower(cipher[i])==tolower(square[k][j])){
							decoded+=square[k].front();
							break;
						}							
					}
				}
			}
		}
	}
	for(unsigned int i=0; i<punct.size(); i++){
		if(punct[i]!=' ')decoded.insert(decoded.begin()+i,punct[i]);
	}
	return decoded;
}

string find_punct(string& cipher){
	string punct=cipher;
	for(unsigned int i=0; i<cipher.size(); i++){
		if(cipher[i]!=' '){
			for(unsigned int j=0; j<alphabet.size(); j++){
				if(tolower(cipher[i])==tolower(alphabet[j])){
					punct.erase(punct.begin()+i);
					punct.insert(i," ");
					break;
				}
			}
		}
	}
	for(unsigned int i=0; i<punct.size(); i++){
		if(punct[i]!=' ')cipher.erase(cipher.begin()+i);
	}
	return punct;
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
	string key;
	cout<<"Input key:     ";
	getline(cin,key);
	key.erase(key.size());
	string cipher;
	cout<<"Input cipher:  ";
	getline(cin,cipher);
	string punct=find_punct(cipher);
	string s=keyed(key,cipher);
	cout<<"Decoded:       "<<decode(s,cipher,square,punct)<<"\n";
	cout<<"Encoded:       "<<encode(s,cipher,square,punct);
	return 0;
}
