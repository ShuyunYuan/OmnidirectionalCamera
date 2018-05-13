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

    if (fileName.isEmpty()) {
        return;
    }
    QPixmap inputPixmap;
    inputPixmap.load(fileName);
    ui->inputImage->setPixmap(inputPixmap.scaled(600, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    cv::Mat matrix = getCenter(fileName.toLocal8Bit().constData());
    cv::cvtColor(matrix, matrix, matrix.type() == CV_8UC1 ? CV_GRAY2RGB : CV_BGR2RGB);
    outputPixmap = QPixmap::fromImage(QImage(matrix.data, matrix.cols, matrix.rows, matrix.cols * 3,
            QImage::Format_RGB888));
    ui->outputImage->setPixmap(outputPixmap.scaled(600, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Viewer::on_saveButton_clicked() {
    QFileInfo fileInfo(fileName);
    QString saveFileName = QDir(fileInfo.path()).filePath("undistorted_" +
            fileInfo.fileName().remove(QRegExp("^test_")));
    saveFileName = QFileDialog::getSaveFileName(this, tr("Save File"), saveFileName,
            tr("Image Files (*.bmp *.jpeg *.jpg *.png)"));
    if (!saveFileName.isEmpty()) {
        outputPixmap.save(saveFileName);
    }
}
