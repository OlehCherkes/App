#include "pch.h"
#include "framework.h"
#include "AppDoc.h"
#include "AppView.h"
#include "Resource.h"
#include "resource.h"
#include <math.h>

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>


#include "ChooseSignalDialog.h"
using namespace std;

namespace little_endian_io
{
	template <typename Word>
	std::ostream& write_word(std::ostream& outs, Word value, unsigned size = sizeof(Word))
	{
		for (; size; --size, value >>= 8)
			outs.put(static_cast <char> (value & 0xFF));
		return outs;
	}
}
using namespace little_endian_io;




IMPLEMENT_DYNCREATE(CAppView, CView)

BEGIN_MESSAGE_MAP(CAppView, CView)
	ON_COMMAND(ID_CHOOSE_SIGNAL, &CAppView::OnChooseSignal)
	ON_COMMAND(ID_32773, &CAppView::OnOpenCSV)
	ON_COMMAND(ID_32774, &CAppView::OnSaveCSV)
	ON_COMMAND(ID_32775, &CAppView::OnOpenWAV)
	ON_COMMAND(ID_32776, &CAppView::OnSaveWAV)
END_MESSAGE_MAP()

CAppView::CAppView() noexcept{
	step_y	= 50;
	step_x	= 50;
	start_x = 100;
	sy		= 0;
	sx		= 0;//фазовый сдвиг
	freq = 2;
	is_triangle = false;
	is_sin = false;
}
CAppView::~CAppView(){}

void CAppView::OnOpenCSV() {

	// Чтение значений с файла csv
	ifstream icsv; //создаем объект класа ofstream
	icsv.open("My_csv.csv"); // открытие фала
	while (icsv.good()) {
		string line;
		getline(icsv, line, ',');
		cout << line << endl;
	}
	icsv.close(); //закрытие файла
	AfxMessageBox(L"OpenCSV");
	//CStatic str;
	//CFileDialog dia(TRUE);
	//dia.DoModal();
	//dia.GetPathName();
}
void CAppView::OnSaveCSV(){
	// Запись значений в файл csv
	
	ofstream ocsv; //создаем объект класа ofstream
	ocsv.open("My_csv.csv"); // открытие фала
	ocsv << "Значение" << ", "; //запись значений в файл csv
	ocsv.close(); //закрытие файла
	AfxMessageBox(L"SaveCSV");
}
void CAppView::OnOpenWAV() {
	AfxMessageBox(L"OpenWAV");
}
void CAppView::OnSaveWAV() {

	ofstream f("example.wav", ios::binary);

	// Write the file headers
	f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
	write_word(f, 16, 4);  // no extension data
	write_word(f, 1, 2);  // PCM - integer samples
	write_word(f, 2, 2);  // two channels (stereo file)
	write_word(f, 44100, 4);  // samples per second (Hz)
	write_word(f, 176400, 4);  // (Sample Rate * BitsPerSample * Channels) / 8
	write_word(f, 4, 2);  // data block size (size of two integer samples, one for each channel, in bytes)
	write_word(f, 16, 2);  // number of bits per sample (use a multiple of 8)

	// Write the data chunk header
	size_t data_chunk_pos = f.tellp();
	f << "data----";  // (chunk size to be filled in later)

	// Write the audio samples
	// (We'll generate a single C4 note with a sine wave, fading from left to right)
	constexpr double two_pi = 6.283185307179586476925286766559;
	constexpr double max_amplitude = 32760;  // "volume"

	double hz = 44100;    // samples per second
	double frequency = step_x;  // middle C
	double seconds = 10;      // time



	int N = hz * seconds;  // total number of samples
	for (int n = 0; n < N; n++)
	{
		double amplitude = (double)n / N * max_amplitude;
		double value = sin((two_pi * n * frequency) / hz);

		write_word(f, (int)(amplitude * value), 2);
		write_word(f, (int)((max_amplitude - amplitude) * value), 2);
	}


	// (We'll need the final file size to fix the chunk sizes above)
	size_t file_length = f.tellp();

	// Fix the data chunk header to contain the data size
	f.seekp(data_chunk_pos + 4);
	write_word(f, file_length - data_chunk_pos + 8);

	// Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
	f.seekp(0 + 4);
	write_word(f, file_length - 8, 4);

	AfxMessageBox(L"SaveWAV");
}

void CAppView::OnDrawGrid(CDC* pDC){
	CRect cr;			//получить размер клиентского окна
	GetClientRect(&cr);	//получить размер клиентского окна
	

	CPen pen, *old_pen;
	pen.CreatePen(PS_SOLID, 1, RGB(210, 210, 210));
	old_pen = pDC->SelectObject(&pen);


	//horizontal
	for (int i = sy; i > 0; i-=step_y){
		pDC->MoveTo(start_x, i);
		pDC->LineTo(cr.Width(), i);
	}

	//vertical
	for (int i = 0; i < cr.Width(); i += step_x) {
		pDC->MoveTo(start_x + i, 0);
		pDC->LineTo(start_x + i, sy);
	}



	pen.DeleteObject();
	pDC->SelectObject(old_pen);

}
void CAppView::OnDrawAxis(CDC * pDC){
	CRect cr;
	GetClientRect(&cr);

	CPen pen, *old_pen;

	//OY
	pen.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	old_pen = pDC->SelectObject(&pen);

	pDC->MoveTo(start_x, 0);
	pDC->LineTo(start_x, cr.Height());

	pen.DeleteObject();
	pDC->SelectObject(old_pen);


	//OX
	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	old_pen = pDC->SelectObject(&pen);

	pDC->MoveTo(0, sy);
	pDC->LineTo(cr.Width(), sy);

	pen.DeleteObject();
	pDC->SelectObject(old_pen);
}
void CAppView::OnDrawFunction(CDC* pDC) {

	CPen pen, *old_pen;
	pen.CreatePen(PS_SOLID, 1, RGB(101, 111, 255));
	old_pen = pDC->SelectObject(&pen);

	
	

	if (is_sin) {
		pDC->MoveTo(start_x, Sin(1 + sx) * step_y + sy);
		float fstep = 2. / freq;
		for (float x = 0; x < 50; x += fstep) {
			for (float j = x; j < x + 1; j += fstep / step_x) {
				pDC->LineTo((j + sx) * step_x - sx * step_x + start_x, Sin(j + sx) * step_y + sy);

			}
		}
	}

	if (is_triangle) {
		pDC->MoveTo(start_x, Triangle(1 + sx) * step_y + sy);
		for (int x = 0; x < 50; x++) {
			for (float j = x; j < x + 1; j += 0.02) {
				pDC->LineTo((j + sx) * step_x - sx * step_x + start_x, Triangle(j + sx) * step_y + sy);
				float f = j;
			}
		}
	}

	pen.DeleteObject();
	pDC->SelectObject(old_pen);
}


void CAppView::OnChooseSignal(){
	ChooseSignalDialog dia(is_triangle, is_sin, step_x, step_y, sx, freq);
	if (dia.DoModal() == 1) {
		is_sin		= dia.is_sin;
		is_triangle = dia.is_triangle;
		sx = _wtof(dia.fshifting);
		step_x = _wtof(dia.x_shifting);
		step_y = _wtof(dia.y_shifting);
		freq = _wtof(dia.sfreq);
		is_triangle = dia.is_triangle;
		is_sin = dia.is_sin;
		Invalidate();
	}
}

BOOL CAppView::PreCreateWindow(CREATESTRUCT& cs){
	return CView::PreCreateWindow(cs);
}

void CAppView::OnDraw(CDC* pDC){
	CAppDoc* pDoc = GetDocument();
	if (!pDoc)return;	

	CRect cr;			//получить размер клиентского окна
	GetClientRect(&cr);	//получить размер клиентского окна
	sy = cr.Height() / 2;

	OnDrawAxis(pDC);
	OnDrawGrid(pDC);
	OnDrawFunction(pDC);

	//pDC->SetBkMode(TRANSPARENT);			//вывод текста
	//pDC->TextOutW(700,300,L"22");			//вывод текста
}

float Sin(float t) {
	return sin(2 * 3.141592f * t);
}

float Triangle(float t){
	return (t - 2 * floor((t + 1) / 2)) * pow(-1, floor((t + 1) / 2));
}

