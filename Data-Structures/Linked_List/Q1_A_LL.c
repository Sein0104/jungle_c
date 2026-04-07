//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{	
	int item;                // 이 노드가 실제로 저장하는 정수 값
	struct _listnode *next;  // 다음 노드를 가리키는 포인터. 마지막 노드는 NULL
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;        // 현재 연결 리스트 안에 들어 있는 노드 개수
	ListNode *head;  // 연결 리스트의 첫 번째 노드를 가리키는 포인터
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

// Q1에서 네가 직접 구현해야 하는 함수.
// 정렬 상태를 유지하면서 item을 넣고, 들어간 index를 반환해야 한다.
int insertSortedLL(LinkedList *ll, int item);

// 아래 함수들은 이미 주어진 보조 함수들이다.
// 직접 구현 대상이 아니라, insertSortedLL()를 이해하거나 작성할 때 참고/활용하면 된다.
void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;   // 실제 연결 리스트 변수
	int c, i, j;     // c: 메뉴 선택, i: 입력값, j: insertSortedLL의 반환값(index)
	c = 1;

	// 빈 연결 리스트로 시작한다.
	// head가 NULL이면 아직 노드가 하나도 없다는 뜻이다.
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		// 사용자가 고른 메뉴에 따라 다른 작업을 수행한다.
		switch (c)
		{
		case 1:
			// 삽입할 정수를 입력받고, 네가 구현할 insertSortedLL()를 호출한다.
			// 반환값은 "몇 번째 index에 들어갔는지" 또는 실패 시 -1 이다.
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			// 가장 최근에 넣으려고 했던 값(i)과 그 결과 index(j)를 출력한다.
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			// 현재 연결 리스트 전체를 출력한 뒤 메모리를 정리한다.
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			// 프로그램 종료 전에 남아 있는 노드 메모리를 해제한다.
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	/* add your code here */
	ListNode *cur;
	cur = ll->head;
	int index = 0;

	while (cur != NULL && item > cur->item) {
		cur = cur->next;
		index ++;				// 연결리스트 순회
	}
		if (cur != NULL && cur->item == item) {			// 중복이면 -1
			return -1;
			}	
		insertNode(ll, index, item);	// 자기보다 큰 값 만나거나 끝까지 안 만나면 맨 뒤에 삽입
		return index;	// index 를 반환하라고 함
	}		

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;  // 현재 보고 있는 노드
	if (ll == NULL)
		return;
	cur = ll->head; // 항상 첫 노드부터 시작해서 next를 따라가며 출력

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		// 현재 노드의 값을 출력하고 다음 노드로 이동
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head; // 현재 지울 노드
	ListNode *tmp;            // next를 잠깐 저장해 둘 임시 포인터

	// 노드를 free한 뒤에는 그 노드의 next에 접근할 수 없으므로,
	// 먼저 tmp에 다음 노드를 저장해 두고 현재 노드를 해제한다.
	while (cur != NULL){
		tmp = cur->next;
		free(cur);		// malloc ㄴㄴ면 free 필요 ㄴㄴ  + heap 은 개발자 관리영역 , stack 는 끄면 자동으로 삭제
		cur = tmp;
	}

	// 모두 지웠으니 빈 리스트 상태로 되돌린다.
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp; // head부터 index번째 노드까지 이동할 때 사용할 포인터

	// index가 범위를 벗어나면 찾을 수 없으므로 NULL 반환
	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	// 빈 리스트이거나 비정상 index면 실패
	if (temp == NULL || index < 0)
		return NULL;

	// index가 0이면 head를 그대로 반환
	// index가 1 이상이면 next를 따라가며 이동
	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	// pre: 새 노드 앞에 있는 노드
	// cur: 새 노드 뒤에 오게 될 노드

	// 넣을 위치가 말이 안 되면 실패
	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;                    // 원래 첫 노드를 잠깐 저장
		ll->head = malloc(sizeof(ListNode)); // 새 노드를 만들고
		ll->head->item = value;              // 값 저장
		ll->head->next = cur;                // 새 노드의 next가 기존 첫 노드를 가리키게 함
		// 즉, "맨 앞 삽입"은 head를 새 노드로 바꾸는 작업이다.
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;                      // 원래 index 위치에 있던 노드
		pre->next = malloc(sizeof(ListNode)); // 새 노드 생성
		pre->next->item = value;              // 값 저장
		pre->next->next = cur;                // 새 노드가 원래 노드를 가리키게 연결
		// 결과적으로 pre -> 새 노드 -> cur 형태가 된다.
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// 지울 수 있는 가장 큰 index는 size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next; // 두 번째 노드를 잠깐 저장
		free(ll->head);       // 원래 첫 노드 제거
		ll->head = cur;       // head를 두 번째 노드로 바꿔서 리스트를 이어 줌
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;       // 실제로 삭제할 노드
		pre->next = cur->next; // 삭제할 노드를 건너뛰도록 연결 수정
		free(cur);             // 노드 메모리 해제
		ll->size--;
		return 0;
	}

	return -1;
}
