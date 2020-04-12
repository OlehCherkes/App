#pragma once


// Диалоговое окно ChooseSignalDialog

class ChooseSignalDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ChooseSignalDialog)

public:
	bool is_triangle;
	bool is_sin;
	CString fshifting;
	CString x_shifting;
	CString y_shifting;
	CString sfreq;
	CString e_step_x;
	CString e_step_y;
	CString e_sx;
	CString e_freq;

	void OnRadio1();
	void OnRadio2();

	int step_x, step_y, freq;
	float sx;

	BOOL OnInitDialog();
	ChooseSignalDialog(bool is_triangle, bool is_sin, int step_x,int step_y,
		float sx, int freq, CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~ChooseSignalDialog();
	void OnOK();
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit2();
};
