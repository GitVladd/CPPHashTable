/********************************************************************/
/*                                                                  */
/*  Put your linked list code from A1 into                          */
/*  this file                                                       */
/*                                                                  */
/********************************************************************/

#include <iostream>
template <typename T>

class DList {
	struct Node { //node implementation
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr)
		{
			data_ = data;
			next_ = next;
			prev_ = prev;
		};
	};

	Node* front_;
	Node* back_;


public:
	class const_iterator {
		friend class DList;
	protected:
		Node* curr_;
		const DList* myList_;
	public:
		const_iterator() //default constructor
		{
			curr_ = nullptr;
			myList_ = nullptr;
		}
		const_iterator(Node* curr, const DList* theList) //custom constructor
		{
			curr_ = curr;
			myList_ = theList;
		}
		const_iterator& operator++() //prefix ++
		{
			curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int) //postfix ++
		{
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}
		const_iterator& operator--()//prefix --
		{
			if (curr_)
			{
				curr_ = curr_->prev_;
			}
			else //if this iterator pointing on after end node, assign it back_ node
			{
				if (myList_)
				{
					curr_ = myList_->back_;
				}
			}
			return *this;
		}
		const_iterator operator--(int)//postfix --
		{
			const_iterator old = *this;
			if (curr_)
			{
				curr_ = curr_->prev_;
			}
			else //if this iterator pointing on after end node, assign it back_ node
			{
				if (myList_)
				{
					curr_ = myList_->back_;
				}
			}
			return old;
		}
		bool operator==(const_iterator rhs) //== operator
		{
			bool toReturn = false;
			if (curr_ == rhs.curr_)
			{
				toReturn = true;
			}

			return toReturn;

		}
		bool operator!=(const_iterator rhs) // != operator
		{
			bool toReturn = false;
			if (curr_ != rhs.curr_)
			{
				toReturn = true;
			}

			return toReturn;
		}
		const T& operator*()const //dereference operator, returns data
		{
			return curr_->data_;
		}
	};
	class iterator :public const_iterator {
		friend class DList;

	public:
		iterator() :const_iterator() {} //default constructor
		iterator(Node* curr, const DList* theList) : const_iterator(curr, theList) {} //custom constructor
		iterator& operator++() //prefix ++
		{
			this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int) //postfix ++
		{
			iterator old = *this;
			if (this->curr_ != nullptr)
			{
				this->curr_ = this->curr_->next_;
			}
			return old;
		}
		iterator& operator--() //prefix --
		{
			if (this->curr_)
			{
				this->curr_ = this->curr_->prev_;
			}
			else//if this iterator pointing on after end node, assign it to back_ node
			{
				if (this->myList_)
				{
					this->curr_ = this->myList_->back_;
				}
			}
			return *this;
		}
		iterator operator--(int)//postfix --
		{
			iterator old = *this;
			if (this->curr_)
			{
				this->curr_ = this->curr_->prev_;
			}
			else//if this iterator pointing on after end node, assign it to back_ node
			{
				if (this->myList_)
				{
					this->curr_ = this->myList_->back_;
				}
			}
			return old;
		}
		T& operator*() //dereference operator, returns data
		{
			return this->curr_->data_;
		}
		const T& operator*()const //dereference operator, returns data const
		{
			return this->curr_->data_;
		}
	};
	DList();
	~DList();
	DList(const DList& rhs);
	DList& operator=(const DList& rhs);
	DList(DList&& rhs);
	DList& operator=(DList&& rhs);
	iterator insert(iterator it, const T& data);
	iterator search(const T& data);
	iterator erase(iterator it);
	void sort(iterator first, iterator last);
	bool empty() const;
	int size() const;

	iterator begin()
	{
		return iterator(this->front_, this); //returns front node
	}
	iterator end()
	{
		return iterator(nullptr, this); //returns after end node
	}
	const_iterator cbegin() const
	{
		return const_iterator(this->front_, this); //returns front node consts
	}
	const_iterator cend() const
	{
		return const_iterator(nullptr, this); //returns after end node const
	}
};

template <typename T>
DList<T>::DList() //default consturcotr
{
	this->front_ = nullptr;
	this->back_ = nullptr;
}
template <typename T>
DList<T>::~DList() //destructor
{
	if (this->front_ != nullptr)
	{
		while (this->front_->next_ != nullptr)
		{
			Node* p = front_->next_;
			delete front_;
			this->front_ = p;
		}
		delete front_;
	}
}
template <typename T>
DList<T>::DList(const DList& rhs)//custom constructor
{
	this->front_ = nullptr;
	this->back_ = nullptr;

	if (rhs.front_ != nullptr) //if rhs is not empty
	{
		DList<T>::iterator it(rhs.front_, &rhs); //declare iterator

		this->insert(this->end(), it.curr_->data_); //insert data from front_ node of rhs

		while (it.curr_->next_ != nullptr) //insert all other data from rhs nodes
		{
			++it;
			this->insert(this->end(), it.curr_->data_);
		}
	}
}
template <typename T>
DList<T>& DList<T>::operator=(const DList& rhs)
{
	//deallocate current DList
	if (front_ != nullptr)
	{
		while (front_->next_ != nullptr)
		{
			Node* p = front_->next_;
			delete front_;
			front_ = p;
		}
		delete front_;

		front_ = nullptr;
		back_ = nullptr;
	}

	if (rhs.front_ != nullptr)//if rhs is not empty
	{
		DList<T>::iterator it(rhs.front_, &rhs); //declare iterator

		this->insert(this->end(), it.curr_->data_); //insert data from front_ node of rhs

		while (it.curr_->next_ != nullptr) //insert all other data from rhs nodes
		{
			++it;
			this->insert(this->end(), it.curr_->data_);
		}
	}
	else //if rhs is empty
	{
		this->front_ = nullptr;
		this->back_ = nullptr;
	}

	return *this;
}
template <typename T>
DList<T>::DList(DList&& rhs)
{
	front_ = rhs.front_; //assign front node of rhs list to this list
	back_ = rhs.back_; //assign back node of rhs list to this list

	rhs.front_ = nullptr; //assign front node of ths to nullptr
	rhs.back_ = nullptr;//assign back node of ths to nullptr
}

template <typename T>
DList<T>& DList<T>::operator=(DList&& rhs)
{
	front_ = rhs.front_;  //assign front node of rhs list to this list
	back_ = rhs.back_; //assign back node of rhs list to this list

	rhs.front_ = nullptr; //assign front node of ths to nullptr
	rhs.back_ = nullptr; //assign back node of ths to nullptr

	return *this;
}


template <typename T>
typename DList<T>::iterator DList<T>::insert(iterator it, const T& data) //insert data after it itaretor node
{
	if (it.curr_ == nullptr) //if insert to the empty list or at the end of list
	{
		if (this->front_ != nullptr) //if insert at the end
		{
			Node* newNode = new Node(data, nullptr, this->back_); //create new node
			this->back_->next_ = newNode; //make back_ node next_ pointiing to new node

			this->back_ = newNode;// make new node back_ of the list

			iterator iter(newNode, this); //create iterator of new node to retrun

			return iter;
		}
		else //if insert to the empty list
		{
			Node* newNode = new Node(data, nullptr, nullptr); //create new node

			this->front_ = newNode; //make new node front_ of the list
			this->back_ = newNode; //make new node back_ of the list

			iterator iter(newNode, this); //create iterator of new node to return it

			return iter;
		}
	}
	else //if insert to not empty list and not at the end
	{
		Node* newNode = new Node(data, it.curr_, it.curr_->prev_); //create new node
		if (it.curr_->prev_ != nullptr) //if insert not at the front
		{
			it.curr_->prev_->next_ = newNode;
		}
		else //if insert at the front
		{
			this->front_ = newNode; //make new node front_ of the list
		}

		it.curr_->prev_ = newNode;

		iterator iter(newNode, this); //create iterator of new node to return it

		return iter;
	}
}
//works
template <typename T>
typename DList<T>::iterator DList<T>::search(const T& data) //search specific data in list
{
	for (DList<T>::iterator it(this->front_, this); it != this->end(); ++it) //iterate over whole list
	{

		//little update because I dont know how to fix a problem with datatype of *it return value. It return address of Record, but I need data_;
		std::string stringType = typeid(*it).name();
		char lastChar = stringType.c_str()[stringType.length() - 1];

		//check if data type is an address
		if (lastChar == '*' || stringType.substr(0, 4) == "PN13") //first for windows, second for linux
		{
			if (*(*it) == *data) //if data is found, return iterator of node which holds this data
			{
				return it;
			}
		}
		else
		{
			//this part is original, all other has been added specially for assignment 2, because this function works differently, depending on compiler 
			if (*it == data) //if data is found, return iterator of node which holds this data
			{
				return it;
			}
		}

	}

	return this->end(); //return end of list if data is not found
}


template <typename T>
typename DList<T>::iterator DList<T>::erase(iterator it) //erase it node 
{
	iterator toReturn(it.curr_->next_, this); //create iterator of next node of it itaretor

	//change next and prev nodes of adjacent to it iterator nodes
	if (it.curr_->next_)
		it.curr_->next_->prev_ = it.curr_->prev_;
	else
		this->back_ = it.curr_->prev_;

	if (it.curr_->prev_)
		it.curr_->prev_->next_ = it.curr_->next_;
	else
		this->front_ = it.curr_->next_;

	delete it.curr_; //erase node

	return toReturn;
}

template <typename T>
void DList<T>::sort(iterator first, iterator last) //sort list fromt first(inclusive) to last(not inclusive) nodes in ascending 
{

	if (first != last) //if both iterators pointing on the same node, dont do anything
	{
		//bubble sort
		for (DList<T>::iterator itCurr = first; itCurr != last; itCurr++)
		{
			for (DList<T>::iterator itNext = itCurr; itNext != last; itNext++)
			{
				if (itNext != itCurr)
				{
					if (itNext.curr_->data_ < itCurr.curr_->data_) //if current node data greater than next node data, we swap them
					{
						//change prev and next nodes of adjacent to itNext and itCurr nodes
						if (itCurr.curr_->prev_ != nullptr) //if itCurr node is not front
							itCurr.curr_->prev_->next_ = itNext.curr_;

						if (itCurr.curr_->next_ != nullptr && itCurr.curr_->next_ != itNext.curr_) //if itCurr node is not back and it`s next node is not itNext
							itCurr.curr_->next_->prev_ = itNext.curr_;

						if (itNext.curr_->next_ != nullptr)//if iTnext node is not back
							itNext.curr_->next_->prev_ = itCurr.curr_;

						if (itNext.curr_->prev_ != nullptr && itNext.curr_->prev_ != itCurr.curr_) //if itNext node is not front and it`s prev node is not itCurr
							itNext.curr_->prev_->next_ = itCurr.curr_;


						//create and assign temporary addresses. We will need these addresses when swap next and prev nodes
						Node* tempAddress2 = nullptr;
						Node* tempAddress1 = nullptr;

						if (itCurr.curr_->next_ != itNext.curr_)
							tempAddress2 = itCurr.curr_->next_;
						else
							tempAddress2 = itCurr.curr_;

						if (itNext.curr_->prev_ != itCurr.curr_)
							tempAddress1 = itNext.curr_->prev_;
						else
							tempAddress1 = itNext.curr_;


						//swap next and prev nodes of itCurr and itNext nodes
						itCurr.curr_->next_ = itNext.curr_->next_;

						itNext.curr_->prev_ = itCurr.curr_->prev_;

						itCurr.curr_->prev_ = tempAddress1;

						itNext.curr_->next_ = tempAddress2;

						if (itCurr.curr_ == front_) //if itCurr was front node, make itNext new front node
							front_ = itNext.curr_;

						if (itNext.curr_ == back_)//if itNext was back node, make itCurr new back node
							back_ = itCurr.curr_;

						itCurr = itNext; //assign itCurr to itNext to not skip some nodes during iteration

					}
				}
			}
		}
	}

}
template <typename T>
bool DList<T>::empty() const //check if list is empty
{
	if (this->front_ == nullptr) //if front is nullptr, list is empty
		return true;
	return false;//if front is not nullptr, list is not empty
}
template <typename T>
int DList<T>::size() const //get size of list
{
	int toReturn = 0;
	if (front_ != nullptr) //if front is nullptr, list is empty (size = 0)
	{
		DList<T>::const_iterator it(front_, this);
		while (it != this->cend()) //iteratre over list until end. Increment toReturn by 1 after each iteration
		{
			++toReturn;
			++it;
		}
	}

	return toReturn; //return size
}

