#ifndef OC_VIEWER_H
#define OC_VIEWER_H

#include <QMainWindow>

namespace Ui {
    class Viewer;
}

class Viewer : public QMainWindow
{
Q_OBJECT

public:
    explicit Viewer(QWidget *parent = 0);
    ~Viewer();

private slots:
    void on_openButton_clicked();
    void on_saveButton_clicked();

private:
    Ui::Viewer *ui;
    QString fileName;
    QPixmap outputPixmap;
};

#endif //OC_VIEWER_H
