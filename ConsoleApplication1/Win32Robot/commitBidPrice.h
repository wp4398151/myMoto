#ifndef _COMMITBIDPRICE_H_ 
#define _COMMITBIDPRICE_H_

#define COMMITBIDPRICENAME "TImageForm"

class CommitBidPrice
{
public:
	CommitBidPrice(){ memcpy(m_WndName, COMMITBIDPRICENAME, sizeof(COMMITBIDPRICENAME)); }

	virtual void beforeFill(IRobot *pRobot);
	virtual BOOL dispachWnd(HWND hwnd, int childIdx, LPSTR buf, INT bufSize);	//�����ڳ���,����Ƿ���FALSE���ǲ���Ҫ��������
	virtual void afterFill(IRobot *pRobot);
	inline virtual const LPSTR GetWndName(){ return m_WndName; }
private:
	char m_WndName[WINDOWNAMEMAXNUM];
};
#endif //_COMMITBIDPRICE_H_