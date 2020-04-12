
// AppView.h: интерфейс класса CAppView
//

#pragma once


class CAppView : public CView
{
protected: // создать только из сериализации
	CAppView() noexcept;
	DECLARE_DYNCREATE(CAppView)
	DECLARE_MESSAGE_MAP()
public:
	bool is_triangle;
	bool is_sin;


	int step_y;
	int step_x;
	int sy;
	float sx;
	int start_x;
	int freq;

	void OnOpenCSV();
	void OnSaveCSV();
	void OnOpenWAV();
	void OnSaveWAV();

	void OnDrawGrid(CDC* pDC);
	void OnDrawAxis(CDC* pDC);
	void OnDrawFunction(CDC* pDC);

	CAppDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CAppView();
	void OnChooseSignal();
};



inline CAppDoc* CAppView::GetDocument() const
   { return reinterpret_cast<CAppDoc*>(m_pDocument); }


float Triangle(float x);
float Sin(float x);