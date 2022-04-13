#ifndef INTERFACE_HEIGHTMAP_PREVIEW_H
#define INTERFACE_HEIGHTMAP_PREVIEW_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>


class heightmap_preview : public QWidget {

    Q_OBJECT

public:

    heightmap_preview(QWidget *parent);

    QLabel* label;
    QLabel* preview_label;
    QVBoxLayout* box;
    QPushButton* reload_button;

    bool ready;

public slots:

    void reload_heightmap();

signals:

    void heightmap_valid_signal();

};

#endif // INTERFACE_HEIGHTMAP_PREVIEW_H
