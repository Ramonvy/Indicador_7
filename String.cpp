#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


class String{
	private: char *str;
	bool log = false;
	
	public: String(char *text){
		if(log){printf("String line 13\n");}
		//str = (char*)malloc((strlen(text) + 1) * sizeof(char));
		//strcpy(str, text);
		
		str = text;
	}
	
	public: char *getstr(){
		if(log){printf("String line 21\n");}
		return str;
	}
	
	public: char charAt(int index){
		if(log){printf("String line 26\n");}
		if(index > 0 && index < strlen(str)){
			return str[index];
		}
		
		//index fora da range alocada
		return -1;
	}
	
	public: String concat(char *in){
		if(log){printf("String line 36\n");}
		String out = String(str);
		
		unsigned long long int p_dif = strlen(str);
		unsigned long long int insz = strlen(in);
		
		for(unsigned long long int i = 0; i <= insz; i++){
			out.str[p_dif + i] = in[i];
		}
		
		return out;
	}
	
	public: bool contains(char *in){
		if(log){printf("String line 50\n");}
		unsigned long long int x = 0;		//Fluxo dentro de in
		unsigned long long int p_dif = 0;	
		
		while(in[x] != 0){
			
			while(in[x] != 0 && str[p_dif + x] == in[x]){
				++x;
			}
			
			if(in[x] != 0){
				x = 0;
				++p_dif;
				
				if(strlen(in) + p_dif > strlen(str)){
					return false;
				}
			}
		}
		
		return true;
	}
	
	public: bool endsWith(char *in){
		if(log){printf("String line 74\n");}
		unsigned long long int in_end = strlen(in) - 1;
		unsigned long long int str_end = length() - 1;
		
		if(in_end > str_end){
			return false;
		}
		
		unsigned long long int b_s = 0;
		
		while(in_end - b_s >= 0){
			if(in[in_end - b_s] != str[str_end - b_s]){
				return false;
			}
			
			if(in_end - b_s == 0){
				return true;
			}
			++b_s;
		}
		
		return true;
	}
	
	public: bool equals(char *in){
		if(log){printf("String line 99\n");}
		if(strcmp(str, in) == 0){
			return true;
		}
		return false;
	}
	
	public: bool equalsIgnoreCase(char *in){
		if(log){printf("String line 107\n");}
		if(stricmp(str, in) == 0){
			return true;
		}
		return false;
	}
	
	public: long int indexOf(char ch, long int fromIndex){
		if(log){printf("String line 115\n");}
		unsigned long long int limit = strlen(str);
		
		for(long int i = fromIndex; i < limit; i++){
			if(str[i] == ch){
				return i;
			}
		}
		
		return -1;
	}
	
	
	public: long int indexOf(char *in){
		if(log){printf("String line 129\n");}
		long int x = 0;		//Fluxo dentro de in
		long int p_dif = 0;	
		
		while(in[x] != 0){
			
			while(in[x] != 0 && str[p_dif + x] == in[x]){
				++x;
			}
			
			if(in[x] != 0){
				x = 0;
				++p_dif;
				
				if(strlen(in) + p_dif > strlen(str)){
					return -1;
				}
			}
		}
		
		return p_dif;
	}
	
	
	public: long long int indexOf(char ch){
		if(log){printf("String line 154\n");}
		
		for(long long int i = 0; str[i] != 0; i++){
			if(str[i] == ch){
				return i;
			}
		}
		
		return -1;
	}
	
	//Obtem a posição de uma ocorrencia especifica de um caracter especifico dessa forma n = 0, retorna a posição da primeira ocorrencia de ch
	public: long long int indexOf(char ch, long long int n){
		if(log){printf("String line 167\n");}
		
		long long int m = 0;
		for(long long int i = 0; str[i] != 0; i++){
			if(str[i] == ch){
				if(m == n){
					return i;
				}
				++m;
			}
		}
		
		return -1;
	}
	
	
	public: bool isEmpty(){
		if(log){printf("String line 184\n");}
		
		if(str == NULL || str[0] == 0){
			return true;
		}
		
		return false;
	}
	
	
	public: unsigned long long int lastIndexOf(char ch){
		if(log){printf("String line 195\n");}
		
		unsigned long long int flow = length();
		--flow;
		
		while(flow >= 0){
			if(str[flow] == ch){
				return flow;
			}
			
			if(flow > 0){
				--flow;
			}
		}
		
		return 0;
	}
	
	
	public: unsigned long long int length(){
		if(log){printf("String line 215\n");}
		
		unsigned long long int x = 0;
		
		while(str[x] != 0){
			++x;
		}
		
		return x;
	}
	
	
	public: String repeat(int count){
		if(log){printf("String line 228\n");}
		String out = String("");
		
		for(int i = 0; i < count; i++){
			out = out.concat(str);
		}
		
		return out;
	}
	
	
	public: String replace(char oldChar, char newChar){
		if(log){printf("String line 240\n");}
		char *aux = (char*)malloc((length() + 1) * sizeof(char));
		
		unsigned long long int s_len = length();
		for(unsigned long long int i = 0; i <= s_len; i++){
			if(str[i] == oldChar){
				aux[i] = newChar;
			}
			else{
				aux[i] = str[i];
			}
		}
		
		return String(aux);
	}
	
	
	public: String replace(char *oldstr, char *newstr){
		if(log){printf("String line 258\n");}
		char *aux = (char*)malloc((length() + (strlen(newstr) - strlen(oldstr))) * sizeof(char));
		unsigned long long int af = 0;		//aux flow
		unsigned long long int sf = 0;		//str flow
		
		long int index = indexOf(oldstr);
	
		
		while(af < index){
			aux[af] = str[af];
			++af;
		}
		sf = index + strlen(oldstr);
		
		for(int i = 0; i < strlen(newstr); i++){
			aux[af] = newstr[i];
			++af;
		}
		
		unsigned long long int s_len = length();
		while(sf < s_len){
			aux[af] = str[sf];
			++af;
			++sf;
		}
		aux[af] = 0;
		
		//printf("aux > %s\n", aux);
		
		return String(aux);
	}
	
	public: char *replace_cdrop(char *oldstr, char *newstr){
		if(log){printf("String line 258\n");}
		//printf("l292\n");
		//char *aux = (char*)malloc((length() + (strlen(newstr) - strlen(oldstr))) * sizeof(char));
		char aux[5000];
		
		unsigned long long int af = 0;		//aux flow
		unsigned long long int sf = 0;		//str flow
		
		//printf("l297\n");
		
		long int index = indexOf(oldstr);
	
		
		while(af < index){
			aux[af] = str[af];
			++af;
		}
		sf = index + strlen(oldstr);
		
		for(int i = 0; i < strlen(newstr); i++){
			aux[af] = newstr[i];
			++af;
		}
		
		//printf("l313\n");
		
		unsigned long long int s_len = length();
		while(sf < s_len){
			aux[af] = str[sf];
			++af;
			++sf;
		}
		aux[af] = 0;
		
		//printf("aux > %s\n", aux);
		
		return aux;
	}
	
	public: bool startsWith(char *in){
		if(log){printf("String line 290\n");}
		unsigned long long int i_sz = String(in).length();
		unsigned long long int s_sz = length();
		
		if(i_sz > s_sz){
			return false;
		}
		
		for(unsigned long long int i = 0; i < i_sz; i++){
			if(in[i] != str[i]){
				return false;
			}
		}
		
		return true;
	}
	
	
	public: bool startsWith(char *in, unsigned long long int toffset){
		if(log){printf("String line 309\n");}
		unsigned long long int i_sz = String(in).length();
		unsigned long long int s_sz = length();
		
		if(i_sz + toffset > s_sz){
			return false;
		}
		
		for(unsigned long long int i = 0; i < i_sz; i++){
			if(in[i] != str[i + toffset]){
				return false;
			}
		}
		
		return true;
	}
	
	
	public: char *substring(unsigned long long int beginIndex, unsigned long long int endIndex){
		if(log){printf("String line 328\n");}
		//printf("s1\n");
		char *aux = (char*)malloc(((endIndex - beginIndex) + 2) * sizeof(char));
		//printf("length() = %llu\n", length());
		
		//printf("s2\n");
		for(unsigned long long int i = 0; (i + beginIndex) < endIndex; i++){
			//printf("i = %lu\n", i);
			//printf("i - beginIndex = %lu\n", (i - beginIndex));
			aux[i] = str[i + beginIndex];
			aux[i + 1] = 0;
		}
		
		//printf("aux = %s\n\n", aux);
		
		//system("pause");
		
		return aux;
	}
	
	
	public: char *substring(unsigned long long int beginIndex){
		if(log){printf("String line 350\n");}
		unsigned long long int x = 0;
		char *aux = (char*)malloc((length() + 1) * sizeof(char));
		
		strcpy(aux, "");
		while(str[x + beginIndex] != 0){
			aux[x] = str[x + beginIndex];
			++x;
		}
		aux[x] = 0;
		
		return aux;
	}
	
	
	public: String toLowerCase(){
		if(log){printf("String line 365\n");}
		unsigned long long int s_sz = length();
		char *aux = (char*)malloc((s_sz + 1) * sizeof(char));
		
		unsigned long long int x = 0;
		while(str[x] != 0){
			aux[x] = tolower(str[x]);
			++x;
		}
		aux[x] = 0;
		
		return String(aux);
	}
	
	
	
	public: String toUpperCase(){
		if(log){printf("String line 382\n");}
		unsigned long long int s_sz = length();
		char *aux = (char*)malloc((s_sz + 1) * sizeof(char));
		
		unsigned long long int x = 0;
		while(str[x] != 0){
			aux[x] = toupper(str[x]);
			++x;
		}
		aux[x] = 0;
		
		return String(aux);
	}
	
	
	
	public: char *valueOf(bool b){
		if(log){printf("String line 399\n");}
		if(b){
			return "true";
		}
		
		return "false";
	}
	
	
	
	public: char *valueOf(int i){
		if(log){printf("String line 410\n");}
		char *aux = (char*)malloc(3000 * sizeof(char));
		sprintf(aux, "%d", i);
		return aux;
	}
	
	
	
	public: char *valueOf(long l){
		if(log){printf("String line 419\n");}
		char *aux = (char*)malloc(3000 * sizeof(char));
		sprintf(aux, "%l", l);
		return aux;
	}
	
	
	
	public: void removeChar(int index){
		if(log){printf("String line 428\n");}
		int x = index;
		int len = strlen(str);
		while(x < len){
			str[x] = str[x + 1];
			++x;
		}
	}
	
	
	
	public: void addChar(char c, int index){
		if(log){printf("String line 440\n");}
		int x = strlen(str);
		
		while(x >= index){
			str[x + 1] = str[x];
			--x;
		}
		++x;
		str[x] = c;
	}
	
	
	
	public: void removeLastChar(){
		if(log){printf("String line 454\n");}
		if(str[0] != 0){
			str[strlen(str) - 1] = 0;
		}
	}
	
	
	
	public: void append(char c){
		if(log){printf("String line 463\n");}
		int len = 0;
		while(str[len] != 0){
			++len;
		}
		str[len + 1] = '\0';
		str[len] = c;
	}
	
	
	
	public: void append(char *s){
		if(log){printf("String line 475\n");}
		int s_len = strlen(s);
		int len = strlen(str);
		
		for(int i = 0; i <= s_len; i++){
			str[len + i + 1] = 0;
			str[len + i] = s[i];	
		}
	}
	
	public: long long int countChar(char ch){
		if(log){printf("String line 486\n");}
		unsigned long long int s_sz = length();
		
		unsigned long long int x = 0;
		long long int y = 0;
		while(x < s_sz){
			if(str[x] == ch){
				++y;
			}
			++x;
		}
		
		return y;
	}
	
};
