#ifndef INTERFACE_ERODED_HEIGHTMAP_PREVIEW_H
#define INTERFACE_ERODED_HEIGHTMAP_PREVIEW_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>


class eroded_heightmap_preview : public QWidget {

public:

    eroded_heightmap_preview(QWidget *parent);

    QLabel* label;
    QLabel* preview_label;
    QVBoxLayout* box;
    QPushButton* reload_button;

    void reload_heightmap();
    void refresh_heightmap();
    void display_loader();

};


#endif // INTERFACE_ERODED_HEIGHTMAP_PREVIEW_H
