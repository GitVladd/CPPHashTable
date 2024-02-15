/*************************************************************/
/*                                                           */
/*  Starter file for a2                                      */
/*                                                           */
/*  Author Name: Ovsiienko Vladyslav                        */
/*************************************************************/

#include <string>
#include <utility>
#include <functional>
#include "mylist.h"


std::size_t hashKey(std::string key) //returns hash for key
{
	std::hash<std::string> hashFunction;
	size_t hash = hashFunction(key);

	return hash;
}


template <class TYPE>
class Table {
public:
	Table() {}
	virtual bool update(const std::string& key, const TYPE& value) = 0;
	virtual bool remove(const std::string& key) = 0;
	virtual bool find(const std::string& key, TYPE& value) = 0;
	virtual int numRecords() const = 0;
	virtual bool isEmpty() const = 0;
	virtual int capacity() const = 0;
	virtual ~Table() {}
};
//
//template <class TYPE>
//class SimpleTable:public Table<TYPE>{
//
//    struct Record{
//        TYPE data_;
//        std::string key_;
//        Record(const std::string& key, const TYPE& data){
//            key_=key;
//            data_=data;
//        }
//
//    };
//
//    Record** records_;   //the table
//    int capacity_;       //capacity of the array
//
//
//public:
//    SimpleTable(int capacity);
//    SimpleTable(const SimpleTable& rhs);
//    SimpleTable(SimpleTable&& rhs);
//    virtual bool update(const std::string& key, const TYPE& value);
//    virtual bool remove(const std::string& key);
//    virtual bool find(const std::string& key, TYPE& value);
//    virtual const SimpleTable& operator=(const SimpleTable& rhs);
//    virtual const SimpleTable& operator=(SimpleTable&& rhs);
//    virtual ~SimpleTable();
//    virtual bool isEmpty() const{return numRecords()==0;}
//    virtual int numRecords() const;
//    virtual int capacity() const {return capacity_;}
//
//};
//
//template <class TYPE>
//int SimpleTable<TYPE>::numRecords() const{
//    int rc=0;
//    for(int i=0;records_[i]!=nullptr;i++){
//        rc++;
//    }
//    return rc;
//}
//
//
//
//template <class TYPE>
//SimpleTable<TYPE>::SimpleTable(int capacity): Table<TYPE>(){
//    records_=new Record*[capacity+1];
//    capacity_=capacity;
//    for(int i=0;i<capacity_+1;i++){
//        records_[i]=nullptr;
//    }
//}
//
//template <class TYPE>
//SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& rhs){
//    records_=new Record*[rhs.capacity_+1];
//    capacity_=rhs.capacity_;
//    for(int i=0;i<capacity_+1;i++){
//        records_[i]=nullptr;
//    }
//    for(int i=0;i<rhs.numRecords();i++){
//        update(rhs.records_[i]->key_,rhs.records_[i]->data_);
//    }
//}
//template <class TYPE>
//SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& rhs){
//    capacity_=rhs.capacity_;
//    records_=rhs.records_;
//    rhs.records_=nullptr;
//    rhs.capacity_=0;
//}
//
//template <class TYPE>
//bool SimpleTable<TYPE>::update(const std::string& key, const TYPE& value){
//    int idx=-1;
//    int sz=numRecords();
//    bool rc=true;
//    for(int i=0;i<sz;i++){
//        if(records_[i]->key_ == key){
//            idx=i;
//        }
//    }
//    if(idx==-1){
//        if(sz < capacity_){
//            records_[numRecords()]=new Record(key,value);
//            for(int i=numRecords()-1;i>0 && records_[i]->key_ < records_[i-1]->key_;i--){
//                Record* tmp=records_[i];
//                records_[i]=records_[i-1];
//                records_[i-1]=tmp;
//            }
//        }
//        else{
//            rc=false;
//        }
//    }
//    else{
//        records_[idx]->data_=value;
//    }
//    return rc;
//}
//
//template <class TYPE>
//bool SimpleTable<TYPE>::remove(const std::string& key){
//    int idx=-1;
//    for(int i=0;records_[i]!=nullptr;i++){
//        if(records_[i]->key_ == key){
//            idx=i;
//        }
//    }
//    if(idx!=-1){
//        delete records_[idx];
//        
//        for(int i=idx;i<numRecords()-1;i++){
//            records_[i]=records_[i+1];
//        }
//        records_[size-1]=nullptr;
//        return true;
//    }
//    else{
//        return false;
//    }
//}
//
//template <class TYPE>
//bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value){
//    int idx=-1;
//    for(int i=0;i<numRecords();i++){
//        if(records_[i]->key_ == key){
//            idx=i;
//        }
//    }
//    if(idx==-1)
//        return false;
//    else{
//        value=records_[idx]->data_;
//        return true;
//    }
//}
//
//template <class TYPE>
//const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& rhs){
//    if(this!=&rhs){
//        if(records_){
//            while(numRecords() != 0){
//                remove(records_[0]->key_);
//            }
//            delete [] records_;
//        }
//        records_=new Record*[rhs.capacity_+1];
//        capacity_=rhs.capacity_;
//        for(int i=0;i<capacity_;i++){
//            records_[i]=nullptr;
//        }
//        for(int i=0;i<rhs.numRecords();i++){
//            update(rhs.records_[i]->key_,rhs.records_[i]->data_);
//        }
//
//    }
//    return *this;
//}
//template <class TYPE>
//const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& rhs){
//    if(records_){
//        while(numRecords() != 0){
//            remove(records_[0]->key_);
//        }
//        delete [] records_;
//    }
//    records_=rhs.records_;
//    capacity_=rhs.capacity_;
//    rhs.records_=nullptr;
//    rhs.capacity_=0;
//
//    return *this;
//}
//template <class TYPE>
//SimpleTable<TYPE>::~SimpleTable(){
//    if(records_){
//        int sz=numRecords();
//        for(int i=0;i<sz;i++){
//            remove(records_[0]->key_);
//        }
//        delete [] records_;
//    }
//}
//

// CHAINING TABLE///////////////////
template <class TYPE>
class ChainingTable :public Table<TYPE> {

	struct Record {
		TYPE data_;
		std::string key_;
		Record(const std::string& key = {}, const TYPE& data = {})
		{
			key_ = key;
			data_ = data;
		}
		bool operator==(Record& rhs) //== operator
		{
			bool toReturn = false;
			if (this->key_ == rhs.key_)
			{
				toReturn = true;
			}
			return toReturn;
		}
		bool operator!=(Record& rhs) //== operator
		{
			bool toReturn = false;
			if (this->key_ != rhs.key_)
			{
				toReturn = true;
			}
			return toReturn;
		}
		bool operator <(Record& rhs)
		{
			bool rc = false;
			if (this.key_ < rhs.key_)
			{
				rc = true;
			}
			return rc;
		}
		/*const TYPE& operator&() const
		{
			return this->data_;
		}*/
		/*const TYPE& operator*() const
		 {
			 return this->data_;
		 }*/

	};

	DList<Record*>** records_;   //the table
	int capacity_;
	unsigned int numRecords_;
public:
	ChainingTable(int maxExpected);
	ChainingTable(const ChainingTable& other);
	ChainingTable(ChainingTable&& other);
	double loadFactor() const;
	virtual bool update(const std::string& key, const TYPE& value);
	virtual bool remove(const std::string& key);
	virtual bool find(const std::string& key, TYPE& value);
	virtual const ChainingTable& operator=(const ChainingTable& other);
	virtual const ChainingTable& operator=(ChainingTable&& other);
	virtual ~ChainingTable();
	virtual bool isEmpty() const;
	virtual int numRecords() const;
	virtual int capacity() const;

};

////default constructor
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity) : Table<TYPE>()
{
	numRecords_ = 0;
	capacity_ = capacity;
	records_ = new DList<Record*>*[capacity_];
	for (int i = 0; i < capacity_; i++)
	{
		records_[i] = new DList<Record*>;
	}
}

//copy consturctor
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other)
{
	numRecords_ = 0;
	capacity_ = other.capacity_;
	records_ = new DList<Record*>*[capacity_];
	for (int i = 0; i < capacity_; i++)
	{
		records_[i] = new DList<Record*>;
		if (!(other.records_[i]->empty()))
		{
			auto iter = other.records_[i]->begin(); //typename DList<Record*>::iterator
			while (iter != other.records_[i]->end())
			{
				numRecords_++;
				auto data = *iter;
				Record* newRecord = new Record(data->key_, data->data_);
				records_[i]->insert(records_[i]->end(), newRecord);
				iter++;
			}
		}
	}
}

//move constructor
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other)
{
	capacity_ = other.capacity_;
	records_ = other.records_;
	numRecords_ = other.numRecords_;

	other.numRecords_ = 0;
	other.capacity_ = 0;
	other.records_ = nullptr;

}


//This function is passed a key-value pair. If your table already has a record with a matching key, the record's value is replaced by the value passed to this function. If no record exists, a record with key-value pair is added to the table. This function always returns true if operation was successful, false otherwise

template <class TYPE>
bool ChainingTable<TYPE>::update(const std::string& key, const TYPE& value)
{

	//get hash values
	size_t hashedKey = hashKey(key);


	size_t index = hashedKey % capacity_;
	//new record 
	Record* newRecord = new Record(key, value);

	auto iter = records_[index]->search(newRecord);
	//if there is no such record
	if (iter == records_[index]->end())
	{

		//insert new record
		records_[index]->insert(records_[index]->end(), newRecord);
		numRecords_++;
		return true;
	}
	//if there is such record
	else
	{
		//delete previous record
		records_[index]->erase(iter);
		//insert new record
		records_[index]->insert(records_[index]->end(), newRecord);
		return true;
	}
}

//This function is passed a key. If your table contains a record with a matching key, the record (both the key and the value) is removed from the table
template <class TYPE>
bool ChainingTable<TYPE>::remove(const std::string& key)
{
	//get hashes
	size_t hashedKey = hashKey(key);
	size_t index = hashedKey % capacity_;

	//if element at this index is empty
	if (records_[index]->size() == 0)
	{
		return false;
	}

	TYPE tempval = {};
	Record newRecord(key, tempval);

	auto iter = records_[index]->search(&newRecord);
	//if not found
	if (iter == records_[index]->end())
	{
		return false;
	}
	//if found
	else
	{
		records_[index]->erase(iter);
		numRecords_--;
		return true;
	}
}

//This function is passed a key and a reference for passing back a found value. If your table contains a record with a matching key, the function returns true, and passes back the value from the record. If it does not find a record with a matching key, function returns false.
template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string& key, TYPE& value)
{
	//get hashes
	size_t hashedKey = hashKey(key);
	size_t index = hashedKey % capacity_;

	//if dlist at this index is empty
	if (records_[index]->size() == 0)
	{
		return false;
	}
	Record newRecord(key, value);

	auto iter = records_[index]->search(&newRecord); //typename DList<Record*>::iterator
	//if not found
	if (iter == records_[index]->end())
	{
		return false;
	}
	//if found
	else
	{
		auto val = *iter;
		value = val->data_;
		return true;
	}
}

//copy assignment operator
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other)
{

	// delete current table
	for (int i = 0; i < capacity_; i++)
	{
		delete records_[i];
	}
	delete records_;


	//copy table
	numRecords_ = 0;
	capacity_ = other.capacity_;
	records_ = new DList<Record*>*[capacity_];

	//deep copy
	for (int i = 0; i < capacity_; i++)
	{
		records_[i] = new DList<Record*>;
		if (!(other.records_[i]->empty()))
		{
			auto iter = other.records_[i]->begin(); //typename DList<Record*>::iterator
			while (iter != other.records_[i]->end())
			{
				numRecords_++;
				auto data = *iter;
				Record* newRecord = new Record(data->key_, data->data_);
				records_[i]->insert(records_[i]->end(), newRecord);
				iter++;
			}
		}
	}

	return *this;
}

//move assignment operator
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other)
{
	for (int i = 0; i < capacity_; i++)
	{
		if (records_[i] != nullptr)
		{
			delete records_[i];
		}
	}

	delete records_;
	//copy
	capacity_ = other.capacity_;
	records_ = other.records_;
	numRecords_ = other.numRecords_;

	other.numRecords_ = 0;
	other.capacity_ = 0;
	other.records_ = nullptr;

	return *this;

}

//destructor
template <class TYPE>
ChainingTable<TYPE>::~ChainingTable()
{
	for (int i = 0; i < capacity_; i++)
	{
		delete records_[i];
		records_[i] = nullptr;

	}

	delete records_;
}

//This function returns the number of records in the table.
template <class TYPE>
bool ChainingTable<TYPE>::isEmpty() const
{
	if (numRecords_ != 0)
	{
		return false;
	}
	return true;
}

//This function returns the number of records in the table.
template <class TYPE>
int ChainingTable<TYPE>::numRecords() const
{
	return numRecords_;
}

//This function returns capacity of the table
template <class TYPE>
int ChainingTable<TYPE>::capacity() const
{
	return capacity_;
}

//This function returns the load factor of the table. (number of records divided by capacity of table)
template <class TYPE>
double ChainingTable<TYPE>::loadFactor() const
{
	return double(numRecords_) / double(capacity_);
}


template <class TYPE>
class LPTable :public Table<TYPE> {
	struct Record {
		TYPE data_;
		std::string key_;
		Record(const std::string& key = {}, const TYPE& data = {})
		{
			key_ = key;
			data_ = data;
		}
		bool operator==(Record& rhs) //== operator
		{
			bool toReturn = false;
			if (this->key_ == rhs.key_)
			{
				toReturn = true;
			}
			return toReturn;
		}
		bool operator!=(Record& rhs) //== operator
		{
			bool toReturn = false;
			if (this->key_ != rhs.key_)
			{
				toReturn = true;
			}
			return toReturn;
		}
		bool operator <(Record& rhs)
		{
			bool rc = false;
			if (this.key_ < rhs.key_)
			{
				rc = true;
			}
			return rc;
		}
		/*const TYPE& operator&() const
		{
			return this->data_;
		}*/
		/*const TYPE& operator*() const
		 {
			 return this->data_;
		 }*/
	};
	int capacity_;
	unsigned int numRecords_;
	Record** arr;
public:
	LPTable(int maxExpected);
	LPTable(const LPTable& other);
	LPTable(LPTable&& other);
	double loadFactor() const;
	virtual bool update(const std::string& key, const TYPE& value);
	virtual bool remove(const std::string& key);
	virtual bool find(const std::string& key, TYPE& value);
	virtual const LPTable& operator=(const LPTable& other);
	virtual const LPTable& operator=(LPTable&& other);
	virtual ~LPTable();
	virtual bool isEmpty() const;
	virtual int numRecords() const;
	virtual int capacity() const;

};

//default constructor
template <class TYPE>
LPTable<TYPE>::LPTable(int capacity) : Table<TYPE>()
{
	capacity_ = capacity;
	arr = new Record * [capacity_];
	for (int i = 0; i < capacity_; i++)
	{
		arr[i] = nullptr;
	}
	numRecords_ = 0;
}

//copy constructor
template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other)
{
	numRecords_ = 0;
	capacity_ = other.capacity_;
	arr = new Record * [capacity_];
	for (int i = 0; i < capacity_; i++)
	{
		if (other.arr[i] != nullptr)
		{
			Record* newRecord = new Record(other.arr[i]->key_, other.arr[i]->data_);
			arr[i] = newRecord;
			numRecords_++;
		}
		else
		{
			arr[i] = nullptr;
		}

	}

}
//move constructor
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other)
{
	numRecords_ = other.numRecords_;
	capacity_ = other.capacity_;
	arr = other.arr;

	other.numRecords_ = 0;
	other.capacity_ = 0;
	other.arr = nullptr;
}

//This function is passed a key-value pair. If your table already has a record with a matching key, the record's value is replaced by the value passed to this function. If no record exists, a record with key-value pair is added to the table.
template <class TYPE>
bool LPTable<TYPE>::update(const std::string& key, const TYPE& value)
{
	//get hash values
	size_t hashedKey = hashKey(key);
	size_t index = hashedKey % capacity_;
	if (arr[index] == nullptr)//if this element is nullptr add new record
	{
		if (numRecords_ == capacity_ - 1)
		{
			return false;
		}
		Record* newRecord = new Record(key, value);
		arr[index] = newRecord;
		numRecords_++;
		return true;
	}
	else
	{
		if (arr[index]->key_ == key)////if such key is found, update value
		{
			arr[index]->data_ = value;
			return true;
		}
		else ////if such key is not found, iterate over array
		{
			while (true)
			{
				index++;
				if (index >= capacity_) //if at the end of table
				{
					index = 0;
				}
				if (arr[index] == nullptr) //if found empty node
				{
					if (numRecords_ == capacity_ - 1)
					{
						return false;
					}
					//new record 
					Record* newRecord = new Record(key, value);
					arr[index] = newRecord;
					numRecords_++;
					return true;
				}
				if (arr[index]->key_ == key)//if such key is found, update value
				{
					arr[index]->data_ = value;
					return true;
				}
			}
		}
	}

}

//This function is passed a key. If your table contains a record with a matching key, the record (both the key and the value) is removed from the table
template <class TYPE>
bool LPTable<TYPE>::remove(const std::string& key)
{
	size_t hashedKey = hashKey(key);
	size_t index = hashedKey % capacity_;

	while (true)
	{
		if (index >= capacity_) //if at the end of table
		{
			index = 0;
		}
		if (arr[index] == nullptr) //if found empty node
		{
			return false;
		}
		if (arr[index]->key_ == key)//if such key is found, update value
		{

			delete arr[index];
			arr[index] = nullptr;
			numRecords_--;
			size_t prevIndex = index;
			index++;
			while (arr[index] != nullptr)
			{
				
				size_t hashedKey = hashKey(arr[index]->key_);
				size_t indexNeedToBe = hashedKey % capacity_;
				if (indexNeedToBe == index || indexNeedToBe > prevIndex)
				{
					
					index++;
				}
				else
				{
					Record* newRecord = new Record(arr[index]->key_, arr[index]->data_);
					
					delete arr[index];
					arr[index] = nullptr;

					arr[prevIndex] = newRecord;

					prevIndex = index;
					index++;
					if (index >= capacity_) //if at the end of table
					{
						index = 0;
					}
				}
			}
			return true;
		}
		index++;
	}
}

//This function is passed a key and a reference for passing back a found value. If your table contains a record with a matching key, the function returns true, and passes back the value from the record. If it does not find a record with a matching key, function returns false.
template <class TYPE>
bool LPTable<TYPE>::find(const std::string& key, TYPE& value)
{
	//get hash values
	size_t hashedKey = hashKey(key);
	size_t index = hashedKey % capacity_;


	while (true)
	{
		if (index >= capacity_) //if at the end of table
		{
			index = 0;
		}
		if (arr[index] == nullptr) //if found empty node
		{
			return false;
		}
		if (arr[index]->key_ == key)//if such key is found, update value
		{
			value = arr[index]->data_;
			return true;
		}
		index++;
	}
}

//copy assignment operator
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other)
{
	for (int i = 0; i < capacity_; i++)
	{
		if (arr[i] != nullptr)
		{
			delete arr[i];
			arr[i] = nullptr;
		}
	}
	delete[] arr;

	numRecords_ = 0;
	capacity_ = other.capacity_;
	arr = new Record * [capacity_];
	for (int i = 0; i < capacity_; i++)
	{
		if (other.arr[i] != nullptr)
		{
			Record* newRecord = new Record(other.arr[i]->key_, other.arr[i]->data_);
			arr[i] = newRecord;
			numRecords_++;
		}
		else
		{
			arr[i] = nullptr;
		}

	}
	return *this;

}

//move assignment operator
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other)
{
	for (int i = 0; i < capacity_; i++)
	{
		if (arr[i] != nullptr)
		{
			delete arr[i];
			arr[i] = nullptr;
		}
	}
	delete[] arr;
	arr = nullptr;

	numRecords_ = other.numRecords_;
	capacity_ = other.capacity_;
	arr = other.arr;

	other.numRecords_ = 0;
	other.capacity_ = 0;
	other.arr = nullptr;

	return *this;

}

//destructor
template <class TYPE>
LPTable<TYPE>::~LPTable()
{
	if (arr != nullptr)
	{
		for (int i = 0; i < capacity_; i++)
		{
			if (arr[i] != nullptr)
			{
				delete arr[i];
				arr[i] = nullptr;
			}
		}
		delete[] arr;
	}
}

//This function returns the number of records in the table.
template <class TYPE>
bool LPTable<TYPE>::isEmpty() const
{
	if (numRecords_ > 0)
	{
		return false;
	}
	return true;
}

//This function returns the number of records in the table.
template <class TYPE>
int LPTable<TYPE>::numRecords() const
{
	return numRecords_;
}

//This function returns capacity of the table.
template <class TYPE>
int LPTable<TYPE>::capacity() const
{
	return capacity_;
}

//This function returns the load factor of the table. (number of records divided by capacity of table)
template <class TYPE>
double LPTable<TYPE>::loadFactor() const
{
	return double(numRecords_) / double(capacity_);
}


