#include <iostream>

template<typename T>
class List {
private:

	struct Node {
		// ����������� ����, next=nullptr ��� ������� ��� ���� ��� ������ ����
		Node(const T& t) : data(t), next(nullptr) {} 
		T data;																	//�������� � ����
		Node* next;																//��������� �� ��������� ���� �������������� ����� ����
		
		Node& operator++() {
			next = next->next;
			return *this;
		}
	};

	Node* head;																	//��������� �� ������ ������� � ������ 
	Node* tail;																	//��������� �� ��������� ���� � ������
	size_t size;

public:

	// ������� ������ ����������� �� ������
	class Iterator { 
	public:
		Node* current = nullptr;
		Iterator(Node* node) {	//����������� 
			current = node;
		}									
		
		T& operator*() {														//�������������� (��������� data �� ���������)
			return current->data;												//������� � ���������, ��� �������� data � "�������" ��
		}

		Iterator& operator++() {												//������� ��������� � ���������� ����
			if(current){														// �������� �� ��, ��� ������ �� ����
				current = current->next;										// ���������� current �� ��������� ����
			}
			return *this;
		}

		bool operator !=(const Iterator& other) const {
			return current != other.current;
		}

		bool operator ==(const Iterator& other) const {
			return current == other.current;
		}
	};

	List() : head(nullptr), tail(nullptr), size(0) {}						//�����������
	
	List(const List& list) : head(nullptr), tail(nullptr), size(0) { //����������� �����������
		for (auto it = list.begin(); it != list.end(); ++it) {           //���������� ���������� �� ���� ����� ���������� ������
			append(*it);												//�� ������ ���� ��������� ����� ���� � ��������� ������
		}
		size = list.size;
	}

	List(List&& list) noexcept {
		head = list.head;
		tail = list.tail;
		size = list.size;
		list.head = nullptr;
		list.tail = nullptr;
		list.size = 0;
	}

	~List() { //����������
		clear();
	}

	List& operator=(const List& list) {										//�������� ������������
		if (this != &list) {
			size = list.size;
			clear();
			for (auto it = list.begin(); it != list.end(); ++it) {           //���������� ���������� �� ���� ����� ���������� ������
				append(*it);												//�� ������ ���� ��������� ����� ���� � ��������� ������
			}
		}
		return *this;
	}

	bool operator==(const List& list) const noexcept {
		if (this == &list) {
			return 1;
		}
		if (size != list.size) {
			return 0;
		}
		auto it0 = begin();
		auto it1 = list.begin();
		for (int i = 0; i < size; i++) {
			if (*it0 != *it1) {
				return 0;
			}
			++it0;
			++it1;
		}
		return 1;
	}

	List& operator=(List&& list) noexcept{
		if (this != &list) {
			clear();
			head = list.head;
			list.head = nullptr;
			tail = list.tail;
			list.tail = nullptr;
			size = list.size;
			list.size = 0;
		}
		return *this;
	}

	T& operator[](size_t ind) {			//����� � ���������
		if (size == 0) throw std::out_of_range("list is empty");						//�������� �� ������ ������
		if (ind < 0 || ind > size - 1) throw std::out_of_range("incorrect index");			//�������� �� ������������ ����� �������

		Iterator it(head);												//������ i-����� �� ������� �����, ������ ��� ������� ��������
		for (int i = 0; i < ind; i++) {
			++it;
		}
		return *it;													//���������� date ���������
	}

	const T& operator[](size_t ind) const {       
		if (size == 0) throw std::out_of_range("list is empty");						//�������� �� ������ ������
		if (ind < 0 || ind > size - 1) throw std::out_of_range("incorrect index");			//�������� �� ������������ ����� �������

		Iterator it(head);
		for (int i = 0; i < ind; i++) {
			it++;
		}
		return *it;
	}

	Node* getTail() const { //��������� ��������� ��������
		return tail;
	}

	Node* getHead() const { //��������� ��������� ��������
		return head;
	}

	void append(const T& value) {					//���������� ���� � ������, ��� value �������� ��������
		Node* newNode = new Node(value);			// ������� ����� ��������� - ���� ������ � �������� � newNode ��������� �� ��� ���������
		if (!head) {								// �������� �� ��, ��� ��� ������ ����������� ����
			head = newNode;
			tail = newNode;
			// �.� ���� ���� head = tail
		}
		else {										// ���� ��� �� ������ ����, �� ������ ������� ����� ����
			tail->next = newNode;					//�������� ������ � next ����������� ���� ����� -> � �������� ���� ������ �� �����(����) ����
			tail = newNode;							// �������, ��� ����� ��� ������� ����
		}
		size++;
	}

	void remove(const T& value) {					// �������� ���� � ��������� value
		//�������� �� ������ ������
		if (!head) { 
			return;
		}

		//�������� "�� ������"
		if (head->data == value) {
			Node* tmp = head;						//�������� �� ��������� ����������, ����� �� �������� ������ ��� ��������
			head = head->next;						//������������ head �� ��������� �� ��������� ����
			delete tmp;								//� ������ ����� ������� ������ head
			size--;									//-1 � �������
			return;
		}

		for (Node* current(head); current != tail; current = current->next) {				
			if (current->next->data == value) {
				Node* tmp = current->next;						//����� �� �������� ������ ��� ��������
				current->next = current->next->next;	    //������������ ��������� next ����� ����(����� ��������� �������)
				
				Iterator ITtmp(tmp);
				Iterator ITtail(tail);
				if (ITtmp == ITtail) {									//���� ����� ���� ��� �������, �� �������� ����� �����������(current)
					tail = current;
				}
				delete tmp;											//����������� ������
				size--;
				return;
			}
		}
	}
	
	void remove() { //�������� head
		//�������� �� ������ ������
		if (!head) {
			return;
		}

		Node* tmp = head->next;
		Iterator ITtmp(tmp);
		if (ITtmp == nullptr) { //��� �������� ���������� ����, ����� ������� ��� tail ��� nullptr
			tail = nullptr;
		}
		delete head;
		head = tmp;
		size--;
	}

	void insert(const T& value, int place) { //������� � ���� � ����� ����� ������
		if (place < 0 || place > size) { //�������� �� ������
			throw std::out_of_range("place is incorrect");
		}

		if (place == 0) {				//���� ������� � ������, �� ���������� ��� ��������� �������
			insert(value);
			return;
		}

		//����� ����� ���� ������������ ��������, �� � �� ����
		Node* current = head;					//������� ����������� ���������
		for (int i = 0; i < place - 1; i++) {		//��������  
			current = current->next;
		}
		Node* tmp = current->next;					//��������� �� ��������� ���������� ��������� �� ������� next
		Node* newNode = new Node(value);			//������� ����� ����
		current->next = newNode;					//�������������� ������� next �� ����� ����
		newNode->next = tmp;						//���������� next �� ������ ��� ��������� �� ��������� ����� ������ ����
		size++;
	}

	void insert(const T& value) {	//������� � ������ ������
		Node* newNode = new Node(value);											//������� ����� ����
		if (!head) {																//�������� �� ������
			head = newNode;
			tail = newNode;
			size++;
			return;
		}
		else {																	//������� ����� ������
			Node* tmp = head;													//���������� ��������� �� ������ ������
			head = newNode;														//�������� ����� ������ ������ head(���, ������ ������)
			head->next = tmp;													//������ ������ ������ ������ head->next(������ �������)
		}
		size++;
	}

	void clear() { 
		Node* current = head;												// ������ ������� ��� �������� ��� ����� ������
		while (current) {													//���� current �� ������ ����� (current = nullptr)
			Node* nextNode = current->next;									//��������� ��������� �� ��������� ����� ����
			delete current;													//������� ������� ����, �� ����� ��������� �� ���������
			current = nextNode;												// �������� �������� ���������� ����
		}
		tail = nullptr;
		head = nullptr;
		size = 0;
	}

	Iterator search(const T& value) {						//����� ��������(���������� ��������� �� ���� � ���� ��������)
		for (Iterator current(head); current != end(); ++current) {
			if (value == *current) {
				return current;
			}
		}
		return nullptr;
	}

	size_t getSize() const noexcept {					//��������� ������� ������
		return size;
	}

	bool empty() {										//�������� �� ������� ������
		if (size == 0) {
			return 1;
		}
		return 0;
	}

	Iterator begin() const {						// ��������� ��������� �� ������
		return Iterator(head);
	}

	Iterator end() const {							// ��������� ��������� �����
		return Iterator(nullptr);
	}
	
	void printList() {
		for (Iterator it = begin(); it != end(); ++it) {       //���������� ���������� �� ����� ������
			std::cout << *it << " => ";							//������� �������� ���������
		}
		std::cout << "nullptr";									//������� �� �����
	}

	//��������� ����� � ������
	friend std::istream& operator>>(std::istream& istr, List& ls)
	{
		for (Iterator it = ls.begin(); it != ls.end(); ++it) {
			std::cin >> *it;
		}
		return istr;
	}

	friend std::ostream& operator<<(std::ostream& ostr, List& ls)
	{
		for (Iterator it = ls.begin(); it != ls.end(); ++it) {
			std::cout << *it << std::endl;
		}
		return ostr;
	}
};
//��� ����� ����������� ����