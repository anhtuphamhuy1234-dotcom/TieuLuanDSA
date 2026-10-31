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
typedef struct treeNode{
	Sach data ;
	struct treeNode *right ;
	struct treeNode *left ;
}treeNode;
treeNode *root = NULL ;
typedef struct stackNode {
    Sach data;
    struct stackNode *next;
} StackNode;
StackNode *top = NULL;
treeNode *taoNodeCay(Sach s){
	treeNode *p =(treeNode*)malloc(sizeof(treeNode)) ;
	if(p == NULL) {
		printf("Khong du bo nho\n") ;
		return NULL ;
	}
	p->data = s ;
	p->left = NULL ;
	p->right = NULL ;
	return p ;
}
treeNode* themVaoCay(treeNode *root, Sach s) {
    if (root == NULL) {
        return taoNodeCay(s) ;
    }
    int cmp = strcmp(s.maSach, root->data.maSach) ;
    if (cmp < 0) {
        root->left = themVaoCay(root->left, s) ;
    } else if (cmp > 0) {
        root->right = themVaoCay(root->right, s) ;
    }
    return root ;
}
void xuatDanhSachCay(treeNode *root) {
    if (root == NULL) {
        return ;
    }
    xuatDanhSachCay(root->left);
    printf("%-10s | %-30s | %-20s | %-10d | %-10d\n",
           root->data.maSach,
           root->data.tenSach,
           root->data.tacGia,
           root->data.namXuatBan,
           root->data.soLuong) ;
    xuatDanhSachCay(root->right) ;
}
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
        root = themVaoCay(root, s);
    }
    fclose(f) ;
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
	root = themVaoCay(root, s);
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
void push(StackNode **top, Sach s) {
    StackNode *p = (StackNode*)malloc(sizeof(StackNode));
    if (p == NULL) {
        printf("Khong du bo nho!\n");
        return;
    }
    p->data = s;
    p->next = *top;
    *top = p;
    printf("Them sach vao Stack thanh cong!\n");
}
void pop(StackNode **top) {
    if (*top == NULL) {
        printf("Stack dang rong!\n");
        return;
    }
    StackNode *temp = *top;
    printf("Da xoa sach: %s - %s\n",
           temp->data.maSach,
           temp->data.tenSach);
    *top = temp->next;
    free(temp);
}
void suaSachStack(StackNode *top) {
    char ma[10];
    printf("Nhap ma sach can sua: ");
    scanf("%9s", ma);
    StackNode *p = top;
    while (p != NULL) {
        if (strcmp(p->data.maSach, ma) == 0) {
            getchar();
            printf("Nhap ten sach moi: ");
            scanf("%49[^\n]", p->data.tenSach);
            getchar();
            printf("Nhap tac gia moi: ");
            scanf("%49[^\n]", p->data.tacGia);
            printf("Nhap nam xuat ban moi: ");
            scanf("%d", &p->data.namXuatBan);
            printf("Nhap so luong moi: ");
            scanf("%d", &p->data.soLuong);
            printf("Sua sach trong Stack thanh cong!\n");
            return;
        }
        p = p->next;
    }
    printf("Khong tim thay sach co ma %s!\n", ma);
}
void hienThiStack(StackNode *top) {
    if (top == NULL) {
        printf("Stack dang rong!\n");
        return;
    }
    printf("\n========== DANH SACH SACH TRONG STACK ==========\n");
    StackNode *p = top;
    while (p != NULL) {
        printf("Ma sach: %s | Ten sach: %s | Tac gia: %s"
               " | Nam XB: %d | So luong: %d\n",
               p->data.maSach,
               p->data.tenSach,
               p->data.tacGia,
               p->data.namXuatBan,
               p->data.soLuong);
        p = p->next;
    }
    printf("================================================\n");
}
void thongKeCay(treeNode *root, int *soDauSach, int *tongSoLuong) {
    if (root == NULL) {
        return;
    }
    (*soDauSach)++;
    *tongSoLuong += root->data.soLuong;
    thongKeCay(root->left, soDauSach, tongSoLuong);
    thongKeCay(root->right, soDauSach, tongSoLuong);
}
void hienThiThongKeCay(treeNode *root) {
    int soDauSach = 0;
    int tongSoLuong = 0;
    thongKeCay(root, &soDauSach, &tongSoLuong);
    printf("\n========== THONG KE DU LIEU CAY BST ==========\n");
    printf("Tong so dau sach       : %d\n", soDauSach);
    printf("Tong so luong sach     : %d\n", tongSoLuong);
    printf("==============================================\n");
}
int main() {
    Node *head = NULL;
    int luaChon;
    do {
        printf("\n================ PHAN MEM QUAN LY THU VIEN ================\n");
        printf("1. Nhap danh sach\n");
        printf("2. Tim kiem phan tu\n");
        printf("3. Doc file .txt\n");
        printf("4. Thong ke du lieu\n");
        printf("5. Them phan tu moi\n");
        printf("6. Hien thi danh sach\n");
        printf("7. Xoa phan tu\n");
        printf("8. Sap xep danh sach (Theo Nam XB)\n");
        printf("9. Xuat danh sach cay BST\n");
        printf("10. Them sach vao Stack\n");
        printf("11. Xoa sach tren Stack\n");
        printf("12. Sua sach trong Stack\n");
        printf("13. Hien thi Stack\n");
        printf("14. Thong ke du lieu cay BST\n");
        printf("0. Thoat chuong trinh\n");
        printf("===========================================================\n");
        printf("Chon chuc nang (0-14): ");
        scanf("%d", &luaChon);
        switch (luaChon) {
            case 1:
                themSach(&head);
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
                break;
            }
            case 3: {
                char fileName[50];
                printf("\nNhap ten file (vd: dssach.txt): ");
                scanf("%s", fileName);
                docFile(&head, fileName);
                break;
            }
            case 4:
                printf("\nThong ke du lieu:\n");
                thongKe(head);
                break;
            case 5:
                themSach(&head);
                break;
            case 6:
                hienThiDanhSach(head);
                break;
            case 7:
                xoaSach(&head);
                break;
            case 8:
                sapXepSach(head);
                hienThiDanhSach(head);
                break;
            case 9:
                xuatDanhSachCay(root);
                break;
            case 10: {
            Sach s;
            printf("Nhap ma sach: ");
            scanf("%9s", s.maSach);
            getchar();
            printf("Nhap ten sach: ");
            scanf("%49[^\n]", s.tenSach);
            getchar();
            printf("Nhap tac gia: ");
            scanf("%49[^\n]", s.tacGia);
            printf("Nhap nam xuat ban: ");
            scanf("%d", &s.namXuatBan);
            printf("Nhap so luong: ");
            scanf("%d", &s.soLuong);
            push(&top, s);
             break;
        }
            case 11:
            pop(&top);
            break;
            case 12:
            suaSachStack(top);
            break;
            case 13:
            hienThiStack(top);
            break;
            case 14:
            hienThiThongKeCay(root);
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
