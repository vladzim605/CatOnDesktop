#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QWindow>
#include <LayerShellQt/Shell>
#include <LayerShellQt/Window>

// Trieda = "návod", ako vyzerá a správa sa naša mačka
class Macka : public QWidget {
public:
    Macka() {
        setAttribute(Qt::WA_TranslucentBackground);  // priehľadné pozadie
        setWindowFlag(Qt::FramelessWindowHint);      // bez rámu
        resize(100, 80);
    }

    // Pripne okno na spodok obrazovky cez layer-shell
    void pripniNaSpodok() {
        winId();  // vynúti vytvorenie natívneho okna, aby sme mali windowHandle()
        m_okno = LayerShellQt::Window::get(windowHandle());
        m_okno->setLayer(LayerShellQt::Window::LayerTop);
        m_okno->setAnchors(LayerShellQt::Window::Anchors(
            LayerShellQt::Window::AnchorBottom | LayerShellQt::Window::AnchorLeft));
        m_okno->setKeyboardInteractivity(
            LayerShellQt::Window::KeyboardInteractivityNone);
        m_okno->setScope("macka");
    }

    // Posun mačky: margin zľava = x
    void posunNa(int x) {
        m_okno->setMargins(QMargins(x, 0, 0, 0));  // vľavo, hore, vpravo, dole
    }

protected:
    // Tu sa kreslí (zatiaľ len placka)
    void paintEvent(QPaintEvent *) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        p.setBrush(QColor(240, 150, 40));
        p.setPen(Qt::NoPen);
        p.drawEllipse(rect().adjusted(5, 15, -5, -2));   // telo
        p.drawEllipse(30, 0, 40, 40);                    // hlava
    }

private:
    LayerShellQt::Window *m_okno = nullptr;
};

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    Macka macka;
    macka.pripniNaSpodok();
    macka.show();

    // Každých ~16 ms posunieme mačku o 2 px, na kraji sa otočí
    int x = 0, smer = 2;
    QTimer casovac;
    QObject::connect(&casovac, &QTimer::timeout, [&]() {
        x += smer;
        if (x > 600 || x < 0) smer = -smer;
        macka.posunNa(x);
    });
    casovac.start(16);

    return app.exec();
}