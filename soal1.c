/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2024/2025
 *   Modul               : 4
 *   Hari dan Tanggal    : Rabut, 6 Mei 2026
 *   Nama (NIM)          : Afdhal Razaq (13224004)
 *   Nama File           : soal1.c
 *   Deskripsi           : membuat DSA queue, lalu memberikan keluaran urutan antrian beserta waktu total tunggu untuk pasien terkahir
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node { //struktur node
    char id[50];
    int time;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct Queue { //structur queue
    Node *front;
    Node *rear;
}Queue;

Node* createNode(char *id, int time) { //inisialisasi node
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->id, id);
    newNode->time = time;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

Queue* createQueue(){ //inisialisasi queue
    Queue *newQueue = (Queue *)malloc(sizeof(Queue));
    newQueue->front = NULL;
    newQueue->rear = NULL;
    return newQueue;
}

int isEmpty(Queue *queue){
    return queue->front == NULL;//cek apakah queue kosong
}



void enqueu(Queue *queue, char *id, int time){ //fungsi penambahan antrian pasien
    Node *newNode = createNode(id, time); 

    if (queue->rear == NULL){
        queue->front = newNode;
        queue->rear = newNode;
        return;
    }
    
    newNode->prev = queue->rear;
    queue->rear->next = newNode;
    queue->rear = newNode;
}

void dequeu(Queue *queue){//keluarkan pasien dari antrian
    if(isEmpty(queue)){
        return;
    }

    Node *temp = queue->front;
    queue->front = queue->front->next;
    queue->front->prev = NULL;

    if (queue->front == NULL){
        queue->rear = NULL;
    }

    free(temp);
}

int idx(Queue *queue){//cek ada berapa banyak pasien/idx
    int count = 0;
    Node *temp = queue->front;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }

    return count;
}

void printHasil(Queue *queue){//print hasil sesuai format
    if(!isEmpty(queue)){
        printf("ORDER");
        Node *temp = queue->front;
        while(temp != NULL){
            printf(" %s", temp->id);
            temp = temp->next;
            Node *temp2 = queue->front;
        }
        printf("\n");
        printf("WAIT ");
        int last = idx(queue);
        int total = 0;
        for(int i = 0; i < last -1; i++){
            temp = queue->front;
            for(int j = 0; j <= i; j++){
                total = total + temp->time;
                temp = temp->next;
            }
        }
        printf("%d\n", total);
    }

    
}

int main(){
    int n;
    scanf("%d", &n);
    Queue *q = createQueue();

    char id[50]; 
    int time = 0;
    int total = 0;

    for(int i =0; i < n; i++){
        scanf("%s", id);
        scanf("%d", &time);
        
        enqueu(q, id, time);
    }
    
    printHasil(q);

    
    return 0;
}


