#include <stdio.h>
#include <string.h>
int chars(char* name);
int words(char* name);
int lines(char* name);
int main(int argc, char* argv[]){
    int num;
    if(strcmp(argv[1],"help") == 0) {
        printf("    -c file.c  �����ļ�file.c���ַ�����\n");
        printf("    -w file.c  �����ļ�file.c�Ĵʵ���Ŀ��\n");
        printf("    -l file.c  �����ļ�file.c��������\n");
    }else if(strcmp(argv[1],"-c") == 0) {
        if((num = chars(argv[2])) >= 0) {
            printf("char: %d\n",num);
        }
    }else if(strcmp(argv[1],"-w") == 0) {
        if((num = words(argv[2])) >= 0) {
            printf("word: %d\n",num);
        }
    }else if(strcmp(argv[1],"-l") == 0) {
        if((num = lines(argv[2])) >= 0) {
            printf("line: %d\n",num);
        }
    }else {
        printf("\'%s\'�������\n",argv[1]);
        printf("��ͨ�� help�����鿴��ʹ������\n");
    }
    return 0;
}
/*
    ������
        name ��ѯ���ļ���
    ���أ�
        count �ļ��е��ַ��� �������з���tab�Ϳո񶼼�����
*/
int chars(char* name){
    FILE *fp;
    int ch;
    int count = 0;
    if((fp = fopen(name,"r")) == NULL ){
        printf("error: cannot to find the file or to open this file.\n");
        return -1;
    }
    else {
        while((ch = fgetc(fp)) != EOF) {
            count++;
        }
    }
    fclose(fp);
    return count;
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
        return -1;
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
        return -1;
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
    return count;
}
