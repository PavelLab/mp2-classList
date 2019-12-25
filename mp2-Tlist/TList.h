#pragma once

template <class T>
struct TNode {
	T val;				//��������
	TNode<T> *pNext;	//��������� �� ��������� 
};
template <class T>
class TList {
	TNode<T> *pFirst, *pLast;	
	TNode<T>*pCurr, *pPrev;		//��������� �� �������/���������� ������� ������
	TNode<T> *pStop;			
	int len;					//�����
	int pos;					//� �������� � ������, �� ������� ��������� pCurr
public:
	TList();
	//TList(const *TList<T> &list);
	~TList();

	T GetCurrEl();				//������� �������� �������� ��������

	void InsFirst(const T &a);	//�������� ������� � ������
	void DelFirst();			//������� ��������� �������
	void InsLast(const T &a);	//�������� ������� � �����
	void InsCurr(const T &a);	//�������� ������� ����� pPrev � pCurr 
	void DelCurr();				//������� ������� ������� 

	void Reset();				//���������� ��������� �� ������
	void GoNext();				//����������� ��������� �� ���������
	bool IsEnd();				//�������� �� ���������

	void InsInOrder(const T &a);//�������� ������� �� �������
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
	if (pFirst == NULL) pLast = pFirst = tmp; //��������, ���� � ������ ���� �������
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