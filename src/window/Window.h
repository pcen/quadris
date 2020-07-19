#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <string>

#include <QMainWindow>
#include <QLabel>
#include <QWidget>
#include <QCloseEvent>

class Window: public QMainWindow
{
	Q_OBJECT

public:
	explicit Window(QWidget* parent = 0);
	virtual ~Window() override {}

	void close(void);

	void poll_input(void);
	void set_size(int width, int height);
	void set_title(const std::string& title);
	void set_background(unsigned long colour);

	bool is_open(void) const;

protected:
	void closeEvent(QCloseEvent *event);
	// void contextMenuEvent(QContextMenuEvent* event);

	bool confirmClose(void);

};

#endif // WINDOW_H
