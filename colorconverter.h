#ifndef COLORCONVERTER_H
#define COLORCONVERTER_H

#include <QWidget>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

class ColorConverter : public QWidget {
    Q_OBJECT

public:
    ColorConverter(QWidget *parent = nullptr);

private slots:
    void updateFromRGB();
    void updateFromRGBSlider();
    void updateFromHSV();
    void updateFromHSVSlider();
    void updateFromLAB();
    void updateFromLABSlider();
    void openColorDialog();

private:
    QLineEdit *rEdit, *gEdit, *bEdit;
    QSlider *rSlider, *gSlider, *bSlider;
    QLineEdit *hEdit, *sEdit, *vEdit;
    QSlider *hSlider, *sSlider, *vSlider;
    QLineEdit *lEdit, *aEdit, *b2Edit;
    QSlider *lSlider, *aSlider, *b2Slider;
    QLabel *colorDisplay;
    QLabel *warningLabel;
    QPushButton *colorPickerButton;

    void updateColorDisplay(const QColor &color);
    void updateHSVFromRGB(int r, int g, int b);
    void updateLABFromRGB(int r, int g, int b);
    void updateRGBFromHSV(int h, int s, int v);
    void updateRGBFromLAB(int l, int a, int b);
    QColor labToRgb(int l, int a, int b);
    void rgbToLab(int r, int g, int b, int &l, int &a, int &b2);
};

#endif // COLORCONVERTER_H
