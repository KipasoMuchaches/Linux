#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct List{
	char data[512]; // поле данных
	struct List *next; // указатель на след элемент
};

typedef struct List *node; //Создание ссылки узла списка

// Создание корневого узла списка, поле указателя на след элемент будет равен NULL, то есть элемента со зн-ем NULL - посл элемент
node createNode(){
	node temp; // объявления узла
	temp = (node)malloc(sizeof(struct List)); // выделение памяти под корень списка
	temp->next == NULL; // последний узел списка(ссылка на след значение т.к NULL)
	return temp; // возвращение нового узла
}

// head - Указатель на узел, после которого происходит добавление,
// value - Данные для добавляемого узла.
node addNote(node head, char value[512]){
	node temp,p; // объявления двух узлов
	temp = createNode(); // создание узла
	strcpy(temp->data, value); // копирование данных из корня и отсюда
	if(head == NULL){ // если этот узел посл, то он станет новым
		head = temp;
	}
	else{ 
		p = head; //если же не посл то происход замена верхнего элемента
		while(p->next != NULL){ // проход по спику, пока р не станет посл(пока не станет NULL)
			p = p->next;
		}
		p->next = temp; // доавление нового узла в конец
	}
	return head; // адрес добавляемого узла
}

node NodeById(int index, node head){
	node n = head;
	for(size_t i = 0; i < index; i++){
		n = n->next; // проходит по списку пока не дойдет до посл индекса
	}
	return n;
}

node DeleteById(int index, node head){

	if(index <= 0) return head; // если вводим 0, то выводит не измененный список(если были 3 записи, то так же выведит 3 записи)
	if(index == 1 && head->next != NULL) return head->next;// если удаляем первый элемент и он не является последним то head начинает выводит со след элемента не считая предыдущий(1, 2, 3 = 2, 3), а т.к кол-во записей понижается (count--), будет (1, 2, 3 = 1, 2)
	NodeById(index-1, head)->next = NodeById(index+1, head);
	//взяли текущий индекс(очстили его), взяли предыдущий(index-1) и создали от него ссылку на следующий(-> next (index+1)), тем самым мы просто визуально удалили этот элемент но в памяти он сохранился
	return head;
}

void changeON(char *str, int mod){
	if(mod == 1){
		for(size_t i = 0; i < 512; i++){
			if(str[i] == '\n'){
				str[i] == ';';
				strcat(str, " ");
				break;
			}
		}
	}
	else if(mod == -1){
		for(size_t i = 0; i < 512; i++){
			if(str[i] == '\n'){ // если был выполнен переход на след строку, то этот символ является последним(\0)
				str[i] == '\0';
				break;
			}
		}
	}
}

int main(void)
	{
		node head = createNode(); //head - создание узла
		char string1[512]; // добавления ввода для нашей бд 
		char string2[512];
		char string3[512];
		char string4[512];
		char string5[512];
		int check = 1;
		int count = 0; // кол-во записей
		while(check == 1){
			printf("Выберете необходимую функцию:\n\n1. Добавить\n2. Удалить\n3. Изменить\n4. Вывести список\n5. Выйти\n\n");
			
			char n = getchar(); // ввод данных
			while(n == '\n') n = getchar(); // при переходе на след строку происходит ввод данных
			switch(n){
			//Добавить
				case '1': {
					getchar();
					printf("\nВведите ФИО брачующегося: ");
					
					fgets(string1, 512, stdin); // считывает символы и сохр в виде ст
					//string1 - массив, в который сохраняются считанные cимволы(char)
					// 512 - макс кол-во символов, stdin - считываются символы
					
					printf("\nВведите ФИО брачующей: ");
					fgets(string2, 512, stdin);
					printf("\nВведите дату: ");
					fgets(string3, 512, stdin);
					printf("\nВведите возраст брачующегося: ");
					fgets(string4, 512, stdin);
					printf("\nВведите возраст брачующегося: ");
					fgets(string5, 512, stdin);
					
					// работает до тех пор пока не будет произведен переход на след строку и так по всем строкам ввода. Этот символ будет равен пустоте
					for(size_t i = 0; i < 512; i++){
						if(string1[i] == '\n'){
							string1[i] == ' ';
							break;
						}
					}
					for(size_t i = 0; i < 512; i++){
						if(string2[i] == '\n'){
							string2[i] == ' ';
							break;
						}
					}
					for(size_t i = 0; i < 512; i++){
						if(string3[i] == '\n'){
							string3[i] == ' ';
							break;
						}
					}
					for(size_t i = 0; i < 512; i++){
						if(string4[i] == '\n'){
							string4[i] == ' ';
							break;
						}
					}
					for(size_t i = 0; i < 512; i++){
						if(string5[i] == '\n'){
							string5[i] == ' ';
							break;
						}
					}
					
					strcat(string1, string2);//в string1 добавляет значения из string2, и так с каждое последующей строкой
					strcat(string1, string3);
					strcat(string1, string4);
					strcat(string1, string5);
					printf("\n%s\n\n", string1);// выводим все эти элементы из str1
					addNote(head, string1); // Указатель на узел, после которого происходит добавление(head) и добавлем данные(str1) 
					count++; // увеличиваем кол-во записей
				}
				break;
				//Удалить
				case '2': {
					int i = 0;
					printf("Выбере элемент:	"); scanf("%d", &i);
					while(i > count || i <= 0){
						printf("Невозможный ввод, повторите попытку: ");
						scanf("%d", &i);
						}
					head = DeleteById(i, head);
					count--; // уменьшается кол-во записей
				}
				break;
				//Изменить
				case '3' : 
					printf("\nВведите номер записи: ");
      		int x = 0;
      		scanf("%d", &x);
      		while(x > count || x <= 0){
						printf("Невозможный ввод, повторите попытку: ");
						scanf("%d", &x);
						}
      		
      		getchar();
					printf("\nВведите ФИО брачующегося: ");
					fgets(string1, 512, stdin); // считывает символы и сохр в виде ст
					//string1 - массив, в который сохраняются считанные cимволы(char)
					// 512 - макс кол-во символов, stdin - считываются символы
					
					printf("\nВведите ФИО брачующей: ");
					fgets(string2, 512, stdin);
					printf("\nВведите дату: ");
					fgets(string3, 512, stdin);
					printf("\nВведите возраст брачующегося: ");
					fgets(string4, 512, stdin);
					printf("\nВведите возраст брачующегося: ");
					fgets(string5, 512, stdin);
					
					// работает до тех пор пока не будет произведен переход на след строку и так по всем строкам ввода. Этот символ будет равен пустоте
					for(size_t i = 0; i < 512; i++){
						if(string1[i] == '\n'){
							string1[i] == ' ';
							break;
						}
					}
					for(size_t i = 0; i < 512; i++){
						if(string2[i] == '\n'){
							string2[i] == ' ';
							break;
						}
					}
					for(size_t i = 0; i < 512; i++){
						if(string3[i] == '\n'){
							string3[i] == ' ';
							break;
						}
					}
					for(size_t i = 0; i < 512; i++){
						if(string4[i] == '\n'){
							string4[i] == ' ';
							break;
						}
					}
					for(size_t i = 0; i < 512; i++){
						if(string5[i] == '\n'){
							string5[i] == ' ';
							break;
						}
					}
					
					strcat(string1, string2);//в string1 добавляет значения из string2, и так с каждое последующей строкой
					strcat(string1, string3);
					strcat(string1, string4);
					strcat(string1, string5);
					printf("\n%s\n\n", string1);// выводим все эти элементы из str1
					strcpy(NodeById(x, head) -> data, string1);
					
					// копируем введенные нами ранее значения(string1) в предыдщие, т.е. заменяем предыдущие значения(->data) на те которые прописали сейчас 
				break;
				//Вывод списка
				case '4': {
					node n = head; // говорим что n - создание узла
					n = n->next; // проходим по всему списку
					int i = 1;
					while(n != NULL){ // пока n не последний элемент списка(не нал)
						printf("%d. %s\n", i++, n->data); // выводим нумерацию записи и данные
						n=n->next; // проход по всему списку
					}
					printf("\n");
				}
				break;
				//Выход
				case '5': 
					return 0;
					break;
			}
		}
		
	}
