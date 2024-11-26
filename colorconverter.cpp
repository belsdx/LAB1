#include "colorconverter.h"
#include <QColorDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QColor>

ColorConverter::ColorConverter(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *rgbLayout = new QHBoxLayout();
    rEdit = new QLineEdit(this);
    gEdit = new QLineEdit(this);
    bEdit = new QLineEdit(this);
    rEdit->setValidator(new QIntValidator(0, 255, this));
    gEdit->setValidator(new QIntValidator(0, 255, this));
    bEdit->setValidator(new QIntValidator(0, 255, this));
    rSlider = new QSlider(Qt::Horizontal, this);
    gSlider = new QSlider(Qt::Horizontal, this);
    bSlider = new QSlider(Qt::Horizontal, this);
    rSlider->setRange(0, 255);
    gSlider->setRange(0, 255);
    bSlider->setRange(0, 255);
    rgbLayout->addWidget(new QLabel("R:", this));
    rgbLayout->addWidget(rEdit);
    rgbLayout->addWidget(rSlider);
    rgbLayout->addWidget(new QLabel("G:", this));
    rgbLayout->addWidget(gEdit);
    rgbLayout->addWidget(gSlider);
    rgbLayout->addWidget(new QLabel("B:", this));
    rgbLayout->addWidget(bEdit);
    rgbLayout->addWidget(bSlider);
    mainLayout->addLayout(rgbLayout);


    QHBoxLayout *hsvLayout = new QHBoxLayout();
    hEdit = new QLineEdit(this);
    sEdit = new QLineEdit(this);
    vEdit = new QLineEdit(this);
    hEdit->setValidator(new QIntValidator(0, 360, this));
    sEdit->setValidator(new QIntValidator(0, 100, this));
    vEdit->setValidator(new QIntValidator(0, 100, this));
    hSlider = new QSlider(Qt::Horizontal, this);
    sSlider = new QSlider(Qt::Horizontal, this);
    vSlider = new QSlider(Qt::Horizontal, this);
    hSlider->setRange(0, 360);
    sSlider->setRange(0, 100);
    vSlider->setRange(0, 100);
    hsvLayout->addWidget(new QLabel("H:", this));
    hsvLayout->addWidget(hEdit);
    hsvLayout->addWidget(hSlider);
    hsvLayout->addWidget(new QLabel("S:", this));
    hsvLayout->addWidget(sEdit);
    hsvLayout->addWidget(sSlider);
    hsvLayout->addWidget(new QLabel("V:", this));
    hsvLayout->addWidget(vEdit);
    hsvLayout->addWidget(vSlider);
    mainLayout->addLayout(hsvLayout);


    QHBoxLayout *labLayout = new QHBoxLayout();
    lEdit = new QLineEdit(this);
    aEdit = new QLineEdit(this);
    b2Edit = new QLineEdit(this);
    lEdit->setValidator(new QIntValidator(0, 100, this));
    aEdit->setValidator(new QIntValidator(-128, 127, this));
    b2Edit->setValidator(new QIntValidator(-128, 127, this));
    lSlider = new QSlider(Qt::Horizontal, this);
    aSlider = new QSlider(Qt::Horizontal, this);
    b2Slider = new QSlider(Qt::Horizontal, this);
    lSlider->setRange(0, 100);
    aSlider->setRange(-128, 127);
    b2Slider->setRange(-128, 127);
    labLayout->addWidget(new QLabel("L:", this));
    labLayout->addWidget(lEdit);
    labLayout->addWidget(lSlider);
    labLayout->addWidget(new QLabel("A:", this));
    labLayout->addWidget(aEdit);
    labLayout->addWidget(aSlider);
    labLayout->addWidget(new QLabel("B:", this));
    labLayout->addWidget(b2Edit);
    labLayout->addWidget(b2Slider);
    mainLayout->addLayout(labLayout);


    colorDisplay = new QLabel(this);
    colorDisplay->setFixedSize(100, 100);
    colorDisplay->setStyleSheet("background-color: black;");
    mainLayout->addWidget(colorDisplay, 0, Qt::AlignCenter);


    warningLabel = new QLabel(this);
    warningLabel->setStyleSheet("QLabel { color : red; }");
    mainLayout->addWidget(warningLabel);


    colorPickerButton = new QPushButton("选择颜色", this);
    connect(colorPickerButton, &QPushButton::clicked, this, &ColorConverter::openColorDialog);
    mainLayout->addWidget(colorPickerButton);


    connect(rEdit, &QLineEdit::editingFinished, this, &ColorConverter::updateFromRGB);
    connect(gEdit, &QLineEdit::editingFinished, this, &ColorConverter::updateFromRGB);
    connect(bEdit, &QLineEdit::editingFinished, this, &ColorConverter::updateFromRGB);
    connect(rSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromRGBSlider);
    connect(gSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromRGBSlider);
    connect(bSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromRGBSlider);
    connect(hEdit, &QLineEdit::editingFinished, this, &ColorConverter::updateFromHSV);
    connect(sEdit, &QLineEdit::editingFinished, this, &ColorConverter::updateFromHSV);
    connect(vEdit, &QLineEdit::editingFinished, this, &ColorConverter::updateFromHSV);
    connect(hSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromHSVSlider);
    connect(sSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromHSVSlider);
    connect(vSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromHSVSlider);
    connect(lEdit, &QLineEdit::editingFinished, this, &ColorConverter::updateFromLAB);
    connect(aEdit, &QLineEdit::editingFinished, this, &ColorConverter::updateFromLAB);
    connect(b2Edit, &QLineEdit::editingFinished, this, &ColorConverter::updateFromLAB);
    connect(lSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromLABSlider);
    connect(aSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromLABSlider);
    connect(b2Slider, &QSlider::valueChanged, this, &ColorConverter::updateFromLABSlider);
}

void ColorConverter::updateFromRGB() {
    bool rOk, gOk, bOk;
    int r = rEdit->text().toInt(&rOk);
    int g = gEdit->text().toInt(&gOk);
    int b = bEdit->text().toInt(&bOk);

    if (rOk && gOk && bOk) {
        QColor color(r, g, b);
        updateColorDisplay(color);
        updateHSVFromRGB(r, g, b);
        updateLABFromRGB(r, g, b);
    } else {
        warningLabel->setText("RGB 值无效！");
    }
}

void ColorConverter::updateFromRGBSlider() {
    int r = rSlider->value();
    int g = gSlider->value();
    int b = bSlider->value();


    disconnect(rSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromRGBSlider);
    disconnect(gSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromRGBSlider);
    disconnect(bSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromRGBSlider);

    rEdit->setText(QString::number(r));
    gEdit->setText(QString::number(g));
    bEdit->setText(QString::number(b));
    updateFromRGB();


    connect(rSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromRGBSlider);
    connect(gSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromRGBSlider);
    connect(bSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromRGBSlider);
}

void ColorConverter::updateFromHSV() {
    bool hOk, sOk, vOk;
    int h = hEdit->text().toInt(&hOk);
    int s = sEdit->text().toInt(&sOk);
    int v = vEdit->text().toInt(&vOk);

    if (hOk && sOk && vOk) {
        QColor color = QColor::fromHsv(h, s * 2.55, v * 2.55);
        updateColorDisplay(color);
        updateRGBFromHSV(h, s, v);
        updateLABFromRGB(color.red(), color.green(), color.blue());
    } else {
        warningLabel->setText("HSV 值无效！");
    }
}

void ColorConverter::updateFromHSVSlider() {
    int h = hSlider->value();
    int s = sSlider->value();
    int v = vSlider->value();


    disconnect(hSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromHSVSlider);
    disconnect(sSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromHSVSlider);
    disconnect(vSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromHSVSlider);

    hEdit->setText(QString::number(h));
    sEdit->setText(QString::number(s));
    vEdit->setText(QString::number(v));
    updateFromHSV();


    connect(hSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromHSVSlider);
    connect(sSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromHSVSlider);
    connect(vSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromHSVSlider);
}

void ColorConverter::updateFromLAB() {
    bool lOk, aOk, bOk;
    int l = lEdit->text().toInt(&lOk);
    int a = aEdit->text().toInt(&aOk);
    int b = b2Edit->text().toInt(&bOk);

    if (lOk && aOk && bOk) {
        QColor color = labToRgb(l, a, b);
        updateColorDisplay(color);
        updateRGBFromLAB(l, a, b);
        updateHSVFromRGB(color.red(), color.green(), color.blue());
    } else {
        warningLabel->setText("LAB 值无效！");
    }
}

void ColorConverter::updateFromLABSlider() {
    int l = lSlider->value();
    int a = aSlider->value();
    int b = b2Slider->value();


    disconnect(lSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromLABSlider);
    disconnect(aSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromLABSlider);
    disconnect(b2Slider, &QSlider::valueChanged, this, &ColorConverter::updateFromLABSlider);

    lEdit->setText(QString::number(l));
    aEdit->setText(QString::number(a));
    b2Edit->setText(QString::number(b));
    updateFromLAB();


    connect(lSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromLABSlider);
    connect(aSlider, &QSlider::valueChanged, this, &ColorConverter::updateFromLABSlider);
    connect(b2Slider, &QSlider::valueChanged, this, &ColorConverter::updateFromLABSlider);
}

void ColorConverter::openColorDialog() {
    QColor color = QColorDialog::getColor(Qt::white, this, "选择颜色");
    if (color.isValid()) {
        rEdit->setText(QString::number(color.red()));
        gEdit->setText(QString::number(color.green()));
        bEdit->setText(QString::number(color.blue()));
        updateFromRGB();
    }
}

void ColorConverter::updateColorDisplay(const QColor &color) {
    colorDisplay->setStyleSheet(QString("background-color: %1;").arg(color.name()));
}

void ColorConverter::updateHSVFromRGB(int r, int g, int b) {
    QColor color(r, g, b);
    int h, s, v;
    color.getHsv(&h, &s, &v);
    hEdit->setText(QString::number(h));
    sEdit->setText(QString::number(static_cast<int>(s / 2.55)));
    vEdit->setText(QString::number(static_cast<int>(v / 2.55)));
    hSlider->setValue(h);
    sSlider->setValue(static_cast<int>(s / 2.55));
    vSlider->setValue(static_cast<int>(v / 2.55));
}

void ColorConverter::updateLABFromRGB(int r, int g, int b) {

    double rNorm = r / 255.0;
    double gNorm = g / 255.0;
    double bNorm = b / 255.0;

    double x = rNorm * 0.4124 + gNorm * 0.3576 + bNorm * 0.1805;
    double y = rNorm * 0.2126 + gNorm * 0.7152 + bNorm * 0.0722;
    double z = rNorm * 0.0193 + gNorm * 0.1192 + bNorm * 0.9505;


    x = x / 0.95047;
    y = y / 1.00000;
    z = z / 1.08883;

    x = (x > 0.008856) ? pow(x, 1.0/3.0) : (7.787 * x) + (16.0 / 116.0);
    y = (y > 0.008856) ? pow(y, 1.0/3.0) : (7.787 * y) + (16.0 / 116.0);
    z = (z > 0.008856) ? pow(z, 1.0/3.0) : (7.787 * z) + (16.0 / 116.0);

    int l = static_cast<int>((116.0 * y) - 16);
    int a = static_cast<int>(500.0 * (x - y));
    int b2 = static_cast<int>(200.0 * (y - z));

    lEdit->setText(QString::number(l));
    aEdit->setText(QString::number(a));
    b2Edit->setText(QString::number(b2));
    lSlider->setValue(l);
    aSlider->setValue(a);
    b2Slider->setValue(b2);
}

void ColorConverter::updateRGBFromHSV(int h, int s, int v) {
    QColor color = QColor::fromHsv(h, s * 2.55, v * 2.55);
    rEdit->setText(QString::number(color.red()));
    gEdit->setText(QString::number(color.green()));
    bEdit->setText(QString::number(color.blue()));
    rSlider->setValue(color.red());
    gSlider->setValue(color.green());
    bSlider->setValue(color.blue());
}

void ColorConverter::updateRGBFromLAB(int l, int a, int b) {
    QColor color = labToRgb(l, a, b);
    rEdit->setText(QString::number(color.red()));
    gEdit->setText(QString::number(color.green()));
    bEdit->setText(QString::number(color.blue()));
    rSlider->setValue(color.red());
    gSlider->setValue(color.green());
    bSlider->setValue(color.blue());
}

QColor ColorConverter::labToRgb(int l, int a, int b) {

    double y = (l + 16.0) / 116.0;
    double x = a / 500.0 + y;
    double z = y - b / 200.0;

    x = (x > 0.206893) ? pow(x, 3) : (x - 16.0 / 116.0) / 7.787;
    y = (y > 0.206893) ? pow(y, 3) : (y - 16.0 / 116.0) / 7.787;
    z = (z > 0.206893) ? pow(z, 3) : (z - 16.0 / 116.0) / 7.787;

    x = x * 0.95047;
    y = y * 1.00000;
    z = z * 1.08883;

    double r = x * 3.2406 + y * -1.5372 + z * -0.4986;
    double g = x * -0.9689 + y * 1.8758 + z * 0.0415;
    double b2 = x * 0.0557 + y * -0.2040 + z * 1.0570;

    r = (r > 0.0031308) ? (1.055 * pow(r, 1.0 / 2.4) - 0.055) : 12.92 * r;
    g = (g > 0.0031308) ? (1.055 * pow(g, 1.0 / 2.4) - 0.055) : 12.92 * g;
    b2 = (b2 > 0.0031308) ? (1.055 * pow(b2, 1.0 / 2.4) - 0.055) : 12.92 * b2;

    return QColor(qBound(0, int(r * 255), 255), qBound(0, int(g * 255), 255), qBound(0, int(b2 * 255), 255));
}

void ColorConverter::rgbToLab(int r, int g, int b, int &l, int &a, int &b2) {

    double rNorm = r / 255.0;
    double gNorm = g / 255.0;
    double bNorm = b / 255.0;


    double x = rNorm * 0.4124 + gNorm * 0.3576 + bNorm * 0.1805;
    double y = rNorm * 0.2126 + gNorm * 0.7152 + bNorm * 0.0722;
    double z = rNorm * 0.0193 + gNorm * 0.1192 + bNorm * 0.9505;


    x = x / 0.95047;
    y = y / 1.00000;
    z = z / 1.08883;

    x = (x > 0.008856) ? pow(x, 1.0/3.0) : (7.787 * x) + (16.0 / 116.0);
    y = (y > 0.008856) ? pow(y, 1.0/3.0) : (7.787 * y) + (16.0 / 116.0);
    z = (z > 0.008856) ? pow(z, 1.0/3.0) : (7.787 * z) + (16.0 / 116.0);

    l = static_cast<int>((116.0 * y) - 16);
    a = static_cast<int>(500.0 * (x - y));
    b2 = static_cast<int>(200.0 * (y - z));
}
