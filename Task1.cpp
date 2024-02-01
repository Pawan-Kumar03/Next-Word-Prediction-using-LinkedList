/*
	Task (Next Word Prediction) 

	Name : Pawan Kumar BSCS III
	CMS : 023-21-0136
	Section - C
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Node
{
public:
	string data;
	Node *next;
	Node()
	{
		data = "";
		next = NULL;
	}
};
class Linkedlist
{
public:
	Node *head;
	Linkedlist(void)
	{
		head = NULL;
	}
};
class C
{
public:
	Linkedlist *list;
	string data;
	int count = 1;
	C()
	{
		list = new Linkedlist();
		data = "";
	}
	// reading File through path
	string readFile(string path)
	{
		string x; // local string to get line from file
		ifstream file;
		file.open(path.c_str(), ios::in);
		while (getline(file, x)) // It reads Line by Line. get line from file and store in x
		{
			data += x;
			data += "\n";
		}
		file.close();
		return data;
	}
	string preProcess(string data)
	{
		string cleaned_Data;
		// removing special characters from data
		for (int i = 0; i < data.length(); i++)
		{
			if ((data[i] >= 'a' && data[i] <= 'z') || (data[i] == ' ') || (data[i] == '\n') || (data[i] >= 'A' && data[i] <= 'Z'))
			{
				cleaned_Data += data[i];
			}
		}
		return cleaned_Data;
	}

	string *split(string cleaned_data)
	{
		// words counter.
		for (int i = 0; i < cleaned_data.length(); i++)
			if (cleaned_data[i] == ' ')
				count++;
		// making array of words of count size
		string *arr = new string[count];
		int index = 0; // index for new array
		for (int i = 0; i < cleaned_data.length(); i++)
		{
			if (cleaned_data[i] == ' ')
				index++; // it will check if the new word starts then it increament index. so that new word willbe stored in next index
			else
				arr[index] += cleaned_data[i]; // concatinating index by index of cleaned data
		}
		return arr;
	}
	Linkedlist *words2List(string *words)
	{
		for (int i = 0; i < count; i++)
		{
			// firstly assigning word to node data then connecting nodes
			Node *n1 = new Node;
			n1->data = words[i];
			if (list->head == NULL)
				list->head = n1;
			else
			{
				Node *ptr = list->head;
				// adding inthe last
				while (ptr->next != NULL)
					ptr = ptr->next;
				ptr->next = n1;
			}
		}
		return list;
	}
	string *predictNextWord(Node *head, string query)
	{
		Node *currNode = head;
		int countQueries = 0; 
		// Counting all quries in whole File
		while (currNode != NULL)
		{
			if (query == currNode->data)
				countQueries++;
			currNode = currNode->next;
		}

		string *query_results = new string[countQueries];
		int index = 0;
		currNode = head; // giving address of head to Current node sothat it start again from head
		while (currNode->next != NULL)
		{
			if (currNode->data == query)
			{   // Adding next two prdicted words inthe Array
				query_results[index] += currNode->next->data + " " + currNode->next->next->data;
				index++;
			}
			currNode = currNode->next;
		}
		
		return query_results;
	}
};
int main()
{
	C *obj = new C();
	string data = obj->readFile("Task1.txt");

	string clean_Data = obj->preProcess(data);

	string *words = obj->split(clean_Data);

	Linkedlist *list1 = obj->words2List(words);

	string *result = obj->predictNextWord(list1->head, "Sukkur");

	// Printing next  predicted words in whole File
	for (int i = 0; i < result->length(); i++)
		cout << result[i] <<endl;
}
