#pragma once

#include <stdexcept>
#include <iostream>
#include <cassert>

/// @brief Singly linked list template class.
template <typename T>
class List {
private:
	/// @brief Internal node structure for the linked list.
	struct Node {
		T data;       ///< Data stored in the node.
		Node* next;   ///< Pointer to the next node.


		Node(T value = T(), Node* next = nullptr):
			data(value),next(next){}
	};

public:
	/// @brief Default constructor. Initializes an empty list.
	List():head(nullptr),tail(nullptr){}
	~List() noexcept {
		free(this->head);
	}
	List(const List& other) {
		this->copyFrom(other);
	}
	List<T>& operator=(const List& other) {
		if (this != &other) {
			Node* oldhead = this->head;
			copyFrom(other);
			free(oldhead);
		}

		return *this;
	}
public:

	/// @brief Access element by index (read-only).
	/// @param index Position of the element.
	/// @throws std::out_of_range If index is out of bounds.
	const T& operator[](size_t index) const {
		Node* current = this->head;
		while (index--) {
			if (!current)
				throw std::out_of_range("Index is out of range!");
			current = current->next;
		}

		if (!current)
			throw std::out_of_range("Index is out of range!");

		return current->data;
	}

	/// @brief Access element by index (read-write).
	/// @param index Position of the element.
	/// @throws std::out_of_range If index is out of bounds.
	T& operator[](size_t index) {

		Node* current = this->head;
		while (index--) {
			if (!current)
				throw std::out_of_range("Index is out of range!");
			current = current->next;
		}

		if (!current)
			throw std::out_of_range("Index is out of range!");

		return current->data;
	}

	/// @brief Adds an element to the front of the list.
	/// @param val Value to add.
	void pushFront(const T& val) {
		Node* newNode = new Node(val);
		if (!this->head) {
			this->head = this->tail = newNode;
			return;
		}

		newNode->next = this->head;
		this->head = newNode;
	}

	/// @brief Adds an element to the back of the list.
   /// @param val Value to add.
	void pushBack(const T& val) {
		Node* newNode = new Node(val);
		if (!this->head) {
			this->head = this->tail = newNode;
			return;
		}

		this->tail->next = newNode;
		this->tail = newNode;
	}

	/// @brief Removes and returns the first element from the list.
	/// @return Value of the removed element.
	T popFront() {
		if (!this->head) {
			throw std::out_of_range("popFront() called on empty list");
		}

		T val = this->head->data;  

		Node* next = this->head->next;
		delete this->head;
		this->head = next;

		return val;
	}

	/// @brief Gets the number of elements in the list.
	size_t size() const {
		Node* current = this->head;
		size_t size = 0;

		while (current) {
			++size;
			current = current->next;
		}

		return size;
	}

	/// @brief Checks whether the list is empty.
	bool isEmpty() const {
		return this->head == nullptr;
	}

	/// @brief Prints the list contents to an output stream.
   /// @param os Output stream to print to.
	void print(std::ostream& os = std::cout) const {
		if (!this->head) {
			os << "[]";
			return;
		}

		Node* current = this->head;
		os << '[';
		while (current) {
			os << current->data;
			if (current->next)
				os << ", ";
			current = current->next;
		}
		os << ']';
	}
	

public://special functions
	
	/// @brief Gets the first element of the list.
	const T& Head() const {
		if (!this->head) {
			throw std::logic_error("Empty list!");
		}

		return this->head->data;
	}

	/// @brief Gets a new list containing all elements except the first.
	List<T> Tail() const {
		if (!this->tail)
			throw std::logic_error("Empty list!");
		
		List<T> TailList;
		
	
		Node* current = this->head->next;
		while (current) {
			TailList.pushBack(current->data);
			current = current->next;
		}
		

		return TailList;
	}

	/// @brief Applies a function to each element
	///and returns a new list of results.
	template <typename Func>
	List<T> map(Func f) const {
		List<T> mapList;

		Node* current = this->head;
		while (current) {
			mapList.pushBack(f(current->data));
			current = current->next;
		}
	
		return mapList;
	}

	/// @brief Filters elements based on a predicate.
	template <typename Predicate>
	List<T> filter(Predicate p) const {
		Node* current = this->head;
		List<T> filtered;

		while (current) {
			if (p(current->data))
				filtered.pushBack(current->data);
			current = current->next;
		}

		return filtered;
	}

	const Node* getHead() const { return this->head; }
	const Node* getTail() const { return this->tail; }

private:
	/// @brief Copies data from another list.
   /// @param other List to copy from.
	void copyFrom(const List& other) {
		Node* result = nullptr;
		Node* resultTail = nullptr;

		try {
			Node* current = other.head;
			while (current) {
				Node* newNode = new Node(current->data, nullptr);
				if (!result) {
					result = resultTail = newNode;
				}
				else {
					resultTail->next = newNode;
					resultTail = resultTail->next;
				}

				current = current->next;
			}
		}
		catch (...) {
			free(result);
			throw;
		}
		

		this->head = result;
		this->tail = resultTail;
	}

	/// @brief Frees memory starting from a given node.
	void free(Node* start) {
		Node* current = start;
		
		while (current) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}

private:
	Node* head; ///< Pointer to the first node in the list.
	Node* tail; ///< Pointer to the last node in the list.
};

