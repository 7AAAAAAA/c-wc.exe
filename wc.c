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
                printf("ȱ�ٲ���\n");
                printf("��ͨ�� help�����鿴��ʹ������\n");
            }
        }else {
            somecmdselect(argv[1],argv[2]);
        }
    }else {
        printf("ȱ�ٲ���\n");
        printf("��ͨ�� help�����鿴��ʹ������\n");
    }
    return 0;
}


/*
    ���ܣ�
        ���еڶ���������Ϊ-s����������ѡ��
    ������
        argv[] ����Ĳ���
    ���أ�
        ���� 0
*/
int somecmdselect(char* cmd,char* file) {
    if(strcmp(cmd,"help") == 0) {
        printf("    -c file.c  �����ļ�file.c���ַ���\n");
        printf("    -w file.c  �����ļ�file.c�Ĵʵ���Ŀ\n");
        printf("    -l file.c  �����ļ�file.c������\n");
        printf("    -a file.c  �����ļ�file.c�Ŀ���/������/ע����\n");
        printf("    -s a b     ���ص�ǰĿ¼����Ŀ¼�з���b������a����\n");
        printf("               a��Ϊ-c/-w/-l/-a\n");
        printf("               b��Ϊ*/*.c�ȣ��˴���֧��*.c��");
    }else if(!file){
        printf("ȱ�ٲ���\n");
        printf("��ͨ�� help�����鿴��ʹ������\n");
    }else if(strcmp(cmd,"-c") == 0) {
        chars(file);
    }else if(strcmp(cmd,"-w") == 0) {
        words(file);
    }else if(strcmp(cmd,"-l") == 0) {
        lines(file);
    }else if(strcmp(cmd,"-a") == 0) {
        mores(file);
    }else {
        printf("\'%s\'�������\n",cmd);
        printf("��ͨ�� help�����鿴��ʹ������\n");
    }
    return 0;
}


/*
    ���ܣ�
        �����ļ����ַ���
    ������
        name ��ѯ���ļ���
    ���أ�
        count �ļ��е��ַ��� ���������ַ�
*/
int chars(char* name){
    FILE *fp;
    int ch;
    int count = 0;
    if((fp = fopen(name,"r")) == NULL ){
        printf("file: %s\n",name);
        printf("�����Ҳ������ļ����ߴ򲻿����ļ�\n");
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
    ���ܣ�
        �����ļ��ĵ�������ָ����ǰ��ո��ֻ����ĸ�Ĵ���
    ������
        name ��ѯ���ļ���
    ���أ�
        count �ļ��еĵ�����
*/
int words(char* name){
    FILE *fp;
    int ch;
    int flag = 0;
    int count = 0;
    if((fp = fopen(name,"r")) == NULL ){
        printf("file: %s\n",name);
        printf("�����Ҳ������ļ����ߴ򲻿����ļ�\n");
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
    ���ܣ�
        �����ļ�������
    ������
        name ��ѯ���ļ���
    ���أ�
        count �ļ��е�����
*/
int lines(char* name){
    FILE *fp;
    int ch;
    int count = 0;
    int flag = 0;
    if((fp = fopen(name,"r")) == NULL ){
        printf("file: %s\n",name);
        printf("�����Ҳ������ļ����ߴ򲻿����ļ�\n");
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
    ���ܣ�
        �����ļ��Ŀ�����/��������/ע������
    ������
        name ��ѯ���ļ���
    ���أ�
        count �ļ��еĿ���/������/ע����
*/
int mores(char* name){
    FILE *fp;
    int ch;
    int count[3] = {0,0,0};
    int flag = 0; //����һ������ʾ�ַ��Ż�Ϊ1
    int flagcommit = 0;//��һ���Ƿ��ѱ���Ϊע��
    int flagcode = 0;//��һ���Ƿ��ѱ���Ϊ����
    int flagchar = 0;//�ļ����Ƿ����κ��ַ�
    if((fp = fopen(name,"r")) == NULL ){
        printf("file: %s\n",name);
        printf("�����Ҳ������ļ����ߴ򲻿����ļ�\n");
        count[0] = -1;
    }
    else {
        while((ch = fgetc(fp)) != EOF) {
            if(flagchar == 0) {
                flagchar = 1;
            }
            if(ch == '/') { //����һ��/
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
            }else if(ch >'\x20'){   //��֪������ʲô�����bug����
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
    ���ܣ�
        �ݹ鴦���exe����Ŀ¼����Ŀ¼�����������������ļ����˴���֧��*.c��
    ������
        folder ������Ŀ¼
        factor ��������
        argv[] �������
    ���أ�0
*/
int watchfiles(char* folder,char* factor,char* argv[]){
    struct _finddata_t f;
    long handle;
    char* currentfactor = (char*)malloc(sizeof(char*)*(strlen(folder)+strlen(factor)+2));//��ŵ�ǰĿ¼��factor
    char* currentfolder= (char*)malloc(sizeof(char*)*(strlen(folder)+strlen(factor)+2));//��ǰĿ¼
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
