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
void thongKe(Node *head){
	int soDauSach = 0 ;
	int tongSL = 0 ;
	Node *p = head ;
	while(p != NULL){
		soDauSach++ ;
		tongSL += p->data.soLuong ;
		p = p->next ;
	}
	printf("So dau sach : %d\n" , soDauSach) ;
	printf("Tong so luong : %d\n" , tongSL) ;
}
//Phuc
void hienThiDanhSach(Node *head) {
	if(head == NULL) {
		printf("\n==============================");
		printf("          DANH SACH HIEN TAI DANG RONG (KHONG CO SACH)!    \n");
		printf("\n==============================");
		return;
	}
	int stt = 1;
	Node *temp = head;
	
	printf("\n================================ DANH SACH SACH HIEN TAI ================================\n");
	printf("%-5s | %-10s | %-30s | %-20s | %-8s | %-8s\n",
			"STT", "Ma Sach", "Ten Sach", "Tac Gia", "Nam XB", "So Luong");
    printf("-----------------------------------------------------------------------------------------\n");

    while (temp != NULL) {
        printf("%-5d | %-10s | %-30s | %-20s | %-8d | %-8d\n", 
               stt++, 
               temp->data.maSach, 
               temp->data.tenSach, 
               temp->data.tacGia, 
               temp->data.namXuatBan, 
               temp->data.soLuong);
        temp = temp->next;
    }
    printf("=========================================================================================\n");
}
void xoaSach(Node **head) {
    if (*head == NULL) {
        printf("\nDanh sach hien tai dang rong! Khong the xoa.\n");
        return;
    }
    char ma[10];
    printf("\n=== XOA SACH ===");
    printf("\nNhap ma sach can xoa: ");
    scanf("%s", ma);
    Node *temp = *head;
    Node *prev = NULL;
    if (temp != NULL && strcmp(temp->data.maSach, ma) == 0) {
        *head = temp->next;
        free(temp);
        printf("-> Xoa sach co ma '%s' thanh cong!\n", ma);
        return;
    }
    while (temp != NULL && strcmp(temp->data.maSach, ma) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("-> Khong tim thay sach co ma '%s' de xoa!\n", ma);
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf("-> Xoa sach co ma '%s' thanh cong!\n", ma);
}
void sapXepSach (Node *head) {
	if(head == NULL || head->next == NULL ) {
		printf("\n Danh sach rong hoac chi co 1 sach, khong can sap xep! \n");
		return;
	}
	for(Node *i = head; i->next != NULL; i = i->next) {
		for(Node *j = i->next; j != NULL; j = j->next) {
			if(i->data.namXuatBan > j->data.namXuatBan) {
				Sach temp = i->data;
				i->data = j->data;
				j->data = temp;
			}
		}
	}
	printf("\n -> Da sap xep theo nam xuat ban thanh cong!\n");
}
char lichSu[100][100];
int soThaoTac = 0;

void ghiLichSu(char *thaoTac) {
	if(soThaoTac < 100) {
		strcpy(lichSu[soThaoTac], thaoTac);
		soThaoTac++;
	}
}


void hienThiLichSu() {
	if(soThaoTac == 0) {
		printf("\n Chua co thao tac nao duoc thuc hien! \n");
		return;
	}
	printf("\n================ LICH SU THAO TAC ================\n");
	for (int i = 0; i < soThaoTac;i++) {
		printf("%d. %s\n", i + 1, lichSu[i]);
	}
	printf("==================================================\n");
}

int main() {
    Node *head = NULL;
    int luaChon;

    do {
        printf("\n================ PHAN MEM QUAN LY THU VIEN ================\n");
        printf("1. Nhap danh sach\n");
        printf("2. Tim kiem phan tu\n");
        printf("3. Cap nhat thong tin\n");
        printf("4. Doc file .txt\n");
        printf("5. Thong ke du lieu\n");
        printf("6. Them phan tu moi\n");
        printf("7. Hien thi danh sach\n");
        printf("8. Xoa phan tu\n");
        printf("9. Sap xep danh sach (Theo Nam XB)\n");
        printf("10. Lich su thao tac\n");
        printf("0. Thoat chuong trinh\n");
        printf("===========================================================\n");
        printf("Chon chuc nang (0-10): ");
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                themSach(&head);
                ghiLichSu("Nhap danh sach");
                break;
            case 2: {
                char ma[10];
                printf("\nNhap ma sach can tim: ");
                scanf("%s", ma);
                Node *p = timSach(head, ma);
                if (p != NULL) {
                    printf("-> Tim thay: Ma %s - Ten: %s\n", p->data.maSach, p->data.tenSach);
                } else {
                    printf("-> Khong tim thay sach!\n");
                }
                ghiLichSu("Tim kiem phan tu");
                break;
            }
            case 3:
                printf("\nCap nhat thong tin sach\n");
                ghiLichSu("Cap nhat thong tin");
                break;
            case 4: {
                char fileName[50];
                printf("\nNhap ten file (vd: dssach.txt): ");
                scanf("%s", fileName);
                docFile(&head, fileName);
                ghiLichSu("Doc file .txt");
                break;
            }
            case 5:
                printf("\nThong ke du lieu:\n");
                thongKe(head);
                ghiLichSu("Thong ke du lieu");
                break;
            case 6:
                themSach(&head);
                ghiLichSu("Them phan tu moi");
                break;
            case 7:
                hienThiDanhSach(head);
                ghiLichSu("Hien thi danh sach");
                break;
            case 8:
                xoaSach(&head);
                ghiLichSu("Xoa phan tu");
                break;
            case 9:
                sapXepSach(head);
                hienThiDanhSach(head);
                ghiLichSu("Sap xep danh sach");
                break;
            case 10:
                hienThiLichSu();
                break;
            case 0:
                printf("\nDa thoat chuong trinh. Tam biet!\n");
                break;
            default:
                printf("\nLua chon khong hop le! Vui long chon lai.\n");
        }
    } while (luaChon != 0);

    return 0;
}