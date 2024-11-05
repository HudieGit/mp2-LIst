#include <iostream>
#include <unordered_map>

template <typename T> class Iterator;

template<typename T>
class List {
private:

	struct Node {
		// конструктор узла, next=nullptr как затычка или если это первый узел
		Node(const T& t) : data(t), next(nullptr) {} 
		T data;																	//хранимое в узле
		Node* next;																//указатель на следующий узел относительного этого узла

	};

	Node* head;																	//указатель на первый элемент в списке 
	Node* tail;																	//указатель на последний узел в списке
	size_t size;

public:

	friend class Iterator<T>;

	List() : head(nullptr), tail(nullptr), size(0) {}						//конструктор
	
	List(const List& list) : head(nullptr), tail(nullptr), size(0) { //конструктор копирования
		for (auto it = list.begin(); it != list.end(); ++it) {           //проходимся итератором по всем узлам пришедшего списка
			append(*it);												//на каждом шаге добавляем новый узел к исходному списку
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

	~List() { //деструктор
		clear();
	}

	List& operator=(const List& list) {										//оператор присваивания
		if (this != &list) {
			size = list.size;
			clear();
			for (auto it = list.begin(); it != list.end(); ++it) {           //проходимся итератором по всем узлам пришедшего списка
				append(*it);												//на каждом шаге добавляем новый узел к исходному списку
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

	T& operator[](size_t ind) {			//сразу с контролем
		if (size == 0) throw std::out_of_range("list is empty");						//проверка на пустой список
		if (ind < 0 || ind > size - 1) throw std::out_of_range("incorrect index");			//проверка на правильность ввода индекса

		Iterator<T> it(head);												//проход i-шками до нужного места, каждый раз сдвигая итератор
		for (int i = 0; i < ind; i++) {
			++it;
		}
		return *it;													//возвращаем date итератора
	}

	const T& operator[](size_t ind) const {       
		if (size == 0) throw std::out_of_range("list is empty");						//проверка на пустой список
		if (ind < 0 || ind > size - 1) throw std::out_of_range("incorrect index");			//проверка на правильность ввода индекса

		Iterator it(head);
		for (int i = 0; i < ind; i++) {
			it++;
		}
		return *it;
	}

	Node* getTail() const { //получение головного элемента
		return tail;
	}

	Node* getHead() const { //получение головного элемента
		return head;
	}

	void append(const T& value) {					//добавления узла в список, где value хранимое значение
		Node* newNode = new Node(value);			// создали новую структуру - узел списка и записали в newNode указатель на эту структуру
		if (!head) {								// проверка на то, что это первый добавленный узел
			head = newNode;
			tail = newNode;
			// т.к один узел head = tail
		}
		else {										// если это не первый узел, то просто создаем новый узел
			tail->next = newNode;					//получили доступ к next предыдущего узла через -> и записали туда ссылку на новый(этот) узел
			tail = newNode;							// указали, что конец это текущий узел
			tail->next = nullptr;
		}
		size++;
	}

	void remove(const T& value) {					// удаление узла с значением value
		//проверка на пустой список
		if (!head) { 
			return;
		}

		//проверка "на голову"
		if (head->data == value) {
			Node* tmp = head;						//записали во временную переменную, чтобы не потерять память при удалении
			head = head->next;						//перезаписали head на указатель на следующий узел
			delete tmp;								//с чистой душой удалили старый head
			size--;									//-1 в размере
			return;
		}

		for (Node* current(head); current != tail; current = current->next) {				
			if (current->next->data == value) {
				Node* tmp = current->next;						//чтобы не потерять память при удалении
				current->next = current->next->next;	    //перекидывает указатель next через один(через удаляемый элемент)
				
				Iterator<T> ITtmp(tmp);
				Iterator<T> ITtail(tail);
				if (ITtmp == ITtail) {									//если вдруг узел был хвостом, то передаем хвост предыдущему(current)
					tail = current;
				}
				delete tmp;											//освобождаем память
				size--;
				return;
			}

		}
		return;
	}
	
	void remove() { //удаление head
		//проверка на пустой список
		if (!head) {
			return;
		}

		Node* tmp = head->next;
		Iterator<T> ITtmp(tmp);
		if (ITtmp == nullptr) { //при удалении последнего нода, нужно сказать что tail уже nullptr
			tail = nullptr;
		}
		delete head;
		head = tmp;
		size--;
	}

	void insert(const T& value, int place) { //вставка в узел в любое место списка
		if (place < 0 || place > size) { //проверка на размер
			throw std::out_of_range("place is incorrect");
		}

		if (place == 0) {				//если вставка в начало, то используем уже сделанную функцию
			insert(value);
			return;
		}

		//здесь можно было использовать итератор, но я не стал
		Node* current = head;					//создаем пробегающий указатель
		for (int i = 0; i < place - 1; i++) {		//проходим  
			current = current->next;
		}
		Node* tmp = current->next;					//сохраняем во временную переменную указатель на текущий next
		Node* newNode = new Node(value);			//создаем новый узел
		current->next = newNode;					//перезаписываем текущий next на новый узел
		newNode->next = tmp;						//записываем next из облака как указатель на следующий после нового узла
		size++;
	}

	void insert(const T& value) {	//вставка в начало списка
		Node* newNode = new Node(value);											//создаем новый узел
		if (!head) {																//проверка на голову
			head = newNode;
			tail = newNode;
			size++;
			return;
		}
		else {																	//создаем новый голову
			Node* tmp = head;													//запоминаем указатель на старую голову
			head = newNode;														//присваем новой голове статус head(ага, головы голова)
			head->next = tmp;													//старая голова теперь просто head->next(второй элемент)
		}
		size++;
	}

	void clear() { 
		Node* current = head;												// первый элемент для удаления это самый первый
		while (current) {													//пока current не станет нулем (current = nullptr)
			Node* nextNode = current->next;									//сохраняем указатель на следующий после узел
			delete current;													//удаляем текущий узел, не теряя указатель на следующий
			current = nextNode;												// передали эстафету следующему узлу
		}
		tail = nullptr;
		head = nullptr;
		size = 0;
	}

	Iterator<T> search(const T& value, size_t number = 1) {						//поиск элемента(возвращает указатель на него в виде итератор)
		size_t counting = 0;
		for (Iterator<T> current(head); current != end(); ++current) {
			if (value == *current && counting == number - 1) {
				return current;
			}
			else if (value == *current) {
				counting++;
			}
		}
		return nullptr;
	}

	size_t getSize() const noexcept {					//получение размера списка
		return size;
	}

	bool empty() {										//проверка на пустоту списка
		if (size == 0) {
			return 1;
		}
		return 0;
	}

	Iterator<T> begin() const {						// получение итератора на начало
		return Iterator<int>(head);
	}

	Iterator<T> end() const {							// получение итератора конец
		return Iterator<int>(nullptr);
	}
	
	void printList() {
		for (Iterator<T> it = begin(); it != end(); ++it) {       //проходимся итератором по всему списку
			std::cout << *it << " => ";							//выводим значение итератора
		}
		std::cout << "nullptr";									//вышенка на торте
	}

	//операторы ввода и вывода
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

	void removeDuplicate() {

		std::unordered_map<int, int> map;

		if (size <= 1) {
			return;
		}

		for (Node* current = head; current != tail->next; current = current->next) {
			map[current->data] = 0;
		}

		Node* current = head;
		map[current->data]++;
		while( current != tail) {
			
			while (current != tail && map[current->next->data] >= 1) {
				Node* tmp = current->next;
				current->next = current->next->next;

				Iterator<T> ITtmp(tmp);
				Iterator<T> ITtail(tail);
				if (ITtmp == ITtail) {								
					tail = current;
				}
				delete tmp;
				size--;
			}

			if (current != tail && map[current->next->data] == 0) {
				map[current->next->data]++;
			}

			if (current != tail) {
				current = current->next;
			}
		}

	}

};

// удобный способ перемещения по списку
template <typename T>
class Iterator {
private:
	typename List<T>::Node* current = nullptr;

public:
	friend class List<T>;
	Iterator(typename List<T>::Node* node) {	//конструктор 
		current = node;
	}

	T& operator*() {														//разыменователь (получение data по указателю)
		return current->data;												//перешли к структуре, где хранится data и "вызвали" ее
	}

	Iterator& operator++() {												//переход итератора к следующему узлу
		if (current) {														// проверка на то, что список не пуст
			current = current->next;										// перемещаем current на следующий узел
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


//мне очень понравилась лаба
