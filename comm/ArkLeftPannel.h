#ifndef ARKLEFTPANNEL_H
#define ARKLEFTPANNEL_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>

class ArkLeftPannel : public QWidget
{
    Q_OBJECT
public:
    explicit ArkLeftPannel(QWidget* parent = 0);
    virtual ~ArkLeftPannel();
};

#endif // ARKLEFTPANNEL_H
