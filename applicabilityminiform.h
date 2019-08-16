#ifndef APPLICABILITYMINIFORM_H
#define APPLICABILITYMINIFORM_H

#include <QWidget>
#include <QKeyEvent>

#include "applicabilitycard.h"

namespace Ui {
class ApplicabilityMiniForm;
}

class ApplicabilityMiniForm : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicabilityMiniForm(QWidget *parent = nullptr);
    ~ApplicabilityMiniForm();

signals:
    void signalApplicabilityMiniFormClose();
    void signalApplicabilityMiniFormAdd(ApplicabilityCard &a);

private slots:
    void on_pushButtonBack_clicked();
    void on_pushButtonAdd_clicked();
    void keyPressEvent(QKeyEvent *);

private:
    Ui::ApplicabilityMiniForm *ui;
};

#endif // APPLICABILITYMINIFORM_H
