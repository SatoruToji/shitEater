#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <Windows.h>
#include <iostream>
#include <thread>
#include <tesseract/baseapi.h>
#include <tchar.h>
using namespace std;
using namespace cv;
using namespace tesseract;

HHOOK XD;
void huy();
bool pizda = false;


LRESULT CALLBACK keyLogger(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* huy = (KBDLLHOOKSTRUCT*)lParam;
        if (huy->vkCode == 0x46) {
            pizda = true;
            //keybd_event('f', 0, 0, 0);
            //keybd_event('f', 0, KEYEVENTF_KEYUP, 0);
        }
        else if (huy->vkCode == 0x54) {
            pizda = false;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void brainFck(Mat& src) {
    Mat img_hsv, orMask, whMask;
    //vector<vector<Point>> contours;
    //vector<Vec4i> hierarchy;
    TessBaseAPI t1, t2;
    string in;

    t1.Init(NULL, "eng");
    t2.Init(NULL, "eng");

    GaussianBlur(src, src, Size(3, 3), 9, 9);

    //////////////////////////orange//////////////////////////////////////
    cvtColor(src, img_hsv, COLOR_BGR2HSV);
    inRange(img_hsv, Scalar(10, 200, 200), Scalar(255, 255, 255), orMask);

    t1.SetImage((uchar*)orMask.data, orMask.cols, orMask.rows, 3, orMask.step);
    string orange = t1.GetUTF8Text();

    ///////////////////////////white//////////////////////////////////////
    cv::cvtColor(src, img_hsv, cv::COLOR_BGR2GRAY);
    cv::threshold(img_hsv, whMask, 200, 255, cv::THRESH_BINARY);

    t2.SetImage((uchar*)whMask.data, whMask.cols, whMask.rows, 3, whMask.step);
    string white = t2.GetUTF8Text();

    while (orange != in && white != in) {
        huy();
        orange = white = "";
    }
    t1.End();
    t2.End();
    //delete[] out;

    //findContours(img_threshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    //for (size_t i = 0; i < contours.size(); i++) {
    //    drawContours(src, contours, static_cast<int>(i), Scalar(0, 255, 0), 2);
    //huy();
    //}
}

void huy() {
    if (pizda) {
        Sleep(7);
        //cout << "huy" << endl;
        SetCursorPos(1100, 700);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(7);
        SetCursorPos(1100, 690);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(7);
        SetCursorPos(1100, 680);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(7);
        SetCursorPos(1100, 670);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(7);
        SetCursorPos(1100, 660);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(7);
        SetCursorPos(1100, 650);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(7);
        SetCursorPos(1100, 640);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(7);
        SetCursorPos(1100, 630);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(7);
        SetCursorPos(1100, 620);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(7);
        SetCursorPos(1100, 610);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(7);
        SetCursorPos(1100, 600);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        SetCursorPos(1100, 590);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        SetCursorPos(1100, 580);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        SetCursorPos(1100, 570);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        SetCursorPos(1100, 560);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        SetCursorPos(1100, 550);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        //pizda = false;
    }
}

Mat stream(HWND hwnd, const Rect& rect) {
    HDC hwindowDC, hwindowCompatibleDC;
    int height, width, srcheight, srcwidth;
    HBITMAP hbwindow;
    Mat src;
    BITMAPINFOHEADER bi;

    hwindowDC = GetDC(hwnd);
    hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

    srcheight = rect.height;
    srcwidth = rect.width;
    height = rect.height / 1;  // Используем только часть высоты и ширины 
    width = rect.width / 1;

    src.create(height, width, CV_8UC4);

    hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    SelectObject(hwindowCompatibleDC, hbwindow);
    StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, rect.x, rect.y, rect.width, rect.height, SRCCOPY);
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    brainFck(src);

    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);

    return src;
}

void streamchick() {
    HWND hwndDesktop = GetDesktopWindow();

    namedWindow("huy", cv::WINDOW_NORMAL);
    Rect captureRect(800, 800, 336, 225);

    for (;;) {
        Mat src = stream(hwndDesktop, captureRect);
        imshow("huy", src);
        waitKey(33);
    }
}

void pidr() {
    XD = SetWindowsHookEx(WH_KEYBOARD_LL, keyLogger, NULL, 0);
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg) | DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(XD);
}

int main(int argc, char** argv) {
    thread t1(streamchick);
    thread t2(pidr);

    t1.join();
    t2.join();
    return 0;
}