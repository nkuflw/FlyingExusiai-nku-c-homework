#include "menu.h"

Menu::Menu(bool isRunning,QWidget*parent):QDialog(parent),states(isRunning)
{
    setWindowFlags(Qt::FramelessWindowHint);
    initUI();
    setMinimumSize(150,300);
    setMaximumSize(150,300);
    move(parent->rect().center()-QPoint(150/2,300/2));
    connect(m_new, SIGNAL(clicked()), this, SLOT(slt_newGame()));
        connect(m_quit, SIGNAL(clicked()), this ,SLOT(slt_quit()));
        connect(m_back, SIGNAL(clicked()), this, SLOT(close()));

}

void Menu::slt_quit()
{
    emit sig_quit();
     close();

}

void Menu::slt_newGame()
{
    emit sig_newGame();
      close();

}

void Menu::initUI()
{
    m_new = new QPushButton("New Game");
        m_back = new QPushButton("Back");
        m_quit = new QPushButton("Quit");

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addStretch();
        mainLayout->addWidget(m_new);
        mainLayout->addWidget(m_back);
        mainLayout->addWidget(m_quit);
        mainLayout->addStretch();
        setLayout(mainLayout);

        if (states) {
            m_new->setDisabled(true);

        } else {
            m_back->setDisabled(true);
        }

}

