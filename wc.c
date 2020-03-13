#include <stdio.h>
#include <string.h>
int chars(char* name);
int words(char* name);
int lines(char* name);
int mores(char* name);
int main(int argc, char* argv[]){
    if(argc > 1){
        if(strcmp(argv[1],"help") == 0) {
            printf("    -c file.c  �����ļ�file.c���ַ�����\n");
            printf("    -w file.c  �����ļ�file.c�Ĵʵ���Ŀ��\n");
            printf("    -l file.c  �����ļ�file.c��������\n");
            printf("    -a file.c  �����ļ�file.c�Ŀ���/������/ע���С�\n");
        }else if(strcmp(argv[1],"-c") == 0) {
            chars(argv[2]);
        }else if(strcmp(argv[1],"-w") == 0) {
            words(argv[2]);
        }else if(strcmp(argv[1],"-l") == 0) {
            lines(argv[2]);
        }else if(strcmp(argv[1],"-a") == 0) {
            mores(argv[2]);
        }else {
            printf("\'%s\'�������\n",argv[1]);
            printf("��ͨ�� help�����鿴��ʹ������\n");
        }
    }else {
        printf("ȱ�ٲ���\n");
        printf("��ͨ�� help�����鿴��ʹ������\n");
    }
    return 0;
}
/*
    ������
        name ��ѯ���ļ���
    ���أ�
        count �ļ��е��ַ��� ��������ʾ�ַ��Ͳ�����ʾ�ַ�
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
    ������
        name ��ѯ���ļ���
    ���أ�
        count �ļ��еĵ����� ָ����ǰ��ո��ֻ����ĸ�Ĵ�
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
    if((fp = fopen(name,"r")) == NULL ){
        printf("error: cannot to find the file or to open this file.\n");
        count[0] = -1;
    }
    else {
        while((ch = fgetc(fp)) != EOF) {
            if(ch == '/') { //������һ��/
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
            }else if(ch >'\x20'){   //��֪������ʲô�����bug����
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
