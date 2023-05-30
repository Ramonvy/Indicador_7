#include <iostream>
#include "String.cpp"


char *get_us_code(char *line){
	int x = 0;
	
	while(line[x] < '0' || line[x] > '9'){
		++x;
	}
	
	char us_code[100];
	
	int y = 0;
	while(line[x] != ' '){
		us_code[y] = line[x];
		++y;
		++x;
	}
	us_code[y] = 0;
	
	return us_code;
}

bool isACID(char *str){
	if(str[0] >= 'A' && str[0] <= 'Z' && str[1] >= '0' && str[1] <= '9'){
		return true;
	}
	
	return false;
}

char *get_w2(char *line){
	char w2[3000];
	
	int x = 2;
	
	while(line[x] != ' '){
		++x;
	}
	
	while(line[x] == ' '){
		++x;
	}
	
	int y = 0;
	while(line[x] != ' '){
		w2[y] = line[x];
		++x;
		++y;
	}
	w2[y] = 0;
	
	return w2;
}

char *get_fist(char *line){
	char first[3000];
	
	int x = 0;
	while(line[x] != ' '){
		first[x] = line[x];
		++x;
	}
	first[x] = 0;
	
	return first;
}

char *get_user_pack(char *line){
	//AMA NOME CNS
	char ama[100];
	char nome[1000];
	char cns[100];
	
	int x = 0;
	
	while(line[x] < '0' || line[x] > '9'){
		++x;
	}
	
	int y = 0;
	while(line[x] != ' '){
		ama[y] = line[x];
		++x;
		++y;
	}
	ama[y] = 0;
	
	x += 2;
	while(line[x] == ' '){
		++x;
	}
	
	y = 0;
	while(line[x] != ':'){
		nome[y] = line[x];
		++x;
		++y;
	}
	nome[y - 4] = 0;
	
	x += 2;
	y = 0;
	while(line[x] != '\n'){
		cns[y] = line[x];
		++x;
		++y;
	}
	cns[y] = 0;
	
	char drop[3000];
	sprintf(drop, "%s\t%s\t%s", ama, nome, cns);
	
	return drop;
}


int main(int argc, char** argv) {
	FILE *f = fopen("raw_data.txt", "r");
	fseek(f, 0, SEEK_END);
	unsigned long long int fsz = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	//DATA AMA NOME CNS CID HG(1/0) COD ESTABELECIMENTO

	
	FILE *f2 = fopen("drop.txt", "w");
	
	char buffer[5000];
	char us_code[100];
	char data[100];
	char user_pack[1500];
	char cid[100];
	bool hg = false;
	
	
	char first[3000];
	strcpy(us_code, "---");
	
	int bp;
	
	//Loop que percorre o arquivo raw_data.txt lendo uma linha por vez
	while(ftell(f) < fsz){
		fgets(buffer, 5000, f);
		bp = 1;
		
		//printf("bp%d\n", bp);
		++bp;
		
		if(String(buffer).startsWith("UNIDADE DE SA")){
			strcpy(us_code, get_us_code(buffer));
		}
		
		//printf("bp%d\n", bp);
		++bp;
		
		if(String(buffer).startsWith("USU")){
			//printf("bp%d\n", bp);
			++bp;
			
			char buffer2[5000];
			strcpy(user_pack, get_user_pack(buffer));
			
			//printf("bp%d\n", bp);
			++bp;
			
			
			fgets(buffer2, 5000, f);
			if(String(buffer2).endsWith("TIPO\n")){
				fgets(buffer2, 5000, f);
				
				//printf("bp%d\n", bp);
				++bp;
				
				
				//Possiveis formatos pra buffer2 nesso ponto
				//CID seguido de nome da enfermidade
				//Data seguida de CID
				
				strcpy(first, get_fist(buffer2));
				
				//printf("bp%d\n", bp);
				++bp;
				
				
				if(isACID(first)){
					strcpy(cid, first);
					
					fgets(buffer2, 5000, f);
					while(buffer2[2] != '/'){
						fgets(buffer2, 5000, f);
					}
					
					strcpy(data, get_fist(buffer2));
					
					if(String(buffer2).contains("Sim")){
						hg = true;
					}
					else if(String(buffer2).contains("Não")){
						hg = false;
					}
					else{
						
						printf("Falha na obtenção dos dados\n");
						system("pause");
					}
				}
				else{
					strcpy(data, first);
					strcpy(cid, get_w2(buffer2));
					
					if(String(buffer2).contains("Sim")){
						hg = true;
					}
					else if(String(buffer2).contains("Não")){
						hg = false;
					}
					else{
						
						printf("Falha na obtenção dos dados\n");
						system("pause");
					}
				}
				
				//printf("bp%d\n", bp);
				++bp;
					
				
				if(hg){
					fprintf(f2, "%s\t%s\t%s\t1\t%s\n", data, user_pack, cid, us_code);
				}
				else{
					fprintf(f2, "%s\t%s\t%s\t0\t%s\n", data, user_pack, cid, us_code);
				}
				
				//printf("bp%d\n", bp);
				++bp;
			}
		}
		
		
	}
	
	fclose(f2);
	fclose(f);
	return 0;
}
