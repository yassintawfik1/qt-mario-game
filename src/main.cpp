#include <QApplication>
#include <QGraphicsView>
#include "Level.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    
    Level* level = new Level();
    QGraphicsView view(level);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setFixedSize(800, 600);

    view.show();
    return app.exec();
}
