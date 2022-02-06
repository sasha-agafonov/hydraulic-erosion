#include "scene_menu.h"

#include <QLineEdit>
#include <QListView>

scene_menu :: scene_menu(QWidget *parent) : QWidget(parent) {

    grid = new QGridLayout(this);

    sensitivity_slider = new QSlider(Qt :: Horizontal);
    sensitivity_slider -> setMaximum(10);
    sensitivity_slider -> setMinimum(2);
    sensitivity_slider -> setStyleSheet("QSlider { max-height: 24px; min-height: 24px; }"
                                "QSlider::add-page:qlineargradient { background: rgba(110, 110, 135, 1); }"
                                "QSlider::groove:horizontal { background: rgba(190, 190, 222, 1); height: 2px; }"
                                "QSlider::handle:horizontal { background: rgba(190, 190, 222, 1); border: 2px solid rgba(1, 1, 1, 0); height: 10px; width: 10px; margin: -6 -1px; border-radius: 7px; }");

    sensitivity_label = new QLabel(this);
    sensitivity_label  -> setText("Sensitivity");
    sensitivity_label  -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); margin-right: 6px; }");

    fov_slider = new QSlider(Qt :: Horizontal);
    fov_slider -> setMaximum(10);
    fov_slider -> setMinimum(2);
    fov_slider -> setStyleSheet("QSlider { max-height: 24px; min-height: 24px; }"
                                "QSlider::add-page:qlineargradient { background: rgba(110, 110, 135, 1); }"
                                "QSlider::groove:horizontal { background: rgba(190, 190, 222, 1); height: 2px; }"
                                "QSlider::handle:horizontal { background: rgba(190, 190, 222, 1); border: 2px solid rgba(1, 1, 1, 0); height: 10px; width: 10px; margin: -6 -1px; border-radius: 7px; }");

    fov_label = new QLabel(this);
    fov_label  -> setText("FOV");
    fov_label  -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); margin-right: 6px; }");

    antialiasing_combo = new QComboBox(this);
    antialiasing_combo -> addItems({ "Off", "2x MSAA", "4x MSAA"});
    antialiasing_combo -> setEditable(true);
    antialiasing_combo -> lineEdit() -> setReadOnly(true);
    antialiasing_combo -> lineEdit() -> setAlignment(Qt::AlignCenter);
    antialiasing_combo -> setView(new QListView());
    antialiasing_combo -> setStyleSheet("QComboBox { border-radius: 0; min-height: 2em; border-width: 0px; background: rgba(190, 190, 222, 1); font-size: 11px; color: rgba(40, 44, 52, 1);}"
                                     "QComboBox:editable { background: rgba(190, 190, 222, 1); }"
                                     "QComboBox QAbstractItemView { background: rgba(40, 44, 52, 1); selection-color: black; color: rgba(190, 190, 222, 1); selection-background-color: rgba(110, 110, 135, 1); }"
                                     "QComboBox QAbstractItemView::item {min-height: 20px; font-size: 10px; }");

    antialiasing_label = new QLabel(this);
    antialiasing_label  -> setText("Anti-Aliasing");
    antialiasing_label  -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); margin-right: 6px; }");

    fps_lock_combo = new QComboBox(this);
    fps_lock_combo -> addItems({ "Off", "30", "60", "120", "144"});
    fps_lock_combo -> setEditable(true);
    fps_lock_combo -> lineEdit() -> setReadOnly(true);
    fps_lock_combo -> lineEdit() -> setAlignment(Qt::AlignCenter);
    fps_lock_combo -> setView(new QListView());
    fps_lock_combo -> setStyleSheet("QComboBox { border-radius: 0; min-height: 2em; border-width: 0px; background: rgba(190, 190, 222, 1); font-size: 11px; color: rgba(40, 44, 52, 1);}"
                                     "QComboBox:editable { background: rgba(190, 190, 222, 1); }"
                                     "QComboBox QAbstractItemView { background: rgba(40, 44, 52, 1); selection-color: black; color: rgba(190, 190, 222, 1); selection-background-color: rgba(110, 110, 135, 1); }"
                                     "QComboBox QAbstractItemView::item {min-height: 20px; font-size: 10px; }");

    fps_lock_label = new QLabel(this);
    fps_lock_label  -> setText("FPS Lock");
    fps_lock_label  -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); margin-right: 6px; }");



    fps_toggle_checkbox = new QCheckBox(this);
    fps_toggle_checkbox -> setStyleSheet("QCheckBox::indicator { height: 10px; width: 10px; }"
                                   "QCheckBox::indicator:unchecked { border: 1px solid rgba(190, 190, 222, 1); background: transparent; border-radius: 5px;}"
                                   "QCheckBox::indicator:unchecked:hover { background: rgba(110, 110, 135, 1);  }"
                                   "QCheckBox::indicator:checked { border: 1px solid rgba(190, 190, 222, 1);  background: rgba(190, 190, 222, 1); border-radius: 5px; }"
                                   "QCheckBox::indicator:checked:hover { background: rgba(110, 110, 135, 1); border-color: rgba(110, 110, 135, 1); } ");

    fps_toggle_label = new QLabel(this);
    fps_toggle_label  -> setText("Toggle FPS Count");
    fps_toggle_label  -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); margin-right: 6px; }");

    flat_shading_checkbox = new QCheckBox(this);
    flat_shading_checkbox -> setStyleSheet("QCheckBox::indicator { height: 10px; width: 10px; }"
                                   "QCheckBox::indicator:unchecked { border: 1px solid rgba(190, 190, 222, 1); background: transparent; border-radius: 5px;}"
                                   "QCheckBox::indicator:unchecked:hover { background: rgba(110, 110, 135, 1);  }"
                                   "QCheckBox::indicator:checked { border: 1px solid rgba(190, 190, 222, 1);  background: rgba(190, 190, 222, 1); border-radius: 5px; }"
                                   "QCheckBox::indicator:checked:hover { background: rgba(110, 110, 135, 1); border-color: rgba(110, 110, 135, 1); } ");

    flat_shading_label = new QLabel(this);
    flat_shading_label  -> setText("Enable Flat Shading");
    flat_shading_label  -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); margin-right: 6px; }");

    save_button = new QPushButton("Apply Settings", this);
    save_button -> setStyleSheet("QPushButton { height: 16px; min-height: 2em; background: rgba(190, 190, 222, 1); border: 0; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    exit_button = new QPushButton("Return To Main Menu", this);
    exit_button -> setStyleSheet("QPushButton { height: 16px; min-height: 2em; background: rgba(190, 190, 222, 1); border: 0; font-size: 11px; color: rgba(40, 44, 52, 1); } "
                                "QPushButton:pressed { background: rgba(110, 110, 135, 1); } ");

    connect(save_button, SIGNAL(clicked()), parent, SLOT(reload_scene()));
    connect(exit_button, SIGNAL(clicked()), parent, SLOT(exit_scene()));

    grid -> addWidget(sensitivity_label, 1, 0, 1, 1);
    grid -> addWidget(sensitivity_slider, 1, 1, 1, 1);

    grid -> addWidget(fov_label, 2, 0, 1, 1);
    grid -> addWidget(fov_slider, 2, 1, 1, 1);

    grid -> addWidget(antialiasing_label, 3, 0, 1, 1);
    grid -> addWidget(antialiasing_combo, 3, 1, 1, 1);

    grid -> addWidget(fps_lock_label, 4, 0, 1, 1);
    grid -> addWidget(fps_lock_combo, 4, 1, 1, 1);

    grid -> addWidget(fps_toggle_label, 5, 0, 1, 1);
    grid -> addWidget(fps_toggle_checkbox, 5, 1, 1, 1);

    grid -> addWidget(flat_shading_label, 6, 0, 1, 1);
    grid -> addWidget(flat_shading_checkbox, 6, 1, 1, 1);

    grid -> addWidget(save_button, 7, 0, 1, 1);
    grid -> addWidget(exit_button, 7, 1, 1, 1);

}
