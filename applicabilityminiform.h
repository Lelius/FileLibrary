#ifndef APPLICABILITYMINIFORM_H
#define APPLICABILITYMINIFORM_H

#include <QWidget>

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
    void ApplicabilityMiniFormClose();
    void ApplicabilityMiniFormAdd(ApplicabilityCard &a);

private slots:
    void on_pushButtonBack_clicked();

    void on_pushButtonAdd_clicked();

private:
    Ui::ApplicabilityMiniForm *ui;
};

#endif // APPLICABILITYMINIFORM_H
