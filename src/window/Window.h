#ifndef WINDOW_H
#define WINDOW_H

#include "../blocks/Board.h"

#include <string>
#include <vector>

#include <QMap>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QSharedPointer>
#include <QKeyEvent>

typedef QSharedPointer<QPushButton> QButtonPtr;

class Window: public QMainWindow
{
	Q_OBJECT

public:
	explicit Window(const std::string& title, QWidget* parent = 0, int width=640, int height=480);
	~Window();

	void open(void);
	bool isOpen(void) const;
	void setTitle(const std::string& title);
	void setSize(int height, int width, bool fixed=true);
	std::vector<std::string> getButtonInput(void);
	std::vector<int> getKeyboardInput(void);

	void render(void);

protected:
	// override to catch and handle Qt events
	void keyPressEvent(QKeyEvent* event) override;
	bool event(QEvent* event) override;
	bool confirmClose(void);

	// draw methods
	void paintEvent(QPaintEvent*) override;
	void _draw_board(QPainter& painter);

private:
	bool _open;
	int _width, _height;
	std::string _title;
	Sprite2D _card;

	// Keyboard input
	std::vector<int> _keyPressed;

	// GUI controls
	void _initializeButtons(void);
	void _positionButtons(void);
	void _onButtonPress(std::string command);
	QWidget _buttonPane;
	QMap<std::string, QButtonPtr> _btns;
	std::vector<std::string> _btnPressed;
};

#endif // WINDOW_H
