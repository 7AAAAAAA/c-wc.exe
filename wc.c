#include <stdio.h>
#include <string.h>
int chars(char* name);
int words(char* name);
int lines(char* name);
int mores(char* name);
int main(int argc, char* argv[]){
    if(argc > 1){
        if(strcmp(argv[1],"help") == 0) {
            printf("    -c file.c  返回文件file.c的字符数。\n");
            printf("    -w file.c  返回文件file.c的词的数目。\n");
            printf("    -l file.c  返回文件file.c的行数。\n");
            printf("    -a file.c  返回文件file.c的空行/代码行/注释行。\n");
        }else if(strcmp(argv[1],"-c") == 0) {
            chars(argv[2]);
        }else if(strcmp(argv[1],"-w") == 0) {
            words(argv[2]);
        }else if(strcmp(argv[1],"-l") == 0) {
            lines(argv[2]);
        }else if(strcmp(argv[1],"-a") == 0) {
            mores(argv[2]);
        }else {
            printf("\'%s\'命令不存在\n",argv[1]);
            printf("可通过 help参数查看可使用命令\n");
        }
    }else {
        printf("缺少参数\n");
        printf("可通过 help参数查看可使用命令\n");
    }
    return 0;
}
/*
    参数：
        name 查询的文件名
    返回：
        count 文件中的字符数 包括可显示字符和不可显示字符
*/
int chars(char* name){
    FILE *fp;
    int ch;
    int count = 0;
    if((fp = fopen(name,"r")) == NULL ){
        printf("error: cannot to find the file or to open this file.\n");
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
    参数：
        name 查询的文件名
    返回：
        count 文件中的单词数 指具有前后空格的只有字母的串
*/
int words(char* name){
    FILE *fp;
    int ch;
    int flag = 0;
    int count = 0;
    if((fp = fopen(name,"r")) == NULL ){
        printf("error: cannot to find the file or to open this file.\n");
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
        printf("error: cannot to find the file or to open this file.\n");
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
    if((fp = fopen(name,"r")) == NULL ){
        printf("error: cannot to find the file or to open this file.\n");
        count[0] = -1;
    }
    else {
        while((ch = fgetc(fp)) != EOF) {
            if(ch == '/') { //遇到第一个/
                if((ch = fgetc(fp)) != EOF){
                    if(ch == '/') {
                        count[2]++;
                        if(flag == 2) {
                            count[2]--;
                            count[1]++;
                        }
                        while((ch = fgetc(fp)) != EOF) {
                            if(ch == '\n') {
                                flag = 0;
                                break;
                            }
                        }
                    }else if(ch == '*') {
                        count[2]++;
                        if(flag == 2) {
                            count[2]--;
                            count[1]++;
                        }
                        while((ch = fgetc(fp)) != EOF) {
                            if(ch == '\n') {
                                count[2]++;
                            }else if(ch == '*') {
                                if((ch = fgetc(fp)) != EOF) {
                                    if(ch == '/') {
                                        flag = 0;
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
                if(flag == 0 || flag == 1){
                    count[0]++;
                }else if(flag == 2){
                    count[1]++;
                }
                flag = 0;
            }else {
                continue;
            }

        }
    }
    fclose(fp);
    if(count[0] >= 0) {
         printf("file: %s\n    empty:%d\t code: %d\tnote: %d\n",name,count[0],count[1],count[2]);
    }
    return 0;
}
