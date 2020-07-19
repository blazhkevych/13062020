#include <iostream>
#include <time.h>
using namespace std;
class Array {
	int N;
	int* array;
public:
	Array();
	explicit Array(int);
	Array(const Array& Ar);
	~Array();
	int Size() const;
	const int* Data() const;
	int* Data();
	void Clear();
	void Print();
	void SetRnd(int min, int max);
	void Input();
	Array& operator=(const Array& Ar);//this = Ar
	Array operator+(const Array& RAr) const;//this + RAr
	Array operator+(int el) const; //this + el
	//Array operator+(int el); //el   + this error
	friend  Array operator+(int el, const Array& Rar);

};

Array::Array()
{
	N = 0;
	array = nullptr;
}
//Array::Array(int n) :N(n), array(new int[n] {0})
Array::Array(int n)
{
	N = n;
	if (N > 0)
		array = new int[n] {0};
	else
		array = nullptr;
}
//Array::Array(const Array& Ar)
//{
//    N = Ar.N;
//    array = new int[Ar.N];
//    for (size_t i = 0; i < N; i++)
//        array[i] = Ar.array[i];
//}
Array::Array(const Array& Ar) :Array(Ar.N)
{
	//copy(Ar.array, Ar.array + N, array);    
	memcpy(array, Ar.array, N * sizeof(*array));
}
Array& Array::operator=(const Array& Ar)
{
	if (&Ar != this) {
		Clear();
		N = Ar.N;
		if (N) {
			array = new int[Ar.N];
			memcpy(array, Ar.array, N * sizeof(*array));
		}
		else
			array = nullptr;
	}
	return *this;
}
Array Array::operator+(const Array& RAr) const
{
	Array nar(N + RAr.N);
	memcpy(nar.array, array, N * sizeof(*array));
	memcpy(nar.array + N, RAr.array, RAr.N * sizeof(*(RAr.array)));
	return nar;
}
Array Array::operator+(int el) const
{
	Array nar(N + 1);
	memcpy(nar.array, array, N * sizeof(*array));
	nar.array[N] = el;
	return nar;
}

//Array operator+(int el, const Array& Rar) { // int + Array
//    Array nar(Rar.Size() + 1);
//    //nar.Data()[0] = el;
//    *nar.Data() = el;
//    memcpy(nar.Data()+1, Rar.Data(), Rar.Size() * sizeof(*Rar.Data()));
//    return nar;
//    //return Rar + el;
//}
Array operator+(int el, const Array& Rar) { // int + Array friend
	Array nar(Rar.N + 1);
	nar.array[0] = el;
	memcpy(nar.array + 1, Rar.array, Rar.N * sizeof(*Rar.array));
	return nar;
}

Array::~Array()
{
	Clear();
}
int Array::Size() const
{
	return N;
}
int* Array::Data()
{
	return array;
}
const int* Array::Data() const
{
	return array;
}
void Array::Clear()
{
	N = 0;
	delete[] array;
	array = nullptr;
}
void Array::Print()
{
	for (int i = 0; i < N; i++)
		cout << array[i] << "\t";
	cout << endl;
}
void Array::SetRnd(int min, int max)
{
	if (min > max)swap(min, max);
	for (int i = 0; i < N; i++)
		array[i] = min + rand() % (max - min + 1);
}
void Array::Input()
{
	for (int i = 0; i < N; i++)
	{
		cout << "array[" << i << "] = ";
		cin >> array[i];
	}
}


int main()
{
	//srand(time(0));
	int f = 10, k = f;
	Array mas1(3);
	//mas1.Print();
	mas1.SetRnd(-5, 5);
	cout << "-------------mas1-------------------\n";
	mas1.Print();
	cout << "-------------mas2-------------------\n";
	//mas.Input();
	Array mas2(5);
	//mas1.Print();
	mas2.SetRnd(-5, 5);
	mas2.Print();
	cout << "--------------mas3------------------\n";
	Array mas3;
	mas3 = mas1 + mas2;
	//mas3 = mas3 + mas3;
	mas3.Print();

	cout << "--------------mas3------------------\n";
	mas3 = mas1 + 30 + 40 + 50 + 60;
	mas3.Print();

	cout << "--------------mas3------------------\n";
	mas3 = 30 + mas1;
	mas3.Print();

	cout << "The end\n";
}