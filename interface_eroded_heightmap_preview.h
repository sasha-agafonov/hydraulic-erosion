#ifndef INTERFACE_ERODED_HEIGHTMAP_PREVIEW_H
#define INTERFACE_ERODED_HEIGHTMAP_PREVIEW_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>


class eroded_heightmap_preview : public QWidget {

    Q_OBJECT

public:

    eroded_heightmap_preview(QWidget *parent);

    QLabel* label;
    QLabel* preview_label;
    QVBoxLayout* box;
    QPushButton* reload_button;

    bool ready;

    void reload_heightmap();
    void refresh_heightmap();
    void display_loader();

signals:

    void eroded_heightmap_valid_signal();

};


#endif // INTERFACE_ERODED_HEIGHTMAP_PREVIEW_H
