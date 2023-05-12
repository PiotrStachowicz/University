#include <stdio.h>
void encrypt(const char* keypath,const char* file_path){
    FILE *key_file = fopen(keypath,"rb");
    FILE *file = fopen(file_path, "r+b");
    if(key_file==NULL || file==NULL){printf("Nie udało się otworzyć pliku lub klucza!");fclose(key_file);fclose(file); return;}
    char character, key;
    while (fread(&character,sizeof(char), 1,file)==1){;
        printf("%c\n", character);
        if(fread(&key,sizeof(char), 1,key_file)!=1){
            fseek(key_file,0,SEEK_SET); // cykl klucza
            fread(&key,sizeof(char), 1,key_file);
        }
        character ^= key;
        fseek(file,-1,SEEK_CUR);
        printf("posA %ld\n",ftell(file));
        if(fwrite(&character,sizeof(char),sizeof(char),file)!=1) printf("error\n");
        printf("posB %ld\n",ftell(file));
        fseek(file,0,SEEK_CUR);
    }
    fclose(file);
    fclose(key_file);
}
int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("Nie podano wszystkich argumentów: ścieżki klucza i pliku do zaszyfrowania\n");
        return 1;
    }
    encrypt(argv[0], argv[1]);
    return 0;
}