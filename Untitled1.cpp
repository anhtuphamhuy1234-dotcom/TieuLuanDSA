#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	char maSach[10] ;
	char tenSach[50] ;
	char tacGia[50] ;
	int namXuatBan ;
	int soLuong ;
}Sach;
typedef struct node {
	Sach data ;
	struct node *next ;
}Node;
Node *head = NULL ;
Node* taoNode (Sach s){
	Node *p = (Node*)malloc(sizeof(Node)) ;
	if(p == NULL){
		printf("Khong du bo nho\n") ;
		return NULL ;
	}
	p->data = s ;
	p->next = NULL ;
	return p ;
}
void themCuoi(Node **head , Sach s){
	Node *p = taoNode(s) ;
	if(p == NULL) return ;
	if(*head == NULL){
		*head = p ;
	} else {
		Node *temp = *head ;
		while (temp->next != NULL){
			temp = temp->next ;
		}
		temp->next = p ;
	}
}
void docFile(Node **head , char *filename){
	FILE *f = fopen(filename , "r") ;
	if(f == NULL){
		printf("Khong mo duoc file\n") ;
		return ;
	}
	Sach s ;
	 while (fscanf(f, "%19[^|]|%99[^|]|%49[^|]|%d|%d\n",
                  s.maSach,
                  s.tenSach,
                  s.tacGia,
                  &s.namXuatBan,
                  &s.soLuong) == 5) {

        themCuoi(head, s);
    }
    fclose(f) ;
}
void xuatDanhSach(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("Ma sach: %s\n", temp->data.maSach);
        printf("Ten sach: %s\n", temp->data.tenSach);
        printf("Tac gia: %s\n", temp->data.tacGia);
        printf("Nam XB: %d\n", temp->data.namXuatBan);
        printf("So luong: %d\n", temp->data.soLuong);
        printf("----------------------\n");
        temp = temp->next;
    }
}
Node* timSach(Node *head , char *ma){
	Node *p = head ;
	while(p != NULL){
		if(strcmp(p->data.maSach , ma) == 0){
			return p ;
		}
		p = p->next ;
	}
	return NULL ;
}
void themSach(Node **head) {
	Sach s;
	printf("\n=== THEM SACH MOI ===\n");	
		do {
		printf("Nhap ma sach: ");
		scanf("%s", s.maSach);
		if(timSach(*head, s.maSach) != NULL) {
			printf("Loi! Nhap lai ma khac. \n");
		}
	}  while(timSach(*head, s.maSach) != NULL);
	getchar();
	printf("Nhap ten sach: ");
	scanf("%[^\n]" , s.tenSach);
	getchar();
	printf("Nhap tac gia: ");
	scanf("%[^\n]" , s.tacGia);
	getchar();
	printf("Nhap nam xuat ban: ");
    scanf("%d", &s.namXuatBan);
    printf("Nhap so luong: ");
    scanf("%d", &s.soLuong);
	themCuoi(head, s);
	printf("-> Them sach thanh cong! \n");
}

