#pragma once

template <class T>
struct TNode {
	T val;				//значение
	TNode<T> *pNext;	//указатель на следующий 
};
template <class T>
class TList {
	TNode<T> *pFirst, *pLast;	
	TNode<T>*pCurr, *pPrev;		//указатели на текущий/предыдущий элемент списка
	TNode<T> *pStop;			
	int len;					//длина
	int pos;					//№ элемента в списке, на который указывает pCurr
public:
	TList();
	//TList(const *TList<T> &list);
	~TList();

	T GetCurrEl();				//вернуть значение текущего элемента

	void InsFirst(const T &a);	//добавить элемент в начало
	void DelFirst();			//удалить начальный элемент
	void InsLast(const T &a);	//добавить элемент в конец
	void InsCurr(const T &a);	//добавить элемент между pPrev и pCurr 
	void DelCurr();				//удалить текущий элемент 

	void Reset();				//установить указатели на начало
	void GoNext();				//передвинуть указатели на следующий
	bool IsEnd();				//проверка на окончание

	void InsInOrder(const T &a);//добавить элемент по порядку
};	

template <class T>
TList<T>::TList()
{
	pFirst = pLast = pCurr = pPrev = pStop = NULL;
	len = 0;
	pos = -1;
}/*-------------------------------------------------------------------------*/

template <class T>
TList<T>::~TList()
{
	TNode<T> *tmp = pFirst;
	while (pFirst != NULL) {
		pFirst = pFirst->pNext;
		delete tmp;
		tmp = pFirst;
	}
}/*-------------------------------------------------------------------------*/


template <class T>
T TList<T>:: GetCurrEl()
{
	if (pCurr == NULL) throw "Error GetCurrEl: pCurr=0";
	return pCurr->val;
}/*-------------------------------------------------------------------------*/


template <class T>
void TList<T>::InsFirst(const T &a)
{
	TNode<T> *tmp = new TNode<T>;
	tmp->pNext = pFirst;
	tmp->val = a;
	if (pFirst == NULL) pLast = pFirst = tmp; //проверка, если в списке один элемент
	else pFirst = tmp;
	len++;
}/*-------------------------------------------------------------------------*/

template <class T>
void TList<T>::DelFirst()
{
	if (pFirst == NULL) throw "Error DelFirst: List is empty";
	TNode<T> *tmp = pFirst;
	pFirst = pFirst->pNext;
	pCurr = pFirst;
	delete tmp;
	len--;
}/*-------------------------------------------------------------------------*/

template <class T>
void TList<T>::InsLast(const T &a)
{
	TNode<T> *tmp = new TNode<T>;
	tmp->pNext = NULL;
	tmp->val = a;
	if (pLast != NULL) {
		pLast->pNext = tmp;
		pLast = tmp;
	}
	else {
		pFirst = pLast = tmp;
	}
	len++;
}/*-------------------------------------------------------------------------*/

template <class T>
void TList<T>::InsCurr(const T &a)
{
	if (pCurr==pFirst) {
		InsFirst(a);
	}
	else if (pCurr==pStop) {
		throw "Error InsCurr: Stop";
	}
	else {
		TNode<T> *tmp = new TNode<T>;
		tmp->val = a;
		pPrev->pNext = tmp;
		tmp->pNext = pCurr;
		pCurr = tmp;
		len++;
	}
}/*-------------------------------------------------------------------------*/

template <class T>
void TList<T>::DelCurr()
{
	if (pCurr == pStop) throw "Error DelCurr: Stop";
	if (pCurr == pFirst) {
		DelFirst();
	}
	else {
		TNode<T> *tmp = pCurr;
		pPrev->pNext = pCurr->pNext;
		pCurr = pCurr->pNext;
		delete tmp;
		len--;
	}
}/*-------------------------------------------------------------------------*/

template <class T>
void TList<T>::Reset() {
	pCurr = pFirst;
	pPrev = pStop;
	pos = 0;
}/*-------------------------------------------------------------------------*/

template <class T>
void TList<T>::GoNext() {
	pPrev = pCurr;
	pCurr = pCurr->pNext;
	pos++;
}/*-------------------------------------------------------------------------*/

template <class T>
bool TList<T>::IsEnd() {
	return pCurr == pStop;
}/*-------------------------------------------------------------------------*/

template <class T>
void TList<T>::InsInOrder(const T &a) {
	if (pFirst == pStop) InsFirst(a);
	else if (pFirst->val<a) InsFirst(a);
	else if (pLast->val > a) InsLast(a);
	else{
		for (Reset(); !IsEnd(); GoNext()) {
			if (a > pCurr->val) {
				InsCurr(a);
				break;
			}
		}
	}
}/*-------------------------------------------------------------------------*/