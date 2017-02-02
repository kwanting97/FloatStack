#include <iostream>
#include <sstream>

using namespace std;

class StackNode 
{
public:
	StackNode *next;

	StackNode(): next(NULL) {}
	virtual ~StackNode() {}

	string toString() const { return "<generic node>"; }
};

class Stack 
{
protected:
	StackNode *top;

public:
	Stack() : top(NULL) {}
	virtual ~Stack() {}

	void push(StackNode *newNode);
	StackNode *pop();
	string toString() const;
};

class FloatNode : public StackNode 
{
private:
	float data;

public:
	FloatNode(float f) : data(f) { }

	string toString() const;
	float getData() const { return data; }
};

class FloatStack : private Stack 
{
public:
	void push(float f);
	float pop();
	string toString() const;
};

int main()
{
	/*
	Stack s;
	s.push(new StackNode());
	s.push(new StackNode());
	s.push(new StackNode());

	cout << s.toString() << endl;
	*/
	FloatStack fs;
	fs.push(1.0);
	fs.push(10.0);
	fs.push(25.0);
	fs.push(63.0);
	cout << fs.toString() << endl;

	float f = fs.pop();
	cout << f << endl;
	cout << fs.toString() << endl;

	return 0;
}

string FloatNode::toString() const {
	ostringstream os;
	os.setf(ios::fixed);
	os.precision(3);
	os << "[" << data << "]";
	return os.str();
}
void Stack::push(StackNode *newNode)
{
	if (newNode == NULL) return;

	StackNode* tempNode;
	tempNode = top;
	top = newNode;
	top->next = tempNode;
}

StackNode *Stack::pop()
{
	if (top == NULL) return NULL;
	StackNode* returnNode;
	returnNode = top;
	top = returnNode->next;
	returnNode->next = NULL;

	return returnNode;
}

string Stack::toString() const
{
	string result = "";
	for (StackNode* p = top; p != NULL; p = p->next)
	{
		result += p->toString();
	}
	return result;
}

void FloatStack::push(float f)
{
	FloatNode* newFloatNode;
	newFloatNode = new FloatNode(f);
	Stack::push(newFloatNode);
}

float FloatStack::pop()
{
	FloatNode* result = (FloatNode*) ( Stack::pop() );
	float f = result->getData();
	delete result;
	return f;
}

string FloatStack::toString() const
{
	string result = "";
	for (StackNode* p = top; p != NULL; p = p->next)
	{
		result += ( (FloatNode*)p )->toString();
	}

	return result;
}
