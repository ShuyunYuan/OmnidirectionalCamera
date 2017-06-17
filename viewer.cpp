#include "viewer.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include "processor.h"
#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent) : QMainWindow(parent), ui(new Ui::Viewer) {
    ui->setupUi(this);
}

Viewer::~Viewer() {
    delete ui;
}

void Viewer::on_openButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
            tr("Image Files (*.bmp *.jpeg *.jpg *.png)"));

    if (fileName.isEmpty()) {
        return;
    }
    QPixmap input;
    input.load(fileName);
    ui->inputImage->setPixmap(input);
    IplImage *iplImage = processFile(fileName.toLocal8Bit().constData());
    cv::Mat matrix = cv::cvarrToMat(iplImage);
    cvReleaseImage(&iplImage);
    cv::cvtColor(matrix, matrix, matrix.type() == CV_8UC1 ? CV_GRAY2RGB : CV_BGR2RGB);
    QPixmap output = QPixmap::fromImage(QImage(matrix.data, matrix.cols, matrix.rows, matrix.cols * 3,
            QImage::Format_RGB888));
    ui->outputImage->setPixmap(output);
}

void Viewer::on_saveButton_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
            tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            //stream << ui->textEdit->toPlainText();
            stream.flush();
            file.close();
        }
    }
}
