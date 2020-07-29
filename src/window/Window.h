#ifndef WINDOW_H
#define WINDOW_H

#include "../blocks/Board.h"

#include <memory>
#include <string>
#include <unordered_map>

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QMap>
#include <QSharedPointer>

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
	void setSize(int height, int width);

	void render(void);

protected:
	// override to catch and handle Qt events
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
	Board _board;

	// GUI controls
	void _initializeButtons(void);
	QWidget _buttonPane;
	QMap<std::string, QButtonPtr> _buttons;
};

#endif // WINDOW_H
