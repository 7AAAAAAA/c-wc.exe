#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
int somecmdselect(char* cmd,char* file);
int chars(char* name);
int words(char* name);
int lines(char* name);
int mores(char* name);
int watchfiles(char* folder,char* factor,char* argv[]);
int main(int argc, char* argv[]){
    if(argc > 1){
        if(strcmp(argv[1],"-s") == 0){
            if(argc > 3){
                watchfiles(".","*.c",argv);
            }else {
                printf("缺少参数\n");
                printf("可通过 help参数查看可使用命令\n");
            }
        }else {
            somecmdselect(argv[1],argv[2]);
        }
    }else {
        printf("缺少参数\n");
        printf("可通过 help参数查看可使用命令\n");
    }
    return 0;
}


/*
    功能：
        进行第二个参数不为-s的其他命令选择
    参数：
        argv[] 输入的参数
    返回：
        返回 0
*/
int somecmdselect(char* cmd,char* file) {
    if(strcmp(cmd,"help") == 0) {
        printf("    -c file.c  返回文件file.c的字符数\n");
        printf("    -w file.c  返回文件file.c的词的数目\n");
        printf("    -l file.c  返回文件file.c的行数\n");
        printf("    -a file.c  返回文件file.c的空行/代码行/注释行\n");
        printf("    -s a b     返回当前目录及子目录中符合b条件的a操作\n");
        printf("               a可为-c/-w/-l/-a\n");
        printf("               b可为*/*.c等（此处仅支持*.c）");
    }else if(!file){
        printf("缺少参数\n");
        printf("可通过 help参数查看可使用命令\n");
    }else if(strcmp(cmd,"-c") == 0) {
        chars(file);
    }else if(strcmp(cmd,"-w") == 0) {
        words(file);
    }else if(strcmp(cmd,"-l") == 0) {
        lines(file);
    }else if(strcmp(cmd,"-a") == 0) {
        mores(file);
    }else {
        printf("\'%s\'命令不存在\n",cmd);
        printf("可通过 help参数查看可使用命令\n");
    }
    return 0;
}


/*
    功能：
        计算文件的字符数
    参数：
        name 查询的文件名
    返回：
        count 文件中的字符数 包括所有字符
*/
int chars(char* name){
    FILE *fp;
    int ch;
    int count = 0;
    if((fp = fopen(name,"r")) == NULL ){
        printf("file: %s\n",name);
        printf("错误：找不到该文件或者打不开该文件\n");
        count = -1;
    }
    else {
        while((ch = fgetc(fp)) != EOF) {
            count++;
        }
    }
    fclose(fp);
    if(count >= 0) {
         printf("file: %s\n    char: %d\n",name,count);
    }
    return 0;
}


/*
    功能：
        计算文件的单词数（指具有前后空格的只有字母的串）
    参数：
        name 查询的文件名
    返回：
        count 文件中的单词数
*/
int words(char* name){
    FILE *fp;
    int ch;
    int flag = 0;
    int count = 0;
    if((fp = fopen(name,"r")) == NULL ){
        printf("file: %s\n",name);
        printf("错误：找不到该文件或者打不开该文件\n");
        count = -1;
    }
    else {
        while((ch = fgetc(fp)) != EOF) {
            if((ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') && flag == 0){
                flag = 1;
            }else if(((ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') && flag == 1) || flag == 0){
                continue;
            }else if(flag == 1) {
                count++;
                flag = 0;
            }
        }
        if(flag == 1) {
            count++;
        }
    }
    fclose(fp);
    if(count >= 0) {
         printf("file: %s\n    word: %d\n",name,count);
    }
    return count;
}


/*
    功能：
        计算文件的行数
    参数：
        name 查询的文件名
    返回：
        count 文件中的行数
*/
int lines(char* name){
    FILE *fp;
    int ch;
    int count = 0;
    int flag = 0;
    if((fp = fopen(name,"r")) == NULL ){
        printf("file: %s\n",name);
        printf("错误：找不到该文件或者打不开该文件\n");
        count = -1;
    }
    else {
        while((ch = fgetc(fp)) != EOF) {
            flag = 1;
            if(ch == '\n'){
                count++;
            }
        }
        if(flag == 1){
            count++;
        }
    }
    fclose(fp);
    if(count >= 0) {
         printf("file: %s\n    line: %d\n",name,count);
    }
    return count;
}


/*
    功能：
        计算文件的空行数/代码行数/注释行数
    参数：
        name 查询的文件名
    返回：
        count 文件中的空行/代码行/注释行
*/
int mores(char* name){
    FILE *fp;
    int ch;
    int count[3] = {0,0,0};
    int flag = 0; //超过一个可显示字符才会为1
    int flagcommit = 0;//这一行是否已被加为注释
    int flagcode = 0;//这一行是否已被加为代码
    int flagchar = 0;//文件中是否有任何字符
    if((fp = fopen(name,"r")) == NULL ){
        printf("file: %s\n",name);
        printf("错误：找不到该文件或者打不开该文件\n");
        count[0] = -1;
    }
    else {
        while((ch = fgetc(fp)) != EOF) {
            if(flagchar == 0) {
                flagchar = 1;
            }
            if(ch == '/') { //遇到一个/
                if((ch = fgetc(fp)) != EOF){
                    if(ch == '/') {
                        if(flag == 2 && flagcode == 0) {
                            count[1]++;
                            flagcode = 1;
                        }
                        if(flagcommit == 0 && flagcode == 0){
                            count[2]++;
                            flagcommit = 1;
                        }
                        while((ch = fgetc(fp)) != EOF) {
                            if(ch == '\n') {
                                flag = 0;
                                flagcode = 0;
                                flagcommit = 0;
                                break;
                            }
                        }
                    }else if(ch == '*') {
                        if(flag == 2 && flagcode == 0) {
                            if(flagcommit == 1) {
                                count[2]--;
                            }
                            count[1]++;
                            flagcode = 1;
                        }
                        if(flagcommit == 0 && flagcode == 0){
                            count[2]++;
                            flagcommit = 1;
                        }
                        while((ch = fgetc(fp)) != EOF) {
                            if(ch == '\n') {
                                count[2]++;
                                flagcommit = 0;
                                flagcode = 0;
                                flag = 0;
                            }else if(ch == '*') {
                                if((ch = fgetc(fp)) != EOF) {
                                    if(ch == '/') {
                                        flagcommit = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }else if(ch >'\x20'){   //不知道后面什么情况，bug待定
                if(flag == 0){
                    flag = 1;
                }else if(flag == 1) {
                    flag = 2;
                }
            }else if(ch == '\n') {
                if((flag == 0 || flag == 1) && flagcode == 0 && flagcommit == 0){
                    count[0]++;
                }else if(flag == 2 && flagcode == 0){
                    count[1]++;
                }
                flag = 0;
                flagcommit = 0;
                flagcode = 0;
            }else {
                continue;
            }

        }
    }
    if((flag == 0 || flag == 1 )&& flagcode == 0 && flagcommit == 0 && flagchar == 1){
        count[0]++;
    }else if(flag == 2 && flagcode == 0 && flagcommit == 0) {
        count[1]++;
    }else if(flag == 2 && flagcode == 0 && flagcommit == 1) {
        count[1]++;
        count[2]--;
    }
    fclose(fp);
    if(count[0] >= 0) {
         printf("file: %s\n    empty:%d\t code: %d\tnote: %d\n",name,count[0],count[1],count[2]);
    }
    return 0;
}


/*
    功能：
        递归处理该exe所在目录及子目录下所有满足条件的文件（此处仅支持*.c）
    参数：
        folder 遍历的目录
        factor 搜索条件
        argv[] 命令参数
    返回：0
*/
int watchfiles(char* folder,char* factor,char* argv[]){
    struct _finddata_t f;
    long handle;
    char* currentfactor = (char*)malloc(sizeof(char*)*(strlen(folder)+strlen(factor)+2));//存放当前目录的factor
    char* currentfolder= (char*)malloc(sizeof(char*)*(strlen(folder)+strlen(factor)+2));//当前目录
    char* path = (char*)malloc(sizeof(char*)*(strlen(folder)+2));
    strcpy(path,folder);
    strcpy(currentfactor,strcat(path,"/"));
    strcpy(currentfolder,path);
    handle = _findfirst(strcat(currentfactor,factor),&f);
    if(handle == -1L) {
        return 0;
    }else {
        do{
            if(f.attrib != _A_SUBDIR){
                char* name = (char*)malloc(sizeof(char*)*(strlen(path)+strlen(f.name)));
                strcpy(name,path);
                somecmdselect(argv[2],strcat(name,f.name));
                free(name);
            }
        }while(_findnext(handle,&f) == 0);
    }
    free(currentfactor);
    _findclose(handle);
    handle = _findfirst(strcat(currentfolder,"*"),&f);
    if(handle == -1L) {
        return 0;
    }else {
        do{
            if(f.attrib == _A_SUBDIR && strcmp(f.name,".") && strcmp(f.name,"..")){
                char* newpath = (char*)malloc(sizeof(char*)*(strlen(path)+strlen(f.name)));
                strcpy(newpath,path);
                watchfiles(strcat(newpath,f.name),factor,argv);
                free(newpath);
            }
        }while(_findnext(handle,&f) == 0);
    }
    _findclose(handle);
    free(currentfolder);
    free(path);
    return 0;
}
