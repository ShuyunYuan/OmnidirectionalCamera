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
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
            tr("Image Files (*.bmp *.jpeg *.jpg *.png)"));
    undistort();
}

void Viewer::on_updateThresholdButton_clicked() {
    undistort();
}

void Viewer::on_saveButton_clicked() {
    if (outputPixmap.isNull()) {
        return;
    }
    QFileInfo fileInfo(fileName);
    QString saveFileName = QDir(fileInfo.path()).filePath("undistorted_" +
            fileInfo.fileName().remove(QRegExp("^test_")));
    saveFileName = QFileDialog::getSaveFileName(this, tr("Save File"), saveFileName,
            tr("Image Files (*.bmp *.jpeg *.jpg *.png)"));
    if (!saveFileName.isEmpty()) {
        outputPixmap.save(saveFileName);
    }
}

void Viewer::undistort() {
    if (fileName.isEmpty()) {
        return;
    }
    QPixmap inputPixmap;
    inputPixmap.load(fileName);
    ui->inputImage->setPixmap(inputPixmap.scaled(600, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    int threshold = ui->thresholdSpinBox->value();
    cv::Mat matrix = undistortPanorama(fileName.toLocal8Bit().constData(), threshold);
    cv::cvtColor(matrix, matrix, matrix.channels() == 1 ? cv::COLOR_GRAY2RGB : cv::COLOR_BGR2RGB);
    outputPixmap = QPixmap::fromImage(QImage(matrix.data, matrix.cols, matrix.rows, matrix.cols * 3,
                                             QImage::Format_RGB888));
    ui->outputImage->setPixmap(outputPixmap.scaled(600, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
