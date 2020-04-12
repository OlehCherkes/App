#include "pch.h"
#include "App.h"
#include "ChooseSignalDialog.h"
#include "afxdialogex.h"

#include "resource.h"
#include "Resource.h"

IMPLEMENT_DYNAMIC(ChooseSignalDialog, CDialogEx)

BEGIN_MESSAGE_MAP(ChooseSignalDialog, CDialogEx)
	ON_COMMAND(IDC_RADIO1, &ChooseSignalDialog::OnRadio1)
	ON_COMMAND(IDC_RADIO2, &ChooseSignalDialog::OnRadio2)
	ON_EN_CHANGE(IDC_EDIT2, &ChooseSignalDialog::OnEnChangeEdit2)
END_MESSAGE_MAP()

void ChooseSignalDialog::OnRadio1(){
	is_triangle = true;
	is_sin = false;
}
void ChooseSignalDialog::OnRadio2() {
	is_triangle = false;
	is_sin = true;
}

BOOL ChooseSignalDialog::OnInitDialog(){
	CDialogEx::OnInitDialog();
	CString str;
	e_sx.Format(L"%f", sx);
	e_step_x.Format(L"%d", step_x);
	e_step_y.Format(L"%d", step_y);
	e_freq.Format(L"%d", freq);
	UpdateData(FALSE);

	return 0;
}

ChooseSignalDialog::ChooseSignalDialog(bool is_triangle, bool is_sin, int step_x, int step_y,
	float sx, int freq, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent){

	this->is_sin		= is_sin;
	this->is_triangle	= is_triangle;
	this->step_x		= step_x;
	this->step_y		= step_y;
	this->sx			= sx;
	this->freq			= freq;
}

ChooseSignalDialog::~ChooseSignalDialog(){
}

void ChooseSignalDialog::OnOK(){
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(fshifting);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(x_shifting);
	GetDlgItem(IDC_EDIT3)->GetWindowTextW(y_shifting);
	GetDlgItem(IDC_FREQ)-> GetWindowTextW(sfreq);
	CDialogEx::OnOK();
}

void ChooseSignalDialog::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, e_sx);
	DDX_Text(pDX, IDC_EDIT2, e_step_x);
	DDX_Text(pDX, IDC_EDIT3, e_step_y);
	DDX_Text(pDX, IDC_FREQ, e_freq);
	((CButton*)(GetDlgItem(IDC_RADIO1)))->SetCheck(is_triangle);
	((CButton*)(GetDlgItem(IDC_RADIO2)))->SetCheck(is_sin);
}

void ChooseSignalDialog::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
